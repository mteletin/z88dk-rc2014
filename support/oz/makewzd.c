/*
 *   Binary to WZD conversion utility
 *   this tool comes from the OZ-7xx Developement Kit
 *   by Alexander R. Pruss 
 *
 *      If (and only if) you use any of the read*() or write*()
 *      functions and publically release your program, you MUST apply to
 *      Alexander R. Pruss (ap85@georgetown.edu) for an owner ID for
 *      your program and you MUST link an owner ID into your program
 *      with makewzd or equivalent.  For in-house testing, you may use
 *      the ID of 65535, but not for public release.  Owner IDs will be
 *      granted free of charge.  Specify what programs you plan to write
 *      and how many IDs you'd like (you can get up to ten each time you
 *      apply). It is illegal to use either an owner ID not assigned to
 *      you or the ID of 65535 for publically released programs.  A
 *      program counts as publically released if it is posted in a
 *      publically available way (e.g., a web site) or sold to the
 *      public.
 *      There is, however, one exception to this rule.  If you write a
 *      program that processes files generated by other applications
 *      which duly have owner IDs assigned, e.g., a program that reads
 *      font files, or a file manager, or a multi-purpose binary file
 *      viewer, you do not need to apply for an owner ID.
 *
 *   $Id: makewzd.c,v 1.2 2005/05/25 17:18:30 stefano Exp $
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
#define O_BINARY 0
#define __unix__
#else
#ifndef __unix__
#include <io.h>
#endif
#endif

#include <fcntl.h>



char *randname(void);
unsigned long getlength(char *s);

/* BASIC ICON */
/*static char thehead[]={
0x1A, 0xFC, 0x0F, 0x02, 0x0C, 0x01, 0x0A, 0xFF, 0x09, 0x01, 0x0D, 0x3D,
0x0D,
0x45, 0x0D, 0x3D, 0x0D, 0x45, 0x0D, 0x3D, 0x0D, 0x01, 0x0D, 0xFF, 0x07,
0x00, 0x00 };
*/
/* C Program Icon */
/*static char thehead[]={
0x1A, 0x00, 0x00, 0x78, 0x00, 0x84, 0x00, 0x02, 0x00, 0xe2, 0x03, 0x22,
0x04,
0x22, 0x04, 0xe2, 0x03, 0x22, 0x00, 0xa4, 0x00, 0x78, 0x00, 0x20, 0x00,
0x00, 0x00 };
*/
/* New C Program Icon */
static char thehead[]={
0x1a, 0xFF, 0x03, 0x01, 0x06, 0xF1, 0x0E, 0xF9, 0x09, 0x99, 0x09, 0x19, 0x08, 0x19,
0x08, 0x99, 0x09, 0xF9, 0x09, 0xF1, 0x08, 0x01, 0x08, 0xFF, 0x0F, 0x00, 0x00 };

#ifndef __unix__
unsigned long getlength(char *s)
{
   int h;
   unsigned long l;
   if(!(h=open(s,O_BINARY|O_RDONLY))) return 0;
   l=filelength(h);
   close(h);
   return l;
}
#else
unsigned long getlength(char *s)
{
    unsigned long l;
    FILE *fh=fopen(s,"rb");
    if(!fh) return 0;
    fseek(fh,0,SEEK_END);
    l=ftell(fh);
    fclose(fh);
    return l;
}
#endif

char *randname()
{
    static char name[9];
    int i;
    int r;
    name[0]='B';
    for(i=1; i<8; i++)
    {
        r=rand()%(26+10);
	if(r<10) name[i]=(char)(r+'0'); else name[i]=(char)(r+'A'-10);
    }
    name[8]=0;
    return name;
}

main(argc,OrigArgv)
int argc;
char **OrigArgv;
{
	FILE *in, *out;
    int c;
	char name[128];
    char *rn;
    char locname[12];
    char **argv;
	unsigned i;
    unsigned short owner,oldowner;
    time_t s;
    srand(time(&s));
    argv=OrigArgv;
    if(argc>1 && argv[1][0]=='-')
    {
      sscanf(argv[1]+1,"%hu",&owner);
      argv++;
      argc--;
    }
    else owner=65535;
    if(argc!=2 && argc!=3 && argc!=4 && argc!=5)
    {
        fprintf(stderr,"makewzd [-ownerid] filename [Title [(\"Description\" | @descfile) [iconfile]]]\n\n"
            "  Creates filename.wzd from filename.bin, adding Title and\n"
            "  Description if specified, and loading in an iconfile if provided.\n"
            "  The default title is the filename.\n");
        return 1;
    }
    strcpy(name,argv[1]);
    strcat(name,".bin");
    if(!getlength(name) || NULL==(in=fopen(name,"rb")))
    {
		fprintf(stderr,"File `%s' is either unaccessible or zero length.\n",name);
		return 4;
    }
    strcpy(name,argv[1]);
    strcat(name,".wzd");
	if(NULL==(out=fopen(name,"wb")))
	{
		fprintf(stderr,"Cannot open `%s' for writing.\n",name);
		return 5;
	}
	fprintf(out,"<SHARP WZD DATA>\r\n"
	"<DATA TYPE>\r\n"
	"MY PROGRAMS\r\n"
	"</DATA TYPE>\r\n"
	"<TITLE>\r\n"
	"%s\r\n"
	"</TITLE>\r\n"
	"<CATEGORY>\r\n"
	"PROGRAM\r\n"
	"</CATEGORY>\r\n"
    "<DESCRIPTION>\r\n", ( (argc==2)?argv[1]: argv[2] ));
    if(argc>=4 && argv[3][0]=='@')
    {
        FILE *desc=fopen(argv[3]+1,"r");
        if(desc==NULL)
        {
            fprintf(stderr,"Cannot open %s.\n",argv[3]+1);
            return 6;
        }
        while(-1!=(c=fgetc(desc)))
          if(c=='\n') fputs("\r\n",out); else fputc(c,out);
        fputs("\r\n",out);
        fclose(desc);
    }
    else fprintf(out,"%s\r\n",(argc==2)?argv[1]:( (argc==3)?argv[2]: argv[3] ));
    fprintf(out,
	"</DESCRIPTION>\r\n"
	"<CONTENT>\r\n"
	"BIN_PROG_1\r\n"
	"</CONTENT>\r\n"
	"<DATA>\r\n"
    "PFILE:%s.BAS\r\n"
	"</DATA>\r\n"
    "<BIN>\r\n",
    rn=randname());
    if(argc==5)
    {
        FILE *icon=fopen(argv[4],"rb");
        if(NULL==icon)
        {
            fprintf(stderr,"Cannot open icon file.\n");
            fclose(out);
            unlink(name);
            return 17;
        }
        while(-1!=(c=getc(icon))) fputc(c,out);
        fclose(icon);
    }
    else
    for(i=0; i<sizeof(thehead)/sizeof(char); i++) fputc(thehead[i],out);
    for(i=0; i<0x14 && -1!=(c=fgetc(in)); i++)  fputc(c,out);
    if(c==-1)
    {
        fprintf(stderr,"Error reading!\n");
        fclose(out);
        unlink(name);
    }
    fread(locname,12,1,in);
    if(strcmp(locname,"BFILNAMEBAS"))
    {
        fprintf(stderr,"Warning: Old init code, no filename record.\n");
        fwrite(locname,12,1,out);
    }
    else
    {
        fwrite(rn,8,1,out);
        fwrite("BAS",4,1,out);
    }
    fread(&oldowner,2,1,in);
    if(oldowner!=65535)
    {
        fprintf(stderr,"Warning: No room for owner ID.\n");
        owner=oldowner;
    }
    fwrite(&owner,2,1,out);
    while(-1!=(c=fgetc(in))) fputc(c,out);
    fclose(in);
	fclose(out);
	return 0;
}


