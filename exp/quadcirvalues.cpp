#include<stdio.h>
#include<math.h>
int a[]={1,2,3,5};
void mydraw(int i, int j)
{
	printf("%d,%d,",i,j);
}

int main()
{
	float x,y,i,j,ra;
    x=960.0;
	y=540.0;
	//printf("%d",sizeof(a)/sizeof(a[0]));
    for(i=960;i<1920;i++)
        for(j=540;j<1080;j++)
    {
        if(i>=x && j>=y && i-960>=j-540)
        {
            ra=(i-x)*(i-x)+(j-y)*(j-y);
            ra=sqrt(ra);
            if(ra>=475 && ra<=500)
                {
					mydraw(i,j);
                }
        }
    }
}

