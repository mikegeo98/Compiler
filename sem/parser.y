%{
    #include <cstdio>
    #include "ast.hpp"
    #include "lexer.hpp"
%}
%token T_AND T_OR T_NOT
%token T_MOD 
%token T_BOOL "bool"
%token T_CHAR "char" 
%token T_INT "int" 
%token T_LIST "list"
%token T_NEW "new"
%token<var> T_NIL "nil"
%token<var> T_ISNIL "nil?"
%token<var> T_TAIL "tail"
%token<var> T_HEAD "head"
%token T_DECL "decl"
%token T_DEF "def"
%token T_REF "ref"
%token T_RETURN "return"
%token T_FOR "for"
%token T_EXIT "exit"
%token T_IF "if"
%token T_ELSE "else"
%token T_ELSEIF "elsif"
%token T_END "end"
%token T_SKIP "skip"
%token<Bool> T_TRUE "true"
%token<Bool> T_FALSE "false"

%token<var> T_ID 
%token<num> T_CONST 
%token<str> T_STRING 
%token<chr> T_CONCHAR 
%token<op> T_DECC ":="
%token<op> T_LPAR '('
%token<op> T_RPAR ')'
%token<op> T_LBR '['
%token<op> T_RBR ']'
%token<op> T_COMMA ','
%token<op> T_ANKA ':'
%token<op> T_SEMI ';'

%left<op> T_OR
%left<op> T_AND
%right<op> T_NOT //PREFIX - NEEDS FIXING
%nonassoc<op> '=' T_NEQUAL '>' '<' T_SOE T_GOE
%right<op> '#'
%left<op> '+' '-' 
%left<op> '*' '/' T_MOD
//%right '+' '-' //PREFIX - NEEDS FIXING

//%expect 8
//%expect-rr 1

%union {
  Block *block;
  Stmt *stmt;
  Expr *expr;
  Expls *expls;
  Fundecl *fundecl;
  Funcal *funcal;
//  formalist *formalist;
//  formal *formal;
  Varlist *varlist;
  Type *type; //ASTERAKI POU DEN YPIRXE
  char *var;
  char chr;
  int num;
  int op;
  char *Bool;
  char *str;
  Elsif *elsif;
  Atom *atom;
  Id *id;
  ConstChar *constchar;
}

%type<block> rule1 rule2 simplelist rule6 rule0
%type<stmt> stmt simple // EKXWRISI SE SYNARTISI??
%type<elsif> rule5
%type<expr> expr 
%type<funcal> call 
%type<expls> rule7
%type<fundecl> func-decl func-def program header
%type<varlist> rule4 var-def rule35 formal rule3
%type<type> type
%type<atom> atom

%%
program:
    func-def { $$ = $1; }
;
func-def:
    "def" header ':' rule0 "end" { $2->add_block($4); $$ = $2; }
;
rule0:
  rule1 rule2 { $1->merge($2); $$ = $1; }
;
rule1:
  func-def rule1 { $2->append_decl($1); $$ = $2; }
| func-decl rule1 { $2->append_decl($1); $$ = $2; }
| var-def rule1 { $2->append_decl($1); $$ = $2; }
|  %empty { $$ = new Block(); }
;
rule2:
  stmt {Block* b = new Block(); b->append_stmt($1); $$ = b; }
| stmt rule2 { $2->append_stmt($1); $$ = $2; }
;
header:
  type T_ID '(' rule35 ')' {$1->make_fun($4); $$ = new Fundecl(new Id($2),$1,$4);}
| type T_ID '(' ')' {$1->make_fun(new Expls()); $$ = new Fundecl(new Id($2),$1,nullptr);}
| T_ID '(' rule35 ')' {$$ = new Fundecl(new Id($1),new Type(false,"void",$3),$3); }
| T_ID '(' ')' {$$ = new Fundecl(new Id($1),new Type(false,"void"),nullptr); }
;
rule35:
  formal rule3 { $2->merge($1); $$ = $2; }
;
rule3:
  ';' formal rule3 { $3->merge($2); $$ = $3; }
| %empty { $$ = new Varlist(); }
;
formal:
  "ref" type T_ID rule4 { $4->fixtypes($2); $$ = $4; }
| type T_ID rule4 { $3->fixtypes($1); $$ = $3; }
;
rule4:
  ',' T_ID rule4 { $3->append_vardecl(new Id($2)); $$ = $3; }
| %empty { $$ = new Varlist(); }
;
type: 
  "int"  { $$ = new Type(true,"int"); }
| "bool" { $$ = new Type(true,"bool"); }
| "char" { $$ = new Type(true,"char"); }
| type '[' ']' { $$ = new Type(true,"array", nullptr, &($1));}
| "list" '[' type ']' { $$ = new Type(true,"list",nullptr,&($3));}
;
func-decl:
  "decl" header { $$ = $2; }
;
var-def:
  type T_ID rule4 { $3->fixtypes($1); $$ = $3; }
;
stmt:
  simple { $$ = $1; }
| "exit" { $$ = new Return(); }
| "return" expr { $$ = new Return($2); }
| "if" expr ':' rule2 "end" { $$ = new If($2, $4); }
| "if" expr ':' rule2 rule5 "else" ':' rule2 "end" { $$ = new If($2, $4, $8, $5); } 
| "for" simplelist ';' expr ';' simplelist ':' rule2 "end" { $$ = new For($2,$4,$6,$8);}
;

rule5:
  "elsif" expr ':' rule2 rule5 { $5->append_elsif($2,$4); $$ = $5; }
| %empty { $$ = new Elsif(); }
;
simple:
  "skip" { $$ = new Stmt(); }
| atom ":=" expr 
{ 
  /*Atom atm; 
  atm.cnstbool = nullptr;
  atm.cnstchar = nullptr;
  atm.cnstint = nullptr;
  atm.cnststring = nullptr;
  atm.id = nullptr;
  atm.cnstlist = nullptr;
  atm.funcall = nullptr;
  
  
  switch(($1->get_kind()).c_str())
  {
    case "ConstInt": atm.cnstint = $1; break;
    case "ConstChar": atm.cnstchar = $1; break;
    case "ConstString": atm.cnststring = $1; break;
    case "ConstBool": atm.cnstbool = $1; break;
    case "ConstList": atm.cnstlist = $1; break;
    case "Id": atm.id = $1; break;
    case "Funcal": atm.funcall = $1; break; 
    default: yyerror("atom has problem");
  } */
  $$ = new Ass($1,$3); 
}
| call { $$ = $1; }
;
simplelist:
  simple rule6 { $2->append_stmt($1); $$ = $2;}
;
call:
  T_ID '(' expr rule7 ')' { $4 -> append_exprls($3); $$ = new Funcal(new Id($1),$4); }
| T_ID '(' ')' { $$ = new Funcal(new Id($1)); }
;
rule6:
  ',' simple rule6 { $3 -> append_stmt($2); $$ = $3; }
| %empty {$$ = new Block();}
;
rule7:
  ',' expr rule7  {$3 -> append_exprls($2); $$ = $3; }
| %empty          { $$ = new Expls(); }
;
atom:
  T_ID { $$ = new Id($1); }
| T_STRING { $$ = new ConstString($1); }
| atom '[' expr ']' { $$ = new Arracc($1,$3); }  
| call { $$ = $1; }
;
expr:
  atom { $$ = $1; }
| T_CONST { $$ = new ConstInt($1); }
| T_CONCHAR { $$ = new ConstChar($1); }
| '(' expr ')' { $$ = $2; }
| '+' expr  { $$ = new MonOp($1, $2); }
| '-' expr  { $$ = new MonOp($1, $2); }
| expr  '+' expr { $$ = new BinOp($1, $2, $3); }
| expr '-' expr { $$ = new BinOp($1, $2, $3); }
| expr '*' expr { $$ = new BinOp($1, $2, $3); }
| expr '/' expr { $$ = new BinOp($1, $2, $3); }
| expr T_MOD expr { $$ = new BinOp($1, $2, $3); }
| expr '=' expr { $$ = new BinOp($1, $2, $3); }
| expr T_NEQUAL expr { $$ = new BinOp($1, $2, $3); }
| expr '<' expr { $$ = new BinOp($1, $2, $3); }
| expr '>' expr { $$ = new BinOp($1, $2, $3); }
| expr T_SOE expr { $$ = new BinOp($1, $2, $3); }
| expr T_GOE expr { $$ = new BinOp($1, $2, $3); }
| "true" { $$ = new ConstBool($1); }
| "false" { $$ = new ConstBool($1); }
| T_NOT expr { $$ = new MonOp($1, $2); }
| expr T_AND expr { $$ = new BinOp($1, $2, $3); }
| expr T_OR  expr { $$ = new BinOp($1, $2, $3); }
| "new" type '[' expr ']' 
| "nil" { $$ = new ConstList($1); }
| "nil?" '(' expr ')'   
  { 
    Expls* a = new Expls(); 
    a -> append_exprls($3); 
    $$ = new Funcal(new Id($1),a); //(false, "bool", a),a); COULD BE BETTER
  } 
| expr '#' expr { $$ = new BinOp($1, $2, $3); }
| "head" '(' expr ')' 
  { 
    Expls* a = new Expls(); 
    a -> append_exprls($3); 
    $$ = new Funcal(new Id($1),a); //COULD BE BETTER
  } 
| "tail" '(' expr ')'
  { 
    Expls* a = new Expls(); 
    a -> append_exprls($3); 
    $$ = new Funcal(new Id($1),a); //COULD BE BETTER
  } 
;


%%

// void yyerror (const char * msg)
// {
//   fprintf(stderr,
//   "syntax error in lines %d: %s\n",lncnt, msg);
//   exit(1);
// }

int main() {
  printf("ok \n");
  yydebug=1;
  int result = yyparse();
  // printf("%d 42\n",result);
  if (result == 0) printf("Success.\n");
  return result;
}