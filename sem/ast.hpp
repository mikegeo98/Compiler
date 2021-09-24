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
//std::string c = "";
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
  Expr(Expr &ex): type(ex.type) {}
  ~Expr(){}
  void type_check(Type *t) {
    sem();
    if (type != *t) yyerror("Type mismatch");
  }
  Type *get_type()
  {
    sem();
    return &type;
  }
  virtual void sem() {
  }
protected:
  Type type;
};

class Arinit: public Expr {
  public:
    Arinit(Type ty, Expr *sz):  size(sz) {type=ty;}
    ~Arinit() {delete size;}
    virtual void printOn(std::ostream &out) const override
    {
      out<<"array(";
      // type.printOn(out);
      out<<",";
      size->printOn(out);
      out<<")"; 
    }
    virtual void sem() override
    {
      size->type_check(new Type(true,"int"));
    }
  private:
    Expr *size;
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
  Type *get_type(int i)
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



class Atom: public Stmt, public Expr{
  public:
    ~Atom(){ /*printf("%c%c%c%c%c%c%c%c%c%c Atom\n",var[0],var[1],var[2],var[3],var[4],var[5],var[6],var[7],var[8],var[9]);*/ delete[] var;}
    virtual void printOn(std::ostream &out) const override {
      out<<var;
    }
    virtual void sem() override {

    }
    char* getName(){
      return var;
    }
    std::string get_kind(){
      return kind;
    }
    char * get_var()
    {
      return var;
    }
    // ConstInt * cnstint;
    // ConstChar * cnstchar;
    // ConstString * cnststring;
    // ConstBool * cnstbool;
    // ConstList * cnstlist;
    // Id *id;
    // Funcal *funcall;
  protected:
    char * var;
    std::string kind;
    
};
//EPISHS EDW DEN EIXAMTE TELEIWSEI

class Id: public Atom {
public:
  Id(char *v): offset(-1) {
    printf("%s Id constructor to moyni tis manas sosu\n", v); 
    kind = "Id"; 
    var = new char[200];
    strcpy(var,v);
  }
  Id(const Id &id): offset(id.offset) { kind = id.kind; var = new char[200]; strcpy(var,id.var); }
  Id &operator =(Id &id)
  {
    offset=id.offset;
    kind=id.kind;
    var = new char[200];
    strcpy(var,id.var);
    return *this;
  }
  ~Id() {/*printf("%c Id\n",var[0]);*/}
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
    Type *tmp = e->type;
    tmp = new Type(*tmp);
    type = *tmp;
    printf("%s Here is type in Id::sem() \n",tmp->get_type().c_str());
    offset = e->offset;
  }
protected:
  //char *var;
  int offset;
};


class Decl: public AST { //isws xreiastei destructoras kapoia stigmi
public:
  ~Decl() {}
  virtual void sem() {}
  virtual Id* get_name() {}
  virtual void printOn(std::ostream &out) const {}
};

class Block: public Stmt {//DECLERATION
public:
  Block(): decl_list(), stmt_list(), size(0) {}
  ~Block() {
    for (Decl *d : decl_list) delete d;
    for (Stmt *s : stmt_list) delete s;
  }
  void append_decl(Decl *d) { 
    // if (d!= nullptr &&d->get_name()!=nullptr && d->get_name()->getName()!=nullptr){
    //   printf("%s In Block::append_decl\n",d->get_name()->getName());
    // }
    printf("apla kati\n");
    decl_list.push_back(d); 
  }
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
    printf("Mou sikwthike stin topothesia Block::sem()\n");
    st.openScope();
    int cnt = 0;
    int cnt2 = 0;
    for (Decl *d : decl_list){
      cnt = cnt + 1;
      printf("Count in Block::sem() %d\n",cnt);
      d->printOn(std::cout);
      d->sem();
    } 
    printf("For ended in Block::sem() \n");
    for (Stmt *s : stmt_list){
      cnt2 = cnt2 + 1;
      printf("Count in 2nd for loop Block::sem() %d\n",cnt2);
      s->sem();
    } 
    printf("2nd For ended in Block::sem() \n");   
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

class ConstInt: public Atom {
public:
  ConstInt(int numb): num(numb) { kind = "ConstInt";}
  ~ConstInt() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstInt( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"int");
    type = *tmp;
  }

  std::string get_kind()
  {
    return "Const Int";
  }
private:
  int num;
};

class ConstChar: public Atom {
public:
  ConstChar(char numb): num(numb) { kind = "ConstChar"; }
  ~ConstChar() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstChar( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"char");
    type = *tmp;
  }

  std::string get_kind()
  {
    return "Const Char";
  }
private:
  char num;
  std::string kind;
};

class ConstString: public Atom {
public:
  ConstString(std::string numb): num(numb) { kind = "ConstString"; }
  ~ConstString() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstString( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"string");
    type = *tmp;
  }

  std::string get_kind()
  {
    return "Const String";
  }
private:
  std::string num;
  
};

class ConstBool: public Atom {
public:
  ConstBool(int numb) {num=numb; kind = "ConstBool"; }//maybe string
  ~ConstBool() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstBool( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"bool");
    type = *tmp;
  }

  std::string get_kind()
  {
    return "Const Bool";
  }
private:
  int num;//maybe string
  
};

class ConstList: public Atom {
public:
  ConstList(int numb): num(numb) { kind = "ConstList"; }
  ~ConstList() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstList( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"list");
    type = *tmp;
  }

  std::string get_kind()
  {
    return "Const List";
  }
private:
  int num;
  
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
          if((right->get_type())->get_type()=="int")
            type = new Type(true,"int");
          else
            yyerror("type needs to be int"); 
          break;
      }
      case T_OR: case T_AND: 
      {
          if((right->get_type())->get_type()=="bool")
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
    printf("Better???\n");
    cond->type_check(new Type(true,"bool"));
    stmt1->sem();
    printf("Are we ok?\n");
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
        if(retval != nullptr) {
            Type *temp=new Type(st.findLastFunc());
            retval->type_check(temp);
        }
    }
  private:
    Expr *retval;
};

class Funcal : public Atom {
  public:
    Funcal(Id *n, Expls *par = nullptr) : name(n), params(par) { kind = "Funcal"; }
    ~Funcal() { delete name; delete params; }
    virtual void printOn(std::ostream &out) const override {
      out<<"funcal(";
      name->printOn(out);
      out<<",";
      params->printOn(out);
      out<<")";
    }
    virtual void sem() override {
      printf("%s is the name in Funcall::sem()\n",name->getName());
      SymbolEntry *e = st.lookup(name->getName());
      Type *typ = new Type(*(e->type));
      printf("Typ is in Funcall:sem()%s\n",typ->get_type().c_str());
      printf("%s %s is the type in Funcall::sem()\n",typ->get_type().c_str(),e->type->get_type().c_str());      
      //offset = e->offset;
      //Type *fun = st.lookup(name->getName());
      if(e == nullptr) {
        yyerror("No such function %s\n",name->getName());
        return;
      }
      if (params!=nullptr)
      {
        if(params->get_size()!=typ->get_param_cnt()) {
          yyerror("wrong number of params");
          return;
        }
        for(int i=0;i<params->get_size();i++)
        {
          // printf("params have types %s %s \n",typ->get_param_type(i)->get_type().c_str(),params->get_type(i)->get_type().c_str());
          if(*(typ->get_param_type(i))!=*(params->get_type(i)))
          {
            yyerror("wrong parameter type in param #%d \n",i);
            return;
          }
        }
        printf("fevgwwww");
      }
      else if(typ->has_params()) {
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


class Ass: public Stmt {
  public:
    Ass (Atom *a, Expr *e): at(a), expr(e) {}
    ~Ass() { delete expr; }  
    virtual void printOn(std::ostream &out) const override {
      out <<"Ass(";
      expr->printOn(out);
      out <<")"; //DEN EKTYPWNOUME TO AT, AFTO PREPEI NA ALLAKSEI
    }
    virtual void sem() override {

      //expr->type_check(at -> new Type(true,"int")); PREPEI NA VROUME TON TYPO TOU AT KAPWS
      if (at->get_kind() == "Id"){
        SymbolEntry *e;
        e = st.lookup(at->getName());
        Type type = e->type;
        expr->type_check(&type);
      }
      else {
        yyerror("Item does not support assignment");
      }
      // if(at.cnstint!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(true,"int"));
      // }
      // else if(at.cnstbool!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(true,"bool"));
      // }
      // else if(at.cnststring!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(true,"string"));
      // }
      // else if(at.cnstlist!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(true,"list",nullptr,new Type(true,"any")));
      // }
      // else if(at.cnstchar!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(true,"char"));
      // }
      // else if(at.id!=nullptr)
      // {
      //   SymbolEntry *e;
      //   e = st.lookup((at.id)->getName());
      //   Type type = e->type;
      //   expr->type_check(type);
      // }
      // else if(at.funcall!=nullptr)
      // {
      //   yyerror("item does not support assgnment");
      //   // expr->type_check(new Type(false,"int"));
      // }
      // else
      // {
      //   yyerror("shit fuck wrong type class ass");
      // }
    }
  private:
    Atom *at;
    Expr *expr;
};

class Arracc : public Atom{ //Pithanon na min exei lythei entelws h fash me Arracc
public:
  Arracc(Atom *i, Expr *e): name(i), pos(e) {}
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
  Atom *name;
  Type type;
  Expr *pos;
};



class Vardecl: public Decl { //MIPWS PREPEI NA NAI YPOKLASI TOU STMT?
public:
  Vardecl(Id *v, Type *ty): var(v), type(*ty) {
    printf("%s is var %s is type in Vardecl::Vardecl()\n",var->get_var(),type.get_type());
  }
  Vardecl(Vardecl &vd):  type(vd.type) {
    char *tmp = new char[200]; 
    printf("%s VD IN Vardecl::Vardecl(Vardecl &vd)\n",vd.var->get_var()); 
    strcpy(tmp,vd.var->get_var());
    var = new Id(tmp);
  }
  Vardecl &operator = (Vardecl &vd){
    type = vd.type;
    var = new Id(*(vd.var));
    return *this;
  }
  ~Vardecl(){delete var;}
  virtual void printOn(std::ostream &out) const override {
    out << "Vardecl(";
    var->printOn(out);
    out<<"type="<<(&type)->get_type()<< ")";    
  }
  virtual void sem() override {
    printf("prin to Vardecl::sem()");
    st.insert(var->getName(),type);
    printf("%s var name in Vardecl::sem()\n",var->getName());
    SymbolEntry *e=st.lookup(var->getName());
    printf("%s var name in Vardecl::sem()\n",e->type->get_type().c_str());

  }
  void chType(Type *ty)
  {
      Type *tmp=new Type(*ty);
      printf("type is %s in Vardecl::chType(Type ty)\n",ty->get_type().c_str());
      type = *tmp;
      printf("type is %s in Vardecl::chType(Type ty)\n",type.get_type().c_str());
  }
  Type *get_type()
  {
    return &type;
  }
  virtual Id *get_name() override
  {
    return var;
  }  
private:
  Id *var;
  Type type;
};

class Varlist: public Vardecl {//THE []S ARE WRONG + PASS BY REFERENCE
public:
  Varlist(): Vardecl(new Id(""), new Type()), size(0), nons(0)  {}// type(),
  Varlist(Varlist &vl): Vardecl(new Id(""), new Type())
  {
    size=vl.size;
    nons=vl.nons;
    for(auto k:vl.var)
    {
      var.push_back(new Vardecl(*k));
    }
  }
  ~Varlist(){
    for (Vardecl *d : var) delete d;
    //for (Type *s : type) delete s;
  }
  void append_vardecl(Id *id, Type *type = new Type(true,"non")) { 
      Vardecl *tmp=new Vardecl(id,type);
      tmp->printOn(std::cout);
      std::cout<<"at Varlist::append_vardecl(Id *id, Type type = new Type(true,\"non\"))\n";
      var.push_back(tmp); //δεικτης 
      if(type->get_type()=="non")
      {
          nons++;
      }
      //type.push_back(type); 
      size++;
      this->printOn(std::cout);
      std::cout<<"at Varlist::append_vardecl(Id *id, Type type = new Type(true,\"non\"))\n";
  }
  void fixtypes(Type *type)
  {
    if (type->get_obj()!=nullptr)
      printf("type has %s %s in Varlis::fixtypes\n",type->get_type().c_str(),type->get_obj()->get_type().c_str());
    else
      printf("wnasoy in Varlist::fixtypes(Type *type)\n");
    for( int i=size-1;i>=size-nons;i--)
    {
        printf("%d in Varlist::fixtypes(Type *type)\n",i);  
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
  Type *get_type(int i)
  {
    return var[i]->get_type();
  }
  virtual void printOn(std::ostream &out) const override {
    out << "Decl(";
    out << size;
    out << " \n";
    out << var.size();
    out << " \n";
    for(int i=0; i<size; i++){
        if(var[i]==nullptr){
          out<<"we have a problem varlist has null member "<<i<<"\n";
        }
        else{
          out<<"hello"<<var[i]->get_type()->get_type()<<'\n';
          // var[i]->printOn(out);
        }
        //out<< var[i] << " : " << type[i] << " ";
    }  
    out<< ")";
  }
  virtual void sem() override {
    for (Vardecl *v : var)
    {
      v->printOn(std::cout);
      v->sem();
    }
  }

private:
  std::vector<Vardecl *> var;
//  std::vector<Type> type;
  int size;
  int nons;
};

class Fundecl: public Decl {//POSSIBLE FUnCS TYPE
    public:
        Fundecl(Id *i, Type *ty, Varlist *pa, Block *bl=nullptr): block(bl), id(i),type(*ty), params(pa){std::cout<<type.get_type()<<"type in Fundecl::Fundecl()";}
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
            // id->printOn(std::cout);
            // SymbolEntry *e;
            // e = st.lookup("putc");
            // if(e==nullptr)yyerror("efakre\n");
            // printf("putc of type %d\n",e->type->get_param_cnt());
            // std::cout<<type.get_type()<<"type in Fundecl::sem()";
            // std::cout<<type.get_type();
            // std::string a(id->getName());
            // std::cout<<a<<" in Fundecl::sem()\n";
            // printf("%s in Fundecl::sem()\n",a);
            // st.openScope();
            st.insert(id->getName(),type);
            // printf("%s inserted in st Fundecl::sem()\n",id->getName());
            if(block!=nullptr)
            {
              printf("afou vastaei i kardia sou %s \n",type.get_type().c_str());
              st.addFunc(type);
              printf("na meinw makria sou, fevgw geia sou geia sou");
            }
            st.openScope();
            if(params!=nullptr) params->sem();
            st.openScope();
            if (block!=nullptr)
                block->sem();
            if(block!=nullptr)
            {
              st.remFunc();
            }
            st.closeScope();
            st.closeScope();
            // st.closeScope();
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

inline Type::Type(const Type &t): isvar(t.isvar){ 
    type = new char[200]; 
    strcpy(type,t.type);
    params = t.params==nullptr?nullptr:new Expls(*t.params);
    if(t.obj==nullptr)
      obj=nullptr;
    else{
      // printf("here %s\n",t.obj->get_type().c_str());
      obj = new Type(*t.obj);
    }
    if (t.params2 != nullptr){
      t.params2->printOn(std::cout);
    }
    params2 = t.params2==nullptr?nullptr:new Varlist(*t.params2); 
    printf("%s is the type in Type::Type(const Type &t)",this->get_type().c_str());
}

inline Type::~Type()  { 
  delete[] type; 
  delete params; 
  delete obj; 
  delete params2;
}

inline bool Type::operator != (Type t)
{
  if(isvar ^ t.isvar) return false;
  if(type!=t.type||std::string(type)=="any"||std::string(t.type)=="any") return false;
  if(obj!=nullptr || t.obj!=nullptr)
    if(obj!=t.obj) return false;
  if(!isvar)
  {
    if (params == nullptr && t.params == nullptr){
      if (params2->get_size() != (t.params2)->get_size()) return false;
        for ( int i=0;i<params2->get_size();i++ )
        {
          if( params2->get_type(i)!=(t.params2)->get_type(i)) return false;
        }
    }
    else if (params2 == nullptr && t.params2 == nullptr){
      if (params->get_size() != (t.params)->get_size()) return false;
        for ( int i=0;i<params->get_size();i++ )
        {
          if( params->get_type(i)!=(t.params)->get_type(i)) return false;
        }
    }
    else if (params == nullptr && t.params2 == nullptr){
      if (params2->get_size() != (t.params)->get_size()) return false;
        for ( int i=0;i<params2->get_size();i++ )
        {
          if( params2->get_type(i)!=(t.params)->get_type(i)) return false;
        }
    }
    else {
      if (params->get_size() != (t.params2)->get_size()) return false;
        for ( int i=0;i<params->get_size();i++ )
        {
          if( params->get_type(i)!=(t.params2)->get_type(i)) return false;
        }
    }
  }
  return true;
}

inline int Type::get_param_cnt()
{
  printf("type is %s in Type::get_param_cnt()\n",get_type().c_str());
  if (params!= nullptr){
    printf("Type::get_param_cntmpika sto params branch \n");
    return params->get_size();
  }
  if (params2!= nullptr){
    printf("Type::get_param_cntmpika sto params2 branch \n");
    return params2->get_size();
  }
  yyerror("no params");
  
}

inline bool Type::has_params()
{
  return !isvar;
}

inline Type *Type::get_param_type(int i)
{
  if (params!= nullptr)
    return params->get_type(i);
  if (params2!= nullptr)
    return params2->get_type(i);
  yyerror("no params get_param_type");
}

inline std::string Type::get_type() const
{
  if (std::string(type)=="list" || std::string(type) == "array")
  {
    // if(obj==nullptr)
    // {
    //   printf("obj is null in Type::get_type()");
    // }
    return std::string(type)+std::string(obj->type);
  }
  else
  {
    return type;
  }
}

inline void Type::make_fun(Expls *pars)
{
  params = pars;
  isvar = false;
}

inline void Type::make_fun2(Varlist *pars)
{
  params2 = pars;
  isvar = false;
}

inline void initSt()
{
  st.openScope();
  
  Varlist *vrd = new Varlist();
  vrd->append_vardecl(new Id("n"),new Type(true,"int"));
  Type *ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("puti",*ty);
  
  vrd = new Varlist();
  vrd->append_vardecl(new Id("b"),new Type(true,"bool"));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("putb",*ty);
  
  vrd = new Varlist();
  vrd->append_vardecl(new Id("c"),new Type(true,"char"));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("putc",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("n"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("puts",*ty);

  // SymbolEntry *e;
  // e = st.lookup("putc");
  // if(e==nullptr)yyerror("efakre\n");
  // printf("putc of type %d\n",e->type->get_param_cnt());
}

#endif
