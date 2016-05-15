
#include<GLUT/GLUT.h>
//#include<glut/gl.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

GLsizei ww=600,wh=800,wx,wy,wx1=600,wy1=800;
int wel=0;
void *currentfont;
int count=0;
float posx,posy;
char *image;
float   a1=0,   a2=0,   a3=0,   b1=0,   b2=0,   b3=0 , a4=0 , b4=0;
int draw;
int undo=0;
float a[100][4];
float b[100][4];
int drw[100];
int m=0;
int k=0;
int s=0;
//const float DEG2RAD = 3.14159/180.0;
int temp1,temp2;
char text[40];
float textx=50,texty=wh-25,textz=0.0;


void setfont(void *font){
    currentfont=font;
}
void    reset()
{
    glColor3f(0.85,0.85,0.85);
    glRectf(0, wh-45,500, wh);
    int i=0;
    a[m][i]=a1;
    a[m][i+1]=a2;
    a[m][i+2]=a3;
    a[m][i+3]=a4;
    b[m][i]=b1;
    b[m][i+1]=b2;
    b[m][i+2]=b3;
    b[m][i+3]=b4;
    drw[m]=draw;
    //printf("%d",drw[m]);
    m++;
    a1=0;
    a2=0;
    b1=0;
    b2=0;
    a3=0;
    b3=0;
    a4=0;
    b4=0;
}


void    drawpoint(int   x,  int y)              //to draw a point
{
    y=wh-y;
    
    if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)))
    {
        
        glBegin(GL_POINTS);
        glVertex2f(x,   y);
        glEnd();
        glFlush();
    }
}

void    delpoint(int    x,  int y)              //to del to first point for undo
{
    
    if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)))
    {
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2f(x,   y);
        glEnd();
        glFlush();
    }
}




void drawstring(float x,float y,float z,char const *string)
{
    char const *c;
    glRasterPos3f(x,y,z);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(currentfont,*c);
    }
}

void	draw_pixel(GLfloat	x,	GLfloat	y)
{
    
    glBegin(GL_POINTS);
    glVertex2f(x,	y);
    glEnd();
    
}



void	plotpixels(GLfloat	p,	GLfloat	q,	GLfloat	x,	GLfloat	y)
{
    draw_pixel(x+p,	y+q);
    draw_pixel(-x+p,	y+q);
    draw_pixel(x+p,	-y+q);
    draw_pixel(-x+p,	-y+q);
    
    
    draw_pixel(y+p,	x+q);
    draw_pixel(-y+p,	x+q);
    draw_pixel(y+p,	-x+q);
    draw_pixel(-y+p,	-x+q);
}


void	draw_circle(GLfloat	p,	GLfloat	q,	GLfloat	r)				/*	to	draw	a	CIRCLE	using	MIDPOINT	CIRCLE	DRAWING	algorithm
                                                                     */
{
    GLfloat	d=1-r,	x=0,	y=r;
    
    while(y>x)
    {
        plotpixels(p,	q,	x,	y);
        if(d<0)	d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        ++x;
    }
    plotpixels(p,	q,	x,	y);
    glFlush();
}


void drawDot (GLint x, GLint y)
{
    
    glBegin (GL_POINTS);
    glVertex2i (x,y);
    glEnd();
}

void symmetricPixels (int x, int y, int xc, int yc)
{
    drawDot (xc + x, yc + y);
    drawDot (xc - x, yc + y);
    drawDot (xc + x, yc - y);
    drawDot (xc - x, yc - y);
}
void down_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x-15,wh-y+15);
    glVertex2f(x,wh-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, wh-y+15);
    glVertex2f(x,wh-y);
    glEnd();
    glFlush();
}
void up_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x-15,wh-y-15);
    glVertex2f(x,wh-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, wh-y-15);
    glVertex2f(x,wh-y);
    glEnd();
    glFlush();
}
void left_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x+15,wh-y+15);
    glVertex2f(x,wh-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, wh-y-15);
    glVertex2f(x,wh-y);
    glEnd();
    glFlush();
}
void right_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x-15,wh-y+15);
    glVertex2f(x,wh-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x-15, wh-y-15);
    glVertex2f(x,wh-y);
    glEnd();
    glFlush();
}
void Ellipse (int a, int b, int xc, int yc)
{
    int aSq,bSq,twoASq,twoBSq,d,dx,dy,x,y;
    aSq = a*a;
    bSq = b*b;
    twoASq = 2*aSq;
    twoBSq = 2*bSq;
    d = bSq - b*aSq + aSq/4;
    dx = 0;
    dy = twoASq*b;
    x = 0;
    y = b;
    
    symmetricPixels(x,y,xc,yc);
    while (dx < dy)
    {
        x++;
        dx += twoBSq;
        if (d >= 0)
        {
            y--;
            dy -= twoASq;
        }
        if (d < 0)
            d += bSq + dx;
        else
            d += bSq + dx - dy;
        symmetricPixels (x,y,xc,yc);
    }
    d = (int)(bSq*(x+0.5)*(x+0.5) + aSq*(y-1)*(y-1) -
              aSq*bSq);
    while (y > 0)
    { y--;
        dy -= twoASq;
        if (d <= 0)
        { x++;
            dx += twoBSq;
        }
        if (d > 0)
            d += aSq - dy;
        else
            d += aSq -dy +dx;
        symmetricPixels(x,y,xc,yc);
    }
    glFlush();
    
}



void	keys(unsigned	char	key,	int	x,	int	y)																		                                        /*	to	get	text from keyboard		*/
{
    
    if(key==127)
    {
        //text[s]=key;
        textx=textx-10;
        glRasterPos3f	(textx,	texty,textz);
        
        glColor3f(0.85, 0.85,   0.85);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[s]);
        
        
        s--;
        
        
    }
    
    else
        
    {
        text[s]=key;
        
        glRasterPos3f	(textx,	texty,textz);
        
        glColor3f(0,	0,	0);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[s]);
        textx=textx+10;
        
        s++;
    }
    
    glFlush();
    
    
    
}


void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(wel==0   ||  wel==1)         {
        
        glClearColor    (0.0,   0.0,    0.0,    1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        setfont(GLUT_BITMAP_HELVETICA_18);
        glColor3f(0,    1,  1);
        drawstring(32*wh/45,    42*wh/45    ,   0.0,    "A  Mini    Project On");
        
        drawstring(22*wh/45,    40*wh/45,   0.0,    "DESIGN AND IMPLEMENTION    OF  FLOWCHART MAKER");
        
        
        
        setfont(GLUT_BITMAP_9_BY_15);
        
        drawstring(33*wh/45,    32*wh/45,   0.0,    "BY:");
        drawstring(20*wh/45,    29*wh/45,   0.0,    "Name : Aishwary Gupta");
        drawstring(20*wh/45,    27*wh/45,   0.0,    "usn : 1PE13CS009");
        
        
        drawstring(44*wh/45,    29*wh/45,   0.0,    "Name : Aman Chaudhary");
        drawstring(44*wh/45,    27*wh/45,   0.0,    "usn : 1PE13CS020");
        
        
        
        drawstring(31*wh/45,    20*wh/45,   0.0,    "UNDER  THE GUIDENCE    OF:");
        
        drawstring(20*wh/45,    17*wh/45,   0.0,    "Mrs. Sudha Y");
        drawstring(20*wh/45,    15*wh/45,   0.0,    "LECTURER,  Dept.   of  CS&E");
        drawstring(20*wh/45,    13*wh/45,   0.0,    "College");
        
        /*drawstring(43*wh/45,    17*wh/45,   0.0,    "Teacher");
         drawstring(43*wh/45,    15*wh/45,   0.0,    "LECTURER,  Dept.   of  CS&E");
         drawstring(43*wh/45,    13*wh/45,   0.0,    "College");*/
        
        
        wel=1;
        
        glFlush();
        glClearColor    (1.0,   1.0,    1.0,    1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
    }
    
    if(wel==2)
    {
        
        count++;
        
        if(count>1)
        {
            
            if(ww!=0    &&  wh!=0)
            {   wx=wx1;
                wy=wy1;
                
                wx1=ww;
                wy1=wh;
            }
            
            glDrawBuffer(GL_FRONT);                                                 /*  selecting   GL_FRONT    buffer      to  write*/
            glRasterPos2f(posx, posy);
            glDrawPixels(wx-wy/10-2,    wy-wy/10-wy/20-1,   GL_RGB, GL_UNSIGNED_BYTE,   image); /*  to  write   pixels  i
                                                                                                 nto    the selected    buffer  */
        }
        glColor3f(0.85, 0.85,   0.85);
        glPointSize(1);
        glLineWidth(1);
        glRectf(0,0,wh/8,wh-(wh/20+10));   // draw grey rectangles.
        glColor3f(0.85,0.85,.85);
        glRectf(0, wh-50, ww, wh);
        glColor3f(1, 0, 0);
        drawstring(ww-750, wh-25, 0.0, "Flowchart maker");
        drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
        
        glColor3f(0.5,  0.5,    0.5);         //to draw the boundry of the main screen.
        glBegin(GL_LINES);
        glVertex2f(wh/8,0);
        glVertex2f(wh/8,wh-(wh/20+10));
        glVertex2f(wh/8+1,0);
        glVertex2f(wh/8+1,wh-(wh/20+10));
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(wh/8,wh-(wh/20+10));
        glVertex2f(ww,wh-(wh/20+10));
        glVertex2f(wh/8,wh-(wh/20+10)+1);
        glVertex2f(ww,  wh-(wh/20+10)+1);
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(wh/8,0);
        glVertex2f(ww,0);
        glVertex2f(wh/8,1);
        glVertex2f(ww,1);
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(ww,0);
        glVertex2f(ww,wh-(wh/20+10));
        glVertex2f(ww-1,0);
        glVertex2f(ww-1,wh-(wh/20+10));
        glEnd();
        
        glColor3f(0,    0,  0);                //tool box specs
        glBegin(GL_LINE_LOOP);
        glVertex2f(2,wh-(wh/20+10));
        glVertex2f(wh/8-2,wh-(wh/20+10)-1);
        glVertex2f(wh/8-2,wh/1.65);
        glVertex2f(2,   wh/1.65);
        glEnd();
        
        
        glBegin(GL_LINES);
        glVertex2f(wh/16,wh-(wh/20+10)-1);
        glVertex2f(wh/16,   wh/1.65);
        
        glVertex2f(2,   18*wh/20-5);
        glVertex2f(wh/8-2,  18*wh/20-5);
        
        glVertex2f(2,   17*wh/20-2);
        glVertex2f(wh/8-2,  17*wh/20-2);
        
        glVertex2f(2,   16*wh/20-2);
        glVertex2f(wh/8-2,  16*wh/20-2);
        
        glVertex2f(2,   15*wh/20-3);
        glVertex2f(wh/8-2,  15*wh/20-3);
        
        glVertex2f(2,   wh/1.43);
        glVertex2f(wh/8-2,  wh/1.43);
        
        glVertex2f(2,   wh/1.53);
        glVertex2f(wh/8-2,  wh/1.53);
        
        
        glEnd();
        
        Ellipse(wh/40,wh/60,wh/32,wh-69);        //draw ellpise option
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(8.5*wh/120,  17.7*wh/20);     // to show the rectangle option.
        glVertex2f(13.5*wh/120-2,   17.7*wh/20);
        glVertex2f(13.5*wh/120-2,   17.1*wh/20);
        glVertex2f(8.5*wh/120,  17.1*wh/20);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(1.1*wh/110,  16.45*wh/20);      // to show diamond symbol
        glVertex2f(3.3*wh/110,16.05*wh/20);
        glVertex2f(5.5*wh/110, 16.45*wh/20);
        glVertex2f(3.3*wh/110,16.85*wh/20);
        glEnd();
        
        glBegin(GL_LINE_LOOP);                 // to show parallelogram option
        glVertex2f(2.2*wh/40,   17.7*wh/20);
        glVertex2f(1.8*wh/40,   17.1*wh/20);
        glVertex2f( wh/90, 17.1*wh/20);
        glVertex2f(1.7*wh/90, 17.7*wh/20);
        glEnd();
        
        glBegin(GL_LINES);                          // to show the line
        glVertex2f(5.5*wh/60,   18.6*wh/20);
        glVertex2f(5.5*wh/60,   18*wh/20);
        //        glVertex2f(5.5*wh/60,   18.6*wh/20);
        //        glVertex2f(5*wh/60, 18.35*wh/20);
        //        glVertex2f(5.5*wh/60,   18.6*wh/20);
        //        glVertex2f(6*wh/60, 18.35*wh/20);
        glEnd();
        
        setfont(GLUT_BITMAP_HELVETICA_10);       // to show undo
        glColor3f(0,0,0);
        drawstring(wh/14,wh-(wh/5.5), 0.0, "UNDO");
        
        setfont(GLUT_BITMAP_HELVETICA_10);       // to show clear screen
        glColor3f(1,0,0);
        drawstring(wh/50,wh-(wh/4.3), 0.0, "CLR");
        
        glColor3f(0,0,0);
        draw_circle(wh/11.11, wh/1.295, 16.0); //to show circle option
        
        down_arrow(wh/34,wh/3.51);
        up_arrow(wh/11,wh/3.75);
        left_arrow(wh/50,wh/3.10);
        right_arrow(wh/10,wh/3.10);
        
        
        
        glFlush();
        
    }
    
    
}



void    mymouse(int btn,    int state,  int x,  int y)
{
    
    
    if(btn==GLUT_LEFT_BUTTON    &&  state==GLUT_DOWN)
    {
        printf("x=%d y=%d \n",x,y);
        setfont(GLUT_BITMAP_9_BY_15);
        
        if(wel==1 || wel==0)
        {
            wel=2;
            display();
        }
        
        if(x>wh/268 && x<wh/17.5 && y>wh/18 && y<wh/10.1)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "START/STOP");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=6;
        }
        
        if(x>wh/16 && x<wh/8 && y>wh/18 && y<wh/9.1)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "LINE");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=1;
            
        }
        if(x>2 && x<wh/16 && y>wh/9.1 && y<wh/6.45)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "PARALLELOGRAM");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=2;
            
        }
        if(x>wh/16 && x<wh/8 && y>wh/9.1 && y<wh/6.45)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "RECTANGLE");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=3;
            
        }
        if(x>2 && x<wh/16 && y>wh/6.45 && y<wh/4.9)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "DIAMOND");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=4;
            
        }
        if((x>wh/16 && x<wh/8&& y>wh/6.45 && y<wh/4.9))
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "UNDO");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            undo=1;
        }
        if(x>2 && x<wh/16 && y>wh/4.9 && y<wh/3.9)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "CLEAR SCREEN");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=5;
            
        }
        
        if(x>wh/16 && x<wh/8.8 && y>wh/5.09 && y<wh/4.14)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "CONNECTOR");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=7;
        }
        
        if(x>wh/200 && x<wh/17.7 && y>wh/4.02 && y<wh/3.49)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "DOWN ARROW");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=8;
        }
        
        if(x>wh/16.32 && x<wh/8.69 && y>wh/4.02 && y<wh/3.49)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "UP ARROW");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=9;
        }
        
        if(x>wh/266.66 && x<wh/17.39 && y>wh/3.43 && y<wh/3)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "LEFT ARROW");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=10;
        }
        
        if(x>wh/16 && x<wh/8.8 && y>wh/3.43 && y<wh/3)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*ww/20, wh-(wh/20), ww, wh);
            glColor3f(1,0,0);
            drawstring(17.5*ww/20,wh-(wh/21) , 0.0, "RIGHT ARROW");
            drawstring(15*ww/20,wh-(wh/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=11;
        }
        
        
        
        if(draw==1)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)) )
            {
                drawpoint(x,y);
                
                a2=a1;
                b2=b1;
                
                a1=x;
                b1=wh-y;
                
                if(a1>(wh/8)+1  &&  a1<ww-2  && b1>2    &&  b1<(wh-(wh/20+10)))
                {
                    if(a2>(wh/8)+1  &&  a2<ww-2  && b2>2    &&  b2<(wh-(wh/20+10)))
                    {
                        temp1=(int)(b2-b1);
                        temp2=(int)(a2-a1);
                        glBegin(GL_LINES);
                        if((abs(temp1)>abs(temp2)))
                        {    glBegin(GL_LINES);
                            glVertex2f(a2,  b2);
                            glVertex2f(a2,  b1);
                            glEnd();
                            /* a1=a2;
                             temp1=int(b1);
                             b2=b1;
                             b1=temp1;*/
                        }
                        else{
                            glBegin(GL_LINES);
                            
                            glVertex2f(a2,  b2);
                            glVertex2f(a1,  b2);
                            glEnd();
                            /* b1=b2;
                             temp1=int(a1);
                             a2=a1;
                             a1=temp1;*/
                            
                        }
                        delpoint(a2,b2);
                        glFlush();
                        reset();
                        
                    }
                }
            }
            
        }
        
        if(draw==2)
        {   glColor3f(0, 0, 0);
            //drawpoint(x, y);
            if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)))
            {
                a1=x-wh/8;
                b1=wh-y;
                a2=x+wh/8;
                b2=b1;
                a3=x+wh/11.6;
                b3=b1-wh/8;
                a4=x-wh/6.15;
                b4=b3;
                
                
                if(a1>(wh/8)+1  &&  a1<ww-2  && b1>2    &&  b1<(wh-(wh/20+10)) )
                {
                    if(a2>(wh/8)+1  &&  a2<ww-2  && b2>2    &&  b2<(wh-(wh/20+10)) )
                    {
                        if(a3>(wh/8)+1  &&  a3<ww-2  && b3>2    &&  b3<(wh-(wh/20+10)) )
                        {
                            
                            if(a4>(wh/8)+1    &&  a4<ww-2  && b4>2    &&  b4<(wh-(wh/20+10)) )
                            {
                                
                                
                                
                                glBegin(GL_LINE_LOOP);
                                glVertex2f(a1,   b1);
                                glVertex2f(a2,   b2);
                                glVertex2f(a3,   b3);
                                glVertex2f(a4,   b4);
                                glEnd();
                                reset();
                                glFlush();
                                
                                
                            }
                        }
                    }
                }
            }
        }
        
        
        if(draw==3)
        {   glColor3f(0, 0, 0);
            //drawpoint(x, y);
            if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)))
            {
                a1=x-wh/8;
                b1=wh-y;
                a2=x+wh/8;
                b2=b1-wh/8;
                
                
                if(a1>(wh/8)+1  &&  a1<ww-2  && b1>2    &&  b1<(wh-(wh/20+10)) )
                {
                    if(a2>(wh/8)+1  &&  a2<ww-2  && b2>2    &&  b2<(wh-(wh/20+10)) )
                    {
                        
                        
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(a1,  b1);
                        glVertex2f(a2,  b1);
                        glVertex2f(a2,  b2);
                        glVertex2f(a1,  b2);
                        glEnd();
                        reset();
                        glFlush();
                        
                        
                    }
                    
                }
            }
            
        }
        
        
        if(draw==4)
        {   glColor3f(0, 0, 0);
            //drawpoint(x, y);
            if(x>(wh/8)+1   &&  x<ww-2  && y>2  &&  y<(wh-(wh/20+10)))
            {
                a1=x;
                b1=wh-y;
                a2=x+wh/14;
                b2=b1-wh/14;
                a3=x;
                b3=b1-wh/7;
                a4=x-wh/14;
                b4=b2;
                
                
                if(a1>(wh/8)+1  &&  a1<ww-2  && b1>2    &&  b1<(wh-(wh/20+10)) )
                {
                    if(a2>(wh/8)+1  &&  a2<ww-2  && b2>2    &&  b2<(wh-(wh/20+10)) )
                    {
                        if(a3>(wh/8)+1  &&  a3<ww-2  && b3>2    &&  b3<(wh-(wh/20+10)) )
                        {
                            
                            if(a4>(wh/8)+1  &&  a4<ww-2  && b4>2    &&  b4<(wh-(wh/20+10)) )
                            {
                                
                                
                                
                                glBegin(GL_LINE_LOOP);
                                glVertex2f(a1,  b1);
                                glVertex2f(a2,  b2);
                                glVertex2f(a3,  b3);
                                glVertex2f(a4,  b4);
                                glEnd();
                                reset();
                                glFlush();
                                
                                
                            }
                            
                        }
                    }
                }
            }
        }
        
        
        if(draw==5)
        {
            
            for(k=0;k<m;k++)
                a[k][0]=a[k][1]=a[k][2]=a[k][3]=0;
            
            for(k=1;k<m;k++)
                b[k][0]=b[k][1]=b[k][2]=b[k][3]=0;
            
            m=0;
            
            
            count=0;
            display();
            
        }
        
        if(draw==6)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && wh-y>2    &&  wh-y<(wh-(wh/20+10)) )
            {
                if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)-(2*wh/32)>2    &&  (wh-y)-(2*wh/32)<(wh-(wh/20+10)) )
                {
                    if(x-(wh/17.78)>(wh/8)+1  &&  x-(wh/17.78)<ww-2  && (wh-y)-wh/32>2    &&  (wh-y)-wh/32<(wh-(wh/20+10)) )
                    {
                        
                        if(x+(wh/17.78)>(wh/8)+1  &&  x+(wh/17.78)<ww-2  && (wh-y)-wh/32>2    &&  (wh-y)-wh/32<(wh-(wh/20+10)) )
                        {
                            
                            a1=x;
                            a2=wh-y;
                            Ellipse(wh/17.78,wh/32,x,(wh-y)-wh/32);
                            reset();
                        }
                    }
                }
            }
        }
        
        if(draw==7)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)-30+30>2    &&  (wh-y)-30+30<(wh-(wh/20+10)) )
            {
                if(x+30>(wh/8)+1  &&  x+30<ww-2  && (wh-y)-30>2    &&  (wh-y)-30<(wh-(wh/20+10)) )
                {
                    if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)-30-30>2    &&  (wh-y)-30-30<(wh-(wh/20+10)) )
                    {
                        
                        if(x-30>(wh/8)+1  &&  x-30<ww-2  && (wh-y)-30>2    &&  (wh-y)-30<(wh-(wh/20+10)) )
                        {
                            
                            a1=x;
                            a2=wh-y;
                            draw_circle(x,(wh-y)-30,30);
                            reset();
                        }
                    }
                }
            }
            
        }
        if(draw==8)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)>2    &&  (wh-y)<(wh-(wh/20+10)) )
            {
                if(x+15>(wh/8)+1  &&  x+15<ww-2  && (wh-y)+15>2    &&  (wh-y)+15<(wh-(wh/20+10)) )
                {
                    if(x-15>(wh/8)+1  &&  x-15<ww-2  && (wh-y)+15>2    &&  (wh-y)+15<(wh-(wh/20+10)) )
                    {
                        
                        a1=x;
                        a2=y;
                        down_arrow(x,y);
                        reset();
                    }
                }
            }
            
        }
        if(draw==9)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)>2    &&  (wh-y)<(wh-(wh/20+10)) )
            {
                if(x+15>(wh/8)+1  &&  x+15<ww-2  && (wh-y)-15>2    &&  (wh-y)-15<(wh-(wh/20+10)) )
                {
                    if(x-15>(wh/8)+1  &&  x-15<ww-2  && (wh-y)-15>2    &&  (wh-y)-15<(wh-(wh/20+10)) )
                    {
                        
                        a1=x;
                        a2=y;
                        up_arrow(x,y);
                        reset();
                    }
                }
            }
            
        }
        if(draw==10)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)>2    &&  (wh-y)<(wh-(wh/20+10)) )
            {
                if(x+15>(wh/8)+1  &&  x+15<ww-2  && (wh-y)-15>2    &&  (wh-y)-15<(wh-(wh/20+10)) )
                {
                    if(x+15>(wh/8)+1  &&  x+15<ww-2  && (wh-y)+15>2    &&  (wh-y)+15<(wh-(wh/20+10)) )
                    {
                        
                        a1=x;
                        a2=y;
                        left_arrow(x,y);
                        reset();
                    }
                }
            }
            
        }
        if(draw==11)
        {
            glColor3f(0, 0, 0);
            if(x>(wh/8)+1  &&  x<ww-2  && (wh-y)>2    &&  (wh-y)<(wh-(wh/20+10)) )
            {
                if(x-15>(wh/8)+1  &&  x-15<ww-2  && (wh-y)+15>2    &&  (wh-y)+15<(wh-(wh/20+10)) )
                {
                    if(x-15>(wh/8)+1  &&  x-15<ww-2  && (wh-y)-15>2    &&  (wh-y)-15<(wh-(wh/20+10)) )
                    {
                        
                        a1=x;
                        a2=y;
                        right_arrow(x,y);
                        reset();
                    }
                }
            }
            
        }
        
        
        
        
        if(undo==1)
        {
            m--;
            if(m<0)
            {    glColor3f(1, 0, 0);
                drawstring(wh/80, wh-25, 0.0, "Nothing to UNDO :)");
                m++;
                
            }
            switch(drw[m])
            {
                case 1:
                    glColor3f(1,1,1);
                    temp1=(int)(b[m][1]-b[m][0]); //b2-b1
                    temp2=(int)(a[m][1]-a[m][0]); //a2-a1
                    glBegin(GL_LINES);
                    if((abs(temp1)>abs(temp2)))
                    {    glBegin(GL_LINES);
                        glVertex2f(a[m][1],  b[m][1]);  //a2,b2
                        glVertex2f(a[m][1],  b[m][0]);   //a2,b2
                        glEnd();
                    }
                    else{
                        glBegin(GL_LINES);
                        
                        glVertex2f(a[m][1],  b[m][1]);  //a2,b2
                        glVertex2f(a[m][0],  b[m][1]); // a1,b2
                        glEnd();
                    }
                    
                    glFlush();
                    undo=0;
                    break;
                case 2:
                    glColor3f(1, 1, 1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(a[m][0],b[m][0]); //a11 b11
                    glVertex2f(a[m][1],b[m][1]);  //a22 b2
                    glVertex2f(a[m][2],b[m][2]);  //a3 b3
                    glVertex2f(a[m][3],b[m][3]);  //a4 b4
                    glEnd();
                    glFlush();
                    undo=0;
                    break;
                case 3:
                    glColor3f(1, 1, 1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(a[m][0],b[m][0]);   //a1b1
                    glVertex2f(a[m][1],b[m][0]);    //a2b1
                    glVertex2f(a[m][1],b[m][1]);   //a2b2
                    glVertex2f(a[m][0],b[m][1]);   //a1b2
                    glEnd();
                    undo=0;
                    glFlush();
                    break;
                case 4:
                    glColor3f(1, 1 ,1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(a[m][0],b[m][0]);   //a1b1
                    glVertex2f(a[m][1],b[m][1]);   //a2b2
                    glVertex2f(a[m][2],b[m][2]);   //a3b3
                    glVertex2f(a[m][3],b[m][3]);   //a4b4
                    glEnd();
                    undo=0;
                    glFlush();
                    break;
                case 6:
                    glColor3f(1, 1 ,1);
                    Ellipse(wh/17.78,wh/32,a[m][0],a[m][1]-wh/32);
                    undo=0;
                    break;
                case 7:
                    //printf("drawing circle with %d ,%d",a[m][0],a[m][1]);
                    glColor3f(1, 1 ,1);
                    draw_circle(a[m][0],a[m][1]-30,30);
                    undo=0;
                    break;
                case 8:
                    glColor3f(1, 1 ,1);
                    down_arrow(a[m][0],a[m][1]);
                    undo=0;
                    break;
                case 9:
                    glColor3f(1, 1 ,1);
                    up_arrow(a[m][0],a[m][1]);
                    undo=0;
                    break;
                case 10:
                    glColor3f(1, 1 ,1);
                    left_arrow(a[m][0],a[m][1]);
                    undo=0;
                    break;
                case 11:
                    glColor3f(1, 1 ,1);
                    right_arrow(a[m][0],a[m][1]);
                    undo=0;
                    break;
                    
                    
                    
                    
                default:; //printf("default");
            }
        }
    }
    
    
    if(btn==GLUT_LEFT_BUTTON    &&  state==GLUT_UP)
    {
        glReadBuffer(GL_FRONT);
        
        
        glReadPixels(wh/10+2,   wh/10,  ww-wh/10-2, wh-wh/10-wh/20-1,GL_RGB,    GL_UNSIGNED_BYTE,   image);
        
        posx=wh/10+2;
        posy=wh/10;
    }
    
}




void    myreshape(GLsizei   w,  GLsizei h)  /*  RESHAPE FUNCTION    */
{
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,    (GLdouble)w,    0.0,    (GLdouble)h,    -1.0,   1.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    glViewport(0,0,w,h);
    glFlush();
    
    
    ww  =   w;
    wh  =   h;
    
    
    glutPostRedisplay();
    
    
    
    
}



int main(int argc, char ** argv)

{
    image   =   (char *)malloc(3*1450*900*sizeof(char));
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|   GLUT_RGB);
    glutCreateWindow("CG PROJECT");
    glutInitWindowSize(ww,wh);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutReshapeFunc(myreshape);
    glutKeyboardFunc(keys);
    glutFullScreen();
    glutMainLoop();
    
}
