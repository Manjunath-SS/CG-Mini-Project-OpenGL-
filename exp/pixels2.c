#include<stdio.h>
#include<math.h>
#include<stdbool.h>
void main()
{
    FILE *mypixelfile;
    bool new;
    int bounds[][2]={{100,125},{125,150},{150,175},{175,200},{200,225},{225,250},{250,275},{275,300},{300,325},{325,350},{350,375},{375,400},{400,425},{425,450},{450,475},{475,500}};
    float ra; //Radius
    int maxx=1920,maxy=1080;
    int x=960; //Half of SCREEN_WIDTH=1090/2
	int y=540; //Half of SCREEN_HEIGHT=1080/2
	int i,j,level;
	mypixelfile=fopen("mypixels", "w");
	fclose(mypixelfile);
    mypixelfile=fopen("mypixels", "a");

    //Computing pixel values for 0th octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",0,level);
        for(i=x;i<maxx;i++)
            for(j=y;j<maxy;j++)
            {
                if(i-x>=j-y)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 0 level %i ",level);
    }

    //Computing pixel values for 1st octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",1,level);
        for(i=x;i<maxx;i++)
            for(j=y;j<maxy;j++)
            {
                if(i-x<j-y)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 1 level %i ",level);
    }

    //Computing pixel values for 2nd octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",2,level);
        for(i=0;i<x;i++)
            for(j=y;j<maxy;j++)
            {
                if(x-i<j-y)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 2 level %i ",level);
    }

    //Computing pixel values for 3rd octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",3,level);
        for(i=0;i<x;i++)
            for(j=y;j<maxy;j++)
            {
                if(x-i>=j-y)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 3 level %i ",level);
    }

    //Computing pixel values for 4th octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",4,level);
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
            {
                if(x-i>=y-j)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 4 level %i ",level);
    }

    //Computing pixel values for 5th octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",5,level);
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
            {
                if(x-i<y-j)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 5 level %i ",level);
    }

    //Computing pixel values for 6th octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",6,level);
        for(i=x;i<maxx;i++)
            for(j=0;j<y;j++)
            {
                if(i-x<y-j)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 6 level %i ",level);
    }

    //Computing pixel values for 7th octet
    for(level=0;level<16;level++)
    {
        new=true;
        fprintf(mypixelfile,"int oct%d_%d[]={",7,level);
        for(i=x;i<maxx;i++)
            for(j=0;j<y;j++)
            {
                if(i-x>=y-j)
                {
                    ra=(i-x)*(i-x)+(j-y)*(j-y);
                    ra=sqrt(ra);
                    if(ra>=bounds[level][0] && ra<bounds[level][1])
                    {
                        if(!new)
                            fprintf(mypixelfile,",");
                        fprintf(mypixelfile,"%d,%d",i,j);
                        new=false;
                    }
                }
            }
        fprintf(mypixelfile,"};\n");
        printf("\n Successfully computed pixels of Octet 7 level %i ",level);
    }

    fclose(mypixelfile);
    printf("\n\n All pixel values generated successfully and written to mypixels file\n\n");
}