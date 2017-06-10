#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>

int miniproj=0, pntrlctn=0;
int coord;
char cor[33];


#define GLOBAL_SIZE 0.5
#define LEG_XSCALE 2.0
#define LEG_YSCALE 0.4
#define LEG_ZSCALE 0.4
#define BODY_XSCALE 0.5
#define BODY_YSCALE LEG_XSCALE * 1.2
#define BODY_ZSCALE 1.5
#define HEAD_RADIUS GLOBAL_SIZE * BODY_XSCALE
#define HAND_XSCALE 1.6
#define HAND_YSCALE LEG_YSCALE
#define HAND_ZSCALE LEG_ZSCALE
#define FOOT_XSCALE 1.0
#define FOOT_YSCALE 0.3
#define FOOT_ZSCALE LEG_ZSCALE

const static double PI = acos(-1.0);

static int leftHigherLegAngle = -60, rightHigherLegAngle = -120;
static int leftLowerLegAngle = 0, rightLowerLegAngle = 0;
static int leftHigherHandAngle = -120, rightHigherHandAngle = -60;
static int leftLowerHandAngle = -60, rightLowerHandAngle = 0;
static int leftFootAngle = 0, rightFootAngle = 0;

static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
static GLint vangle = 0;

GLUquadricObj *quadratic;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);

}

void drawSolidCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int sections = 200;
    GLfloat TWOPI = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= sections; ++ i) {
            glVertex2f(x + radius * cos(i * TWOPI / sections), y + radius * sin(i * TWOPI / sections));
        }
    glEnd();
}


void drawStrokeText(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, char str[], GLfloat width, GLubyte R, GLubyte G, GLubyte B)
{
	int i;
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 600);
	if (miniproj==0)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(1000, 0);
		glVertex2f(1000, 600);
		glVertex2f(0, 600);
		glEnd();
	}
	glDepthFunc(GL_ALWAYS);
	glColor3ub(R, G, B);
	glLineWidth(width);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);
	for (i = 0; str[i] != '\0'; ++i)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
	glDepthFunc(GL_LESS);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void displayInfo()
{

	//drawStrokeText(x, y, sx, sy, str[], width, R, G, B);
	drawStrokeText(130, 550, 0.35, 0.4, "Cambridge Institute of Technology", 4, 0, 0, 255);
	drawStrokeText(170, 510, 0.2, 0.2, "Department of Computer Science & Engineering", 2.5, 0, 0, 255);
	drawStrokeText(10, 430, 0.4, 0.4, "OpenGL Utility Tools And Walking Man", 6, 255, 0, 0);
	drawStrokeText(400, 380, 0.2, 0.2, "VI Semester", 2.2, 0, 255, 0);
	drawStrokeText(370, 350, 0.2, 0.2, "Graphics Package", 2.2, 0, 255, 0);
	drawStrokeText(400, 310, 0.2, 0.2, "Submitted By", 2.2, 0, 255, 255);
	drawStrokeText(230, 270, 0.2, 0.2, "1CD13CS001", 2.5, 255, 255, 0);
	drawStrokeText(600, 270, 0.2, 0.2, "Abhishek.M", 2.5, 255, 255, 0);
    drawStrokeText(230, 230, 0.2, 0.2, "1CD14CS091", 2.5, 255, 255, 0);
	drawStrokeText(600, 230, 0.2, 0.2, "Manjunath.S.S", 2.5, 255, 255, 0);
	drawStrokeText(300, 190, 0.2, 0.2, "for the academic year 2017", 2.0, 255, 0, 255);

    drawStrokeText(340, 145, 0.2, 0.2, "Under the Guidance of", 2.2, 0, 255, 255);
	drawStrokeText(320, 100, 0.2, 0.2, "Prof. Sonia Maria D'Souza", 2.5, 255, 255, 0);
	drawStrokeText(410, 60, 0.2, 0.2, "Prof. Ganesh", 2.5, 255, 255, 0);


	drawStrokeText(360, 20, 0.15, 0.15, "(Press right click to explore)", 2, 255, 0, 0);
}

void miniproj1()
{
		glClearColor(0.0,0.0,0.0,1.0);
    glColor3f(0.8, 0.8, 0.8);
    // Ground
    int minx = (int) centerX - 30;
    int maxx = (int) centerX + 30;
    int minz = (int) centerZ - 30;
    int maxz = (int) centerZ + 30;
    for (int x = minx; x <= maxx; ++ x) {
        glBegin(GL_LINES);
            glVertex3f(x, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE, minz);
            glVertex3f(x, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE, maxz);
        glEnd();
    }

    for (int z = minz; z <= maxz; ++ z) {
        glBegin(GL_LINES);
            glVertex3f(minx, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE, z);
            glVertex3f(maxx, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE, z);
        glEnd();
    }

    glPushMatrix();
        glTranslatef(centerX, centerY, centerZ);
        glRotatef(vangle, 0.0, 1.0, 0.0);

        glColor3f(0.5, 0.5, 0.5);
        // Left LegAngle
        glPushMatrix();
            //glTranslatef(- GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glRotatef((GLfloat) leftHigherLegAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, GLOBAL_SIZE * LEG_ZSCALE);
            glPushMatrix();
                glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            // Joint
            glPushMatrix();
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE / 2);
                gluCylinder(quadratic, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_ZSCALE, 32, 32);
                glTranslatef(0.0, 0.0, GLOBAL_SIZE * LEG_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
            glPopMatrix();
            //glTranslatef(GLOBAL_SIZE * LEG_ZSCALE / 2, 0.0, 0.0);
            glRotatef((GLfloat) leftLowerLegAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glPushMatrix();
                glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            // Foot
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glRotatef(90.0, 0.0, 0.0, 1.0);
            glTranslatef(-GLOBAL_SIZE * FOOT_XSCALE / 2 + GLOBAL_SIZE * LEG_YSCALE / 2, 0.0, 0.0);
            glRotatef((GLfloat) leftFootAngle, 0.0, 0.0, 1.0);
            glPushMatrix();
                glScalef(FOOT_XSCALE, FOOT_YSCALE, FOOT_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
        glPopMatrix();

        // Right LegAngle
        glPushMatrix();
            //glTranslatef(- GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glRotatef((GLfloat) rightHigherLegAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
            glPushMatrix();
                glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            // Joint
            glPushMatrix();
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE / 2);
                gluCylinder(quadratic, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_ZSCALE, 32, 32);
                glTranslatef(0.0, 0.0, GLOBAL_SIZE * LEG_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
            glPopMatrix();

            glRotatef((GLfloat) rightLowerLegAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glPushMatrix();
                glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            // Foot
            glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
            glRotatef(90.0, 0.0, 0.0, 1.0);
            glTranslatef(-GLOBAL_SIZE * FOOT_XSCALE / 2 + GLOBAL_SIZE * LEG_YSCALE / 2, 0.0, 0.0);
            glRotatef((GLfloat) rightFootAngle, 0.0, 0.0, 1.0);
            glPushMatrix();
                glScalef(FOOT_XSCALE, FOOT_YSCALE, FOOT_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
        glPopMatrix();

        // Body
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
            glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE / 2, 0.0);
            glScalef(BODY_XSCALE, BODY_YSCALE, BODY_ZSCALE);
            glutSolidCube(GLOBAL_SIZE);
        glPopMatrix();

        // Head
        glPushMatrix();
            glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE + HEAD_RADIUS, 0.0);
            glutSolidSphere(HEAD_RADIUS, 10, 8);
        glPopMatrix();

        // Left hand
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
            glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE, 0.0);
            glRotatef((GLfloat) leftHigherHandAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, GLOBAL_SIZE * (BODY_ZSCALE + HAND_ZSCALE) / 2);
            glPushMatrix();
                glScalef(HAND_XSCALE, HAND_YSCALE, HAND_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, 0.0);
            // Joint
            glPushMatrix();
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * HAND_ZSCALE / 2);
                gluCylinder(quadratic, GLOBAL_SIZE * HAND_YSCALE / 2, GLOBAL_SIZE * HAND_YSCALE / 2, GLOBAL_SIZE * HAND_ZSCALE, 32, 32);
                glTranslatef(0.0, 0.0, GLOBAL_SIZE * HAND_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * HAND_YSCALE / 2);
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * HAND_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * HAND_YSCALE / 2);
            glPopMatrix();

            glRotatef((GLfloat) leftLowerHandAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, 0.0);
            glPushMatrix();
                glScalef(HAND_XSCALE, HAND_YSCALE, HAND_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
        glPopMatrix();

        // Right hand
        glPushMatrix();
            glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE, 0.0);
            glRotatef((GLfloat) rightHigherHandAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, -GLOBAL_SIZE * (BODY_ZSCALE + HAND_ZSCALE) / 2);
            glPushMatrix();
                glScalef(HAND_XSCALE, HAND_YSCALE, HAND_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, 0.0);
            // Joint
            glPushMatrix();
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * HAND_ZSCALE / 2);
                gluCylinder(quadratic, GLOBAL_SIZE * HAND_YSCALE / 2, GLOBAL_SIZE * HAND_YSCALE / 2, GLOBAL_SIZE * HAND_ZSCALE, 32, 32);
                glTranslatef(0.0, 0.0, GLOBAL_SIZE * HAND_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * HAND_YSCALE / 2);
                glTranslatef(0.0, 0.0, -GLOBAL_SIZE * HAND_ZSCALE);
                drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * HAND_YSCALE / 2);
            glPopMatrix();

            glRotatef((GLfloat) rightLowerHandAngle, 0.0, 0.0, 1.0);
            glTranslatef(GLOBAL_SIZE * HAND_XSCALE / 2, 0.0, 0.0);
            glPushMatrix();
                glScalef(HAND_XSCALE, HAND_YSCALE, HAND_ZSCALE);
                glutSolidCube(GLOBAL_SIZE);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void PntrLctn()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//displayInfo();
	//glClearColor(0.502, 0.502, 0.000,1.0);
	gluOrtho2D(0.0,1920.0,0.0,1080.0);


	drawStrokeText(400, 310, 0.2, 0.2, cor, 2.2, 0, 255, 0);
	glColor4f(1.0,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,500);
		glVertex2f(500,500);
		glVertex2f(500,0);
	glEnd();
	glColor4f(1.0,1.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(50,50);
		glVertex2f(50,0);
	glEnd();
	glBegin(GL_POINTS);
		glVertex2f(100.0,200.0);
        glVertex2f(0,0);
        glVertex2f(1900,1000);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(1920,1080);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(miniproj==0)
    {
				//init();
				displayInfo();
    }
    else if(miniproj==1)
    {
        miniproj1();
    }
		else if(miniproj==3)
		{
				//miniproj3();
		}
		else if(miniproj==2)
		{
				PntrLctn();
		}

    glFlush();
    glutSwapBuffers();
}

static double lookatx = 3.5, lookatz = 3.5, lookaty = 0;
static int scrw, scrh;

void reshape(int w, int h) {
			scrw = w;
	    scrh = h;
	    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 1000.0);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

void passiveMotionFunc(int x, int y) {
    lookatx = -5.0 + (double) x / scrw * 10.0;
    lookatz = sqrt(25 - lookatx * lookatx) + centerZ;
    lookatx += centerX;
    double tmpy = -5.0 + (double) y / scrh * 10.0;
    if (tmpy >= -GLOBAL_SIZE * LEG_XSCALE * 2)
        lookaty = tmpy;
    glLoadIdentity();
    coord=x;

    gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            vangle = (vangle + 1) % 360;
            break;
        case 'd':
            vangle = (vangle - 1) % 360;
            break;
        case 27:
            exit(0);
        case 's':
            vangle = (vangle + 180) % 360;
            break;
        case '2':
            system("/media/sf_M_DRIVE/CG_MiniProject/Mouse/a.out");
            exit(0);
        default:
            break;
    }
}

bool dir1 = false;
static const double legLength = 2 * GLOBAL_SIZE * LEG_XSCALE + GLOBAL_SIZE * FOOT_YSCALE;

void calculateData(int id) {
    if(miniproj==1)
    {
        centerY = legLength * sin(-leftHigherLegAngle / 180.0 * PI) - legLength;
        double mvx = cos(vangle / 180.0 * PI) * 0.035;
        double mvz = sin(vangle / 180.0 * PI) * 0.035;
          //printf("X=%lf Y=%lf Z=%lf\n", centerX, centerY, centerZ);

          if (!dir1) {
            leftHigherLegAngle --;
            rightHigherLegAngle ++;
            if (leftHigherLegAngle >= -75) {
                leftLowerLegAngle += 6;
                leftFootAngle = 0;
              }
              else if (leftHigherLegAngle < -105) leftLowerLegAngle -= 6;

              if (leftHigherLegAngle == -120) {
                dir1 = true;

              }

              rightFootAngle = -rightHigherLegAngle - 90;

              leftHigherHandAngle ++;
              leftLowerHandAngle ++;
              rightHigherHandAngle --;
              rightLowerHandAngle --;
            }
            else {
              leftHigherLegAngle ++;
              rightHigherLegAngle --;
              if (rightHigherLegAngle >= -75) {
                rightLowerLegAngle += 6;
                rightFootAngle = 0;
              }
              else if (rightHigherLegAngle < -105) rightLowerLegAngle -= 6;

              if (leftHigherLegAngle == -60) dir1 = false;

              leftFootAngle = -leftHigherLegAngle - 90;

              leftHigherHandAngle --;
              leftLowerHandAngle --;
              rightHigherHandAngle ++;
              rightLowerHandAngle ++;
            }

            centerX -= mvx;
            lookatx -= mvx;
            centerZ += mvz;
            lookatz += mvz;
            glLoadIdentity();
      //printf("X=%lf,Z=%lf, lX=%lf,lZ=%lf\n", centerX, centerZ, lookatx, lookatz);
        gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);

        glutPostRedisplay();
    }
		glutTimerFunc(10, calculateData, 0);
}

void printthis(int x,int y){printf("x=%d-y=%d\n",x,y);}

void myMouse(int button,int state,int x,int y)
{
		//if(pntrlctn!=0)

      if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        {printthis(x,y);}
}

void top_menu(int id)
{
    switch(id)
    {
      case 0: exit(0);
			case 1: miniproj=1; break;
			case 2: miniproj=0; break;
			case 3: miniproj=3; break;
    }
    glutPostRedisplay();
}

void sub_options(int id)
{
    switch(id)
    {
			case 20:pntrlctn=0;
              break;
    	case 21:miniproj=2;
              break;
      case 22:pntrlctn=22;
      				break;
			case 23:pntrlctn=23;
							break;
			case 24:pntrlctn=24;
							break;
    }
    glutPostRedisplay();
}

void mymenu()
{
				int sub_menu=glutCreateMenu(sub_options);
        glutAddMenuEntry("Top-Left",21);
        glutAddMenuEntry("Top-Right",22);
				glutAddMenuEntry("Bottom-Left",23);
				glutAddMenuEntry("Bottom-Right",24);
				glutAddMenuEntry("Disable",20);

				glutCreateMenu(top_menu);
				glutAddMenuEntry("Welcome Page",2);
        glutAddMenuEntry("3D Walking Man",1);
				glutAddSubMenu("Pointer Scale",sub_menu);
				glutAddMenuEntry("Color Palette",3);
				glutAddMenuEntry("Quit",0);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    mymenu();
    glutMouseFunc(myMouse);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMotionFunc);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutFullScreen();
    calculateData(0);
    glutMainLoop();
    return 0;
}
