%option noyywrap

%{
    #include "lexer.hpp"
    #include "ast.hpp"
    // #include "parser.hpp"
    // #define T_eof 0
    // #define T_AND 1001
    // #define T_OR 1002
    // #define T_NOT 1003
    // #define T_MOD 1004
    // #define T_BOOL 1005
    // #define T_CHAR 1006
    // #define T_INT 1007
    // #define T_LIST 1008
    // #define T_NEW 1009
    // #define T_NIL 1010
    // #define T_ISNIL 1011
    // #define T_TAIL 1012
    // #define T_HEAD 1013
    // #define T_DECL 1014
    // #define T_DEF 1015
    // #define T_REF 1016
    // #define T_RETURN 1017
    // #define T_FOR 1018
    // #define T_EXIT 1019
    // #define T_IF 1020
    // #define T_ELSE 1021
    // #define T_ELSEIF 1022
    // #define T_END 1023
    // #define T_SKIP 1024
    // #define T_TRUE 1025
    // #define T_FALSE 1026
    // #define T_PUTI 1027
    // #define T_PUTB 1028
    // #define T_PUTC 1029
    // #define T_PUTS 1030
    // #define T_GETI 1031
    // #define T_GETB 1032
    // #define T_GETC 1033
    // #define T_GETS 1034
    // #define T_ABS 1035
    // #define T_ORD 1036
    // #define T_CHR 1037
    // #define T_STRLEN 1038
    // #define T_STRCMP 1039
    // #define T_STRCPY 1040
    // #define T_STRCAT 1041
    // #define T_ID 1042
    // #define T_CONST 1043
    // #define T_STRING 1044
    // #define T_CONCHAR 1045
    // #define T_NEQUAL 1046
    // #define T_SOE 1047
    // #define T_GOE 1048
    // #define T_DECC 1049 
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
"def" {printf("def\n");return T_DEF;}
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

{L}{LC}* {printf("%d T_ID/n",T_ID);return T_ID;}
{D}+ {return T_CONST;}
["][^"]*["] {return T_STRING;}
['][^']['] {return T_CONCHAR;}
['][\\][0nrt'"\\]['] {return T_CONCHAR;}
['][\\][x][0-9a-f][0-9a-f]['] {return T_CONCHAR;}


[\+\-\*\/\#\=\<\>\(\)\,\;\:\[\]]   { printf("%c symbol\n",yytext[0]); return yytext[0]; }
"<>" {return T_NEQUAL;}
"<=" {return T_SOE;}
">=" {return T_GOE;}
":=" {return T_DECC;}
[%][^\n]* {printf ("%s\n",yytext);/*do nth*/}

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