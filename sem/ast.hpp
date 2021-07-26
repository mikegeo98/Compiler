#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "parser.hpp"
#include "lexer.hpp"

void yyerror(const char *msg,...);

inline std::ostream& operator<<(std::ostream &out, Type t) {
  switch (t) {
    case TYPE_int: out << "int"; break;
    case TYPE_bool: out << "bool"; break;
    case TYPE_char: out << "char"; break;
    case TYPE_list: out << "list"; break;
    case TYPE_array: out << "array"; break;
  }
  return out;
}

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

class Expr: public AST { //DES PARAKATW SXOLIO
public:
  virtual int eval() const = 0;
  void type_check(Type t) {
    sem();
    if (type != t) yyerror("Type mismatch");
  }
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
  virtual void printOn(std::ostream &out) const override {
      out << "Expression List(" ;
      for (auto i: expls){
          i.printOn(out);
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
    vector < Expr* > expls;
    int size;
};

class Stmt: public AST {
public:
  virtual void run() const = 0;
};

extern std::vector<int> rt_stack;
extern int lncnt;

class Id: public Expr {
public:
  Id(char v): var(v), offset(-1) {}
  virtual void printOn(std::ostream &out) const override {
    out << "Id(" << var << "@" << offset << ")";
  }
  virtual int eval() const override {
    return rt_stack[offset];
  }
  virtual void sem() override {
    SymbolEntry *e = st.lookup(var);
    type = e->type;
    offset = e->offset;
  }
protected:
  char var;
  int offset;
};

class Const: public Expr {
public:
  Const(int n): num(n) {}
  virtual void printOn(std::ostream &out) const override {
    out << "Const(" << num << ")";
  }
  virtual int eval() const override {
    return num;
  }
  virtual void sem() override {
    type = TYPE_int;
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
  virtual int eval() const override {
    switch (op) {
      case '+': return left->eval() + right->eval();break;
      case '-': return left->eval() - right->eval();break;
      case '*': return left->eval() * right->eval();break;
      case '/': return left->eval() / right->eval();break;
      case T_MOD: return left->eval() % right->eval();break;
      case '=': return left->eval() == right->eval();break;
      case '<': return left->eval() < right->eval();break;
      case '>': return left->eval() > right->eval();break;
      case T_NEQUAL: return left->eval() != right->eval();break;
      case T_SOE: return left->eval() <= right->eval();break;
      case T_GOE: return left->eval() >= right->eval();break;
      case '#': return (left->eval()).append(right->eval());break;
      default: yyerror("unknown operator %d %c",op,op);
    }
    return 0;  // this will never be reached.
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

class Elsif: public Stmt{
public:
    Elsif(Expr *c, Stmt *s1): cond(c), stmt1(s1) {}
    ~Elsif() {delete cond; delete stmt1;}
    virtual void printOn(std::ostream &out) const override {
        out << "Elsif(" << *cond << 
    }
private:
  Expr *cond;
  Stmt *stmt1;
};

class If: public Stmt {//SHITFUCKERY
public:
  If(Expr *c, Stmt *s1, Stmt *s2 = nullptr):
    cond(c), stmt1(s1), stmt2(s2) {}
  ~If() { delete cond; delete stmt1; delete stmt2; }
  virtual void printOn(std::ostream &out) const override {
    out << "If(" << *cond << ", " << *stmt1;
    if (stmt2 != nullptr) out << ", " << *stmt2;
    out << ")";
  }
  virtual void run() const override {
    if (cond->eval())
      stmt1->run();
    else if (stmt2 != nullptr)
      stmt2->run();
  }
  virtual void sem() override {
    cond->type_check(TYPE_bool);
    stmt1->sem();
    if (stmt2 != nullptr) stmt2->sem();
  }
private:
  Expr *cond;
  Stmt *stmt1;
  Stmt *stmt2;
};

class For: public Stmt {//SHITFUCKERY
public:
  For(Expr *e, Stmt *s): expr(e), stmt(s) {}
  ~For() { delete expr; delete stmt; }
  virtual void printOn(std::ostream &out) const override {
    out << "For(" << *expr << ", " << *stmt << ")";
  }
  virtual void run() const override {
    for (int times = expr->eval(), i = 0; i < times; ++i)
      stmt->run();
  }
  virtual void sem() override {
    expr->type_check(TYPE_int);
    stmt->sem();
  }
private:
  Expr *expr;
  Stmt *stmt;
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

private:
  Id *var;
  Type type;
};

class Varlist: public Vardecl {//THE []S ARE WRONG + PASS BY REFERENCE
public:
  Varlist(): var(), size(0) {} // type(),
  ~Varlist(){
    for (Vardecl *d : var) delete d;
    //for (Type *s : type) delete s;
  }
  void append_vardecl(Id *id, Type type) { 
      Vardecl tmp(id,type);
      var.push_back(tmp); 
      //type.push_back(type); 
      size++;
  }
  //void merge(Vardecl *v) {
  //  stmt_list = b->stmt_list;
  //  b->stmt_list.clear();
  //  delete b;
  //}
  

  int get_size(){
      return size;
  }
  virtual void printOn(std::ostream &out) const override {
    out << "Decl(";
    for(int i=0; i<size; i++){
        var[i].printOn(out);
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
};

class Fundecl: public AST {//POSSIBLE FUnCS TYPE
    public:
        Fundecl(Block *block, Id *id, Type type, Varlist *params): block(block), id(id),type(type), params(params){}
        ~Fundecl() {
            delete id;
            if (block!=nullptr)
                delete block;
            delete params;
        }
        virtual void printOn(std::ostream &out) const override
        {
            out<<"Function declaration(";
            id.printOn(out);
            params.printOn(out);
            if (block!=nullptr)
                block.printOn(out);
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
    private:
        Block *block;
        Id *id;
        Type type;
        Varlist *params;
};

class Block: public Stmt {
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
  virtual void run() const override {
    for (int i = 0; i < size; ++i) rt_stack.push_back(0);
    for (Stmt *s : stmt_list) s->run();
    for (int i = 0; i < size; ++i) rt_stack.pop_back();
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