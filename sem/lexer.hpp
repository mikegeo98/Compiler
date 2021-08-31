#ifndef __LEXER_HPP__
#define __LEXER_HPP__

extern int lncnt;
int yylex();
void yyerror(const char *msg,...);
// extern int yydebug;

#ifndef YYTOKENTYPE //ONASOY AYTO EINAI LATHOS
# define YYTOKENTYPE
#pragma GCC diagnostic warning "-Wformat";
  enum yytokentype
  {
    T_AND = 258,
    T_OR = 259,
    T_NOT = 260,
    T_MOD = 261,
    T_BOOL = 262,
    T_CHAR = 263,
    T_INT = 264,
    T_LIST = 265,
    T_NEW = 266,
    T_NIL = 267,
    T_ISNIL = 268,
    T_TAIL = 269,
    T_HEAD = 270,
    T_DECL = 271,
    T_DEF = 272,
    T_REF = 273,
    T_RETURN = 274,
    T_FOR = 275,
    T_EXIT = 276,
    T_IF = 277,
    T_ELSE = 278,
    T_ELSEIF = 279,
    T_END = 280,
    T_SKIP = 281,
    T_TRUE = 282,
    T_FALSE = 283,
    T_ID = 284,
    T_CONST = 285,
    T_STRING = 286,
    T_CONCHAR = 287,
    T_DECC = 288,
    T_LPAR = 289,
    T_RPAR = 290,
    T_LBR = 291,
    T_RBR = 292,
    T_COMMA = 293,
    T_ANKA = 294,
    T_SEMI = 295,
    T_NEQUAL = 296,
    T_SOE = 297,
    T_GOE = 298
  };
#endif

#endif
