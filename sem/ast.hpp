#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
// #include "parser.cpp"
#include "lexer.hpp"
#include "symbol.hpp"

//void yyerror(const char *msg,...);

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


private:
    std::vector<Expr *> expls;
    int size;
};



class Stmt: public AST {
public:
  ~Stmt(){}
  virtual void printOn(std::ostream &out) const override
  {
      out<<"skip";
  }
  virtual void sem() override {}
};

class Decl: public AST { //isws xreiastei destructoras kapoia stigmi
public:
  virtual void sem();
  virtual void printOn(std::ostream &out) const;
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

class ConstInt: public Expr {
public:
  ConstInt(int numb): num(numb) {}
  ~ConstInt();
  virtual void printOn(std::ostream &out) const override {
    out << "ConstInt( " << num << ")";
  }

  virtual void sem() override {
    type = new Type(true,"int");
  }

  std::string get_kind()
  {
    return "Const Int";
  }
private:
  int num;
  
};

class ConstChar: public Expr {
public:
  ConstChar(char numb): num(numb) {}
  ~ConstChar();
  virtual void printOn(std::ostream &out) const override {
    out << "ConstChar( " << num << ")";
  }

  virtual void sem() override {
    type = new Type(true,"char");
  }

  std::string get_kind()
  {
    return "Const Char";
  }
private:
  char num;
  
};

class ConstString: public Expr {
public:
  ConstString(std::string numb): num(numb) {}
  ~ConstString();
  virtual void printOn(std::ostream &out) const override {
    out << "ConstString( " << num << ")";
  }

  virtual void sem() override {
    type = new Type(true,"string");
  }

  std::string get_kind()
  {
    return "Const String";
  }
private:
  std::string num;
  
};

class ConstBool: public Expr {
public:
  ConstBool(std::string numb): num(numb) {}
  ~ConstBool();
  virtual void printOn(std::ostream &out) const override {
    out << "ConstBool( " << num << ")";
  }

  virtual void sem() override {
    type = new Type(true,"bool");
  }

  std::string get_kind()
  {
    return "Const Bool";
  }
private:
  std::string num;
  
};

class ConstList: public Expr {
public:
  ConstList(std::string numb): num(numb) {}
  ~ConstList();
  virtual void printOn(std::ostream &out) const override {
    out << "ConstList( " << num << ")";
  }

  virtual void sem() override {
    type = new Type(true,"list");
  }

  std::string get_kind()
  {
    return "Const List";
  }
private:
  std::string num;
  
};

class BinOp: public Expr {
public:
  BinOp(Expr *l, char o, Expr *r): left(l), op(o), right(r) {}
  ~BinOp() { delete left; delete right; }
  virtual void printOn(std::ostream &out) const override {
    out << op << "(" << *left << ", " << *right << ")";
  }

  virtual void sem() override {
    if(op!='#')left->type_check(right->get_type());
    // right->type_check(TYPE_int);
    switch (op) {
      case '+': case '-': case '*': case '/': case T_MOD: 
      {
          if((right->get_type()).get_type()=="int")
            type = new Type(true,"int");
          else
            yyerror("type needs to be int"); 
          break;
      }
      case T_OR: case T_AND: 
      {
          if((right->get_type()).get_type()=="bool")
            type = new Type(true,"bool");
          else
            yyerror("type needs to be bool"); 
          break;
      }
      case '=': case '<': case '>': case T_NEQUAL: case T_SOE: case T_GOE: 
        type = right->get_type(); break;
      case '#':
        type = new Type(true,"list");break;
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
    if(op!=T_NOT)right->type_check(new Type(true,"int"));
    else right->type_check(new Type(true,"bool"));
    switch (op) {
      case '+': case '-':
        type = new Type(true,"int"); break;
      case T_NOT:
        type = new Type(true,"bool"); break;
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
            cond[i]->type_check(new Type(true,"bool"));
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
    cond->type_check(new Type(true,"bool"));
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
    cond->type_check(new Type(true,"bool"));
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
      SymbolEntry *e = st.lookup(name->getName());
      Type type = e->type;
      //offset = e->offset;
      //Type *fun = st.lookup(name->getName());
      if(e == nullptr) {
        yyerror("No such function %s\n",name->getName());
        return;
      }
      if (params!=nullptr)
      {
        if(params->get_size()!=type.get_param_cnt()) {
          yyerror("wrong number of params");
          return;
        }
        for(int i=0;i<params->get_size();i++)
        {
          if(type.get_param_type(i)!=params->get_type(i))
          {
            yyerror("wrong parameter type in param #%d \n",i);
            return;
          }
        }
      }
      else if(type.has_params()) {
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

union Atom {
  ConstInt * cnstint;
  ConstChar * cnstchar;
  ConstString * cnststring;
  ConstBool * cnstbool;
  ConstList * cnstlist;
  Id *id;
  Funcal *funcall;
};
//EPISHS EDW DEN EIXAMTE TELEIWSEI
class Ass: public Stmt {
  public:
    Ass (Atom a, Expr *e): at(a), expr(e) {}
    ~Ass() { delete expr; }  
    virtual void printOn(std::ostream &out) const override {
      out <<"Ass(";
      expr->printOn(out);
      out <<")"; //DEN EKTYPWNOUME TO AT, AFTO PREPEI NA ALLAKSEI
    }
    virtual void sem() override {

      //expr->type_check(at -> new Type(true,"int")); PREPEI NA VROUME TON TYPO TOU AT KAPWS
      if (!oti_valoume_meta){
        yyerror("atom and expression don't match");
      }
    }
  private:
    Atom at;
    Expr *expr;
};

class Arracc : public Expr{
public:
  Arracc(Id *i, Expr *e): name(i), pos(e) {}
  ~Arracc() { delete name; delete pos; }
  virtual void printOn(std::ostream &out) const override {
    out << "Arrcall(";
    name->printOn(out);
    pos->printOn(out);
    out<< ")";    
  }

  virtual void sem() override {
    pos->type_check(new Type(true,"int"));
    SymbolEntry *e = st.lookup(name->getName());
    if(e!=nullptr) type = e->type;
    // offset = e->offset;
    else yyerror("no such array");
  }
private:
  Id *name;
  Type type;
  Expr *pos;
};



class Vardecl: public Decl { //MIPWS PREPEI NA NAI YPOKLASI TOU STMT?
public:
  Vardecl(Id *var, Type type): var(var), type(type) {}
  ~Vardecl(){delete var;}
  virtual void printOn(std::ostream &out) const override {
    out << "Vardecl(";
    var->printOn(out);
    out<< ")";    
  }
  virtual void sem() override {
    st.insert(var->getName(),type);
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
  Varlist(): size(0), nons(0) {}// type(),
  ~Varlist(){
    for (Vardecl *d : var) delete d;
    //for (Type *s : type) delete s;
  }
  void append_vardecl(Id *id, Type type = new Type(true,"non")) { 
      Vardecl tmp(id,type);
      var.push_back(&tmp); 
      if(type.get_type()=="non")
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
  int size;
  int nons;
};

class Fundecl: public Decl {//POSSIBLE FUnCS TYPE
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
            st.insert(id->getName(),type);
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


Type::~Type()  { delete params; delete obj; }

bool Type::operator != (Type t)
{
  if(isvar ^ t.isvar) return false;
  if(type!=t.type) return false;
  if(obj!=nullptr || t.obj!=nullptr)
    if(obj!=t.obj) return false;
  if(!isvar)
  {
    if (params->get_size() != (t.params)->get_size()) return false;
    for ( int i=0;i<params->get_size();i++ )
    {
      if( params->get_type(i)!=(t.params)->get_type(i)) return false;
    }
  }
  return true;
}

int Type::get_param_cnt()
{
  return params->get_size();
}

bool Type::has_params()
{
  return !isvar;
}

Type Type::get_param_type(int i)
{
  return params->get_type(i);
}

std::string Type::get_type()
{
  if (type=="list" || type == "array")
  {
    return type+obj->type;
  }
  else
  {
    return type;
  }
}

void Type::make_fun(Expls *pars)
{
  params = pars;
  isvar = false;
}

#endif
