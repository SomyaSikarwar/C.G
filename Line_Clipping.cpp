#include<GL/glut.h>
#include<stdio.h>

int xmin,ymin,xmax,ymax,xa,ya,xb,yb;
int Outcode1[4];
int Outcode2[4];
int And[4];

int round1(float a)
{
    return (int)(a+0.5);
}

void DDA(int xa,int ya,int xb,int yb)
{
    int dx = xb - xa;
    int dy = yb - ya;
    int steps;
    
    if(abs(dx)>abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float xin , yin;
    
    xin = dx/(float)steps;
    yin = dy/(float)steps;
    
    float x=xa;
    float y=ya;
    glVertex2i(round1(x),round1(y));
    
    for(int i=0;i<steps;i++)
    {
        x = x + xin;
        y = y + yin;
        glVertex2i(round1(x),round1(y));
    }
}

void clip(int xa ,int ya,int xb,int yb)
{
    for(int i=0;i<4;i++)
    {
        Outcode1[i]=0;
        Outcode2[i]=0;
    }
    if(ya>ymax)
    {
        Outcode1[0]=1;
    }
    if(ya<ymin)
    {
        Outcode1[1]=1;
    }
    if(xa>xmax)
    {
        Outcode1[2]=1;
    }
    if(xa<xmin)
    {
        Outcode1[3]=1;
    }
    if(yb>ymax)
    {
        Outcode2[0]=1;
    }
    if(yb<ymin)
    {
        Outcode2[1]=1;
    }
    if(xb>xmax)
    {
        Outcode2[2]=1;
    }
    if(xb<xmin)
    {
        Outcode2[3]=1;
    }
  
  //step1
  int flag=0;
  for(int i=0;i<4;i++)
  {
        if(Outcode1[i]==0 && Outcode2[i]==0)
        {
          continue;
        }
        else
        {
          flag=1;
          break;
        }
  }
  if(flag==0)
  {
    DDA(xa,ya,xb,yb);
  }
  //step2
  
  else
  {
        for(int j=0;j<4;j++)
        {
          And[j] = Outcode1[j] & Outcode2[j];
        }
        
        int flag1=0;
        for(int k=0;k<4;k++)
        {
            if(And[k]==0)
            {
              continue;
            }
            else
            {
              flag1=1;
              break;
            }
        }
        
        if(flag1==0)
        {
            int a,b,c,d;
            float m=(yb-ya)/(xb-xa);
            
            if(Outcode1[0]==1)
            {
              b=ymax;
              a=xa+(1/m)*(b-ya);
            }
            else if(Outcode1[1]==1)
            {
              b=ymin;
              a=xa+(1/m)*(b-ya);
            }
            else if(Outcode1[2]==1)
            {
              a=xmax;
              b=ya+m*(a-xa);
            }
            else if(Outcode1[3]==1)
            {
              a=xmin;
              b=ya+m*(a-xa);
            }
            else
            {
              a=xa;
              b=ya;
            }
            
            if(Outcode2[0]==1)
            {
              d=ymax;
              c=xa+(1/m)*(d-ya);
            }
            else if(Outcode2[1]==1)
            {
              d=ymin;
              c=xa+(1/m)*(d-ya);
            }
            else if(Outcode2[2]==1)
            {
              c=xmax;
              d=ya+m*(c-xa);
            }
            else if(Outcode2[3]==1)
            {
              c=xmin;
              d=ya+m*(c-xa);
            }
            else
            {
              c=xb;
              d=yb;
            }
            DDA(a,b,c,d);
        }
  }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    DDA(xmin,ymin,xmax,ymin);
    DDA(xmax,ymin,xmax,ymax);
    DDA(xmax,ymax,xmin,ymax);
    DDA(xmin,ymax,xmin,ymin);
    glColor3f(1.0,0.0,0.0);
    DDA(xa,ya,xb,yb);
    glColor3f(0.0,1.0,0.0);
    clip(xa,ya,xb,yb);
    glEnd();
    glFlush();
}

int main(int argc , char** argv)
{
    printf("Enter the min size");
    scanf("%d",&xmin);
    scanf("%d",&ymin);
    printf("Enter the max size");
    scanf("%d",&xmax);
    scanf("%d",&ymax);
    printf("Enter the line coordinates");
    scanf("%d",&xa);
    scanf("%d",&ya);
    scanf("%d",&xb);
    scanf("%d",&yb);
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Line clipping");
    
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0,800,0,800);
    glutDisplayFunc(draw);
    
    glutMainLoop();
}
