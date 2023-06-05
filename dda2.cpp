#include<GL/glut.h>
#include<iostream>
using namespace std;

struct Point{
    int x , y ;
    Point(){
        x = y = 0;
    }

    Point(int x , int y){
        this -> x = x;
        this -> y = y;
    }
};

Point points[20];
int count = 0;


int abs(int x){
    return (x<0)? -x : x;
}


void plotPoint(Point a){
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
		glVertex2i(a.x, a.y);
	glEnd();
	glFlush();	
}

void dda(Point a, Point b,int type ){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	float x = a.x, y = a.y;
	int counter = 1;
	bool draw = true ; 
	
	int step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
	
	float Dx = (float(dx)) / step, Dy = ( float (dy))/ step;
	
	plotPoint(Point(a.x, a.y));
	
	for(int i = 0; i <= step; i++){
		x += Dx;
		y += Dy;
		
		a.x = x;
		a.y = y;
		
		if(type == 0){
			plotPoint(Point(a.x, a.y));
		}
		
		//dotted line
		else if(type == 1){
			if(counter % 7 == 0){
				plotPoint(Point(a.x, a.y));
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
				plotPoint(Point(a.x, a.y));
			}
			
		}
		
		counter++;
	}

}

void init(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-400,400,-400,400);
    glFlush();
}

void axis(){

dda(Point(400,0),Point(-400,0),0);
dda(Point(0,400),Point(0,-400),0);
}


void mouse(int button, int state, int x, int y){
 	y = 400 - y;
 	x = x - 400; 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		Point p(x,y);
		points[count++] = p;
	}
}

void keyboard(unsigned char key, int x, int y){

	if(key == 'd'){
		dda(points[0], points[1],2);
		count = 0;
	}
	if(key == 's'){
		dda(points[0], points[1],0);
		count = 0;
	}
	if(key == 'z'){
		dda(points[0], points[1],1);
		count = 0;
	}
	
}


int main(int argc , char** argv){
    glutInit(&argc ,argv);
    glutInitDisplayMode,(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("dda");
    init();
    axis();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0 ;
}

