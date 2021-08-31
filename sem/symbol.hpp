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
    Type(bool iv=true, std::string ty="", Expls *pa=nullptr, Type *o = nullptr, Varlist *pa2 = nullptr): isvar(iv), type(nullptr), params(pa), obj(o), params2(pa2) {type = new char[200];strcpy(type,ty.c_str());}
    Type(const Type &t);
    ~Type();
    // Type &operator = (Type &ty)
    bool operator != (Type t);
    int get_param_cnt();
    bool has_params();
    Type *get_param_type(int i);
    void make_fun(Expls *pars);
    void make_fun2(Varlist *pars);
    std::string get_type();

  private:
    bool isvar;
    char *type;
    Expls *params;
    Type *obj;
    Varlist *params2;
};

struct SymbolEntry {
  Type type;
  int nesting, offset;
  SymbolEntry() {}
  SymbolEntry(Type t, int nst, int ofs) : type(t), nesting(nst), offset(ofs) {}
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
    if (locals.find(c) != locals.end())
      yyerror("Duplicate variable");
    locals[c] = SymbolEntry(t, nesting, offset++);
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
    }
    yyerror("Variable not found");
    return nullptr;
  }
  void insert(std::string c, Type t) { scopes.back().insert(c, t); }
  int getSizeOfCurrentScope() const { return scopes.back().getSize(); }
  int getCurrentNesting() const { return scopes.size() - 1; }
  void addFunc(Type type)
  {
    funs.push_back(type);
  }
  void remFunc()
  {
    funs.pop_back();
  }
  Type findLastFunc()
  {
    Type t=new Type(funs.back());
    return t;
  }
private:  
  std::vector<Scope> scopes;
  std::vector<Type> funs;
};

inline SymbolTable st;

#endif