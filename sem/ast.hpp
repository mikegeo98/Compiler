#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "parser.hpp"
#include "lexer.hpp"

void yyerror(const char *msg,...);

class AST {
public:
  virtual ~AST() {}
  virtual void printOn(std::ostream &out) const = 0;
  virtual void sem() {}
};

inline std::ostream& operator<< (std::ostream &out, const AST &t) {
  t.printOn(out);
  return out;
}



class Expr: public AST { //DES PARAKATW SXOLIO THELEI KONSTRAKTOR
public:
  Expr() {}
  ~Expr(){}
  void type_check(Type t) {
    sem();
    if (type != t) yyerror("Type mismatch");
  }
  Type get_type()
  {
    return type;
  }
  virtual void sem() {}
protected:
  Type type;
};

class Expls: public Expr { //MALLON LEEIPEI H SEM STA EXPRESSIONS
public:
  Expls(): expls(),size(0) {}
  ~Expls(){
      for(auto i: expls){
          delete i;
      }
  }
  void append_exprls(Expr *expr) { 
      expls.push_back(expr);
      size++;
  }
  Type get_type(int i)
  {
    return expls[i]->get_type();
  }
  int get_size()
  {
    return size;
  }
  virtual void printOn(std::ostream &out) const override {
      out << "Expression List(" ;
      for (auto i: expls){
          i->printOn(out);
      }
      out << ")";
  }
  virtual void sem() override {
      for (auto i: expls){
          i->sem();
      }
  }
  int get_size(){
      return size;
  }


private:
    std::vector<Expr *> expls;
    int size;
};

class Type {
  public:
    Type(bool iv, std::string ty, Expls *pa=nullptr): isvar(iv), type(ty), params(pa) {}
    ~Type() { delete params; }

    bool operator != (Type t)
    {
      if(isvar ^ t.isvar) return false;
      if(type!=t.type) return false;
      if(!isvar)
      {
        if (params->get_size() != (t.params)->get_size()) return false;
        for ( int i=0;i<params->get_size();i++ )
        {
          if( params->get_type(i)!=(t.params)->get_type(i)) return false;
        }
      }
    }

    int get_param_cnt()
    {
      return params->get_size();
    }

    bool has_params()
    {
      return !isvar;
    }

    Type get_param_type(int i)
    {
      return params->get_type(i);
    }
  private:
    bool isvar;
    std::string type;
    Expls *params;
};

class Stmt: public AST {
public:
  ~Stmt(){}
  virtual void printOn(std::ostream &out) const override
  {
      out<<"skip";
  }
  virtual void run() const = 0;
  virtual void sem() override {}
};

extern std::vector<int> rt_stack;
extern int lncnt;

class Id: public Expr {
public:
  Id(char *v): var(v), offset(-1) {}
  virtual void printOn(std::ostream &out) const override {
    out << "Id(" << var << "@" << offset << ")";
  }

  char *getName(){
    return var;
  }


  std::string get_kind()
  {
    return "Id";
  }

  virtual void sem() override {
    SymbolEntry *e = st.lookup(var);
    type = e->type;
    offset = e->offset;
  }
protected:
  char *var;
  int offset;
};

class Const: public Expr {
public:
  Const(union u *numb): num(numb) {}
  virtual void printOn(std::ostream &out) const override {
    out << "Const(" << num << ")";
  }

  virtual void sem() override {
    type = TYPE_int;//NEEDS FIXING
  }

  std::string get_kind()
  {
    return "Const";
  }
private:
  
};

class BinOp: public Expr {
public:
  BinOp(Expr *l, char o, Expr *r): left(l), op(o), right(r) {}
  ~BinOp() { delete left; delete right; }
  virtual void printOn(std::ostream &out) const override {
    out << op << "(" << *left << ", " << *right << ")";
  }

  virtual void sem() override {
    left->type_check(TYPE_int);
    right->type_check(TYPE_int);
    switch (op) {
      case '+': case '-': case '*': case '/': case T_MOD:
        type = TYPE_int; break;
      case '=': case '<': case '>': case T_NEQUAL: case T_SOE: case T_GOE:
        type = TYPE_bool; break;
      case '#':
        type = ;//ONASOY;
    }
  }
private:
  Expr *left;
  int op;
  Expr *right;
};

class MonOp: public Expr {
public:
  MonOp(char o, Expr *r): op(o), right(r) {}
  ~MonOp() { delete right; }
  virtual void printOn(std::ostream &out) const override {
    out << op << "(";
    right->printOn(out);
    out << ")";
  }

  virtual void sem() override {
    right->type_check(TYPE_int);
    switch (op) {
      case '+': case '-':
        type = TYPE_int; break;
    }
  }
private:
  int op;
  Expr *right;
};

class Elsif: public Stmt{
public:
    Elsif(): cond(), stmt1(), size(0){}
    ~Elsif() 
    {
        for(auto c:cond)delete c; 
        for(auto s:stmt1)delete s;
    }
    void append_elsif(Expr *con, Stmt *stm)
    {
        cond.push_back(con);
        stmt1.push_back(stm);
    }
    virtual void printOn(std::ostream &out) const override {
        out<<"Elsifs(";
        for(int i=0;i<size;i++)
        {
            out << "Elsif( ";
            cond[i]->printOn(out);
            out<< " then: ";
            stmt1[i]->printOn(out);
            out<< ")";
        }
        out<<")";
    }
    virtual void sem() override {
        for(int i=0;i<size;i++)
        {
            cond[i]->type_check(TYPE_bool);
            stmt1[i]->sem();
        }
    }

private:
  std::vector<Expr *>cond;
  std::vector<Stmt *>stmt1;
  int size;
};

class If: public Stmt {//SHITFUCKERY
public:
  If(Expr *c, Stmt *s1, Stmt *s2 = nullptr, Elsif *ei=nullptr):
    cond(c), stmt1(s1), stmt2(s2), elif(ei) {}
  ~If() { delete cond; delete stmt1; delete stmt2; delete elif;}
  virtual void printOn(std::ostream &out) const override {
    out << "If(" << *cond << ", " << *stmt1;
    if (elif != nullptr) {
        out<<", ";
        elif->printOn(out);
    }
    if (stmt2 != nullptr) out << ", " << *stmt2;
    out << ")";
  }

  virtual void sem() override {
    cond->type_check(TYPE_bool);
    stmt1->sem();
    if (elif != nullptr) elif->sem();
    if (stmt2 != nullptr) stmt2->sem();
  }
private:
  Expr *cond;
  Stmt *stmt1;
  Stmt *stmt2;
  Elsif *elif;
};

class For: public Stmt {//SHITFUCKERY
public:
  For(Block *f, Expr *e, Block *s, Stmt *c): init(f), cond(e), step(s), code(c) {}
  ~For() { delete init; delete cond; delete step; delete code; }
  virtual void printOn(std::ostream &out) const override {
    out << "For( ";
    init->printOn(out);
    cond->printOn(out);
    step->printOn(out);
    code->printOn(out); 
    out << ")";
  }

  virtual void sem() override {
    st.openScope();
    init->sem();
    cond->type_check(TYPE_bool);
    step->sem();
    code->sem();
    st.closeScope();
  }
private:
  Block *init;
  Expr *cond;
  Block *step;
  Stmt *code;
};

class Return: public Stmt {
  public:
    Return(Expr *expr = nullptr) : retval(expr) {}
    ~Return() { delete retval; }
    virtual void printOn(std::ostream &out) const override {
        if(retval != nullptr)
        {
            out<<"return( ";
            retval->printOn(out);
            out<<")";
        }
        else
        {
            out<<"exit";
        }
    }
    virtual void sem() override {
        if(retval != nullptr) 
            retval->type_check(st.findLastFunc());
    }
  private:
    Expr *retval;
};

class Funcal : public Stmt {
  public:
    Funcal(Id *n, Expls *par = nullptr) : params(par), name(n) {}
    ~Funcal() { delete name; delete params; }
    virtual void printOn(std::ostream &out) const override {
      out<<"funcal(";
      name->printOn(out);
      out<<",";
      params->printOn(out);
      out<<")";
    }
    virtual void sem() override {
      Type *fun = st.lookup(name);
      if(fun == nullptr) {
        yyerror("No such function %s\n",name->getName());
        return;
      }
      if (params!=nullptr)
      {
        if(params->get_size()!=fun->get_param_cnt()) {
          yyerror("wrong number of params");
          return;
        }
        for(int i=0;i<params->get_size();i++)
        {
          if(fun->get_param_type(i)!=params->get_type(i))
          {
            yyerror("wrong parameter type in param #%d \n",i);
            return;
          }
        }
      }
      else if(fun->has_params()) {
        yyerror("function has parameters");
        return;
      }
    }

    std::string get_kind()
    {
      return "Funcal";
    }

  private:
    Id *name;
    Expls *params;
}; 

union atom {
  Const * cnst;
  Id *id;
  Funcal *funcall;
};

class Ass: public Stmt {
  public:
    Ass (atom a, Expr *e): at(a), expr(e) {}
  private:
    atom at;
    Expr *expr;
};

class Vardecl: public AST {
public:
  Vardecl(Id *var, Type type): var(var), type(type) {}
  ~Vardecl(){delete var;}
  virtual void printOn(std::ostream &out) const override {
    out << "Vardecl(";
    id.printOn(out);
    out<< ")";    
  }
  virtual void sem() override {
    st.insert(*var,type);
  }
  void chType(Type ty)
  {
      type=ty;
  }
private:
  Id *var;
  Type type;
};

class Varlist: public Vardecl {//THE []S ARE WRONG + PASS BY REFERENCE
public:
  Varlist(): var(), size(0), nons(0) {} // type(),
  ~Varlist(){
    for (Vardecl *d : var) delete d;
    //for (Type *s : type) delete s;
  }
  void append_vardecl(Id *id, Type type = TYPE_nontype) { 
      Vardecl tmp(id,type);
      var.push_back(&tmp); 
      if(type==TYPE_nontype)
      {
          nons++;
      }
      //type.push_back(type); 
      size++;
  }
  void fixtypes(Type type)
  {
      for( int i=size-1;i>=size-nons;i--)
      {
          var[i]->chType(type);
      }
      nons=0;
  }
  void merge(Varlist *li)
  {
      var.insert(var.end(),li->var.begin(),li->var.end());
      size+=li->size;
  }

  int get_size(){
      return size;
  }
  virtual void printOn(std::ostream &out) const override {
    out << "Decl(";
    for(int i=0; i<size; i++){
        var[i]->printOn(out);
        //out<< var[i] << " : " << type[i] << " ";
    }  
    out<< ")";
  }
  virtual void sem() override {
    for (Vardecl *v : var) v->sem();
  }

private:
  std::vector<Vardecl *> var;
//  std::vector<Type> type;
  int size,nons;
};

class Fundecl: public AST {//POSSIBLE FUnCS TYPE
    public:
        Fundecl(Id *i, Type ty, Varlist *pa, Block *bl=nullptr): block(bl), id(i),type(ty), params(pa){}
        ~Fundecl() {
            delete id;
            if (block!=nullptr)
                delete block;
            delete params;
        }
        virtual void printOn(std::ostream &out) const override
        {
            out<<"Function declaration(";
            id->printOn(out);
            params->printOn(out);
            if (block!=nullptr)
                block->printOn(out);
            out<<")";
        }
        virtual void sem() override
        {
            st.insert(id,type);
            st.openScope();
            params->sem();
            if (block!=nullptr)
                block->sem();
            st.closeScope();
        }
        bool isfuncdef(){
            return block!=nullptr;
        }
        void add_block(Block *bl)
        {
            block = bl;
        }
    private:
        Block *block;
        Id *id;
        Type type;
        Varlist *params;
};

class Block: public Stmt {//DECLERATION
public:
  Block(): decl_list(), stmt_list(), size(0) {}
  ~Block() {
    for (Decl *d : decl_list) delete d;
    for (Stmt *s : stmt_list) delete s;
  }
  void append_decl(Decl *d) { decl_list.push_back(d); }
  void append_stmt(Stmt *s) { stmt_list.push_back(s); }
  void merge(Block *b) {
    stmt_list = b->stmt_list;
    b->stmt_list.clear();
    delete b;
  }
  virtual void printOn(std::ostream &out) const override {
    out << "Block(";
    bool first = true;
    for (Decl *d : decl_list) {
      if (!first) out << ", ";
      first = false;
      out << *d;
    }
    for (Stmt *s : stmt_list) {
      if (!first) out << ", ";
      first = false;
      out << *s;
    }
    out << ")";
  }

  virtual void sem() override {
    st.openScope();
    for (Decl *d : decl_list) d->sem();
    for (Stmt *s : stmt_list) s->sem();
    size = st.getSizeOfCurrentScope();
    st.closeScope();
  }
private:
  std::vector<Decl *> decl_list;
  std::vector<Stmt *> stmt_list;
  int size;
};


#endif