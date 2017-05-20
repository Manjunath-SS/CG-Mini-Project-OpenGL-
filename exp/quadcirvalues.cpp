#include<stdio.h>
#include<math.h>
int a[]={1,2,3,5};
void mydraw(int i, int j)
{
	printf("%d,%d,",i,j);
}

int main()
{
	float x,y,i,j,ra,n,p;
    x=960.0;
	y=540.0;
	//printf("%d",sizeof(a)/sizeof(a[0]));
    for(i=0;i<1920;i++)
        for(j=0;j<1080;j++)
    {
    	n=i-960;
    	p=fabs(n);
        if(i<x && j>=y && p >=j-540)
        {
            ra=(x-i)*(x-i)+(j-y)*(j-y);
            ra=sqrt(ra);
            if(ra>475 && ra<=500)
                {
					mydraw(i,j);
                }
        }
    }

}

