#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>

using namespace std;

class Point {
	public:
	
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

Point points[20];
int count = 0;

void plotPoint(int x,int y){
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();	
}

int abs(int x){
	return (x < 0)? -x : x;
}



void gentleLine(Point a, Point b, int type){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	int Dx, Dy;
	
	Dx = (b.x > a.x)? 1 : -1;
	Dy = (b.y > a.y)? 1 : -1;
	int pk = (2 * dy) - dx;
	
	int counter = 1;
	bool draw = true;
	for(int i = 0; i < dx; i++){
		if(pk < 0){
			pk += 2 * dy;
			a.x += Dx;
		}
		else{
			pk += 2 * (dy - dx);
			a.x += Dx;
			a.y += Dy;
		}
		
		//simple Line
		if(type == 0){
			plotPoint(a.x, a.y);
		}
		
		//dotted line
		else if(type == 1){
			if(counter % 7 == 0){
				plotPoint(a.x, a.y);
			}
		}
		//dashed line
		else if (type == 2){
			if(counter % 20 == 0){
				if(draw){
					draw = false;
				}
				else{
					draw = true;
				}
			}
			if(draw){
				plotPoint(a.x, a.y);
			}
			
		}
		
		counter++;
		
		
	}
	
}


void harshLine(Point a, Point b, int type){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	int Dx, Dy;
	
	Dx = (b.x > a.x)? 1 : -1;
	Dy = (b.y > a.y)? 1 : -1;
	int pk = (2 * dx) - dy;
	
	int counter = 1;
	bool draw = true;
	for(int i = 0; i < dy; i++){
		if(pk < 0){
			pk += 2 * dx;
			a.y += Dy;
		}
		else{
			pk += 2 * (dx - dy);
			a.x += Dx;
			a.y += Dy;
		}
		
		//simple Line
		if(type == 0){
			plotPoint(a.x, a.y);
		}
		
		//dotted line
		else if(type == 1){
			if(counter % 7 == 0){
				plotPoint(a.x, a.y);
			}
		}
		//dashed line
		else if (type == 2){
			if(counter % 20 == 0){
				if(draw){
					draw = false;
				}
				else{
					draw = true;
				}
			}
			if(draw){
				plotPoint(a.x, a.y);
			}
			
		}
		cout<<counter<<endl;
		counter++;
	}
	
}

void bresenham(Point a, Point b, int type){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	(dx > dy)? gentleLine(a,b,type) : harshLine(a,b,type);
	
}



void axes(){
	Point a(-500,0), b(500,0), c(0,-500), d(0,500);
	bresenham(a,b,0);
	bresenham(c,d,0);
}

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500,500,-500,500);
	axes();
	glFlush();
}

void mouse(int button, int state, int x, int y){
 	y = 500 - y;
 	x = x - 500; 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		Point p(x,y);
		points[count++] = p;
	}
}

void keyboard(unsigned char key, int x, int y){
	if(key == 'd'){
		bresenham(points[0], points[1],2);
		count = 0;
	}
	if(key == 's'){
		bresenham(points[0], points[1],0);
		count = 0;
	}
	if(key == 'z'){
		bresenham(points[0], points[1],1);
		count = 0;
	}
	
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham");
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
