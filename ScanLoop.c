/*ScanLoop.c for recognizing identifiers and integer literals*/
#include<stdio.h>
#include<ctype.h>
int in_char, c;
while((in_char=getchar())!=EOF)
if(isspace(in_char))
continue;
else if(isalpha(in_char))
{
for(c=getchar();isalnum(c)||c=='_';c=getchar());
ungetc(c,stdin);
return ID;
}
else if(isdigit(in_char))
{
while(isdigit((c=getchar())));
ungetc(c,stdin);
return INTLITERAL;
}
else
lexical_error(in_char);
}
