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
%token T_PUTI "puti"
%token T_PUTB "putb"
%token T_PUTC "putc"
%token T_PUTS "puts"
%token T_GETI "geti"
%token T_GETB "getb"
%token T_GETC "getc"
%token T_GETS "gets"
%token T_ABS "abs"
%token T_ORD "ord"
%token T_CHR "chr"
%token T_STRLEN "strlen"
%token T_STRCMP "strcmp"
%token T_STRCPY "strcpy"
%token T_STRCAT "strcat"
%token T_ID 
%token T_CONST 
%token T_STRING 
%token T_CONCHAR 
%token T_NEQUAL T_SOE T_GOE 
%token T_DECC ":="

%left "or"
%left "and"
%right "not" //PREFIX - NEEDS FIXING
%nonassoc '=' T_NEQUAL '>' '<' T_SOE T_GOE
%right '#'
%left '+' '-'
%left '*' '/' T_MOD
%right '+' '-' //PREFIX - NEEDS FIXING

%expect 1

%%
program:
    func-def
;
func-def:
    "def" header ":" rule1 rule2 "end"

rule1:
  func-­def rule1
| func-­decl rule1
| var­-def rule1
|  %empty

rule2:
  stmt 
| stmt rule2

header:
  type T_ID "(" formal rule3 ")"

rule3:
  ";" formal
| %empty

formal:
  "ref" type T_ID rule4

rule4:
  "," T_ID
| %empty 

type: 
  "int"
| "bool"
| "char"
| type "[" "]" 
| "list" "[" type "]"

funcdecl:
  "decl" header

var­def:
  type T_ID rule4

stmt:
  simple
| "exit"
| "return" expr
| "if" expr ":" rule2 
| "if" expr ":" rule2 rule5 "else" ":" rule2 "end"
| "for" simplelist ";" expr ";" simplelist ":" rule2 "end"

rule5:
  "elsif" ⟨expr⟩ ":" rule2
| %empty

simple:
  "skip"
| atom ":=" expr
| call

simplelist:
  simple rule6

call:
  T_ID "(" expr rule7 ")"

rule6:
  "," simple
| %empty

rule7:
  "," expr
| %empty

atom:
  T_ID
| stringliteral
| atom "[" expr "]"
| call

expr:
  atom
| T_CONST 
| T_CONCHAR
| "(" expr ")"
| ("+" | "-") expr
| expr ( "+" | "-" | "*" | "/" | "mod" ) expr
| expr ( "=" | "<>" | "<" | ">" | "<=" | ">=" ) expr
| "true" 
| "false" 
| "not" expr 
| expr ( "and" | "or" ) expr
| "new" type "[" expr "]" 
| "nil" 
| "nil?" "(" expr ")"
| expr "#" expr 
| "head" "(" expr ")" 
| "tail" "(" expr ")"



%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}