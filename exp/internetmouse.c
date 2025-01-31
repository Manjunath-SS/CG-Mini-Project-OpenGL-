#include<stdlib.h>
#include<stdio.h>
    #include<GL/glut.h>
    GLsizei wh=500,ww=500;
    GLfloat size=3.0;

    void display()
    {
    glFlush();
    }

    void myInit()
    {
        glViewport(0,0,ww,wh);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
        glMatrixMode(GL_MODELVIEW);
        glClearColor(0.0,0.0,0.0,1.0);
        glColor3f(1.0,0.0,0.0);
    }

    void myReshape(GLsizei w,GLsizei h)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0,0,w,h);
        ww=w;
        wh=h;
    }

    void drawSquare(int x,int y)
    {

        y=wh-y;
        glBegin(GL_POLYGON);
        glVertex2f(x+size,y+size);
        glVertex2f(x-size,y+size);
        glVertex2f(x-size,y-size);
        glVertex2f(x+size,y-size);
        glEnd();
        glFlush();

    }

    void size_menu(int id)
    {
        switch(id)
        {
        case 2: size=size*2;
                break;
        case 3:if(size>1) size=size/2;
        break;
        }
        glutPostRedisplay();
    }
void printthis(int x,int y){printf("x=%d-y=%d\n",x,y);}
    void top_menu(int id)
    {
        switch(id)
        {
        case 1:exit(0);break;
        }
        glutPostRedisplay();
    }

    void myMouse(int button,int state,int x,int y)
    {	
	
        if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        {drawSquare(x,y); printthis(x,y);}
        if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
            exit(0);
    }

    int main(int argc,char **argv)
    {
        int sub_menu;
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutCreateWindow("Hierarchical Menus to Draw Squares");
        glutDisplayFunc(display);
        myInit();
        glutMouseFunc(myMouse);
        sub_menu=glutCreateMenu(size_menu);
        glutAddMenuEntry("Increase Square Size",2);
        glutAddMenuEntry("Decrease Square Size",3);
        glutCreateMenu(top_menu);
        glutAddMenuEntry("Quit",1);
        glutAddSubMenu("Resize",sub_menu);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        glutReshapeFunc(myReshape);
        glClear(GL_COLOR_BUFFER_BIT);
        glutMainLoop();
        return 0;
    }
