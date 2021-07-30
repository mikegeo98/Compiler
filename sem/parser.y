%{
    #include <cstdio>
    #include "lexer.hpp"
%}
%token T_AND T_OR T_NOT
%token T_MOD 
%token T_BOOL "bool"
%token T_CHAR "char" 
%token T_INT "int" 
%token T_LIST "list"
%token T_NEW "new"
%token T_NIL "nil"
%token T_ISNIL "nil?"
%token T_TAIL "tail"
%token T_HEAD "head"
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
%token T_TRUE "true"
%token T_FALSE "false"

%token<var> T_ID 
%token<num> T_CONST 
%token<str> T_STRING 
%token<str> T_CONCHAR 
%token<op> T_NEQUAL "<>"
%token<op> T_SOE "<="
%token<op> T_GOE ">="
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
  block *block;
  stmt *stmt;
  Expr *expr;
  Exprlis *expls;
  fundecl *fundecl;
  fundef *fundef;
  header *header;
  formalist *formalist;
  formal *formal;
  varlist *varlist;
  Type type;
  char var;
  int num;
  string str;
}

%type<block> program rule1 rule2 simplelist rule6
%type<stmt> stmt rule5 simple // EKXWRISI SE SYNARTISI??
%type<expr> expr call atom
%type<expls> rule7
%type<fundecl> func-decl 
%type<fundef> func-def
%type<header> header
%type<formalist> rule3
%type<formal> formal
%type<varlist> rule4 var-def
%type<type> type

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
  stmt { b = new Block(); b->append_stmt($1); $$ = b; }
| stmt rule2 { $2->append_stmt($1); $$ = $2; }
;
header:
  type T_ID '(' rule35 ')' { new Fundecl($2,$1,$4); }
| type T_ID '(' ')' { new Fundecl($2,$1,nullptr)}
| T_ID '(' rule35 ')' { new Fundecl($1,TYPE_void,$3); }
| T_ID '(' ')' { new Fundecl($1,TYPE_void,nullptr); }
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
  ',' T_ID rule4 { $3->append_vardecl($2); $$ = $3; }
| %empty { $$ = new Varlist(); }
;
type: 
  "int"
| "bool"
| "char"
| type '[' ']' 
| "list" '[' type ']'
;
func-decl:
  "decl" header { $$ = $2}
;
var-def:
  type T_ID rule4 { $3->fixtypes($1); $$ = $3; }
;
stmt:
  simple { $$ = $1; }
| "exit" { $$ = new Return(); }
| "return" expr { $$ = new Return($2); }
| "if" expr ':' rule2 "end" { $$ = new If($2, $4); }
| "if" expr ':' rule2 rule5 "else" ':' rule2 "end" { $$ = new If($2, $4, $8, $5);/*elpizoume me to $5 na parei olo to elsif na to xwsei mesa*/ } 
| "for" simplelist ';' expr ';' simplelist ':' rule2 "end" { $$ = new For($2,$4,$6,$8);}
;

rule5:
  "elsif" expr ':' rule2 rule5 { $5->append_elsif($2,$4); $$ = $5; }
| %empty { $$ = new Elsif()}
;
simple:
  "skip" { $$ = new Stmt(); }
| atom ":=" expr 
| call { $$ = $1; }
;
simplelist:
  simple rule6 {$2->append_stmt($1);$$ = $2;}
;
call:
  T_ID '(' expr rule7 ')' { $4 -> append_exprls($3); $$ = new Funcal($1,$4); }
| T_ID '(' ')' { $$ = new Funcal($1); }
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
| T_STRING { $$ = new Const($1); }
| atom '[' expr ']' 
| call
;
expr:
  atom
| T_CONST { $$ = new Const($1); }
| T_CONCHAR { $$ = new Const($1); }
| '(' expr ')' { $$ = $2; }
| '+' expr  { $$ = new MonOp($1, $2); }
| '-' expr  { $$ = new MonOp($1, $2); }
| expr  '+' expr { $$ = new BinOp($1, $2, $3); }
| expr '-' expr { $$ = new BinOp($1, $2, $3); }
| expr '*' expr { $$ = new BinOp($1, $2, $3); }
| expr '/' expr { $$ = new BinOp($1, $2, $3); }
| expr T_MOD expr { $$ = new BinOp($1, $2, $3); }
| expr '=' expr { $$ = new BinOp($1, $2, $3); }
| expr "<>" expr { $$ = new BinOp($1, $2, $3); }
| expr '<' expr { $$ = new BinOp($1, $2, $3); }
| expr '>' expr { $$ = new BinOp($1, $2, $3); }
| expr "<=" expr { $$ = new BinOp($1, $2, $3); }
| expr ">=" expr { $$ = new BinOp($1, $2, $3); }
| "true" { $$ = new Const($1); }
| "false" { $$ = new Const($1); }
| T_NOT expr { $$ = new MonOp($1, $2); }
| expr T_AND expr { $$ = new BinOp($1, $2, $3); }
| expr T_OR  expr { $$ = new BinOp($1, $2, $3); }
| "new" type '[' expr ']' 
| "nil" { $$ = new Const($1); }
| "nil?" '(' expr ')'
| expr '#' expr { $$ = new BinOp($1, $2, $3); }
| "head" '(' expr ')' 
| "tail" '(' expr ')'
;


%%

// void yyerror (const char * msg)
// {
//   fprintf(stderr,
//   "syntax error in lines %d: %s\n",lncnt, msg);
//   exit(1);
// }

int main() {
  printf("ok\n");
  yydebug=1;
  int result = yyparse();
  // printf("%d 42\n",result);
  if (result == 0) printf("Success.\n");
  return result;
}