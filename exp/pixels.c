#include<stdio.h>
#include<math.h>
#include<stdbool.h>
void main()
{
    FILE *mypixelfile;
    bool new;
    int bounds[][2]={{100,125},{125,150},{150,175},{175,200},{200,225},{225,250},{250,275},{275,300},{300,325},{325,350},{350,375},{375,400},{400,425},{425,450},{450,475},{475,500}};
    char varname0[][8]={{"oct0_0"},{"oct0_1"},{"oct0_2"},{"oct0_3"},{"oct0_4"},{"oct0_5"},{"oct0_6"},{"oct0_7"},{"oct0_8"},{"oct0_9"},{"oct0_10"},{"oct0_11"},{"oct0_12"},{"oct0_13"},{"oct0_14"},{"oct0_15"}};
    char varname1[][8]={{"oct1_0"},{"oct1_1"},{"oct1_2"},{"oct1_3"},{"oct1_4"},{"oct1_5"},{"oct1_6"},{"oct1_7"},{"oct1_8"},{"oct1_9"},{"oct1_10"},{"oct1_11"},{"oct1_12"},{"oct1_13"},{"oct1_14"},{"oct1_15"}};
    char varname2[][8]={{"oct2_0"},{"oct2_1"},{"oct2_2"},{"oct2_3"},{"oct2_4"},{"oct2_5"},{"oct2_6"},{"oct2_7"},{"oct2_8"},{"oct2_9"},{"oct2_10"},{"oct2_11"},{"oct2_12"},{"oct2_13"},{"oct2_14"},{"oct2_15"}};
    char varname3[][8]={{"oct3_0"},{"oct3_1"},{"oct3_2"},{"oct3_3"},{"oct3_4"},{"oct3_5"},{"oct3_6"},{"oct3_7"},{"oct3_8"},{"oct3_9"},{"oct3_10"},{"oct3_11"},{"oct3_12"},{"oct3_13"},{"oct3_14"},{"oct3_15"}};
    char varname4[][8]={{"oct4_0"},{"oct4_1"},{"oct4_2"},{"oct4_3"},{"oct4_4"},{"oct4_5"},{"oct4_6"},{"oct4_7"},{"oct4_8"},{"oct4_9"},{"oct4_10"},{"oct4_11"},{"oct4_12"},{"oct4_13"},{"oct4_14"},{"oct4_15"}};
    char varname5[][8]={{"oct5_0"},{"oct5_1"},{"oct5_2"},{"oct5_3"},{"oct5_4"},{"oct5_5"},{"oct5_6"},{"oct5_7"},{"oct5_8"},{"oct5_9"},{"oct5_10"},{"oct5_11"},{"oct5_12"},{"oct5_13"},{"oct5_14"},{"oct5_15"}};
    char varname6[][8]={{"oct6_0"},{"oct6_1"},{"oct6_2"},{"oct6_3"},{"oct6_4"},{"oct6_5"},{"oct6_6"},{"oct6_7"},{"oct6_8"},{"oct6_9"},{"oct6_10"},{"oct6_11"},{"oct6_12"},{"oct6_13"},{"oct6_14"},{"oct6_15"}};
    char varname7[][8]={{"oct7_0"},{"oct7_1"},{"oct7_2"},{"oct7_3"},{"oct7_4"},{"oct7_5"},{"oct7_6"},{"oct7_7"},{"oct7_8"},{"oct7_9"},{"oct7_10"},{"oct7_11"},{"oct7_12"},{"oct7_13"},{"oct7_14"},{"oct7_15"}};
    char varname8[][8]={{"oct8_0"},{"oct8_1"},{"oct8_2"},{"oct8_3"},{"oct8_4"},{"oct8_5"},{"oct8_6"},{"oct8_7"},{"oct8_8"},{"oct8_9"},{"oct8_10"},{"oct8_11"},{"oct8_12"},{"oct8_13"},{"oct8_14"},{"oct8_15"}};
    char varname9[][8]={{"oct9_0"},{"oct9_1"},{"oct9_2"},{"oct9_3"},{"oct9_4"},{"oct9_5"},{"oct9_6"},{"oct9_7"},{"oct9_8"},{"oct9_9"},{"oct9_10"},{"oct9_11"},{"oct9_12"},{"oct9_13"},{"oct9_14"},{"oct9_15"}};
    char varname10[][8]={{"oct10_0"},{"oct10_1"},{"oct10_2"},{"oct10_3"},{"oct10_4"},{"oct10_5"},{"oct10_6"},{"oct10_7"},{"oct10_8"},{"oct10_9"},{"oct10_10"},{"oct10_11"},{"oct10_12"},{"oct10_13"},{"oct10_14"},{"oct10_15"}};
    char varname11[][8]={{"oct11_0"},{"oct11_1"},{"oct11_2"},{"oct11_3"},{"oct11_4"},{"oct11_5"},{"oct11_6"},{"oct11_7"},{"oct11_8"},{"oct11_9"},{"oct11_10"},{"oct11_11"},{"oct11_12"},{"oct11_13"},{"oct11_14"},{"oct11_15"}};
    char varname12[][8]={{"oct12_0"},{"oct12_1"},{"oct12_2"},{"oct12_3"},{"oct12_4"},{"oct12_5"},{"oct12_6"},{"oct12_7"},{"oct12_8"},{"oct12_9"},{"oct12_10"},{"oct12_11"},{"oct12_12"},{"oct12_13"},{"oct12_14"},{"oct12_15"}};
    char varname13[][8]={{"oct13_0"},{"oct13_1"},{"oct13_2"},{"oct13_3"},{"oct13_4"},{"oct13_5"},{"oct13_6"},{"oct13_7"},{"oct13_8"},{"oct13_9"},{"oct13_10"},{"oct13_11"},{"oct13_12"},{"oct13_13"},{"oct13_14"},{"oct13_15"}};
    char varname14[][8]={{"oct14_0"},{"oct14_1"},{"oct14_2"},{"oct14_3"},{"oct14_4"},{"oct14_5"},{"oct14_6"},{"oct14_7"},{"oct14_8"},{"oct14_9"},{"oct14_10"},{"oct14_11"},{"oct14_12"},{"oct14_13"},{"oct14_14"},{"oct14_15"}};
    char varname15[][8]={{"oct15_0"},{"oct15_1"},{"oct15_2"},{"oct15_3"},{"oct15_4"},{"oct15_5"},{"oct15_6"},{"oct15_7"},{"oct15_8"},{"oct15_9"},{"oct15_10"},{"oct15_11"},{"oct15_12"},{"oct15_13"},{"oct15_14"},{"oct15_15"}};

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
        fprintf(mypixelfile,"int %s[]={",varname0[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname1[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname2[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname3[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname4[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname5[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname6[level]);
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
        fprintf(mypixelfile,"int %s[]={",varname7[level]);
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