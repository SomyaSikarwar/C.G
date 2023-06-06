#include<iostream>
#include<GL/glut.h>
#include<GL/gl.h>
#include<cmath>

using namespace std;

struct Point {
	int x;
	int y;
	
	Point(){
		x = 0;
		y = 0;
	}
	
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

struct Color{
	int r, g, b;
	
	Color(){
		r = 1;
		g = 1;
		b = 1;
	} 
	
	Color(int r, int g, int b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

int yOffset = 0;


void plotPoint(Point a, Color color){
	glPointSize(3);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(a.x, a.y);
	glEnd();	
}


//using 4 control points.
Point calcBazier(Point a, Point b, Point c, Point d, float t){
	Point p;
	
	p.x = ((pow(1-t,3) * a.x) + (3 * t * pow(1-t, 2) * b.x) + (3 * pow(t,2) * (1-t) * c.x) + (pow(t,3) * d.x));
	p.y = ((pow(1-t,3) * a.y) + (3 * t * pow(1-t, 2) * b.y) + (3 * pow(t,2) *  (1-t) * c.y) + (pow(t,3) * d.y));
	
	return p;	
}

void bazierPlot(Color color){

	Point a(200,500);
	Point b(400,500 + yOffset);
	Point c(600,500 - yOffset);
	Point d(800,500);
	
	for(float t = 0; t < 1; t += 0.002){
		plotPoint(calcBazier(a, b, c, d, t), color);
	}
	
	glFlush();
	
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,1000,0,1000);
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	if(key == '+'){
		bazierPlot(Color(0,0,0));
		yOffset += 70;
		bazierPlot(Color(1,1,1));
		
	}
	
	if(key == '-'){
		bazierPlot(Color(0,0,0));
		yOffset -= 70;
		bazierPlot(Color(1,1,1));
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bazier");
	glutKeyboardFunc(keyboard);
	init();
	bazierPlot(Color(1,1,1));
	glutMainLoop();
}
