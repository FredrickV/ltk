#include "g_local.h"
#include "fred.h"

void ftrace(char *p)
{
FILE *fp;
short i = 0;

if(!ltk_trace->value)
    return;

fp = fopen("LTK\\LTK\\log.txt","a");

if(!fp)
  return;

Traces++;
fprintf(fp,"%d",Traces);fprintf(fp," ");
fprintf(fp,p);
fclose(fp);
}
