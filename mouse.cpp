#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
#include<stdlib.h>

int i;
char buffer[64];
void printthis(int x,int y){printf("x=%d-y=%d\n",x,glutGet(GLUT_WINDOW_HEIGHT)-y);}
void top_menu(int id)
{
        switch(id)
        {
        case 1:exit(0);break;
        }
        glutPostRedisplay();
}

char *itoa(long i, char* s, int dummy_radix) {
    sprintf(s, "%ld", i);
    return s;
}

void myMouse(int button,int state,int x,int y)
    {	
	
        if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
            {printthis(10000,9999);i=x;}
        if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
            exit(0);
    }

void passiveMotionFunc(int x, int y) {
	glColor3f(1,1,0);

	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,glutGet(GLUT_WINDOW_HEIGHT)-y);
		glVertex2f(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
		glVertex2f(x,0);		
	glEnd();
	glFlush();
    	printthis(x,y);
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
	glColor4f(1,0,0,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,100);
		glVertex2f(100,100);
		glVertex2f(100,0);		
	glEnd();
    itoa(i,buffer,10);
	glBegin(GL_POINTS);
		glVertex2f(100.0,200.0);
        glVertex2f(0,0);
        glVertex2f(1900,1000);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(1920,1080);
    glEnd();
    itoa(i,buffer,64);
    output(100,100,1.0,1.0,0.0,0,buffer);
	glFlush();
}


/*
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
   	passiveMotionFunc(w-glutGet(GLUT_WINDOW_WIDTH),h-glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay();
    
}*/


void myinit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.502, 0.502, 0.000,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(5.0);
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