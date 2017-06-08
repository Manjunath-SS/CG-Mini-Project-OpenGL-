#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"var.c"

int xval,yval;
char char_xval[32], char_yval[32];

int sel[][2]={{100,125},{125,150},{150,175},{175,200},{200,225},{225,250},{250,275},{275,300},{300,325},{325,350},{350,375},{375,400},{400,425},{425,450},{450,475},{475,500}};

void printthis(int x,int y)
{
    printf("x=%d-y=%d\n",x,glutGet(GLUT_WINDOW_HEIGHT)-y);
}

char *itoa(long i, char* s, int dummy_radix) {
    sprintf(s, "%ld", i);
    return s;
}


void mydraw(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void mydrawpalette(int val,int *mat,int size)
{
    int i;
    glColor3fv(oct_clr[val]);
   	for(i=0;i<(size/sizeof(mat[0]));i+=2)
    {
    	mydraw(mat[i],mat[i+1]);
    }
}

float current[]={0.0,0.0,0.0};
float previous[]={0.0,0.0,0.0};
int newcodeslno,oldcodeslno;

void copy(float *source, float *destination)
{

        destination[0]=source[0];
        destination[1]=source[1];
        destination[2]=source[2];
        oldcodeslno=newcodeslno;
}


void output(int x, int y, float r, float g, float b, int font, char *string)
{
  //glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}


void sel_clr(int curx, int cury)
{

	float ra;
    int x=960.0;
	int y=540.0;
	int i,j;
	cury=1080-cury;
    if(curx>=x && cury>=y && curx-960>=cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
            copy(current,previous);
			current[0]=oct_clr[i][0];
            current[1]=oct_clr[i][1];
            current[2]=oct_clr[i][2];
            newcodeslno=i;
			glutPostRedisplay();
        }
    }
    else if(curx>=x && cury>=y && curx-960<cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
            copy(current,previous);
			current[0]=oct_clr[16+i][0];
            current[1]=oct_clr[16+i][1];
            current[2]=oct_clr[16+i][2];
            newcodeslno=16+i;
			glutPostRedisplay();
        }
    }
    else if(curx<x && cury>=y && 960-curx<cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
            copy(current,previous);
			current[0]=oct_clr[32+i][0];
            current[1]=oct_clr[32+i][1];
            current[2]=oct_clr[32+i][2];
            newcodeslno=32+i;
			glutPostRedisplay();
        }
    }
    else if(curx<x && cury>=y && 960-curx>=cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
            copy(current,previous);
			current[0]=oct_clr[48+i][0];
            current[1]=oct_clr[48+i][1];
            current[2]=oct_clr[48+i][2];
            newcodeslno=48+i;
			glutPostRedisplay();
        }
    }
    else if(curx<x && cury<y && 960-curx>=540-cury)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
            copy(current,previous);
			current[0]=oct_clr[64+i][0];
            current[1]=oct_clr[64+i][1];
            current[2]=oct_clr[64+i][2];
            newcodeslno=64+i;
			glutPostRedisplay();
        }
    }
    else if(curx<x && cury<y && 960-curx<540-cury)
    {
        copy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
			current[0]=oct_clr[80+i][0];
            current[1]=oct_clr[80+i][1];
            current[2]=oct_clr[80+i][2];
            newcodeslno=80+i;
			glutPostRedisplay();
        }
    }
    else if(curx>=x && cury<y && curx-960<540-cury)
    {
        copy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
			current[0]=oct_clr[96+i][0];
            current[1]=oct_clr[96+i][1];
            current[2]=oct_clr[96+i][2];
            newcodeslno=96+i;
			glutPostRedisplay();
        }
    }
    else
    {
        copy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=sel[i][0] && ra<=sel[i][1])
        {
			current[0]=oct_clr[112+i][0];
            current[1]=oct_clr[112+i][1];
            current[2]=oct_clr[112+i][2];
            newcodeslno=112+i;
			glutPostRedisplay();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

  mydrawpalette(0,oct0_0,sizeof(oct0_0));
	mydrawpalette(1,oct0_1,sizeof(oct0_1));
	mydrawpalette(2,oct0_2,sizeof(oct0_2));
	mydrawpalette(3,oct0_3,sizeof(oct0_3));
	mydrawpalette(4,oct0_4,sizeof(oct0_4));
	mydrawpalette(5,oct0_5,sizeof(oct0_5));
	mydrawpalette(6,oct0_6,sizeof(oct0_6));
	mydrawpalette(7,oct0_7,sizeof(oct0_7));
	mydrawpalette(8,oct0_8,sizeof(oct0_8));
	mydrawpalette(9,oct0_9,sizeof(oct0_9));
	mydrawpalette(10,oct0_10,sizeof(oct0_10));
	mydrawpalette(11,oct0_11,sizeof(oct0_11));
	mydrawpalette(12,oct0_12,sizeof(oct0_12));
	mydrawpalette(13,oct0_13,sizeof(oct0_13));
	mydrawpalette(14,oct0_14,sizeof(oct0_14));
	mydrawpalette(15,oct0_15,sizeof(oct0_15));

	mydrawpalette(16,oct1_0,sizeof(oct1_0));
	mydrawpalette(17,oct1_1,sizeof(oct1_1));
	mydrawpalette(18,oct1_2,sizeof(oct1_2));
	mydrawpalette(19,oct1_3,sizeof(oct1_3));
	mydrawpalette(20,oct1_4,sizeof(oct1_4));
	mydrawpalette(21,oct1_5,sizeof(oct1_5));
	mydrawpalette(22,oct1_6,sizeof(oct1_6));
	mydrawpalette(23,oct1_7,sizeof(oct1_7));
	mydrawpalette(24,oct1_8,sizeof(oct1_8));
	mydrawpalette(25,oct1_9,sizeof(oct1_9));
	mydrawpalette(26,oct1_10,sizeof(oct1_10));
	mydrawpalette(27,oct1_11,sizeof(oct1_11));
	mydrawpalette(28,oct1_12,sizeof(oct1_12));
	mydrawpalette(29,oct1_13,sizeof(oct1_13));
	mydrawpalette(30,oct1_14,sizeof(oct1_14));
	mydrawpalette(31,oct1_15,sizeof(oct1_15));

	mydrawpalette(32,oct2_0,sizeof(oct2_0));
	mydrawpalette(33,oct2_1,sizeof(oct2_1));
	mydrawpalette(34,oct2_2,sizeof(oct2_2));
	mydrawpalette(35,oct2_3,sizeof(oct2_3));
	mydrawpalette(36,oct2_4,sizeof(oct2_4));
	mydrawpalette(37,oct2_5,sizeof(oct2_5));
	mydrawpalette(38,oct2_6,sizeof(oct2_6));
	mydrawpalette(39,oct2_7,sizeof(oct2_7));
	mydrawpalette(40,oct2_8,sizeof(oct2_8));
	mydrawpalette(41,oct2_9,sizeof(oct2_9));
	mydrawpalette(42,oct2_10,sizeof(oct2_10));
	mydrawpalette(43,oct2_11,sizeof(oct2_11));
	mydrawpalette(44,oct2_12,sizeof(oct2_12));
	mydrawpalette(45,oct2_13,sizeof(oct2_13));
	mydrawpalette(46,oct2_14,sizeof(oct2_14));
	mydrawpalette(47,oct2_15,sizeof(oct2_15));

	mydrawpalette(48,oct3_0,sizeof(oct3_0));
	mydrawpalette(49,oct3_1,sizeof(oct3_1));
	mydrawpalette(50,oct3_2,sizeof(oct3_2));
	mydrawpalette(51,oct3_3,sizeof(oct3_3));
	mydrawpalette(52,oct3_4,sizeof(oct3_4));
	mydrawpalette(53,oct3_5,sizeof(oct3_5));
	mydrawpalette(54,oct3_6,sizeof(oct3_6));
	mydrawpalette(55,oct3_7,sizeof(oct3_7));
	mydrawpalette(56,oct3_8,sizeof(oct3_8));
	mydrawpalette(57,oct3_9,sizeof(oct3_9));
	mydrawpalette(58,oct3_10,sizeof(oct3_10));
	mydrawpalette(59,oct3_11,sizeof(oct3_11));
	mydrawpalette(60,oct3_12,sizeof(oct3_12));
	mydrawpalette(61,oct3_13,sizeof(oct3_13));
	mydrawpalette(62,oct3_14,sizeof(oct3_14));
	mydrawpalette(63,oct3_15,sizeof(oct3_15));

	mydrawpalette(64,oct4_0,sizeof(oct4_0));
	mydrawpalette(65,oct4_1,sizeof(oct4_1));
	mydrawpalette(66,oct4_2,sizeof(oct4_2));
	mydrawpalette(67,oct4_3,sizeof(oct4_3));
	mydrawpalette(68,oct4_4,sizeof(oct4_4));
	mydrawpalette(69,oct4_5,sizeof(oct4_5));
	mydrawpalette(70,oct4_6,sizeof(oct4_6));
	mydrawpalette(71,oct4_7,sizeof(oct4_7));
	mydrawpalette(72,oct4_8,sizeof(oct4_8));
	mydrawpalette(73,oct4_9,sizeof(oct4_9));
	mydrawpalette(74,oct4_10,sizeof(oct4_10));
	mydrawpalette(75,oct4_11,sizeof(oct4_11));
	mydrawpalette(76,oct4_12,sizeof(oct4_12));
	mydrawpalette(77,oct4_13,sizeof(oct4_13));
	mydrawpalette(78,oct4_14,sizeof(oct4_14));
	mydrawpalette(79,oct4_15,sizeof(oct4_15));

	mydrawpalette(80,oct5_0,sizeof(oct5_0));
	mydrawpalette(81,oct5_1,sizeof(oct5_1));
	mydrawpalette(82,oct5_2,sizeof(oct5_2));
	mydrawpalette(83,oct5_3,sizeof(oct5_3));
	mydrawpalette(84,oct5_4,sizeof(oct5_4));
	mydrawpalette(85,oct5_5,sizeof(oct5_5));
	mydrawpalette(86,oct5_6,sizeof(oct5_6));
	mydrawpalette(87,oct5_7,sizeof(oct5_7));
	mydrawpalette(88,oct5_8,sizeof(oct5_8));
	mydrawpalette(89,oct5_9,sizeof(oct5_9));
	mydrawpalette(90,oct5_10,sizeof(oct5_10));
	mydrawpalette(91,oct5_11,sizeof(oct5_11));
	mydrawpalette(92,oct5_12,sizeof(oct5_12));
	mydrawpalette(93,oct5_13,sizeof(oct5_13));
	mydrawpalette(94,oct5_14,sizeof(oct5_14));
	mydrawpalette(95,oct5_15,sizeof(oct5_15));

	mydrawpalette(96,oct6_0,sizeof(oct6_0));
	mydrawpalette(97,oct6_1,sizeof(oct6_1));
	mydrawpalette(98,oct6_2,sizeof(oct6_2));
	mydrawpalette(99,oct6_3,sizeof(oct6_3));
	mydrawpalette(100,oct6_4,sizeof(oct6_4));
	mydrawpalette(101,oct6_5,sizeof(oct6_5));
	mydrawpalette(102,oct6_6,sizeof(oct6_6));
	mydrawpalette(103,oct6_7,sizeof(oct6_7));
	mydrawpalette(104,oct6_8,sizeof(oct6_8));
	mydrawpalette(105,oct6_9,sizeof(oct6_9));
	mydrawpalette(106,oct6_10,sizeof(oct6_10));
	mydrawpalette(107,oct6_11,sizeof(oct6_11));
	mydrawpalette(108,oct6_12,sizeof(oct6_12));
	mydrawpalette(109,oct6_13,sizeof(oct6_13));
	mydrawpalette(110,oct6_14,sizeof(oct6_14));
	mydrawpalette(111,oct6_15,sizeof(oct6_15));

	mydrawpalette(112,oct7_0,sizeof(oct7_0));
	mydrawpalette(113,oct7_1,sizeof(oct7_1));
	mydrawpalette(114,oct7_2,sizeof(oct7_2));
	mydrawpalette(115,oct7_3,sizeof(oct7_3));
	mydrawpalette(116,oct7_4,sizeof(oct7_4));
	mydrawpalette(117,oct7_5,sizeof(oct7_5));
	mydrawpalette(118,oct7_6,sizeof(oct7_6));
	mydrawpalette(119,oct7_7,sizeof(oct7_7));
	mydrawpalette(120,oct7_8,sizeof(oct7_8));
	mydrawpalette(121,oct7_9,sizeof(oct7_9));
	mydrawpalette(122,oct7_10,sizeof(oct7_10));
	mydrawpalette(123,oct7_11,sizeof(oct7_11));
	mydrawpalette(124,oct7_12,sizeof(oct7_12));
	mydrawpalette(125,oct7_13,sizeof(oct7_13));
	mydrawpalette(126,oct7_14,sizeof(oct7_14));
	mydrawpalette(127,oct7_15,sizeof(oct7_15));

    glColor3fv(previous);
    glBegin(GL_POLYGON);
        glVertex2f(100,200);
        glVertex2f(100,300);
        glVertex2f(400,300);
        glVertex2f(400,200);
    glEnd();
    output(50,350,1.0,1.0,0.0,0,code[oldcodeslno]);

    glColor3fv(current);
    glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(100,200);
        glVertex2f(400,200);
        glVertex2f(400,100);
    glEnd();
    output(50,50,1.0,1.0,0.0,0,code[newcodeslno]);


	glFlush();
}

void myMouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
    {
        float dx=1920/(float)glutGet(GLUT_WINDOW_WIDTH);
        float dy=1080/(float)glutGet(GLUT_WINDOW_HEIGHT);
        sel_clr(dx*x,dy*y);
    }
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        exit(0);
}


void myKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '1': system("/media/sf_M_DRIVE/CG_MiniProject/a.out"); exit(0);
            break;
        case '3':
            exit(0);
        default:
            break;
    }
}



void myinit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1920.0,0.0,1080.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	//glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Color Palette");
	//glutFullScreen();
  glutMouseFunc(myMouse);
  glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

}
