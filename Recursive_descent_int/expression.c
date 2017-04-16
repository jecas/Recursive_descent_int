#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokens.h"

int yylex(); //lexical analysis
int lookahead; //current token
int yylval; //value of current token

int error(char *s){
  fprintf(stderr, "%s\n", s);
  exit(EXIT_FAILURE);
}

int E();
int EP(int u);
int T();
int TP(int u);
int F();

int E(){
  if(lookahead==num_token || lookahead=='('){
    printf("E=>TE'\n");
    return EP(T());
  }
  else
    error("E(): I except number or ( on input");
  return -1;
}

int EP(int u){
  if(lookahead=='+'){
    printf("E'=>+TE'\n");
    lookahead=yylex();
    return EP(u+T());
  }
  else if(lookahead=='-'){
    printf("E'=>-TE'\n");
    lookahead=yylex();
    return EP(u-T());
  }
  else if(lookahead==eoi_token || lookahead==')'){
    printf("E'=>eps\n");
    return u;
  }
  else
    error("E'(): I except + or - or end of input token or )");
  return -1;
}

int T(){
  if(lookahead==num_token || lookahead=='('){
    printf("T=>FT'\n");
    return TP(F());
  }
  else
    error("T(): I except number or ( on input");
  return -1;
}

int TP(int u){
  if(lookahead=='*'){
    printf("T'=>*FT'\n");
    lookahead=yylex();
    return TP(u*F());
  }
  else if(lookahead=='/'){
    printf("T'=>/FT'\n");
    lookahead=yylex();
    return TP(u/F());
  }
  else if(lookahead=='+' || lookahead=='-' || lookahead==eoi_token || lookahead==')'){
    printf("T'=>eps\n");
    return u;
  }
  else
    error("T'(): I except * or / or end of input token or )");
  return -1;
}

int F(){
  if(lookahead==num_token){
    printf("F=>num\n");
    lookahead=yylex();
    return yylval;
  }
  else if(lookahead=='('){
    printf("F=>(E)\n");
    lookahead=yylex();
    int tmp=E();

    if(lookahead!=')')
      error("F(): I except ) on input");
    lookahead=yylex();
    return tmp;
  }
  else
    error("F(): I except number or ( on input");
  return -1;
}

int main(){
  int tmp;
  lookahead=yylex();
  tmp=E();
  if(lookahead!=eoi_token)
    error("Override tokens on input");
  printf("Value of expression is %lf\n", tmp);
  return 0;
}
