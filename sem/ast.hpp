#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
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



class Expr: public AST { 
public:
  Expr() {}
  Expr(Expr &ex): type(ex.type) {}
  ~Expr(){}
  void type_check(Type *t) {
    sem();
    // if(t==nullptr)printf("gtxm in Expr::type_check()\n");
    if (type != *t) 
    {
      fprintf(stderr,"Types are %s and %s \n",type.get_type().c_str(),t->get_type().c_str());
      yyerror("Type mismatch");
    }
  }
  Type *get_type()
  {
    // printf("we are before sem() in Expr::get_type type is %s\n",type.get_type().c_str());
    sem();
    // printf("we are after sem() in Expr::get_type type is %s\n",type.get_type().c_str());
    return &type;
  }
  virtual std::string get_kind() {}
  virtual void sem() {
  }
protected:
  Type type;
};

class Arinit: public Expr {
  public:
    Arinit(Type *ty, Expr *sz):  size(sz) {
      Type *tmp = new Type(true,"array",nullptr,ty);
      type=*tmp;
    }
    ~Arinit() {delete size;}
    virtual void printOn(std::ostream &out) const override
    {
      out<<"array(";
      out<< type.get_type();
      // type.printOn(out);
      out<<",";
      size->printOn(out);
      out<<")"; 
    }
    virtual void sem() override
    {
      size->type_check(new Type(true,"int"));
    }
    virtual std::string get_kind() override {
      return "arinit";
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
    // printf("we are in Exprls::get_type\n");
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
  Expr *get_param(int i)
  {
    return expls[i];
  }
  virtual void sem() override {
      for (auto i: expls){
          // printf("%d is i in Exprls::sem()\n");
          i->sem();
      }
  }
  virtual std::string get_kind() override {
    return "expls";
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
    virtual std::string get_kind() override{
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
    kind = "Id"; 
    var = new char[200];
    for (int i=0; i<200; i++){
        var[i] = '0';
      }
    strcpy(var,v);
  }
  Id(const Id &id): offset(id.offset) 
  { 
    kind = id.kind; 
    var = new char[200]; 
    for (int i=0; i<200; i++){
        var[i] = '0';
    }
    strcpy(var,id.var); 
  }
  Id &operator =(Id &id)
  {
    offset=id.offset;
    kind=id.kind;
    var = new char[200];
    for (int i=0; i<200; i++){
      var[i] = '0';
    }    
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
    // printf("we are in Id::sem()\n");
    SymbolEntry *e = st.lookup(var);
    Type *tmp = e->type;
    tmp = new Type(*tmp);
    type = *tmp;
    // printf("%s Here is type in Id::sem() \n",tmp->get_type().c_str());
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
    // printf("apla kati\n");
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
    st.openScope();
    int cnt = 0;
    int cnt2 = 0;
    std::reverse(decl_list.begin(),decl_list.end());
    for (Decl *d : decl_list){
      cnt = cnt + 1;
      // printf("Count in Block::sem() %d\n",cnt);
      // d->printOn(std::cout);
      d->sem();
    } 
    // printf("For ended in Block::sem() \n");
    for (Stmt *s : stmt_list){
      cnt2 = cnt2 + 1;
      // printf("Count in 2nd for loop Block::sem() %d\n",cnt2);
      s->sem();
    } 
    // printf("2nd For ended in Block::sem() \n");   
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
    // printf("type is %s in ConstInt::sem()\n",type.get_type().c_str());
  }

  std::string get_kind()
  {
    return "ConstInt";
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
    return "ConstChar";
  }
private:
  char num;
  std::string kind;
};

inline bool isnothex(char c)
{
  return !((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'));
}

class ConstString: public Atom {
public:
  ConstString(std::string numb): num(numb) { 
    kind = "ConstString";
    for(int i=1;i<strlen(num.c_str())-1;i++)
    {
      if(num[i]=='"'||num[i]=='\''||num[i]=='\t') 
      {
        fprintf(stderr,"In string %s \n",num.c_str());
        yyerror("syntax error 1 in string escape needed");
      }
      // printf("1 num[%d] is %c in ConstString::ConstString()\n",i,num[i]);
      if(num[i]=='\\')
      {
        // printf("2 num[%d] is %c in ConstString::ConstString()\n",i+1,num[i+1]);
        if(i==strlen(num.c_str())-2||(num[i+1]!='n'&&num[i+1]!='r'&&num[i+1]!='t'&&num[i+1]!='0'&&num[i+1]!='\''&&num[i+1]!='"'))
        {        
          // printf("3 num[%d] is %c in ConstString::ConstString()\n",i+1,num[i+1]);
          if(i>=strlen(num.c_str())-4||(num[i+1]!='x'||isnothex(num[i+2])||isnothex(num[i+3]))) 
          {
              fprintf(stderr,"In string %s \n",num.c_str());
              yyerror("syntax error 2 in string escape needed");
          }
        }
        i++;
      }
    }
  }
  ~ConstString() {}
  virtual void printOn(std::ostream &out) const override {
    out << "ConstString( " << num << ")";
  }

  virtual void sem() override {
    Type *tmp = new Type(true,"array",nullptr,new Type(true,"char"));
    type = *tmp;
  }

  std::string get_kind()
  {
    return "ConstString";
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
    return "ConstBool";
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
    // printf("we are in ConstList::sem()\n");
    Type *tmp = new Type(true,"list",nullptr,new Type(true,"any"));
    type = *tmp;
    // printf("Type = %s\n",type.get_type().c_str());
  }

  std::string get_kind()
  {
    return "ConstList";
  }
private:
  int num;
  
};

class BinOp: public Expr {
public:
  BinOp(Expr *l, int o, Expr *r): left(l), op(o), right(r) {}
  ~BinOp() { delete left; delete right; }
  virtual void printOn(std::ostream &out) const override {
    out << op << "(" << *left << ", " << *right << ")";
  }

  virtual void sem() override {
    // printf("we are in BinOp::sem() %d\n",op);
    if(op!='#')left->type_check(right->get_type());
    // right->type_check(TYPE_int);
    switch (op) {
      case '+': case '-': case '*': case '/': case T_MOD: 
      {
          if((right->get_type())->get_type()=="int"){
            Type *tmp = new Type(true,"int");
            type = *tmp; 
          }
          else{
            fprintf(stderr,"Operator %c and left type is %s and right type is %s\n",op,left->get_type()->get_type().c_str(),right->get_type()->get_type().c_str());
            yyerror("type needs to be int"); 
          }
          break;
      }
      case T_OR: case T_AND:
      {
          // printf("right type is %s in BinOP::sem()\n",right->get_type()->get_type().c_str());
          if((right->get_type())->get_type()=="bool"){
            Type *tmp = new Type(true,"bool");
            type = *tmp; 
          }
          else
          {
              fprintf(stderr,"Operator %c and left type is %s and right type is %s\n",op,left->get_type()->get_type().c_str(),right->get_type()->get_type().c_str());
              yyerror("type needs to be bool"); 
          }
          break;
      }
      // EDW KATI DEN DOULEVEI
      case '=': case '<': case '>': case T_NEQUAL: case T_SOE: case T_GOE: 
      {
        if (right->get_type()->get_type() != "int" && right->get_type()->get_type() != "bool" && right->get_type()->get_type() != "char")
        {
          fprintf(stderr,"Operator %c\n",op);
          yyerror("Has invalid operand"); 
        }
        Type *tmp = new Type(true,"bool");
        type = *tmp; 
        break;
      }
      case '#':
      {
        // printf("FLAGG\n");
        if(right->get_type()->get_type()[0]!='l'||right->get_type()->get_type()[2]!='s')
        {
          fprintf(stderr,"ERROR right is type %s and left is %s\n",right->get_type()->get_type().c_str(),left->get_type()->get_type().c_str());
          // left->printOn(std::cout);
          // printf("\n");
          // right->printOn(std::cout);
          // printf("\n");
          yyerror("# should be applied to a list");
        }
        // printf("CORRECT Left type is %s and right type is %s in BinOp::sem()\n",left->get_type()->get_type().c_str(),right->get_type()->get_type().c_str());
        left->type_check(right->get_type()->get_obj());
        // if()
        // {
        //   yyerror("head doesnt match tail in operator #");
        // }
        Type *tmp = new Type(true,"list",nullptr,left->get_type());
        type = *tmp;
        // printf("Type in BinoOp::sem is %s\n",tmp->get_type().c_str());
        break;
      }
    }
  }
  virtual std::string get_kind() override {
    return "binop";
  }
private:
  Expr *left;
  int op;
  Expr *right;
};

class MonOp: public Expr {
public:
  MonOp(int o, Expr *r): op(o), right(r) {}
  ~MonOp() { delete right; }
  virtual void printOn(std::ostream &out) const override {
    out << op << "(";
    right->printOn(out);
    out << ")";
  }

  virtual void sem() override {
    // printf("the operator is %d in MonOp::sem()\n",op);
    if(op!=T_NOT)right->type_check(new Type(true,"int"));
    else right->type_check(new Type(true,"bool"));
    switch (op) {
      case '+': case '-':
      {
        Type *tmp = new Type(true,"int");
        type = *tmp; break;
      }
      case T_NOT:
      {
        Type *tmp = new Type(true,"bool");
        type = *tmp; break;
      }
    }
  }
  virtual std::string get_kind() override {
    return "monop";
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
    // printf("Better???\n");
    cond->type_check(new Type(true,"bool"));
    stmt1->sem();
    // printf("Are we ok?\n");
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
      // printf("we are in Return::sem()\n");
      if(retval != nullptr) {
          Type one = st.findLastFunc();
          // printf("Type one is %s in Return::sem()\n",one.get_type().c_str());
          Type *temp=new Type(one);
          retval->type_check(temp);
      }
    }
  private:
    Expr *retval;
};

class Funcal : public Atom {
  public:
    Funcal(Id *n, Expls *par = nullptr) : name(n), params(par) { 
      kind = "Funcal"; 
      // printf("name is %s in Funcal::Funcal()\n",name->getName());
      // par->printOn(std::cout);
      // printf("ok\n");
      var = new char[200];
      for (int i=0; i<200; i++){
        var[i] = '0';
      }  
      strcpy(var,n->get_var());
    }
    ~Funcal() { delete name; delete params; }
    virtual void printOn(std::ostream &out) const override {
      out<<"funcal(";
      name->printOn(out);
      out<<",";
      if (params!=nullptr) params->printOn(out);
      out<<")";
    }
    virtual void sem() override {
      // printf("%s is the name in Funcall::sem()\n",name->getName());
      SymbolEntry *e = st.lookup(name->getName());
      // printf("Typ is in Funcall:sem()%s\n",e->type->get_type().c_str());
      Type *typ = new Type(*(e->type));
      type = *typ;
      // printf("Typ is in Funcall:sem()%s\n",typ->get_type().c_str());
      // printf("%s %s is the type in Funcall::sem()\n",typ->get_type().c_str(),e->type->get_type().c_str());      
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
        if((name->getName()[0]=='h'&&name->getName()[1]=='e'&&name->getName()[2]=='a'&&name->getName()[3]=='d')||(name->getName()[0]=='t'&&name->getName()[1]=='a'&&name->getName()[2]=='i'&&name->getName()[3]=='l'))
        {
          Type *tmp=new Type(true,"list",nullptr,new Type(true,"any")); 
          if(!(*(params->get_type(0))!=*(tmp)||(params->get_type(0)->get_obj()!=nullptr&&params->get_type(0)->get_obj()->get_type()!="any")))
          { 
            yyerror("no empty list in head or tail");
          }
          if(name->getName()[0]=='h'&&name->getName()[1]=='e'&&name->getName()[2]=='a'&&name->getName()[3]=='d')
          {
            tmp=params->get_type(0)->get_obj();
            // printf("here1 in funcal::sem()\n");
            tmp = new Type(*tmp);
            type=*tmp;
          }
          else
          {
            tmp=params->get_type(0);
            // printf("here2 in funcal::sem()\n");
            tmp = new Type(*tmp);
            type=*tmp;
          }
        }
        // printf("we are in a chp -1 Funcall::sem();\n");
        for(int i=0;i<params->get_size();i++)
        {
          // printf("we are in a chp %d Funcall::sem();\n",i);
          // params->printOn(std::cout);
          // printf("params have types %s %s \n",typ->get_param_type(i)->get_type().c_str(),params->get_type(i)->get_type().c_str());
          if(*(typ->get_param_type(i))!=*(params->get_type(i)))
          {
            yyerror("wrong parameter type in param #\n");
            // return;
          }
          // printf("%d lol in funcal::sem()\n",typ->cbr());
          if(typ->cbr())
          {
            if(params->get_param(i)->get_kind()!="id")
            {
              // this->printOn(std::cout);
              // printf("ith name %s\n",params->get_param(i)->get_kind().c_str(),params->get_param(i)->get_type()->get_type().c_str());
              yyerror("can't be passed by reference r-values");
            }
          }
        }
      }
      else if(typ->has_params()) {
        fprintf(stderr,"Typ has name %s and type %s\n",name->getName(),typ->get_type().c_str());
        yyerror("function has parameters");
        return;
      }
    }

    std::string get_kind()
    {
      return "Funcal";
    }
    char* get_var()
    {
      return name->get_var();
    }
    char* getName()
    {
      return name->getName();
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
      at->printOn(out);
      out<<',';
      expr->printOn(out);
      out <<")";
    }
    virtual void sem() override {
      // this->printOn(std::cout);
      if (at->get_kind() == "Id"){
        SymbolEntry *e;
        e = st.lookup(at->getName());
        expr->type_check(e->type);
      }
      else if(at->get_kind() == "Arracc")
      {
        // at->printOn(std::cout);
        at->sem();
        expr->type_check(at->get_type());
      }
      else {
        yyerror("Item does not support assignment");
      }
    }
  private:
    Atom *at;
    Expr *expr;
};

class Arracc : public Atom{ //Pithanon na min exei lythei entelws h fash me Arracc
public:
  Arracc(Atom *i, Expr *e): name(i), pos(e) {
    kind="Arracc";
    var = new char[200];
    for (int i=0; i<200; i++){
      var[i] = '0';
    }  
    if (i->get_kind() == "Id" || name->get_kind() == "Funcal"|| name->get_kind() == "Arracc")
      strcpy(var,i->get_var());
    else 
      var = nullptr;
  }
  ~Arracc() { delete name; delete pos; }
  virtual void printOn(std::ostream &out) const override {
    out << "Arrcall(";
    name->printOn(out);
    pos->printOn(out);
    out<< ")";    
  }

  virtual void sem() override {
    pos->type_check(new Type(true,"int"));
    // this->printOn(std::cout);
    if (name->get_kind() == "Id" || name->get_kind() == "Funcal"){
      // printf("name type is %s in Arracc::sem()\n",name->get_kind().c_str());
      SymbolEntry *e = st.lookup(name->getName());
      if(e->type->get_obj()==nullptr) yyerror("object is not an array");
      // printf("tmp has type %s in Arracc::sem()\n",e->type->get_type().c_str());
      Type *tmp=e->type->get_obj();
      tmp = new Type(*tmp);
      if(e!=nullptr) type = *tmp;
      // offset = e->offset;
      else {
        fprintf(stderr,"array %s\n",name->getName());
        yyerror("no such array");
      }
    }
    else if(name->get_kind()=="Arracc")
    {
      name->sem();
      Type *tmp=name->get_type()->get_obj();
      tmp = new Type(*tmp);
      type = *tmp;
    }
    else {
      Type *tmp = new Type(true,"char");
      type = *tmp;
    }
  }
  Type *get_type()
  {
    // printf("type is %s in Arracc::get_type",type.get_type().c_str());
    return &type;
  }
  std::string get_kind()
  {
    return "Arracc";
  }
private:
  Atom *name;
  // Type type;
  Expr *pos;
};



class Vardecl: public Decl { //MIPWS PREPEI NA NAI YPOKLASI TOU STMT?
public:
  Vardecl(Id *v, Type *ty): var(v), type(*ty) {}
  Vardecl(Vardecl &vd):  type(vd.type) {
    char *tmp = new char[200]; 
    for (int i=0; i<200; i++){
      tmp[i] = '0';
    }  
    // printf("%s VD IN Vardecl::Vardecl(Vardecl &vd)\n",vd.var->get_var()); 
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
    // printf("prin to Vardecl::sem()");
    st.insert(var->getName(),type);
    // printf("%s var name in Vardecl::sem()\n",var->getName());
    SymbolEntry *e=st.lookup(var->getName());
    // printf("%s var name in Vardecl::sem()\n",e->type->get_type().c_str());

  }
  void chType(Type *ty)
  {
      Type *tmp=new Type(*ty);
      // printf("type is %s in Vardecl::chType(Type ty)\n",ty->get_type().c_str());
      type = *tmp;
      // printf("type is %s in Vardecl::chType(Type ty)\n",type.get_type().c_str());
  }
  Type *get_type()
  {
    return &type;
  }
  virtual Id *get_name() override
  {
    return var;
  }  
  // void mbr()
  // {
  //   by_ref=true;
  // }
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
      // tmp->printOn(std::cout);
      // std::cout<<"at Varlist::append_vardecl(Id *id, Type type = new Type(true,\"non\"))\n";
      var.push_back(tmp); //δεικτης 
      if(type->get_type()=="non")
      {
          nons++;
      }
      //type.push_back(type); 
      size++;
      // this->printOn(std::cout);
      // std::cout<<"at Varlist::append_vardecl(Id *id, Type type = new Type(true,\"non\"))\n";
  }
  void fixtypes(Type *type, bool br = false)
  {
    if(br)type->mbr();
    for( int i=size-1;i>=size-nons;i--)
    {
        // printf("%d in Varlist::fixtypes(Type *type)\n",i);  
        var[i]->chType(type);
        // if(br) var[i]->mbr();
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
      // v->printOn(std::cout);
      v->sem();
    }
  }

private:
  std::vector<Vardecl *> var;
//  std::vector<Type> type;
  int size;
  int nons;
};

class Fundecl: public Decl {
    public:
        Fundecl(Id *i, Type *ty, Varlist *pa, Block *bl=nullptr): block(bl), id(i),type(*ty), params(pa){}
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
            if (params!=nullptr) params->printOn(out);
            if (block!=nullptr)
                block->printOn(out);
            out<<")";
        }
        virtual void sem() override
        {
            st.insert(id->getName(),type);
            if(block!=nullptr)
            {
              st.addFunc(type);
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

inline Type::Type(const Type &t): byref(t.byref), isvar(t.isvar){ 
    type = new char[200]; 
    for (int i=0; i<200; i++){
      type[i] = '0';
    }  
    strcpy(type,t.type);
    params = t.params==nullptr?nullptr:new Expls(*t.params);
    if(t.obj==nullptr)
      obj=nullptr;
    else{
      obj = new Type(*t.obj);
    }
    if (t.params2 != nullptr){
      // t.params2->printOn(std::cout);
    }
    params2 = t.params2==nullptr?nullptr:new Varlist(*t.params2); 
    // printf("%s is the type in Type::Type(const Type &t)\n",this->get_type().c_str());
}

inline Type::~Type()  { 
  delete[] type; 
  delete params; 
  delete obj; 
  delete params2;
}

inline bool Type::operator != (Type t)
{
  // printf("start Type::operator!=\n");
  if(std::string(type)=="any" || std::string(t.type)=="any")
  {
    return false;
  }
  if(std::string(type)!=std::string(t.type) && std::string(type)!="any" && std::string(t.type)!="any") {  
    // printf("TYPES NOT SAME 2 %s %s\n",type,t.type);
    return true;
  } 
  // printf("mid Type::operator!=\n");
  if(obj!=nullptr || t.obj!=nullptr)
  {
    // printf("Obj is %d amd t.Obj is %d in Type::operator != \n", obj,t.obj);
    if(*obj!=*t.obj) {
      // printf("Obj is %s amd t.Obj is %s in Type::operator != \n", obj->get_type().c_str(),t.obj->get_type().c_str());
      return true;
    }
  }
  // printf("end Type::oper/ator!=\n");
  return false;
}

inline int Type::get_param_cnt()
{
  // printf("type is %s in Type::get_param_cnt()\n",get_type().c_str());
  if (params!= nullptr){
    return params->get_size();
  }
  if (params2!= nullptr){
    return params2->get_size();
  }
  yyerror("no params");
  
}

inline bool Type::has_params()
{
  if(params!=nullptr)
  {
    // printf("params in Type::has_params()\n");
    // params->printOn(std::cout);
  }

  return params2!=nullptr||params!=nullptr;
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
  vrd->append_vardecl(new Id("s"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("puts",*ty);

  ty = new Type(false,"int");
  st.insert("geti",*ty);

  ty = new Type(false,"bool");
  st.insert("getb",*ty);

  ty = new Type(false,"char");
  st.insert("getc",*ty);
  
  vrd = new Varlist();
  vrd->append_vardecl(new Id("n"),new Type(true,"int"));
  vrd->append_vardecl(new Id("s"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("gets",*ty);
  
  vrd = new Varlist();
  vrd->append_vardecl(new Id("n"),new Type(true,"int"));
  ty = new Type(false,"int",nullptr,nullptr,vrd);
  st.insert("abs",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("c"),new Type(true,"char"));
  ty = new Type(false,"int",nullptr,nullptr,vrd);
  st.insert("ord",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("n"),new Type(true,"int"));
  ty = new Type(false,"char",nullptr,nullptr,vrd);
  st.insert("chr",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("s"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"int",nullptr,nullptr,vrd);
  st.insert("strlen",*ty);   

  vrd = new Varlist();
  vrd->append_vardecl(new Id("s1"),new Type(true,"array",nullptr,new Type(true,"char")));
  vrd->append_vardecl(new Id("s2"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"int",nullptr,nullptr,vrd);
  st.insert("strcmp",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("trg"),new Type(true,"array",nullptr,new Type(true,"char")));
  vrd->append_vardecl(new Id("src"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("strcpy",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("trg"),new Type(true,"array",nullptr,new Type(true,"char")));
  vrd->append_vardecl(new Id("src"),new Type(true,"array",nullptr,new Type(true,"char")));
  ty = new Type(false,"void",nullptr,nullptr,vrd);
  st.insert("strcat",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("list"),new Type(true,"list",nullptr,new Type(true,"any")));
  ty = new Type(false,"bool",nullptr,nullptr,vrd);
  st.insert("nil?",*ty);

  vrd = new Varlist();
  vrd->append_vardecl(new Id("list"),new Type(true,"list",nullptr,new Type(true,"any")));
  ty = new Type(false,"any",nullptr,nullptr,vrd);
  st.insert("head",*ty);
  vrd = new Varlist();
  vrd->append_vardecl(new Id("list"),new Type(true,"list",nullptr,new Type(true,"any")));
  ty = new Type(false,"list",nullptr,new Type(true,"any"),vrd);
  st.insert("tail",*ty);
}

#endif
