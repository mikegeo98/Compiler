#ifndef __LEXER_HPP__
#define __LEXER_HPP__

extern int lncnt;
int yylex();
void yyerror(const char *msg);

#endif
