#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <map>
#include <vector>
#include <string.h>
//void yyerror(const char *msg);

class Expr;
class Expls;
class Varlist;

class Type {
  public:
    Type(bool iv=true, std::string ty="", Expls *pa=nullptr, Type *o = nullptr, Varlist *pa2 = nullptr): byref(false),isvar(iv), type(nullptr), params(pa), obj(o), params2(pa2) {
      type = new char[200];
      for (int i=0; i<200; i++){
        type[i] = '0';
      }
      strcpy(type,ty.c_str()); 
      
    }
    Type(const Type &t);
    ~Type();
    bool operator != (Type t);
    int get_param_cnt();
    bool has_params();
    Type *get_param_type(int i);
    void make_fun(Expls *pars);
    void make_fun2(Varlist *pars);
    std::string get_type() const;
    void mbr()
    {
      byref=true;
    }
    bool cbr()
    {
      return byref;
    }
    Type *get_obj()
    {
      return obj;
    }
  private:
    bool byref;
    bool isvar;
    char *type;
    Expls *params;
    Type *obj;
    Varlist *params2;
};

struct SymbolEntry {
  Type *type;
  int nesting, offset;
  SymbolEntry() {}
  SymbolEntry(Type *t, int nst, int ofs) : type(t), nesting(nst), offset(ofs) {}
};

class Scope {
public:
  Scope(int nst) : locals(), nesting(nst), offset(1), size(0) {}
  SymbolEntry *lookup(std::string c) {
    if (locals.find(c) == locals.end())
      return nullptr;
    return &locals[c];
  }
  void insert(std::string c, Type t) {
    if (locals.find(c) != locals.end()){
      fprintf(stderr,"%s\n",c.c_str());
      yyerror("Duplicate variable");
    }
    // printf("%s is the  type in Scope::insert(std::string c, Type t)\n",t.get_type().c_str());
    Type *t2 = new Type(t);
    locals[c] = SymbolEntry(t2, nesting, offset++);
    ++size;
  }
  int getSize() const { return size; }

private:
  std::map<std::string, SymbolEntry> locals;
  int nesting, offset, size;
};

class SymbolTable {
public:
  void openScope() {
    int nesting = scopes.size();
    scopes.push_back(Scope(nesting));
  }
  void closeScope() { scopes.pop_back(); }
  SymbolEntry *lookup(std::string c) {
    for (auto i = scopes.rbegin(); i != scopes.rend(); ++i) {
      SymbolEntry *e = i->lookup(c);
      if (e != nullptr)
        return e;
      // else
      //   // printf("%s not found in scope in SymbolTable::lookup\n",c.c_str());
    }
    yyerror(("Variable not found "+c).c_str());
    return nullptr;
  }
  void insert(std::string c, Type t) { 
    // // printf("%s in SymbolTable::insert\n",c);
    // // std::cout<<c<<" in SymbolTable::insert\n";
    // std::cout<<t.get_type()<<" type in insert::Symbolentry\n";
    scopes.back().insert(c, t); 
  }
  int getSizeOfCurrentScope() const { return scopes.back().getSize(); }
  int getCurrentNesting() const { return scopes.size() - 1; }
  void addFunc(Type type)
  {
    // printf("%s type in SymbolTable::addFunc(Type)\n",type.get_type().c_str());
    funs.push_back(type);
    // printf("%s type in SymbolTable::addFunc(Type)\n",funs[0].get_type().c_str());

  }
  
  void remFunc()
  {
    funs.pop_back();
  }
  Type findLastFunc()
  {
    Type *t=new Type(funs.back());
    return *t;
  }
private:  
  std::vector<Scope> scopes;
  std::vector<Type> funs;
};

inline SymbolTable st;

#endif