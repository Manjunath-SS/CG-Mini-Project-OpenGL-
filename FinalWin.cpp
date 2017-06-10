#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "mypixels"

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
static double lookatx = 3.5, lookatz = 3.5, lookaty = 0;
static int scrw, scrh;
GLUquadricObj *quadratic;
bool dir1 = false;
static const double legLength = 2 * GLOBAL_SIZE * LEG_XSCALE + GLOBAL_SIZE * FOOT_YSCALE;

float current[]={0.0,0.0,0.0}; //Used to store current color
float previous[]={0.0,0.0,0.0}; //Used to store previous color
int newcodeslno,oldcodeslno; //Used to store corresponding color's array indices
int miniproj=-1;
int xval,yval,scalelinex=100,scaleliney=100;
char char_xval[32], char_yval[32];
//Specifying boundaries for colors in color palette
int bounds[][2]={{100,125},{125,150},{150,175},{175,200},{200,225},{225,250},{250,275},{275,300},{300,325},{325,350},{350,375},{375,400},{400,425},{425,450},{450,475},{475,500}};
char code[][50]={"{0.804, 0.361, 0.361}", "{0.941, 0.502, 0.502}", "{0.980, 0.502, 0.447}", "{0.914, 0.588, 0.478}", "{1.000, 0.627, 0.478}", "{0.863, 0.078, 0.235}", "{1.000, 0.000, 0.000}", "{0.698, 0.133, 0.133}", "{0.545, 0.000, 0.000}", "{1.000, 0.753, 0.796}", "{1.000, 0.714, 0.757}", "{1.000, 0.412, 0.706}", "{1.000, 0.078, 0.576}", "{0.780, 0.082, 0.522}", "{0.859, 0.439, 0.576}", "{1.000, 0.627, 0.478}", "{1.000, 0.498, 0.314}", "{1.000, 0.388, 0.278}", "{1.000, 0.271, 0.000}", "{1.000, 0.549, 0.000}", "{1.000, 0.647, 0.000}", "{1.000, 0.843, 0.000}", "{1.000, 1.000, 0.000}", "{1.000, 1.000, 0.878}", "{1.000, 0.980, 0.804}", "{0.980, 0.980, 0.824}", "{1.000, 0.937, 0.835}", "{1.000, 0.894, 0.710}", "{1.000, 0.855, 0.725}", "{0.933, 0.910, 0.667}", "{0.941, 0.902, 0.549}", "{0.741, 0.718, 0.420}", "{0.902, 0.902, 0.980}", "{0.847, 0.749, 0.847}", "{0.867, 0.627, 0.867}", "{0.933, 0.510, 0.933}", "{0.855, 0.439, 0.839}", "{1.000, 0.000, 1.000}", "{1.000, 0.000, 1.000}", "{0.729, 0.333, 0.827}", "{0.576, 0.439, 0.859}", "{0.541, 0.169, 0.886}", "{0.580, 0.000, 0.827}", "{0.600, 0.196, 0.800}", "{0.545, 0.000, 0.545}", "{0.502, 0.000, 0.502}", "{0.294, 0.000, 0.510}", "{0.416, 0.353, 0.804}", "{0.282, 0.239, 0.545}", "{0.678, 1.000, 0.184}", "{0.498, 1.000, 0.000}", "{0.486, 0.988, 0.000}", "{0.000, 1.000, 0.000}", "{0.196, 0.804, 0.196}", "{0.596, 0.984, 0.596}", "{0.565, 0.933, 0.565}", "{0.000, 0.980, 0.604}", "{0.000, 1.000, 0.498}", "{0.235, 0.702, 0.443}", "{0.180, 0.545, 0.341}", "{0.133, 0.545, 0.133}", "{0.000, 0.502, 0.000}", "{0.000, 0.392, 0.000}", "{0.604, 0.804, 0.196}", "{0.420, 0.557, 0.137}", "{0.502, 0.502, 0.000}", "{0.333, 0.420, 0.184}", "{0.400, 0.804, 0.667}", "{0.561, 0.737, 0.561}", "{0.125, 0.698, 0.667}", "{0.000, 0.545, 0.545}", "{0.000, 0.502, 0.502}", "{0.000, 1.000, 1.000}", "{0.878, 1.000, 1.000}", "{0.686, 0.933, 0.933}", "{0.498, 1.000, 0.831}", "{0.251, 0.878, 0.816}", "{0.282, 0.820, 0.800}", "{0.000, 0.808, 0.820}", "{0.373, 0.620, 0.627}", "{0.275, 0.510, 0.706}", "{0.690, 0.769, 0.871}", "{0.690, 0.878, 0.902}", "{0.678, 0.847, 0.902}", "{0.529, 0.808, 0.922}", "{0.529, 0.808, 0.980}", "{0.000, 0.749, 1.000}", "{0.118, 0.565, 1.000}", "{0.392, 0.584, 0.929}", "{0.482, 0.408, 0.933}", "{0.255, 0.412, 0.882}", "{0.000, 0.000, 1.000}", "{0.000, 0.000, 0.804}", "{0.000, 0.000, 0.545}", "{0.000, 0.000, 0.502}", "{0.098, 0.098, 0.439}", "{1.000, 0.973, 0.863}", "{1.000, 0.922, 0.804}", "{1.000, 0.894, 0.769}", "{1.000, 0.871, 0.678}", "{0.961, 0.871, 0.702}", "{0.871, 0.722, 0.529}", "{0.824, 0.706, 0.549}", "{0.737, 0.561, 0.561}", "{0.957, 0.643, 0.376}", "{0.855, 0.647, 0.125}", "{0.722, 0.525, 0.043}", "{0.804, 0.522, 0.247}", "{0.824, 0.412, 0.118}", "{0.545, 0.271, 0.075}", "{0.627, 0.322, 0.176}", "{0.647, 0.165, 0.165}", "{0.502, 0.000, 0.000}", "{1.000, 1.000, 1.000}", "{0.941, 1.000, 0.941}", "{0.961, 1.000, 0.980}", "{1.000, 0.961, 0.933}", "{0.961, 0.961, 0.863}", "{0.992, 0.961, 0.902}", "{1.000, 0.980, 0.941}", "{1.000, 1.000, 0.941}", "{0.980, 0.922, 0.843}", "{0.980, 0.941, 0.902}", "{1.000, 0.941, 0.961}", "{1.000, 0.894, 0.882}", "{0.863, 0.863, 0.863}", "{0.827, 0.827, 0.827}", "{0.753, 0.753, 0.753}", "{0.663, 0.663, 0.663}", "{0.502, 0.502, 0.502}", "{0.412, 0.412, 0.412}", "{0.467, 0.533, 0.600}", "{0.439, 0.502, 0.565}", "{0.184, 0.310, 0.310}", "{0.000, 0.000, 0.000}"};
float oct_clr[][3]={{0.804, 0.361, 0.361}, {0.941, 0.502, 0.502}, {0.980, 0.502, 0.447}, {0.914, 0.588, 0.478}, {1.000, 0.627, 0.478}, {0.863, 0.078, 0.235}, {1.000, 0.000, 0.000}, {0.698, 0.133, 0.133}, {0.545, 0.000, 0.000}, {1.000, 0.753, 0.796}, {1.000, 0.714, 0.757}, {1.000, 0.412, 0.706}, {1.000, 0.078, 0.576}, {0.780, 0.082, 0.522}, {0.859, 0.439, 0.576}, {1.000, 0.627, 0.478}, {1.000, 0.498, 0.314}, {1.000, 0.388, 0.278}, {1.000, 0.271, 0.000}, {1.000, 0.549, 0.000}, {1.000, 0.647, 0.000}, {1.000, 0.843, 0.000}, {1.000, 1.000, 0.000}, {1.000, 1.000, 0.878}, {1.000, 0.980, 0.804}, {0.980, 0.980, 0.824}, {1.000, 0.937, 0.835}, {1.000, 0.894, 0.710}, {1.000, 0.855, 0.725}, {0.933, 0.910, 0.667}, {0.941, 0.902, 0.549}, {0.741, 0.718, 0.420}, {0.902, 0.902, 0.980}, {0.847, 0.749, 0.847}, {0.867, 0.627, 0.867}, {0.933, 0.510, 0.933}, {0.855, 0.439, 0.839}, {1.000, 0.000, 1.000}, {1.000, 0.000, 1.000}, {0.729, 0.333, 0.827}, {0.576, 0.439, 0.859}, {0.541, 0.169, 0.886}, {0.580, 0.000, 0.827}, {0.600, 0.196, 0.800}, {0.545, 0.000, 0.545}, {0.502, 0.000, 0.502}, {0.294, 0.000, 0.510}, {0.416, 0.353, 0.804}, {0.282, 0.239, 0.545}, {0.678, 1.000, 0.184}, {0.498, 1.000, 0.000}, {0.486, 0.988, 0.000}, {0.000, 1.000, 0.000}, {0.196, 0.804, 0.196}, {0.596, 0.984, 0.596}, {0.565, 0.933, 0.565}, {0.000, 0.980, 0.604}, {0.000, 1.000, 0.498}, {0.235, 0.702, 0.443}, {0.180, 0.545, 0.341}, {0.133, 0.545, 0.133}, {0.000, 0.502, 0.000}, {0.000, 0.392, 0.000}, {0.604, 0.804, 0.196}, {0.420, 0.557, 0.137}, {0.502, 0.502, 0.000}, {0.333, 0.420, 0.184}, {0.400, 0.804, 0.667}, {0.561, 0.737, 0.561}, {0.125, 0.698, 0.667}, {0.000, 0.545, 0.545}, {0.000, 0.502, 0.502}, {0.000, 1.000, 1.000}, {0.878, 1.000, 1.000}, {0.686, 0.933, 0.933}, {0.498, 1.000, 0.831}, {0.251, 0.878, 0.816}, {0.282, 0.820, 0.800}, {0.000, 0.808, 0.820}, {0.373, 0.620, 0.627}, {0.275, 0.510, 0.706}, {0.690, 0.769, 0.871}, {0.690, 0.878, 0.902}, {0.678, 0.847, 0.902}, {0.529, 0.808, 0.922}, {0.529, 0.808, 0.980}, {0.000, 0.749, 1.000}, {0.118, 0.565, 1.000}, {0.392, 0.584, 0.929}, {0.482, 0.408, 0.933}, {0.255, 0.412, 0.882}, {0.000, 0.000, 1.000}, {0.000, 0.000, 0.804}, {0.000, 0.000, 0.545}, {0.000, 0.000, 0.502}, {0.098, 0.098, 0.439}, {1.000, 0.973, 0.863}, {1.000, 0.922, 0.804}, {1.000, 0.894, 0.769}, {1.000, 0.871, 0.678}, {0.961, 0.871, 0.702}, {0.871, 0.722, 0.529}, {0.824, 0.706, 0.549}, {0.737, 0.561, 0.561}, {0.957, 0.643, 0.376}, {0.855, 0.647, 0.125}, {0.722, 0.525, 0.043}, {0.804, 0.522, 0.247}, {0.824, 0.412, 0.118}, {0.545, 0.271, 0.075}, {0.627, 0.322, 0.176}, {0.647, 0.165, 0.165}, {0.502, 0.000, 0.000}, {1.000, 1.000, 1.000}, {0.941, 1.000, 0.941}, {0.961, 1.000, 0.980}, {1.000, 0.961, 0.933}, {0.961, 0.961, 0.863}, {0.992, 0.961, 0.902}, {1.000, 0.980, 0.941}, {1.000, 1.000, 0.941}, {0.980, 0.922, 0.843}, {0.980, 0.941, 0.902}, {1.000, 0.941, 0.961}, {1.000, 0.894, 0.882}, {0.863, 0.863, 0.863}, {0.827, 0.827, 0.827}, {0.753, 0.753, 0.753}, {0.663, 0.663, 0.663}, {0.502, 0.502, 0.502}, {0.412, 0.412, 0.412}, {0.467, 0.533, 0.600}, {0.439, 0.502, 0.565}, {0.184, 0.310, 0.310}, {0.000, 0.000, 0.000}};


void mydraw(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
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

//Function to plot pixels in color palette
void mydrawpalette(int val,int *mat,int size)
{
    int i;
    glColor3fv(oct_clr[val]);
   	for(i=0;i<(size/sizeof(mat[0]));i+=2)
    {
    	mydraw(mat[i],mat[i+1]);
    }
}

//Function to mycopy array of RGB values along with corresponding array index
void mycopy(float *source, float *destination)
{
        destination[0]=source[0];
        destination[1]=source[1];
        destination[2]=source[2];
        oldcodeslno=newcodeslno;
}

//Function to determine the color which lies on current cursor position
void sel_clr(int curx, int cury)
{

	float ra; //Radius
    int x=960.0; //Half of SCREEN_WIDTH=1090/2
	int y=540.0; //Half of SCREEN_HEIGHT=1080/2
	int i,j;
	cury=1080-cury;
    //Checks if color of 1st octet is selected
    if(curx>=x && cury>=y && curx-960>=cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
            mycopy(current,previous);
			current[0]=oct_clr[i][0];
            current[1]=oct_clr[i][1];
            current[2]=oct_clr[i][2];
            newcodeslno=i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 2nd octet is selected
    else if(curx>=x && cury>=y && curx-960<cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
            mycopy(current,previous);
			current[0]=oct_clr[16+i][0];
            current[1]=oct_clr[16+i][1];
            current[2]=oct_clr[16+i][2];
            newcodeslno=16+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 3rd octet is selected
    else if(curx<x && cury>=y && 960-curx<cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
            mycopy(current,previous);
			current[0]=oct_clr[32+i][0];
            current[1]=oct_clr[32+i][1];
            current[2]=oct_clr[32+i][2];
            newcodeslno=32+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 4th octet is selected
    else if(curx<x && cury>=y && 960-curx>=cury-540)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
            mycopy(current,previous);
			current[0]=oct_clr[48+i][0];
            current[1]=oct_clr[48+i][1];
            current[2]=oct_clr[48+i][2];
            newcodeslno=48+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 5th octet is selected
    else if(curx<x && cury<y && 960-curx>=540-cury)
    {
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
            mycopy(current,previous);
			current[0]=oct_clr[64+i][0];
            current[1]=oct_clr[64+i][1];
            current[2]=oct_clr[64+i][2];
            newcodeslno=64+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 6th octet is selected
    else if(curx<x && cury<y && 960-curx<540-cury)
    {
        mycopy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
			current[0]=oct_clr[80+i][0];
            current[1]=oct_clr[80+i][1];
            current[2]=oct_clr[80+i][2];
            newcodeslno=80+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 7th octet is selected
    else if(curx>=x && cury<y && curx-960<540-cury)
    {
        mycopy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
			current[0]=oct_clr[96+i][0];
            current[1]=oct_clr[96+i][1];
            current[2]=oct_clr[96+i][2];
            newcodeslno=96+i;
			glutPostRedisplay();
        }
    }
    //Checks if color of 8th octet is selected
    else if(curx>=x && cury<y && curx-960>=540-cury)
    {
        mycopy(current,previous);
        ra=(curx-x)*(curx-x)+(cury-y)*(cury-y);
        ra=sqrt(ra);
        for(i=0;i<16;i++)
		if(ra>=bounds[i][0] && ra<=bounds[i][1])
        {
			current[0]=oct_clr[112+i][0];
            current[1]=oct_clr[112+i][1];
            current[2]=oct_clr[112+i][2];
            newcodeslno=112+i;
			glutPostRedisplay();
        }
    }
}

//Prints cursor coordinates in terminal
void printthis(int x,int y)
{
    printf("The cursor co-ordinates are x = %d, y = %d\n",x,glutGet(GLUT_WINDOW_HEIGHT)-y);
}

void myinit(void) 
{
    if(miniproj==1 || miniproj==0)
    {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);
        quadratic = gluNewQuadric();
        gluQuadricNormals(quadratic, GLU_SMOOTH);
        gluQuadricTexture(quadratic, GL_TRUE);
    }
    else if(miniproj==3)
    {
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glClearColor(0.0, 0.0, 0.0, 1.0);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
        gluOrtho2D(0.0,1920.0,0.0,1080.0);
    }
    else if(miniproj==2)
    {
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0, 1.0, 1.0,1.0);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
        gluOrtho2D(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT));
    }
}

//dummy-value added to make it compatible with both Windows and Ubuntu
char *itoa(long i, char* s, int dummy_radix) 
{
    sprintf(s, "%ld", i);
    return s;
}

//Function which renders text
void mytext(int x, int y, float r, float g, float b, int font, char *string)
{
  //glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

void cursorfunc()
{
    int x,y;
    char charx[32],chary[32];
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Drawing some random picture in background
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,400);
		glVertex2f(400,600);
		glVertex2f(600,0);
         glColor3f(0.0,1.0,0.0);
        glVertex2f(550,800);
		glVertex2f(550,900);
		glVertex2f(900,1000);
		glVertex2f(1000,550);
	glEnd();

    glColor4f(1,0,0,0.2);
	glBegin(GL_POLYGON);
    //Drawing background for vertical scale
		glVertex2f(0,0);
		glVertex2f(0,glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(100,glutGet(GLUT_WINDOW_HEIGHT));
		glVertex2f(100,0);
    //Drawing background for horizontal scale
        glVertex2f(0,0);
		glVertex2f(0,100);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH),100);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH),0);
	glEnd();

    //Drawing scale marking for every 20 pixels vertically
    glColor3f(1.0,1.0,1.0);
    for(y=100;y<=glutGet(GLUT_WINDOW_HEIGHT);y+=20)
    {
        glBegin(GL_LINES);
            glVertex2f(0,y);
            glVertex2f(50,y);
        glEnd();
        //Rendering pixel value at every 100th pixel
        if(y%100==0)
        {
            itoa(y,chary,10);
            mytext(50,y-6,1.0,1.0,0.0,0,chary);
        }
    }

    //Drawing scale marking for every 20 pixels horizontally
    for(x=100;x<=glutGet(GLUT_WINDOW_WIDTH);x+=20)
    {
        glBegin(GL_LINES);
            glVertex2f(x,0);
            glVertex2f(x,50);
        glEnd();
        //Rendering pixel value at every 200th pixel
        if(x%200==0)
        {
            itoa(x,charx,10);
            mytext(x-20,60,1.0,1.0,0.0,0,charx);
        }
    }

    //Drawing dynamic scale lines corresponging to cursor co-ordinates
    glColor4f(0.0,0.0,0.0,0.5);
    glBegin(GL_LINES);
        //Vertical scale line
        glVertex2f(xval,0);
        glVertex2f(xval,scaleliney);
        //Horizontal scale line
        glVertex2f(0,yval);
        glVertex2f(scalelinex,yval);
    glEnd();
    //Rendering dynamic cursor co-ordinates 
    mytext(7,60,1.0,1.0,0.0,0,"x =");
    mytext(7,30,1.0,1.0,0.0,0,"y =");
    mytext(44,60,1.0,1.0,0.0,0,char_xval);
    mytext(44,30,1.0,1.0,0.0,0,char_yval);
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

void walkingman()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor3f(0.0,1.0,0.0);
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

void colorpalette()
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

    //Displaying previous and current selected colors
    glColor3fv(previous);
    glBegin(GL_POLYGON);
        glVertex2f(100,200);
        glVertex2f(100,300);
        glVertex2f(400,300);
        glVertex2f(400,200);
    glEnd();
    mytext(150,320,1.0,1.0,0.0,0,code[oldcodeslno]);

    glColor3fv(current);
    glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(100,200);
        glVertex2f(400,200);
        glVertex2f(400,100);
    glEnd();
    mytext(150,70,1.0,1.0,0.0,0,code[newcodeslno]);
}

void display(void) 
{
    if(miniproj==0)
    {
        displayInfo();
        glFlush();
        glutSwapBuffers();
    }
    if(miniproj==1)
    {
        walkingman();
        glFlush();
        glutSwapBuffers();
    }
    else if(miniproj==2)
    {
  	    cursorfunc();
	    glFlush();
    }
    else if(miniproj==3)
    {
        colorpalette();
    	glFlush();
    }
}

void reshape(int w, int h) 
{
    if(miniproj==1)
    {
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
    if(miniproj!=1)
    {
        glViewport(0, 0, w, h);
    }
}

void passiveMotionFunc(int x, int y) 
{
    if(miniproj==1)
    {
        lookatx = -5.0 + (double) x / scrw * 10.0;
        lookatz = sqrt(25 - lookatx * lookatx) + centerZ;
        lookatx += centerX;
        double tmpy = -5.0 + (double) y / scrh * 10.0;
        if (tmpy >= -GLOBAL_SIZE * LEG_XSCALE * 2)
            lookaty = tmpy;
        glLoadIdentity();
        gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
    }
    else if(miniproj==2)
    {
        xval=x;
        yval=glutGet(GLUT_WINDOW_HEIGHT)-y;
        itoa(xval,char_xval,10);
        itoa(yval,char_yval,10);
    }
    glutPostRedisplay();
}

void myMouse(int button,int state,int x,int y)
{
    if(miniproj==2)
    {
        if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
            printthis(x,y);
        if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        {
            if(scalelinex==100)
            {
                scalelinex=glutGet(GLUT_WINDOW_WIDTH);
                scaleliney=glutGet(GLUT_WINDOW_HEIGHT);
            }
            else
            {
                scalelinex=scaleliney=100;
            }
        }
    }
    else if(miniproj==3)
    {
        if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        {
            //Converting x and y wrt development computer screen size so that it works on all screen sizes
            float dx=1920/(float)glutGet(GLUT_WINDOW_WIDTH);
            float dy=1080/(float)glutGet(GLUT_WINDOW_HEIGHT);
            sel_clr(dx*x,dy*y);
        }
    }
    glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) 
{
    if(key==27) //Quit on pressing "Esc" key
            exit(0);
    if(miniproj==0)
    {
        switch (key) {
            case '1': system("FinalWin.exe 1"); exit(0);
            case '2': system("FinalWin.exe 2"); exit(0);
            case '3': system("FinalWin.exe 3"); exit(0);
        }
    }
    else if(miniproj==1)
    {
        switch (key) 
        {
            case 'a': vangle = (vangle + 1) % 360; break;
            case 'd': vangle = (vangle - 1) % 360; break;
            case 's': vangle = (vangle + 180) % 360; break;
            case '0': system("FinalWin.exe 0"); exit(0);
            case '2': system("FinalWin.exe 2"); exit(0);
            case '3': system("FinalWin.exe 3"); exit(0);
        }
    }
    else if(miniproj==2)
    {
        switch (key) 
        {
            case '0': system("FinalWin.exe 0"); exit(0);
            case '1': system("FinalWin.exe 1"); exit(0);
            case '3': system("FinalWin.exe 3"); exit(0);
        }
    }
    else if(miniproj==3)
    {
        switch (key) 
        {
            case '0': system("FinalWin.exe 0"); exit(0);
            case '1': system("FinalWin.exe 1"); exit(0);
            case '2': system("FinalWin.exe 2"); exit(0);
        }
    }
    
}

void calculateData(int id) 
{
    if(miniproj==1)
    {
        centerY = legLength * sin(-leftHigherLegAngle / 180.0 * PI) - legLength;
        double mvx = cos(vangle / 180.0 * PI) * 0.035;
        double mvz = sin(vangle / 180.0 * PI) * 0.035;
            //printf("X=%lf Y=%lf Z=%lf\n", centerX, centerY, centerZ);
        if (!dir1)
        {
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
        else 
        {
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
        glutTimerFunc(10, calculateData, 0);
    }
}

int main(int argc, char **argv) 
{
    if(argv[1])
        miniproj=atoi(argv[1]);
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("OpenGL Utility Tools and Walking Man");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutPassiveMotionFunc(passiveMotionFunc);
    glutMouseFunc(myMouse);
    glutFullScreen();
    calculateData(0);
    glutMainLoop();
    return 0;
}
