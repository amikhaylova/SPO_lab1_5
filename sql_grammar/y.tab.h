/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 141 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
