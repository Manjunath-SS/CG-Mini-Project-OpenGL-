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
    for(i=960;i<1500;i++)
        for(j=0;j<540;j++)
    {
    	n=i-960;
    	p=fabs(n);
        if(i>=x && j<y && p >= 540-j)
        {
            ra=(i-x)*(i-x)+(y-j)*(y-j);
            ra=sqrt(ra);
//            if(ra>100 && ra<=125)
//            if(ra>125 && ra<=150)
//            if(ra>150 && ra<=175)
//            if(ra>175 && ra<=200)
//            if(ra>200 && ra<=225)
//            if(ra>225 && ra<=250)
//            if(ra>250 && ra<=275)
//            if(ra>275 && ra<=300)
//            if(ra>300 && ra<=325)
//            if(ra>325 && ra<=350)
//            if(ra>350 && ra<=375)
//            if(ra>375 && ra<=400)
//            if(ra>400 && ra<=425)
//            if(ra>425 && ra<=450)
//            if(ra>450 && ra<=475)
            if(ra>475 && ra<=500)
                {
					mydraw(i,j);
                }
        }
    }

}

