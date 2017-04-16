%option noyywrap
%option noinput
%option nounput
%{
#include <stdio.h>
#include "tokens.h"

extern int yylval;

%}

%%

[0-9]+	{
		yylval=atoi(yytext);
		return num_token;
				}
[-+*/()]	{ return *yytext; }
[ \t]	{ }
\n		{	return eoi_token; }
.		{
			fprintf(stderr, "Lexical error: unknown character '%c'\n", *yytext);
			exit(EXIT_FAILURE);
		}
%%
