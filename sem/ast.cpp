#include "ast.hpp"


Type::~Type()  { delete type; delete params; delete obj; delete params2;}

bool Type::operator != (Type t)
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

int Type::get_param_cnt()
{
  if (params!= nullptr)
    return params->get_size();
  if (params2!= nullptr)
    return params2->get_size();
  yyerror("no params");
  
}

bool Type::has_params()
{
  return !isvar;
}

Type Type::get_param_type(int i)
{
  if (params!= nullptr)
    return params->get_type(i);
  if (params2!= nullptr)
    return params2->get_type(i);
  yyerror("no params");
}

std::string Type::get_type()
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

void Type::make_fun(Expls *pars)
{
  params = pars;
  isvar = false;
}

void Type::make_fun2(Varlist *pars)
{
  params2 = pars;
  isvar = false;
}