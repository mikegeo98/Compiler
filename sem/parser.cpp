/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

    #include <cstdio>
    #include "ast.hpp"
    #include "lexer.hpp"

#line 72 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 56 "parser.y" /* yacc.c:355  */

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

#line 179 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   566

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    54,     2,     2,     2,     2,
      35,    37,    57,    55,    43,    56,     2,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    47,
      51,    48,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      36,    38,    40,    42,    44,    46,    49,    52,    53,    59,
      60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    90,    90,    93,    96,    99,   100,   101,   102,   105,
     106,   109,   110,   111,   112,   115,   118,   119,   122,   123,
     126,   127,   130,   131,   132,   133,   134,   137,   140,   143,
     144,   145,   146,   147,   148,   152,   153,   156,   157,   161,
     164,   167,   168,   171,   172,   175,   176,   179,   180,   181,
     182,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   217,   218,   226
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AND", "T_OR", "T_NOT", "T_MOD",
  "\"bool\"", "\"char\"", "\"int\"", "\"list\"", "\"new\"", "\"nil\"",
  "\"nil?\"", "\"tail\"", "\"head\"", "\"decl\"", "\"def\"", "\"ref\"",
  "\"return\"", "\"for\"", "\"exit\"", "\"if\"", "\"else\"", "\"elsif\"",
  "\"end\"", "\"skip\"", "\"true\"", "\"false\"", "T_ID", "T_CONST",
  "T_STRING", "T_CONCHAR", "\":=\"", "T_LPAR", "'('", "T_RPAR", "')'",
  "T_LBR", "'['", "T_RBR", "']'", "T_COMMA", "','", "T_ANKA", "':'",
  "T_SEMI", "';'", "'='", "T_NEQUAL", "'>'", "'<'", "T_SOE", "T_GOE",
  "'#'", "'+'", "'-'", "'*'", "'/'", "PLUS", "MINUS", "$accept", "program",
  "func-def", "rule0", "rule1", "rule2", "header", "rule35", "rule3",
  "formal", "rule4", "type", "func-decl", "var-def", "stmt", "rule5",
  "simple", "simplelist", "call", "rule6", "rule7", "atom", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    40,   290,    41,   291,    91,
     292,    93,   293,    44,   294,    58,   295,    59,    61,   296,
      62,    60,   297,   298,    35,    43,    45,    42,    47,   299,
     300
};
# endif

#define YYPACT_NINF -49

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-49)))

#define YYTABLE_NINF -51

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-51)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,    98,    17,   -49,   -49,   -49,   -49,   -36,    -9,   -10,
     -18,   -49,   219,    94,   152,     9,    24,    32,   219,   -49,
      33,    41,   -17,    98,   152,    49,   193,   -14,   152,   152,
     112,   -49,   -49,     3,   -49,    30,   -49,    56,   -49,   -49,
     -49,   510,    37,   -49,   510,   -49,    65,   -49,   -49,   193,
     -49,    -5,    10,    56,   -49,   -49,   -49,    72,    56,    41,
      81,   -49,   510,   219,   -49,    78,    83,    88,   -49,   -49,
     -49,   -49,   510,   510,   510,   -49,    89,   352,    90,    85,
       2,   448,   -49,   510,   510,   -49,   -49,   -49,   -49,    56,
     383,    95,   510,   510,   510,    27,   -49,   -49,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   510,    37,   -49,   510,   193,   -49,   147,   352,   182,
     -49,   479,   204,   239,   261,   -49,   383,   363,   -49,   416,
     416,   416,   416,   416,   416,    40,     4,     4,   -49,   -49,
      90,   274,   115,   510,   106,   -49,   296,   -49,   -49,   -49,
     -49,    37,   510,   101,   147,   -49,   -49,    99,   330,   103,
     -49,   -49,   193,   193,   193,   127,   115,   130,   -49,   -49,
     -49
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,    23,    24,    22,     0,     0,     0,
       0,     1,     0,     0,     8,     0,     0,     0,     0,    14,
       0,    17,     0,     0,     8,     0,     0,     0,     8,     8,
       0,    25,    26,     0,    13,     0,    15,    21,    27,     5,
       3,     0,     0,    30,     0,    37,    47,    48,     4,     9,
      29,    39,     0,    21,     6,     7,    12,     0,    21,    17,
       0,    19,     0,     0,    74,     0,     0,     0,    68,    69,
      52,    53,     0,     0,     0,    50,    51,    31,    44,     0,
       0,     0,    10,     0,     0,    28,    11,    18,    16,    21,
      70,     0,     0,     0,     0,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,    42,    46,    38,     0,
      20,     0,     0,     0,     0,    54,    71,    72,    61,    62,
      63,    65,    64,    66,    67,    76,    57,    58,    59,    60,
      44,     0,    36,     0,     0,    49,     0,    75,    78,    77,
      43,     0,     0,     0,    46,    41,    73,     0,     0,     0,
      32,    45,     0,     0,     0,     0,    36,     0,    34,    35,
      33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   158,   -49,    63,   -48,   140,   134,   111,   154,
     -44,     6,   -49,   -49,   -49,    25,   -40,    42,   -26,    52,
      55,   -22,    73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    24,    25,    26,    48,     9,    20,    36,    21,
      61,    27,    28,    29,    49,   153,    50,    79,    75,   113,
     144,    76,    77
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    82,    78,    12,    52,    98,    99,    10,   100,    85,
     100,    15,    37,     1,    87,    53,    51,    11,    17,    22,
      52,    16,    16,    51,    33,    16,    13,    52,   -50,    10,
      98,    99,    58,   100,   -50,    14,    22,     4,     5,     6,
       7,    22,    16,    83,    30,   120,   100,   115,    18,    84,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   110,   111,    45,   125,    31,    46,   142,    47,    91,
      34,    16,   140,    32,    40,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,    51,    39,    35,    51,
      52,    54,    55,    52,   107,   108,   109,   110,   111,    60,
      81,     4,     5,     6,     7,     4,     5,     6,     7,    86,
      89,    78,    18,    92,   165,   166,   167,    80,    93,     4,
       5,     6,     7,    94,   159,    51,   160,     8,    84,    52,
      18,    19,   114,   112,   121,    90,    51,    51,    51,   152,
      52,    52,    52,   155,   162,    95,    96,    97,   164,    56,
      98,    99,   168,   100,   117,   170,   118,   119,     3,     4,
       5,     6,     7,    38,    57,   122,   123,   124,    23,     1,
      88,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,    98,    99,   141,   100,    59,
     143,   169,   150,   157,   146,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     0,    98,    99,   161,
     100,     0,    41,    42,    43,    44,   154,     0,     0,    45,
       0,     0,    46,   145,    47,   158,     4,     5,     6,     7,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   147,    98,    99,     0,   100,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,    98,    99,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   148,    98,    99,     0,
     100,     0,     0,     0,     0,     0,     0,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   149,    98,
      99,     0,   100,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   151,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    98,    99,     0,   100,   156,     0,     0,
       0,     0,     0,     0,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,    98,    99,     0,   100,     0,
       0,     0,     0,     0,     0,     0,    98,     0,     0,   100,
       0,     0,     0,     0,     0,   163,     0,     0,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   100,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,    63,
      64,    65,    66,    67,   -51,   -51,   -51,   -51,   -51,   -51,
     107,   108,   109,   110,   111,    68,    69,    46,    70,    47,
      71,     0,     0,    72,    62,   116,     0,     0,     0,     0,
      63,    64,    65,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,     0,    68,    69,    46,    70,
      47,    71,     0,     0,    72,    62,     0,     0,     0,     0,
      31,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,     0,    68,    69,    46,
      70,    47,    71,     0,     0,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,    74
};

static const yytype_int16 yycheck[] =
{
      26,    49,    42,    39,    26,     3,     4,     1,     6,    53,
       6,    29,    29,    17,    58,    29,    42,     0,    12,    13,
      42,    39,    39,    49,    18,    39,    35,    49,    33,    23,
       3,     4,    29,     6,    39,    45,    30,     7,     8,     9,
      10,    35,    39,    33,    35,    89,     6,    45,    18,    39,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    57,    58,    26,    37,    41,    29,   115,    31,    63,
      37,    39,   112,    41,    25,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,   112,    24,    47,   115,
     112,    28,    29,   115,    54,    55,    56,    57,    58,    43,
      35,     7,     8,     9,    10,     7,     8,     9,    10,    37,
      29,   151,    18,    35,   162,   163,   164,    44,    35,     7,
       8,     9,    10,    35,    23,   151,    25,    29,    39,   151,
      18,    37,    47,    43,    39,    62,   162,   163,   164,    24,
     162,   163,   164,    37,    45,    72,    73,    74,    45,    37,
       3,     4,    25,     6,    81,    25,    83,    84,     0,     7,
       8,     9,    10,    23,    30,    92,    93,    94,    16,    17,
      59,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     3,     4,   114,     6,    35,
      43,   166,   140,   151,   121,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,     3,     4,   154,
       6,    -1,    19,    20,    21,    22,   143,    -1,    -1,    26,
      -1,    -1,    29,    41,    31,   152,     7,     8,     9,    10,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    37,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    37,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     3,     4,    -1,     6,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    11,
      12,    13,    14,    15,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,     5,    37,    -1,    -1,    -1,    -1,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    27,    28,    29,    30,
      31,    32,    -1,    -1,    35,     5,    -1,    -1,    -1,    -1,
      41,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    62,    63,     7,     8,     9,    10,    29,    67,
      72,     0,    39,    35,    45,    29,    39,    72,    18,    37,
      68,    70,    72,    16,    63,    64,    65,    72,    73,    74,
      35,    41,    41,    72,    37,    47,    69,    29,    67,    65,
      25,    19,    20,    21,    22,    26,    29,    31,    66,    75,
      77,    79,    82,    29,    65,    65,    37,    68,    29,    70,
      43,    71,     5,    11,    12,    13,    14,    15,    27,    28,
      30,    32,    35,    55,    56,    79,    82,    83,    77,    78,
      83,    35,    66,    33,    39,    71,    37,    71,    69,    29,
      83,    72,    35,    35,    35,    83,    83,    83,     3,     4,
       6,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    43,    80,    47,    45,    37,    83,    83,    83,
      71,    39,    83,    83,    83,    37,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      77,    83,    66,    43,    81,    41,    83,    37,    37,    37,
      80,    47,    24,    76,    83,    37,    41,    78,    83,    23,
      25,    81,    45,    45,    45,    66,    66,    66,    25,    76,
      25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    72,    72,    73,    74,    75,
      75,    75,    75,    75,    75,    76,    76,    77,    77,    77,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     2,     2,     2,     2,     0,     1,
       2,     5,     4,     4,     3,     2,     3,     0,     4,     3,
       3,     0,     1,     1,     1,     3,     4,     2,     3,     1,
       1,     2,     6,     9,     9,     5,     0,     1,     3,     1,
       2,     5,     3,     3,     0,     3,     0,     1,     1,     4,
       1,     1,     1,     1,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       2,     3,     3,     5,     1,     4,     3,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 90 "parser.y" /* yacc.c:1646  */
    { initSt();st.openScope();(yyvsp[0].fundecl)->sem(); st.closeScope();st.closeScope();}
#line 1470 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 93 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-3].fundecl)->add_block((yyvsp[-1].block)); (yyval.fundecl) = (yyvsp[-3].fundecl); }
#line 1476 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 96 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].block)->merge((yyvsp[0].block)); (yyval.block) = (yyvsp[-1].block); }
#line 1482 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 99 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block)->append_decl((yyvsp[-1].fundecl)); (yyval.block) = (yyvsp[0].block); }
#line 1488 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block)->append_decl((yyvsp[-1].fundecl)); (yyval.block) = (yyvsp[0].block); }
#line 1494 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 101 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block)->append_decl((yyvsp[-1].varlist)); (yyval.block) = (yyvsp[0].block); }
#line 1500 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 102 "parser.y" /* yacc.c:1646  */
    { (yyval.block) = new Block(); }
#line 1506 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 105 "parser.y" /* yacc.c:1646  */
    {Block* b = new Block(); b->append_stmt((yyvsp[0].stmt)); (yyval.block) = b; }
#line 1512 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 106 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block)->append_stmt((yyvsp[-1].stmt)); (yyval.block) = (yyvsp[0].block); }
#line 1518 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 109 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-4].type)->make_fun2((yyvsp[-1].varlist)); (yyval.fundecl) = new Fundecl(new Id((yyvsp[-3].var)),(yyvsp[-4].type),(yyvsp[-1].varlist));}
#line 1524 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 110 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-3].type)->make_fun(nullptr); (yyval.fundecl) = new Fundecl(new Id((yyvsp[-2].var)),(yyvsp[-3].type),nullptr);}
#line 1530 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 111 "parser.y" /* yacc.c:1646  */
    {(yyval.fundecl) = new Fundecl(new Id((yyvsp[-3].var)),new Type(false,"void",nullptr,nullptr,(yyvsp[-1].varlist)),(yyvsp[-1].varlist)); }
#line 1536 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 112 "parser.y" /* yacc.c:1646  */
    { (yyval.fundecl) = new Fundecl(new Id((yyvsp[-2].var)),new Type(false,"void"),nullptr);}
#line 1542 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 115 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].varlist)->merge((yyvsp[-1].varlist)); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1548 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].varlist)->merge((yyvsp[-1].varlist)); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1554 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyval.varlist) = new Varlist(); }
#line 1560 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 122 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].varlist)->append_vardecl(new Id((yyvsp[-1].var)));(yyvsp[0].varlist)->fixtypes((yyvsp[-2].type),true); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1566 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].varlist)->append_vardecl(new Id((yyvsp[-1].var))); (yyvsp[0].varlist)->fixtypes((yyvsp[-2].type)); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1572 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].varlist)->append_vardecl(new Id((yyvsp[-1].var))); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1578 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval.varlist) = new Varlist(); }
#line 1584 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type(true,"int"); }
#line 1590 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 131 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type(true,"bool"); }
#line 1596 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type(true,"char"); }
#line 1602 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type(true,"array", nullptr, (yyvsp[-2].type), nullptr);}
#line 1608 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 134 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type(true,"list",nullptr, (yyvsp[-1].type), nullptr);}
#line 1614 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.fundecl) = (yyvsp[0].fundecl); }
#line 1620 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 140 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].varlist)->append_vardecl(new Id((yyvsp[-1].var))); (yyvsp[0].varlist)->fixtypes((yyvsp[-2].type)); (yyval.varlist) = (yyvsp[0].varlist); }
#line 1626 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1632 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Return(); }
#line 1638 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Return((yyvsp[0].expr)); }
#line 1644 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 146 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new If((yyvsp[-4].expr), (yyvsp[-2].block)); }
#line 1650 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new If((yyvsp[-7].expr), (yyvsp[-5].block), (yyvsp[-1].block), (yyvsp[-4].elsif)); }
#line 1656 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new For((yyvsp[-7].block),(yyvsp[-5].expr),(yyvsp[-3].block),(yyvsp[-1].block));}
#line 1662 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].elsif)->append_elsif((yyvsp[-3].expr),(yyvsp[-1].block)); (yyval.elsif) = (yyvsp[0].elsif); }
#line 1668 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.elsif) = new Elsif(); }
#line 1674 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new Stmt(); }
#line 1680 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 158 "parser.y" /* yacc.c:1646  */
    { 
  (yyval.stmt) = new Ass((yyvsp[-2].atom),(yyvsp[0].expr)); 
}
#line 1688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].funcal); }
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 164 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block)->append_stmt((yyvsp[-1].stmt)); (yyval.block) = (yyvsp[0].block);}
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].expls) -> append_exprls((yyvsp[-2].expr)); (yyval.funcal) = new Funcal(new Id((yyvsp[-4].var)),(yyvsp[-1].expls)); }
#line 1706 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.funcal) = new Funcal(new Id((yyvsp[-2].var))); }
#line 1712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].block) -> append_stmt((yyvsp[-1].stmt)); (yyval.block) = (yyvsp[0].block); }
#line 1718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 172 "parser.y" /* yacc.c:1646  */
    {(yyval.block) = new Block();}
#line 1724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 175 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].expls) -> append_exprls((yyvsp[-1].expr)); (yyval.expls) = (yyvsp[0].expls); }
#line 1730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.expls) = new Expls(); }
#line 1736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.atom) = new Id((yyvsp[0].var)); }
#line 1742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.atom) = new ConstString((yyvsp[0].str)); }
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.atom) = new Arracc((yyvsp[-3].atom),(yyvsp[-1].expr)); }
#line 1754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.atom) = (yyvsp[0].funcal); }
#line 1760 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].atom); }
#line 1766 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstInt((yyvsp[0].num)); }
#line 1772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstChar((yyvsp[0].chr)); }
#line 1778 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1784 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new MonOp('+', (yyvsp[0].expr)); }
#line 1790 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new MonOp('-', (yyvsp[0].expr)); }
#line 1796 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 1802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 1808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 193 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 1814 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 1820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_MOD, (yyvsp[0].expr)); }
#line 1826 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 196 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 1832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_NEQUAL, (yyvsp[0].expr)); }
#line 1838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 1844 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 1850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_SOE, (yyvsp[0].expr)); }
#line 1856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_GOE, (yyvsp[0].expr)); }
#line 1862 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstBool((yyvsp[0].Bool)); }
#line 1868 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 203 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstBool((yyvsp[0].Bool)); }
#line 1874 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new MonOp(T_NOT, (yyvsp[0].expr)); }
#line 1880 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_AND, (yyvsp[0].expr)); }
#line 1886 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr), T_OR, (yyvsp[0].expr)); }
#line 1892 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Arinit((yyvsp[-3].type),(yyvsp[-1].expr)); }
#line 1898 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstList((yyvsp[0].op)); }
#line 1904 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 210 "parser.y" /* yacc.c:1646  */
    { 
    Expls* a = new Expls(); 
    a -> append_exprls((yyvsp[-1].expr)); 
    char* c=new char[10];
    strcpy(c,"nil?");
    (yyval.expr) = new Funcal(new Id(c),a); //(false, "bool", a),a); COULD BE BETTER
  }
#line 1916 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new BinOp((yyvsp[-2].expr), '#', (yyvsp[0].expr)); }
#line 1922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 219 "parser.y" /* yacc.c:1646  */
    { 
    Expls* a = new Expls(); 
    a -> append_exprls((yyvsp[-1].expr)); 
    char* c=new char[10];
    strcpy(c,"head");
    (yyval.expr) = new Funcal(new Id(c),a); //COULD BE BETTER
  }
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 227 "parser.y" /* yacc.c:1646  */
    { 
    Expls* a = new Expls(); 
    a -> append_exprls((yyvsp[-1].expr)); 
    char* c=new char[10];
    strcpy(c,"tail");
    (yyval.expr) = new Funcal(new Id(c),a); //COULD BE BETTER
  }
#line 1946 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1950 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 237 "parser.y" /* yacc.c:1906  */


int main() {
  // yydebug=1;
  int result = yyparse();
  std::ios::sync_with_stdio(false);
  if (result == 0) printf("Success.\n");
  return result;
}
