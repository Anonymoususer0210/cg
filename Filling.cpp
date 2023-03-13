#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;


struct Point{
    int x;
    int y;
};

struct Color{
    float r;
    float g;
    float b;
};

vector<Point> P;
Point winmin = {50,50};
Point winmax = {600,400};

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
    glClearColor(1,1,1,0.5);
}

static void display(void)
{
    /*glBegin(GL_LINE_LOOP);
    glVertex2d(winmin.x,winmin.y);
    glVertex2d(winmin.x,winmax.y);
    glVertex2d(winmax.x,winmax.y);
    glVertex2d(winmax.x,winmin.y);
    glEnd();
    glFlush();*/
}

Color getPixelColor(int x, int y)
{
	struct Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(int x, int y,struct Color color) {

	glBegin(GL_POINTS);
	glColor3f(color.r,color.g,color.b);
	glVertex2f(x,y);
	glEnd();
	//glFlush();
}

void flood(int x, int y,struct Color old_col,struct Color new_col)
{
	struct 	Color color;
	color = getPixelColor(x,y);
	cout<<color.r<<","<<color.g<<","<<color.b<<endl;

  //check current pixel is old_color or not
      if(color.r==new_col.r && color.g==new_col.g && color.b == new_col.b)
        return;
      if (color.r==old_col.r && color.g==old_col.g && color.b == old_col.b)
        {
          // put new pixel with new color
          setPixelColor(x,y,new_col);
          glFlush();
          flood(x + 1, y,old_col,new_col);
          flood(x - 1, y,old_col,new_col);
          flood(x, y + 1,old_col,new_col);
          flood(x, y - 1,old_col,new_col);
          return;
        }
        return;
}

void boundary(int x,int y,Color boundarycol, Color fillcol)
{
    Color color;
    color = getPixelColor(x,y);
    cout<<color.r<<","<<color.g<<","<<color.b<<endl;
    if((color.r == boundarycol.r && color.g == boundarycol.g && color.b == boundarycol.b) ||
       (color.r == fillcol.r && color.g == fillcol.g && color.b == fillcol.b))
       return;
    if((color.r != boundarycol.r || color.g != boundarycol.g || color.b != boundarycol.b) &&
       (color.r != fillcol.r || color.g != fillcol.g || color.b != fillcol.b))
    {
        setPixelColor(x,y,fillcol);
        glFlush();
        boundary(x + 1, y,boundarycol,fillcol);
        boundary(x - 1, y,boundarycol,fillcol);
        boundary(x, y + 1,boundarycol,fillcol);
        boundary(x, y - 1,boundarycol,fillcol);
        return;
    }
}

void key(unsigned char ch,int x,int y)
{
    if(ch == 'f' || ch == 'F')
    {
        struct Color old_col={0.0,0.0,0.0};
        struct Color new_col={1.0,0.0,0.0};
        Point centroid;
        float sumx = 0;
        float sumy = 0;
        for(int i = 0; i< P.size(); i++)
        {
            sumx += P[i].x;
            sumy += P[i].y;
        }
        centroid.x = sumx/P.size();
        centroid.y = sumy/P.size();

        struct Color boundarycol = {1.0,0.0,0.0};
        struct Color fillcol = {0.0,1.0,0.0};

        flood(centroid.x,centroid.y,old_col,new_col);
        //boundary(centroid.x,centroid.y,boundarycol,fillcol);
    }
}

void mouse(int button, int state, int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int x1 = x;
        int y1 = 480 - y;
        glBegin(GL_POINTS);
        glColor3d(1,0,0);
        glVertex2d(x1,y1);
        glEnd();
        Point P1 = {x1,y1};
        P.push_back(P1);
        glFlush();
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glColor3d(1,0,0);
        glBegin(GL_LINE_LOOP);
        for(int i = 0;i<P.size();i++)
        {
            glVertex2d(P[i].x,P[i].y);
        }
        glEnd();
    }
    glFlush();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Polygon Filling");
    init();
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
