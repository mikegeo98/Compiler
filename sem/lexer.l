%option noyywrap

%{
    #include "lexer.hpp"
    #include "ast.hpp"
    #include "parser.hpp"
    int lncnt = 1;
    int nstcmt = 0; 
%}

L [a-zA-Z]
LC [a-zA-Z_0-9?] 
D [0-9]
W [ \t\r]


%x COMMENT

%%
"and" {return T_AND;}
"or" {return T_OR;}
"not" {return T_NOT;}
"mod" {return T_MOD;}

"bool" {return T_BOOL;}
"char" {return T_CHAR;}
"int" {return T_INT;}

"list" {return T_LIST;}
"new" {return T_NEW;}
"nil" {return T_NIL;}
"nil?" {return T_ISNIL;}
"tail" {return T_TAIL;}
"head" {return T_HEAD;}

"decl" {return T_DECL;}
"def" {return T_DEF;}
"ref" {return T_REF;}
"return" {return T_RETURN;}

"for" {return T_FOR;}
"exit" {return T_EXIT;}
"if" {return T_IF;}
"else" {return T_ELSE;}
"elsif" {return T_ELSEIF;}
"end" {return T_END;}
"skip" {return T_SKIP;}

"true" {return T_TRUE;}
"false" {return T_FALSE;}

{L}{LC}* {yylval.var = (char*)malloc(strlen(yytext) + 1);strcpy(yylval.var,yytext);return T_ID;}
{D}+ {yylval.num = atoi(yytext); return T_CONST;}
["]([^"\\\n]|\\.|\\\n)*["] {yylval.str = (char*)malloc(strlen(yytext) + 1);strcpy(yylval.str,yytext); return T_STRING;}
['][^']['] {yylval.chr = yytext[0];return T_CONCHAR;}
['][\\][0nrt'"\\]['] {yylval.chr = yytext[0]; return T_CONCHAR;}
['][\\][x][0-9a-f][0-9a-f]['] {yylval.chr = yytext[0]; return T_CONCHAR;}


[\+\-\*\/\#\=\<\>\(\)\,\;\:\[\]]   { return yytext[0]; }
"<>" {return T_NEQUAL;}
"<=" {return T_SOE;}
">=" {return T_GOE;}
":=" {return T_DECC;}
[%][^\n]* {/*do nth*/}

{W}+ {/*do nth*/}
"\n" {lncnt++;}

"<*" {BEGIN(COMMENT);nstcmt++;}
<COMMENT>"*>" {if(--nstcmt==0)BEGIN(INITIAL);}
<COMMENT>"<*" {nstcmt++;}
<COMMENT>[^\n*] {/*do nth*/}
<COMMENT>\n {lncnt++;}
<COMMENT>[*] {/*do nth*/}
. {printf ("ERROR Line %d\n",lncnt);}

%%
void yyerror(const char *msg,...)
{
  fprintf(stderr,"%s %d\n",msg,lncnt);
  exit(1);
}