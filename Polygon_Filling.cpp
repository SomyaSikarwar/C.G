#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>

#define errorMargin 0.00001

using namespace std;

struct Point{
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
	float r, g, b;
	
	Color(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	Color(){
		r = 1;
		g = 1;
		b = 1;
	}
};

Color interiorColor(0,0,0);

Point points[20];
int count = 0;

void init(){
	glClearColor(interiorColor.r, interiorColor.g, interiorColor.b ,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,1000,0,1000);
	glFlush();
}

void plotPoint(Point a){
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
		glVertex2i(a.x, a.y);
	glEnd();
	glFlush();	
}

void DDA(Point a, Point b){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	float x = a.x, y = a.y;
	
	int step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
	
	float Dx = (float(dx)) / step, Dy = (float(dy))/ step;
	
	plotPoint(Point(a.x, a.y));
	
	for(int i = 0; i <= step; i++){
		x += Dx;
		y += Dy;
		
		a.x = x;
		a.y = y;
		
		plotPoint(Point(a.x, a.y));
	}

}


Color getPixelColor(Point a){
	Color color;
	glReadPixels(a.x, a.y, 1.0, 1.0, GL_RGB, GL_FLOAT, &color);
	return color;
}

bool sameColor(Color a, Color b){
	return abs(a.r - b.r) < errorMargin && abs(a.g - b.g) < errorMargin && abs(a.b - b.b) < errorMargin;
}

void colorPixel(Point a, Color color){
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(a.x, a.y);
	glEnd();
	glFlush();
}

void floodFill(Point seed, Color fillColor = Color(1,0,1)){
	//default color mentioned 
	//by the point should be 
	//the only color which should be 
	//filled with fill color.
	
	Color pixelColor = getPixelColor(seed);
	
	int x = seed.x, y = seed.y;
	
	if(sameColor(pixelColor, interiorColor)){
		colorPixel(Point(x,y), fillColor);
		
		floodFill(Point(x+1,y), fillColor);
		floodFill(Point(x-1,y), fillColor);
		floodFill(Point(x, y+1), fillColor);
		floodFill(Point(x,y-1), fillColor);
	}
	
}

void boundryFill(Point seed, Color fillColor, Color boundryColor = Color(0,0,1)){

	//only pixels not having boundry color and fill color should be colored.
	
	Color pixelColor = getPixelColor(seed);
	
	int x = seed.x, y = seed.y;
	
	if(!sameColor(pixelColor, boundryColor) && !sameColor(pixelColor, fillColor)){
		colorPixel(Point(x,y), fillColor);
		
		boundryFill(Point(x+1,y), fillColor, boundryColor);
		boundryFill(Point(x-1,y), fillColor, boundryColor);
		boundryFill(Point(x, y+1), fillColor, boundryColor);
		boundryFill(Point(x,y-1), fillColor, boundryColor);
	}
}


void mouse(int button, int state, int x, int y){
	y = 1000 - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout<<"X : "<<x<<"Y : "<<y<<endl;
		points[count++] = Point(x,y);
	}

	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		for(int i = 0; i < count; i++){
			cout<<points[i].x<<" "<<points[i].y<<endl;
		}
	}
	
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		for(int i = 0; i < count; i++){
			if(i+1 < count)
				DDA(points[i], points[i+1]);
			else
				DDA(points[i], points[0]);
		}
		count = 0;
		
		
	}
}

void keyboard(unsigned char key, int x, int y){
	
	if(key == 'f'){
		floodFill(points[0]);
		count = 0;
	}
	
	if(key == 'b'){
		boundryFill(points[0], Color(0,0,1));
		count = 0;
	}
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Filling");
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
