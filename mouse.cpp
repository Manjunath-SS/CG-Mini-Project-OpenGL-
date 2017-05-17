#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
#include<stdlib.h>

int xval,yval;
char char_xval[32], char_yval[32];

void printthis(int x,int y)
{
    printf("x=%d-y=%d\n",x,glutGet(GLUT_WINDOW_HEIGHT)-y);
}

char *itoa(long i, char* s, int dummy_radix) {
    sprintf(s, "%ld", i);
    return s;
}

void output(int x, int y, float r, float g, float b, int font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}


void display()
{
    int x,y;
    char charx[32],chary[32];
    glClear(GL_COLOR_BUFFER_BIT);
  	glColor4f(1,0,0,0.6);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,1080);
		glVertex2f(100,1080);
		glVertex2f(100,0);		

        glVertex2f(0,0);
		glVertex2f(0,100);
		glVertex2f(1920,100);
		glVertex2f(1920,0);
	glEnd();

    glColor3f(1.0,1.0,1.0);
    for(y=100;y<=glutGet(GLUT_WINDOW_HEIGHT);y+=20)
    {
        glBegin(GL_LINES);
            glVertex2f(0,y);
            glVertex2f(50,y);
        glEnd();
        if(y%100==0)
        {
            itoa(y,chary,32);
            output(50,y-6,1.0,1.0,0.0,0,chary);
        }
    }

    for(x=100;x<=glutGet(GLUT_WINDOW_WIDTH);x+=20)
    {
        glBegin(GL_LINES);
            glVertex2f(x,0);
            glVertex2f(x,50);
        glEnd();
        if(x%200==0)
        {
            itoa(x,charx,32);
            output(x-20,60,1.0,1.0,0.0,0,charx);
        }
    }

    output(7,60,1.0,1.0,0.0,0,"x =");
    output(7,30,1.0,1.0,0.0,0,"y =");
    output(44,60,1.0,1.0,0.0,0,char_xval);
    output(44,30,1.0,1.0,0.0,0,char_yval);
	glFlush();
}

void myMouse(int button,int state,int x,int y)
{	
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        printthis(x,y);
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        exit(0);
}

void passiveMotionFunc(int x, int y) 
{
    xval=x;
    yval=glutGet(GLUT_WINDOW_HEIGHT)-y;
    itoa(xval,char_xval,32);
    itoa(yval,char_yval,32);
	glutPostRedisplay();
}


/*
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
   	passiveMotionFunc(w-glutGet(GLUT_WINDOW_WIDTH),h-glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay();
    
}*/


void myinit()
{
	glClearColor(0.0, 1.0, 1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1920.0,0.0,1080.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(1920,1080);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Mouse Coordinates");
	//glutReshapeFunc(reshape);
	glutFullScreen();
	glutPassiveMotionFunc(passiveMotionFunc);
    glutMouseFunc(myMouse);
	glutDisplayFunc(display);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	myinit();
	glutMainLoop();
}