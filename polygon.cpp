#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

int xmax,ymax,xmin,ymin;
int input[2][10];
float output[2][10],output1[2][10],output2[2][10],output3[2][10];
int v,v4,k;

int Round(float a)
{
    return (int)(a+0.5);
}

void DDA(float xa,float ya,float xb,float yb)
{
    float dx=xb - xa;
    float dy=yb - ya;
    float steps;
    
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    
    float xin,yin;
    xin = dx/steps;
    yin = dy/steps;
    
    float x,y;
    x=xa;
    y=ya;
    glVertex2d(Round(x),Round(y));
    
    for(int i=0;i<steps;i++)
    {
        x = x + xin;
        y = y + yin;
        glVertex2d(Round(x),Round(y));
    }
}

void leftclip(float xa,float ya,float xb,float yb)
{
    float x,y,m;
    m = (yb-ya)/(xb-xa);
    
    if(xa<xmin && xb>xmin)
    {
        x = xmin;
        y = ya + m*(x-xa);
        
        output[0][k]=x;
        output[1][k]=y;
        k = k+1;
        
        output[0][k]=xb;
        output[1][k]=yb;
        k = k+1;
    }
    if(xa>xmin && xb>xmin)
    {
        output[0][k]=xb;
        output[1][k]=yb;
        k = k+1;
    }
    if(xa>xmin && xb<xmin)
    {
        x = xmin;
        y = ya + m*(x-xa);
        
        output[0][k]=x;
        output[1][k]=y;
        k = k+1;
    }
}

void rightclip(float xa,float ya,float xb,float yb)
{
    float x,y,m;
    m = (yb-ya)/(xb-xa);
    
    if(xa>xmax && xb<xmax)
    {
        x = xmax;
        y = ya + m*(x-xa);
        
        output1[0][k]=x;
        output1[1][k]=y;
        k = k+1;
        
        output1[0][k]=xb;
        output1[1][k]=yb;
        k = k+1;
    }
    if(xa<xmax && xb<xmax)
    {
        output1[0][k]=xb;
        output1[1][k]=yb;
        k = k+1;
    }
    if(xa<xmax && xb>xmax)
    {
        x = xmax;
        y = ya + m*(x-xa);
        
        output1[0][k]=x;
        output1[1][k]=y;
        k = k+1;
    }
}
void bottomclip(float xa,float ya,float xb,float yb)
{
    float x,y,m;
    m = (yb-ya)/(xb-xa);
    
    if(ya<ymin && yb>ymin)
    {
       y = ymin;
       x = xa + (y-ya)/m;
        
        output2[0][k]=x;
        output2[1][k]=y;
        k = k+1;
        
        output2[0][k]=xb;
        output2[1][k]=yb;
        k = k+1;
    }
    if(ya>ymin && yb>ymin)
    {
        output2[0][k]=xb;
        output2[1][k]=yb;
        k = k+1;
    }
    if(ya>ymin && yb<ymin)
    {
         y = ymin;
         x = xa + (y-ya)/m;
        
        output2[0][k]=x;
        output2[1][k]=y;
        k = k+1;
    }
}
void topclip(float xa,float ya,float xb,float yb)
{
    float x,y,m;
    m = (yb-ya)/(xb-xa);
    
    if(ya>ymax && yb<ymax)
    {
       y = ymax;
       x = xa + (y-ya)/m;
        
        output3[0][k]=x;
        output3[1][k]=y;
        k = k+1;
        
        output3[0][k]=xb;
        output3[1][k]=yb;
        k = k+1;
    }
    if(ya<ymax && yb<ymax)
    {
        output3[0][k]=xb;
        output3[1][k]=yb;
        k = k+1;
    }
    if(ya<ymax && yb>ymax)
    {
         y = ymax;
         x = xa + (y-ya)/m;
        
        output3[0][k]=x;
        output3[1][k]=y;
        k = k+1;
    }
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    DDA(xmin,ymin,xmax,ymin);
    DDA(xmax,ymin,xmax,ymax);
    DDA(xmax,ymax,xmin,ymax);
    DDA(xmin,ymax,xmin,ymin);
    
    glColor3f(1.0,1.0,0.0);
    
    int i;
    for(i=0;i<v-1;i++)
    {
        DDA(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
    }
    DDA(input[0][i],input[1][i],input[0][0],input[1][0]);
    
    glColor3f(1.0,0.0,0.0);
    int j;
    for(j=0;j<v4-1;j++)
    {
        DDA(output3[0][j],output3[1][j],output3[0][j+1],output3[1][j+1]);
    }
    DDA(output3[0][j],output3[1][j],output3[0][0],output3[1][0]);
    printf("Hello");
    glEnd();
    glFlush();
}

int main(int argc,char** argv)
{
    printf("Enter the xmax =");
  scanf("%d",&xmax);
  printf("Enter the ymax =");
  scanf("%d",&ymax);
  printf("Enter the xmin =");
  scanf("%d",&xmin);
  printf("Enter the ymin =");
  scanf("%d",&ymin);
  
  printf("Enter the number of vertices = ");
  scanf("%d",&v);
  
  for(int i=0;i<v;i++)
  {
      printf("Enter the X co-ordinate");
      scanf("%d",&input[0][i]);
      printf("Enter the Y co-ordinate");
      scanf("%d",&input[1][i]);
  }
  
  int a;
  for(a=0;a<v-1;a++)
  {
      leftclip(input[0][a],input[1][a],input[0][a+1],input[1][a+1]);
  }
  leftclip(input[0][a],input[1][a],input[0][0],input[1][0]);
  
  int v1=k;
  k=0;
  
  int b;
  for(b=0;b<v1-1;b++)
  {
      rightclip(output[0][b],output[1][b],output[0][b+1],output[1][b+1]);
  }
  rightclip(output[0][b],output[1][b],output[0][0],output[1][0]);
  
  int v2=k;
  k=0;
  
   int c;
  for(c=0;c<v2-1;c++)
  {
      bottomclip(output1[0][c],output1[1][c],output1[0][c+1],output1[1][c+1]);
  }
  bottomclip(output1[0][c],output1[1][c],output1[0][0],output1[1][0]);
  
  int v3=k;
  k=0;
  
  int d;
  for(d=0;d<v3-1;d++)
  {
      topclip(output2[0][d],output2[1][d],output2[0][d+1],output2[1][d+1]);
  }
  topclip(output2[0][d],output2[1][d],output2[0][0],output2[1][0]);
  
   v4=k;
  
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,800);
    glutCreateWindow("PolyClip");
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0,800,0,800);
    glutDisplayFunc(draw);
    glutMainLoop();

}
