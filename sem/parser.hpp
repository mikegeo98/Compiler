/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
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
    T_GOE = 298,
    PLUS = 299,
    MINUS = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 56 "parser.y" /* yacc.c:1909  */

  Block *block;
  Stmt *stmt;
  Expr *expr;
  Expls *expls;
  Fundecl *fundecl;
  Funcal *funcal;
  Varlist *varlist;
  Type *type; 
  char *var;
  char chr;
  int num;
  int op;
  int Bool;
  char *str;
  Elsif *elsif;
  Atom *atom;
  Id *id;
  ConstChar *constchar;

#line 121 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
