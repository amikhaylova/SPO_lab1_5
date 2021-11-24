/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sql_grammar.yacc"

#include <stdio.h>
#include <string.h>
#include "../sql_lexical_analyzer/lex.yy.h"

#define CORRECT_SYNTAX_MESSAGE "Syntax Correct\n"
#define YYERROR_VERBOSE 1

int yylex(void);
int yyparse(void);
int yychar;

void yyerror(const char *str)
{
        fprintf(stderr,"Error: %s\n",str);
}

int yywrap()
{
        return 1;
}

struct sql_node * new_sql_node (
    int node_type,
    char * text,
    struct sql_node * first,
    struct sql_node * next
) {
  struct sql_node * sql_node = malloc (sizeof (struct sql_node));
  sql_node->node_type = node_type;
  sql_node->text = text;
  sql_node->first = first;
  sql_node->next = next;
  return sql_node;
}

struct sql_node * root;


#line 111 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    QUERY = 258,                   /* QUERY  */
    SELECT = 259,                  /* SELECT  */
    INSERT = 260,                  /* INSERT  */
    UPDATE = 261,                  /* UPDATE  */
    CREATE = 262,                  /* CREATE  */
    DELETE = 263,                  /* DELETE  */
    DROP = 264,                    /* DROP  */
    FROM = 265,                    /* FROM  */
    IDENTIFIERS = 266,             /* IDENTIFIERS  */
    WHERE = 267,                   /* WHERE  */
    AND = 268,                     /* AND  */
    VALUES = 269,                  /* VALUES  */
    INTO = 270,                    /* INTO  */
    SET = 271,                     /* SET  */
    TABLE = 272,                   /* TABLE  */
    TABLE_NAME = 273,              /* TABLE_NAME  */
    STATEMENT = 274,               /* STATEMENT  */
    TABLE_DEF = 275,               /* TABLE_DEF  */
    ALL = 276,                     /* ALL  */
    TEXT_TYPE = 277,               /* TEXT_TYPE  */
    NUMBER_TYPE = 278,             /* NUMBER_TYPE  */
    INT_TYPE = 279,                /* INT_TYPE  */
    UINT_TYPE = 280,               /* UINT_TYPE  */
    COLUMN_NAME = 281,             /* COLUMN_NAME  */
    SET_VALUE = 282,               /* SET_VALUE  */
    SET_VALUES = 283,              /* SET_VALUES  */
    CONDITION = 284,               /* CONDITION  */
    COLUMN_TYPE = 285,             /* COLUMN_TYPE  */
    ITEMS = 286,                   /* ITEMS  */
    COLUMN = 287,                  /* COLUMN  */
    COLUMNS = 288,                 /* COLUMNS  */
    IDENTIFIER = 289               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define QUERY 258
#define SELECT 259
#define INSERT 260
#define UPDATE 261
#define CREATE 262
#define DELETE 263
#define DROP 264
#define FROM 265
#define IDENTIFIERS 266
#define WHERE 267
#define AND 268
#define VALUES 269
#define INTO 270
#define SET 271
#define TABLE 272
#define TABLE_NAME 273
#define STATEMENT 274
#define TABLE_DEF 275
#define ALL 276
#define TEXT_TYPE 277
#define NUMBER_TYPE 278
#define INT_TYPE 279
#define UINT_TYPE 280
#define COLUMN_NAME 281
#define SET_VALUE 282
#define SET_VALUES 283
#define CONDITION 284
#define COLUMN_TYPE 285
#define ITEMS 286
#define COLUMN 287
#define COLUMNS 288
#define IDENTIFIER 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "sql_grammar.yacc"

    struct sql_node * node;
    int number;
    char * text;

#line 238 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_QUERY = 3,                      /* QUERY  */
  YYSYMBOL_SELECT = 4,                     /* SELECT  */
  YYSYMBOL_INSERT = 5,                     /* INSERT  */
  YYSYMBOL_UPDATE = 6,                     /* UPDATE  */
  YYSYMBOL_CREATE = 7,                     /* CREATE  */
  YYSYMBOL_DELETE = 8,                     /* DELETE  */
  YYSYMBOL_DROP = 9,                       /* DROP  */
  YYSYMBOL_FROM = 10,                      /* FROM  */
  YYSYMBOL_IDENTIFIERS = 11,               /* IDENTIFIERS  */
  YYSYMBOL_WHERE = 12,                     /* WHERE  */
  YYSYMBOL_AND = 13,                       /* AND  */
  YYSYMBOL_VALUES = 14,                    /* VALUES  */
  YYSYMBOL_INTO = 15,                      /* INTO  */
  YYSYMBOL_SET = 16,                       /* SET  */
  YYSYMBOL_TABLE = 17,                     /* TABLE  */
  YYSYMBOL_TABLE_NAME = 18,                /* TABLE_NAME  */
  YYSYMBOL_STATEMENT = 19,                 /* STATEMENT  */
  YYSYMBOL_TABLE_DEF = 20,                 /* TABLE_DEF  */
  YYSYMBOL_ALL = 21,                       /* ALL  */
  YYSYMBOL_TEXT_TYPE = 22,                 /* TEXT_TYPE  */
  YYSYMBOL_NUMBER_TYPE = 23,               /* NUMBER_TYPE  */
  YYSYMBOL_INT_TYPE = 24,                  /* INT_TYPE  */
  YYSYMBOL_UINT_TYPE = 25,                 /* UINT_TYPE  */
  YYSYMBOL_COLUMN_NAME = 26,               /* COLUMN_NAME  */
  YYSYMBOL_SET_VALUE = 27,                 /* SET_VALUE  */
  YYSYMBOL_SET_VALUES = 28,                /* SET_VALUES  */
  YYSYMBOL_CONDITION = 29,                 /* CONDITION  */
  YYSYMBOL_COLUMN_TYPE = 30,               /* COLUMN_TYPE  */
  YYSYMBOL_ITEMS = 31,                     /* ITEMS  */
  YYSYMBOL_COLUMN = 32,                    /* COLUMN  */
  YYSYMBOL_COLUMNS = 33,                   /* COLUMNS  */
  YYSYMBOL_IDENTIFIER = 34,                /* IDENTIFIER  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_40_ = 40,                       /* '>'  */
  YYSYMBOL_41_ = 41,                       /* '<'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_query = 43,                     /* query  */
  YYSYMBOL_query_type = 44,                /* query_type  */
  YYSYMBOL_select_query = 45,              /* select_query  */
  YYSYMBOL_insert_query = 46,              /* insert_query  */
  YYSYMBOL_create_query = 47,              /* create_query  */
  YYSYMBOL_drop_query = 48,                /* drop_query  */
  YYSYMBOL_update_query = 49,              /* update_query  */
  YYSYMBOL_delete_query = 50,              /* delete_query  */
  YYSYMBOL_from_stmt = 51,                 /* from_stmt  */
  YYSYMBOL_into_stmt = 52,                 /* into_stmt  */
  YYSYMBOL_add_table_stmt = 53,            /* add_table_stmt  */
  YYSYMBOL_table_name = 54,                /* table_name  */
  YYSYMBOL_items = 55,                     /* items  */
  YYSYMBOL_columns = 56,                   /* columns  */
  YYSYMBOL_values = 57,                    /* values  */
  YYSYMBOL_identifiers = 58,               /* identifiers  */
  YYSYMBOL_identifier = 59,                /* identifier  */
  YYSYMBOL_column_type_val = 60,           /* column_type_val  */
  YYSYMBOL_column_type = 61,               /* column_type  */
  YYSYMBOL_column_name = 62,               /* column_name  */
  YYSYMBOL_column_def = 63,                /* column_def  */
  YYSYMBOL_column_defs = 64,               /* column_defs  */
  YYSYMBOL_condition = 65,                 /* condition  */
  YYSYMBOL_set_value = 66,                 /* set_value  */
  YYSYMBOL_set_values = 67                 /* set_values  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   68

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  87

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      41,    39,    40,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    64,    66,    68,    70,    72,    74,    76,
      80,    85,    90,    94,    97,   100,   108,   114,   117,   120,
     125,   128,   129,   131,   134,   137,   139,   142,   145,   148,
     151,   154,   157,   160,   163,   167,   169,   172,   176,   180,
     184,   188,   190
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "QUERY", "SELECT",
  "INSERT", "UPDATE", "CREATE", "DELETE", "DROP", "FROM", "IDENTIFIERS",
  "WHERE", "AND", "VALUES", "INTO", "SET", "TABLE", "TABLE_NAME",
  "STATEMENT", "TABLE_DEF", "ALL", "TEXT_TYPE", "NUMBER_TYPE", "INT_TYPE",
  "UINT_TYPE", "COLUMN_NAME", "SET_VALUE", "SET_VALUES", "CONDITION",
  "COLUMN_TYPE", "ITEMS", "COLUMN", "COLUMNS", "IDENTIFIER", "';'", "'('",
  "')'", "','", "'='", "'>'", "'<'", "$accept", "query", "query_type",
  "select_query", "insert_query", "create_query", "drop_query",
  "update_query", "delete_query", "from_stmt", "into_stmt",
  "add_table_stmt", "table_name", "items", "columns", "values",
  "identifiers", "identifier", "column_type_val", "column_type",
  "column_name", "column_def", "column_defs", "condition", "set_value",
  "set_values", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    59,    40,    41,    44,    61,
      62,    60
};
#endif

#define YYPACT_NINF (-46)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       3,   -18,   -11,    -6,    16,    26,    20,    39,     7,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,    35,   -46,     8,
      -6,   -12,   -46,    31,    -6,   -46,    -6,    -6,   -46,   -46,
      -6,    36,    15,   -46,    17,    15,    37,    15,    18,    38,
     -46,   -46,    15,   -46,    15,    19,    21,    13,    22,    43,
      15,    15,   -14,   -46,    24,   -46,   -46,    15,    15,    15,
      15,   -46,    -5,    25,    27,   -46,    15,    15,    15,   -46,
      28,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
      15,   -46,   -46,   -46,   -46,   -46,   -46
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       6,     5,     7,     4,     8,    21,    27,     0,    22,    25,
       0,     0,    20,     0,     0,    13,     0,     0,     1,     2,
       0,     9,     0,    18,     0,     0,     0,     0,     0,     0,
      14,    17,     0,    26,     0,     0,     0,     0,    41,     0,
       0,     0,     0,    10,     0,    24,    23,     0,     0,     0,
       0,    33,     0,    35,     0,    16,     0,     0,     0,    12,
       0,    40,    42,    15,    29,    28,    30,    31,    32,    34,
       0,    19,    37,    38,    39,    11,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,    14,   -46,   -46,     1,     0,   -37,   -46,   -46,
     -46,   -46,   -21,   -45,   -46,     9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    31,
      21,    25,    23,    17,    36,    54,    55,    19,    78,    79,
      62,    63,    64,    53,    48,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    18,    34,    15,    20,    52,    65,     1,     2,     3,
       4,     5,     6,    61,    52,    73,    16,    74,    75,    76,
      77,    71,    47,    52,    35,    66,    67,    68,    22,    82,
      83,    84,    43,    24,    33,    45,    26,    27,    38,    28,
      39,    40,    29,    61,    41,    30,    32,    37,    42,    16,
      51,    46,    58,    44,    50,    60,    56,    57,    70,    86,
      59,    69,     0,    80,    81,    85,     0,     0,    72
};

static const yytype_int8 yycheck[] =
{
      37,     1,    14,    21,    15,    42,    51,     4,     5,     6,
       7,     8,     9,    50,    51,    60,    34,    22,    23,    24,
      25,    58,    59,    60,    36,    39,    40,    41,    34,    66,
      67,    68,    32,    17,    20,    35,    10,    17,    24,     0,
      26,    27,    35,    80,    30,    10,    38,    16,    12,    34,
      12,    14,    39,    36,    36,    12,    37,    36,    57,    80,
      38,    37,    -1,    38,    37,    37,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    43,    44,    45,
      46,    47,    48,    49,    50,    21,    34,    55,    58,    59,
      15,    52,    34,    54,    17,    53,    10,    17,     0,    35,
      10,    51,    38,    54,    14,    36,    56,    16,    54,    54,
      54,    54,    12,    58,    36,    58,    14,    59,    66,    67,
      36,    12,    59,    65,    57,    58,    37,    36,    39,    38,
      12,    59,    62,    63,    64,    65,    39,    40,    41,    37,
      57,    59,    67,    65,    22,    23,    24,    25,    60,    61,
      38,    37,    59,    59,    59,    37,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    44,    44,    44,    44,    45,
      45,    46,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    55,    56,    57,    58,    58,    59,    60,    60,
      60,    60,    61,    62,    63,    64,    64,    65,    65,    65,
      66,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       5,     7,     6,     2,     3,     6,     5,     2,     2,     5,
       1,     1,     1,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* query: query_type ';'  */
#line 60 "sql_grammar.yacc"
    {(yyval.node) = new_sql_node(QUERY, "query", (yyvsp[-1].node), NULL);
    printf(CORRECT_SYNTAX_MESSAGE);
    root = (yyval.node);}
#line 1335 "y.tab.c"
    break;

  case 3: /* query_type: select_query  */
#line 64 "sql_grammar.yacc"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1341 "y.tab.c"
    break;

  case 4: /* query_type: update_query  */
#line 66 "sql_grammar.yacc"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1347 "y.tab.c"
    break;

  case 5: /* query_type: create_query  */
#line 68 "sql_grammar.yacc"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1353 "y.tab.c"
    break;

  case 6: /* query_type: insert_query  */
#line 70 "sql_grammar.yacc"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1359 "y.tab.c"
    break;

  case 7: /* query_type: drop_query  */
#line 72 "sql_grammar.yacc"
                       {(yyval.node) = (yyvsp[0].node);}
#line 1365 "y.tab.c"
    break;

  case 8: /* query_type: delete_query  */
#line 74 "sql_grammar.yacc"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1371 "y.tab.c"
    break;

  case 9: /* select_query: SELECT items from_stmt  */
#line 77 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(SELECT, "select", (yyvsp[-1].node), NULL);
                (yyval.node)->first->next = (yyvsp[0].node);}
#line 1378 "y.tab.c"
    break;

  case 10: /* select_query: SELECT items from_stmt WHERE condition  */
#line 81 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(SELECT, "select", (yyvsp[-3].node), NULL);
                (yyval.node)->first->next = (yyvsp[-2].node);
                (yyval.node)->first->next->next = (yyvsp[0].node);}
#line 1386 "y.tab.c"
    break;

  case 11: /* insert_query: INSERT into_stmt columns VALUES '(' values ')'  */
#line 86 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(INSERT, "insert", (yyvsp[-5].node), NULL);
                (yyval.node)->first->next = (yyvsp[-4].node);
                (yyval.node)->first->next->next = (yyvsp[-1].node);}
#line 1394 "y.tab.c"
    break;

  case 12: /* insert_query: INSERT into_stmt VALUES '(' values ')'  */
#line 91 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(INSERT, "insert", (yyvsp[-4].node), NULL);
                (yyval.node)->first->next = (yyvsp[-1].node);}
#line 1401 "y.tab.c"
    break;

  case 13: /* create_query: CREATE add_table_stmt  */
#line 95 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(CREATE, "create", (yyvsp[0].node), NULL);}
#line 1407 "y.tab.c"
    break;

  case 14: /* drop_query: DROP TABLE table_name  */
#line 98 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(DROP, "drop", (yyvsp[0].node), NULL);}
#line 1413 "y.tab.c"
    break;

  case 15: /* update_query: UPDATE table_name SET set_values WHERE condition  */
#line 101 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(UPDATE, "update", (yyvsp[-4].node), NULL);
                struct sql_node *  set_values_node = new_sql_node(SET_VALUES, "set_values", (yyvsp[-2].node), NULL);
                (yyval.node)->next = set_values_node;
                 struct sql_node *  condition_node = new_sql_node(CONDITION, "condition", (yyvsp[0].node), NULL);
                (yyval.node)->next->next = condition_node;}
#line 1423 "y.tab.c"
    break;

  case 16: /* delete_query: DELETE FROM table_name WHERE condition  */
#line 109 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(DELETE, "delete", (yyvsp[-2].node), NULL);
                struct sql_node *  condition_node = new_sql_node(CONDITION, "condition", (yyvsp[0].node), NULL);
                (yyval.node)->next = condition_node;
                }
#line 1432 "y.tab.c"
    break;

  case 17: /* from_stmt: FROM table_name  */
#line 115 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(FROM, "from", (yyvsp[0].node), NULL);}
#line 1438 "y.tab.c"
    break;

  case 18: /* into_stmt: INTO table_name  */
#line 118 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(INTO, "into", (yyvsp[0].node), NULL);}
#line 1444 "y.tab.c"
    break;

  case 19: /* add_table_stmt: TABLE table_name '(' column_defs ')'  */
#line 121 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(TABLE, "table", (yyvsp[-3].node), NULL);
                    struct sql_node *  node = new_sql_node(COLUMNS, "columns", (yyvsp[-1].node), NULL);
                    (yyval.node)->first->next = node;}
#line 1452 "y.tab.c"
    break;

  case 20: /* table_name: IDENTIFIER  */
#line 126 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(TABLE, (yyvsp[0].text), NULL, NULL);}
#line 1458 "y.tab.c"
    break;

  case 21: /* items: ALL  */
#line 128 "sql_grammar.yacc"
           { (yyval.node) = new_sql_node(ALL, "all", NULL, NULL);}
#line 1464 "y.tab.c"
    break;

  case 22: /* items: identifiers  */
#line 129 "sql_grammar.yacc"
                     {(yyval.node) = new_sql_node(ITEMS, "values", (yyvsp[0].node), NULL);}
#line 1470 "y.tab.c"
    break;

  case 23: /* columns: '(' identifiers ')'  */
#line 132 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(COLUMNS, "columns", (yyvsp[-1].node), NULL);}
#line 1476 "y.tab.c"
    break;

  case 24: /* values: identifiers  */
#line 135 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(VALUES, "values", (yyvsp[0].node), NULL);}
#line 1482 "y.tab.c"
    break;

  case 25: /* identifiers: identifier  */
#line 138 "sql_grammar.yacc"
                {(yyval.node) = (yyvsp[0].node);}
#line 1488 "y.tab.c"
    break;

  case 26: /* identifiers: identifier ',' identifiers  */
#line 140 "sql_grammar.yacc"
                { (yyvsp[-2].node)->next = (yyvsp[0].node);}
#line 1494 "y.tab.c"
    break;

  case 27: /* identifier: IDENTIFIER  */
#line 143 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(IDENTIFIER, (yyvsp[0].text), NULL, NULL);}
#line 1500 "y.tab.c"
    break;

  case 28: /* column_type_val: NUMBER_TYPE  */
#line 146 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(NUMBER_TYPE, "NUM", NULL, NULL);}
#line 1506 "y.tab.c"
    break;

  case 29: /* column_type_val: TEXT_TYPE  */
#line 149 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(TEXT_TYPE, "TEXT", NULL, NULL);}
#line 1512 "y.tab.c"
    break;

  case 30: /* column_type_val: INT_TYPE  */
#line 152 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(INT_TYPE, "INT", NULL, NULL);}
#line 1518 "y.tab.c"
    break;

  case 31: /* column_type_val: UINT_TYPE  */
#line 155 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(UINT_TYPE, "UINT", NULL, NULL);}
#line 1524 "y.tab.c"
    break;

  case 32: /* column_type: column_type_val  */
#line 158 "sql_grammar.yacc"
                { (yyval.node) = new_sql_node(COLUMN_TYPE, "column_type", (yyvsp[0].node), NULL);}
#line 1530 "y.tab.c"
    break;

  case 33: /* column_name: identifier  */
#line 161 "sql_grammar.yacc"
                {(yyval.node) = new_sql_node(COLUMN_NAME, "column_name", (yyvsp[0].node), NULL);}
#line 1536 "y.tab.c"
    break;

  case 34: /* column_def: column_name column_type  */
#line 164 "sql_grammar.yacc"
                    {(yyval.node) = new_sql_node(COLUMN, "column_def", (yyvsp[-1].node), NULL);
                    (yyvsp[-1].node)->next = (yyvsp[0].node);}
#line 1543 "y.tab.c"
    break;

  case 36: /* column_defs: column_def ',' column_defs  */
#line 170 "sql_grammar.yacc"
                {(yyvsp[-2].node)->next = (yyvsp[0].node);}
#line 1549 "y.tab.c"
    break;

  case 37: /* condition: identifier '=' identifier  */
#line 173 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(CONDITION, "=", (yyvsp[-2].node), NULL);
            (yyval.node)->first->next = (yyvsp[0].node);}
#line 1556 "y.tab.c"
    break;

  case 38: /* condition: identifier '>' identifier  */
#line 177 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(CONDITION, ">", (yyvsp[-2].node), NULL);
             (yyval.node)->first->next = (yyvsp[0].node);}
#line 1563 "y.tab.c"
    break;

  case 39: /* condition: identifier '<' identifier  */
#line 181 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(CONDITION, "<", (yyvsp[-2].node), NULL);
             (yyval.node)->first->next = (yyvsp[0].node);}
#line 1570 "y.tab.c"
    break;

  case 40: /* set_value: identifier '=' identifier  */
#line 185 "sql_grammar.yacc"
            {(yyval.node) = new_sql_node(SET_VALUE, "=", (yyvsp[-2].node), NULL);
            (yyval.node)->first->next = (yyvsp[0].node);}
#line 1577 "y.tab.c"
    break;

  case 42: /* set_values: set_value ',' set_values  */
#line 191 "sql_grammar.yacc"
                {(yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 1583 "y.tab.c"
    break;


#line 1587 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 193 "sql_grammar.yacc"


void print_sql_tree(struct sql_node * curr, int level) {
    if (curr == NULL) {
        return;
    }
    for(int i = 0; i < level; i++) printf("  ");
    printf("|_%s %d\n", curr->text, curr->node_type);
    print_sql_tree(curr->first, level + 1);
    print_sql_tree(curr->next, level);
}

int parse_string(const char* in, struct sql_node * node) {
  set_input_string(in);
  int rv = yyparse();
  *node = *root;
  printf("\n");
  end_lexical_scan();
  return rv;
}

main_1()
{
        yyparse();
}
