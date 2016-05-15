
#include<GLUT/GLUT.h>
//#include<glut/gl.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

GLsizei window_width=600,window_height=800;
GLsizei wx,wy,wx1=600,wy1=800;
int screenIndex=0;
void *currentfont;
int count=0;
float posx,posy;
char *image;
float   a1=0,   a2=0,   a3=0,   b1=0,   b2=0,   b3=0 , a4=0 , b4=0;
int draw;
int undo=0;
float flowchart_element_x[100][4];
float flowchart_element_y[100][4];
int drw[100];
int element_index=0;
int k=0;
int s=0;
//const float DEG2RAD = 3.14159/180.0;
int temp1,temp2;
char text[40];
float textx=0,texty=0,textz=0;
const float GUI_GRAY = 0.85f;

void setfont(void *font){
    currentfont=font;
}

void stack_push(){
    int i = 0;
    flowchart_element_x[element_index][i]=a1;
    flowchart_element_x[element_index][i+1]=a2;
    flowchart_element_x[element_index][i+2]=a3;
    flowchart_element_x[element_index][i+3]=a4;
    flowchart_element_y[element_index][i]=b1;
    flowchart_element_y[element_index][i+1]=b2;
    flowchart_element_y[element_index][i+2]=b3;
    flowchart_element_y[element_index][i+3]=b4;
    drw[element_index++]=draw;
}

void clear_left_status(){
    
}

void clear_right_status(){
    glColor3f(GUI_GRAY, GUI_GRAY, GUI_GRAY);
    glRectf(0, window_height-45, 500, window_height);
}
/*
 Resets all the variables being used
 */
void reset()
{
    clear_left_status();
    stack_push();
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
    y=window_height-y;
    
    if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)))
    {
        
        glBegin(GL_POINTS);
        glVertex2f(x,   y);
        glEnd();
        glFlush();
    }
}

void    delpoint(int    x,  int y)              //to del to first point for undo
{
    
    if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)))
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
    glVertex2f(x-15,window_height-y+15);
    glVertex2f(x,window_height-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, window_height-y+15);
    glVertex2f(x,window_height-y);
    glEnd();
    glFlush();
}
void up_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x-15,window_height-y-15);
    glVertex2f(x,window_height-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, window_height-y-15);
    glVertex2f(x,window_height-y);
    glEnd();
    glFlush();
}
void left_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x+15,window_height-y+15);
    glVertex2f(x,window_height-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+15, window_height-y-15);
    glVertex2f(x,window_height-y);
    glEnd();
    glFlush();
}
void right_arrow(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x-15,window_height-y+15);
    glVertex2f(x,window_height-y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x-15, window_height-y-15);
    glVertex2f(x,window_height-y);
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
    
    if(screenIndex==0   ||  screenIndex==1)         {
        
        glClearColor    (0.0,   0.0,    0.0,    1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        setfont(GLUT_BITMAP_HELVETICA_18);
        glColor3f(0,    1,  1);
        drawstring(32*window_height/45,    42*window_height/45    ,   0.0,    "A  Mini    Project On");
        
        drawstring(22*window_height/45,    40*window_height/45,   0.0,    "DESIGN AND IMPLEMENTION    OF  FLOWCHART MAKER");
        
        
        
        setfont(GLUT_BITMAP_9_BY_15);
        
        drawstring(33*window_height/45,    32*window_height/45,   0.0,    "BY:");
        drawstring(20*window_height/45,    29*window_height/45,   0.0,    "Name : Aishwary Gupta");
        drawstring(20*window_height/45,    27*window_height/45,   0.0,    "usn : 1PE13CS009");
        
        
        drawstring(44*window_height/45,    29*window_height/45,   0.0,    "Name : Aman Chaudhary");
        drawstring(44*window_height/45,    27*window_height/45,   0.0,    "usn : 1PE13CS020");
        
        
        
        drawstring(31*window_height/45,    20*window_height/45,   0.0,    "UNDER  THE GUIDENCE    OF:");
        
        drawstring(20*window_height/45,    17*window_height/45,   0.0,    "Mrs. Sudha Y");
        drawstring(20*window_height/45,    15*window_height/45,   0.0,    "LECTURER,  Dept.   of  CS&E");
        drawstring(20*window_height/45,    13*window_height/45,   0.0,    "College");
        
        /*drawstring(43*wh/45,    17*wh/45,   0.0,    "Teacher");
         drawstring(43*wh/45,    15*wh/45,   0.0,    "LECTURER,  Dept.   of  CS&E");
         drawstring(43*wh/45,    13*wh/45,   0.0,    "College");*/
        
        
        screenIndex=1;
        
        glFlush();
        glClearColor    (1.0,   1.0,    1.0,    1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
    }
    
    if(screenIndex==2)
    {
        
        count++;
        
        if(count>1)
        {
            
            if(window_width!=0    &&  window_height!=0)
            {   wx=wx1;
                wy=wy1;
                
                wx1=window_width;
                wy1=window_height;
            }
            
            glDrawBuffer(GL_FRONT);                                                 /*  selecting   GL_FRONT    buffer      to  write*/
            glRasterPos2f(posx, posy);
            glDrawPixels(wx-wy/10-2,    wy-wy/10-wy/20-1,   GL_RGB, GL_UNSIGNED_BYTE,   image); /*  to  write   pixels  i
                                                                                                 nto    the selected    buffer  */
        }
        glColor3f(0.85, 0.85,   0.85);
        glPointSize(1);
        glLineWidth(1);
        glRectf(0,0,window_height/8,window_height-(window_height/20+10));   // draw grey rectangles.
        glColor3f(0.85,0.85,.85);
        glRectf(0, window_height-50, window_width, window_height);
        glColor3f(1, 0, 0);
        drawstring(window_width-750, window_height-25, 0.0, "Flowchart maker");
        drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
        
        glColor3f(0.5,  0.5,    0.5);         //to draw the boundry of the main screen.
        glBegin(GL_LINES);
        glVertex2f(window_height/8,0);
        glVertex2f(window_height/8,window_height-(window_height/20+10));
        glVertex2f(window_height/8+1,0);
        glVertex2f(window_height/8+1,window_height-(window_height/20+10));
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(window_height/8,window_height-(window_height/20+10));
        glVertex2f(window_width,window_height-(window_height/20+10));
        glVertex2f(window_height/8,window_height-(window_height/20+10)+1);
        glVertex2f(window_width,  window_height-(window_height/20+10)+1);
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(window_height/8,0);
        glVertex2f(window_width,0);
        glVertex2f(window_height/8,1);
        glVertex2f(window_width,1);
        glEnd();
        
        glColor3f(0.5,  0.5,    0.5);
        glBegin(GL_LINES);
        glVertex2f(window_width,0);
        glVertex2f(window_width,window_height-(window_height/20+10));
        glVertex2f(window_width-1,0);
        glVertex2f(window_width-1,window_height-(window_height/20+10));
        glEnd();
        
        glColor3f(0,    0,  0);                //tool box specs
        glBegin(GL_LINE_LOOP);
        glVertex2f(2,window_height-(window_height/20+10));
        glVertex2f(window_height/8-2,window_height-(window_height/20+10)-1);
        glVertex2f(window_height/8-2,window_height/1.65);
        glVertex2f(2,   window_height/1.65);
        glEnd();
        
        
        glBegin(GL_LINES);
        glVertex2f(window_height/16,window_height-(window_height/20+10)-1);
        glVertex2f(window_height/16,   window_height/1.65);
        
        glVertex2f(2,   18*window_height/20-5);
        glVertex2f(window_height/8-2,  18*window_height/20-5);
        
        glVertex2f(2,   17*window_height/20-2);
        glVertex2f(window_height/8-2,  17*window_height/20-2);
        
        glVertex2f(2,   16*window_height/20-2);
        glVertex2f(window_height/8-2,  16*window_height/20-2);
        
        glVertex2f(2,   15*window_height/20-3);
        glVertex2f(window_height/8-2,  15*window_height/20-3);
        
        glVertex2f(2,   window_height/1.43);
        glVertex2f(window_height/8-2,  window_height/1.43);
        
        glVertex2f(2,   window_height/1.53);
        glVertex2f(window_height/8-2,  window_height/1.53);
        
        
        glEnd();
        
        Ellipse(window_height/40,window_height/60,window_height/32,window_height-69);        //draw ellpise option
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(8.5*window_height/120,  17.7*window_height/20);     // to show the rectangle option.
        glVertex2f(13.5*window_height/120-2,   17.7*window_height/20);
        glVertex2f(13.5*window_height/120-2,   17.1*window_height/20);
        glVertex2f(8.5*window_height/120,  17.1*window_height/20);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(1.1*window_height/110,  16.45*window_height/20);      // to show diamond symbol
        glVertex2f(3.3*window_height/110,16.05*window_height/20);
        glVertex2f(5.5*window_height/110, 16.45*window_height/20);
        glVertex2f(3.3*window_height/110,16.85*window_height/20);
        glEnd();
        
        glBegin(GL_LINE_LOOP);                 // to show parallelogram option
        glVertex2f(2.2*window_height/40,   17.7*window_height/20);
        glVertex2f(1.8*window_height/40,   17.1*window_height/20);
        glVertex2f( window_height/90, 17.1*window_height/20);
        glVertex2f(1.7*window_height/90, 17.7*window_height/20);
        glEnd();
        
        glBegin(GL_LINES);                          // to show the line
        glVertex2f(5.5*window_height/60,   18.6*window_height/20);
        glVertex2f(5.5*window_height/60,   18*window_height/20);
        //        glVertex2f(5.5*wh/60,   18.6*wh/20);
        //        glVertex2f(5*wh/60, 18.35*wh/20);
        //        glVertex2f(5.5*wh/60,   18.6*wh/20);
        //        glVertex2f(6*wh/60, 18.35*wh/20);
        glEnd();
        
        setfont(GLUT_BITMAP_HELVETICA_10);       // to show undo
        glColor3f(0,0,0);
        drawstring(window_height/14,window_height-(window_height/5.5), 0.0, "UNDO");
        
        setfont(GLUT_BITMAP_HELVETICA_10);       // to show clear screen
        glColor3f(1,0,0);
        drawstring(window_height/50,window_height-(window_height/4.3), 0.0, "CLR");
        
        glColor3f(0,0,0);
        draw_circle(window_height/11.11, window_height/1.295, 16.0); //to show circle option
        
        down_arrow(window_height/34,window_height/3.51);
        up_arrow(window_height/11,window_height/3.75);
        left_arrow(window_height/50,window_height/3.10);
        right_arrow(window_height/10,window_height/3.10);
        
        
        
        glFlush();
        
    }
    
    
}



void    mymouse(int btn,    int state,  int x,  int y)
{
    
    
    if(btn==GLUT_LEFT_BUTTON    &&  state==GLUT_DOWN)
    {
        printf("x=%d y=%d \n",x,y);
        setfont(GLUT_BITMAP_9_BY_15);
        
        if(screenIndex==1 || screenIndex==0)
        {
            screenIndex=2;
            display();
        }
        
        if(x>window_height/268 && x<window_height/17.5 && y>window_height/18 && y<window_height/10.1)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "START/STOP");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=6;
        }
        
        if(x>window_height/16 && x<window_height/8 && y>window_height/18 && y<window_height/9.1)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "LINE");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=1;
            
        }
        if(x>2 && x<window_height/16 && y>window_height/9.1 && y<window_height/6.45)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "PARALLELOGRAM");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=2;
            
        }
        if(x>window_height/16 && x<window_height/8 && y>window_height/9.1 && y<window_height/6.45)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "RECTANGLE");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=3;
            
        }
        if(x>2 && x<window_height/16 && y>window_height/6.45 && y<window_height/4.9)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "DIAMOND");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=4;
            
        }
        if((x>window_height/16 && x<window_height/8&& y>window_height/6.45 && y<window_height/4.9))
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "UNDO");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            undo=1;
        }
        if(x>2 && x<window_height/16 && y>window_height/4.9 && y<window_height/3.9)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "CLEAR SCREEN");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            
            draw=5;
            
        }
        
        if(x>window_height/16 && x<window_height/8.8 && y>window_height/5.09 && y<window_height/4.14)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "CONNECTOR");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=7;
        }
        
        if(x>window_height/200 && x<window_height/17.7 && y>window_height/4.02 && y<window_height/3.49)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "DOWN ARROW");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=8;
        }
        
        if(x>window_height/16.32 && x<window_height/8.69 && y>window_height/4.02 && y<window_height/3.49)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "UP ARROW");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=9;
        }
        
        if(x>window_height/266.66 && x<window_height/17.39 && y>window_height/3.43 && y<window_height/3)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "LEFT ARROW");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=10;
        }
        
        if(x>window_height/16 && x<window_height/8.8 && y>window_height/3.43 && y<window_height/3)
        {
            glColor3f(0.85, 0.85,   0.85);
            glRectf(15*window_width/20, window_height-(window_height/20), window_width, window_height);
            glColor3f(1,0,0);
            drawstring(17.5*window_width/20,window_height-(window_height/21) , 0.0, "RIGHT ARROW");
            drawstring(15*window_width/20,window_height-(window_height/21) , 0.0, "SELECTED ->");
            glFlush();
            draw=11;
        }
        
        
        
        if(draw==1)
        {
            glColor3f(0, 0, 0);
            if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)) )
            {
                drawpoint(x,y);
                
                a2=a1;
                b2=b1;
                
                a1=x;
                b1=window_height-y;
                
                if(a1>(window_height/8)+1  &&  a1<window_width-2  && b1>2    &&  b1<(window_height-(window_height/20+10)))
                {
                    if(a2>(window_height/8)+1  &&  a2<window_width-2  && b2>2    &&  b2<(window_height-(window_height/20+10)))
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
            if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)))
            {
                a1=x-window_height/8;
                b1=window_height-y;
                a2=x+window_height/8;
                b2=b1;
                a3=x+window_height/11.6;
                b3=b1-window_height/8;
                a4=x-window_height/6.15;
                b4=b3;
                
                
                if(a1>(window_height/8)+1  &&  a1<window_width-2  && b1>2    &&  b1<(window_height-(window_height/20+10)) )
                {
                    if(a2>(window_height/8)+1  &&  a2<window_width-2  && b2>2    &&  b2<(window_height-(window_height/20+10)) )
                    {
                        if(a3>(window_height/8)+1  &&  a3<window_width-2  && b3>2    &&  b3<(window_height-(window_height/20+10)) )
                        {
                            
                            if(a4>(window_height/8)+1    &&  a4<window_width-2  && b4>2    &&  b4<(window_height-(window_height/20+10)) )
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
            if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)))
            {
                a1=x-window_height/8;
                b1=window_height-y;
                a2=x+window_height/8;
                b2=b1-window_height/8;
                
                
                if(a1>(window_height/8)+1  &&  a1<window_width-2  && b1>2    &&  b1<(window_height-(window_height/20+10)) )
                {
                    if(a2>(window_height/8)+1  &&  a2<window_width-2  && b2>2    &&  b2<(window_height-(window_height/20+10)) )
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
            if(x>(window_height/8)+1   &&  x<window_width-2  && y>2  &&  y<(window_height-(window_height/20+10)))
            {
                a1=x;
                b1=window_height-y;
                a2=x+window_height/14;
                b2=b1-window_height/14;
                a3=x;
                b3=b1-window_height/7;
                a4=x-window_height/14;
                b4=b2;
                
                
                if(a1>(window_height/8)+1  &&  a1<window_width-2  && b1>2    &&  b1<(window_height-(window_height/20+10)) )
                {
                    if(a2>(window_height/8)+1  &&  a2<window_width-2  && b2>2    &&  b2<(window_height-(window_height/20+10)) )
                    {
                        if(a3>(window_height/8)+1  &&  a3<window_width-2  && b3>2    &&  b3<(window_height-(window_height/20+10)) )
                        {
                            
                            if(a4>(window_height/8)+1  &&  a4<window_width-2  && b4>2    &&  b4<(window_height-(window_height/20+10)) )
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
            
            for(k=0;k<element_index;k++)
                flowchart_element_x[k][0]=flowchart_element_x[k][1]=flowchart_element_x[k][2]=flowchart_element_x[k][3]=0;
            
            for(k=1;k<element_index;k++)
                flowchart_element_y[k][0]=flowchart_element_y[k][1]=flowchart_element_y[k][2]=flowchart_element_y[k][3]=0;
            
            element_index=0;
            
            
            count=0;
            display();
            
        }
        
        if(draw==6)
        {
            glColor3f(0, 0, 0);
            if(x>(window_height/8)+1  &&  x<window_width-2  && window_height-y>2    &&  window_height-y<(window_height-(window_height/20+10)) )
            {
                if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)-(2*window_height/32)>2    &&  (window_height-y)-(2*window_height/32)<(window_height-(window_height/20+10)) )
                {
                    if(x-(window_height/17.78)>(window_height/8)+1  &&  x-(window_height/17.78)<window_width-2  && (window_height-y)-window_height/32>2    &&  (window_height-y)-window_height/32<(window_height-(window_height/20+10)) )
                    {
                        
                        if(x+(window_height/17.78)>(window_height/8)+1  &&  x+(window_height/17.78)<window_width-2  && (window_height-y)-window_height/32>2    &&  (window_height-y)-window_height/32<(window_height-(window_height/20+10)) )
                        {
                            
                            a1=x;
                            a2=window_height-y;
                            Ellipse(window_height/17.78,window_height/32,x,(window_height-y)-window_height/32);
                            reset();
                        }
                    }
                }
            }
        }
        
        if(draw==7)
        {
            glColor3f(0, 0, 0);
            if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)-30+30>2    &&  (window_height-y)-30+30<(window_height-(window_height/20+10)) )
            {
                if(x+30>(window_height/8)+1  &&  x+30<window_width-2  && (window_height-y)-30>2    &&  (window_height-y)-30<(window_height-(window_height/20+10)) )
                {
                    if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)-30-30>2    &&  (window_height-y)-30-30<(window_height-(window_height/20+10)) )
                    {
                        
                        if(x-30>(window_height/8)+1  &&  x-30<window_width-2  && (window_height-y)-30>2    &&  (window_height-y)-30<(window_height-(window_height/20+10)) )
                        {
                            
                            a1=x;
                            a2=window_height-y;
                            draw_circle(x,(window_height-y)-30,30);
                            reset();
                        }
                    }
                }
            }
            
        }
        if(draw==8)
        {
            glColor3f(0, 0, 0);
            if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)>2    &&  (window_height-y)<(window_height-(window_height/20+10)) )
            {
                if(x+15>(window_height/8)+1  &&  x+15<window_width-2  && (window_height-y)+15>2    &&  (window_height-y)+15<(window_height-(window_height/20+10)) )
                {
                    if(x-15>(window_height/8)+1  &&  x-15<window_width-2  && (window_height-y)+15>2    &&  (window_height-y)+15<(window_height-(window_height/20+10)) )
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
            if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)>2    &&  (window_height-y)<(window_height-(window_height/20+10)) )
            {
                if(x+15>(window_height/8)+1  &&  x+15<window_width-2  && (window_height-y)-15>2    &&  (window_height-y)-15<(window_height-(window_height/20+10)) )
                {
                    if(x-15>(window_height/8)+1  &&  x-15<window_width-2  && (window_height-y)-15>2    &&  (window_height-y)-15<(window_height-(window_height/20+10)) )
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
            if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)>2    &&  (window_height-y)<(window_height-(window_height/20+10)) )
            {
                if(x+15>(window_height/8)+1  &&  x+15<window_width-2  && (window_height-y)-15>2    &&  (window_height-y)-15<(window_height-(window_height/20+10)) )
                {
                    if(x+15>(window_height/8)+1  &&  x+15<window_width-2  && (window_height-y)+15>2    &&  (window_height-y)+15<(window_height-(window_height/20+10)) )
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
            if(x>(window_height/8)+1  &&  x<window_width-2  && (window_height-y)>2    &&  (window_height-y)<(window_height-(window_height/20+10)) )
            {
                if(x-15>(window_height/8)+1  &&  x-15<window_width-2  && (window_height-y)+15>2    &&  (window_height-y)+15<(window_height-(window_height/20+10)) )
                {
                    if(x-15>(window_height/8)+1  &&  x-15<window_width-2  && (window_height-y)-15>2    &&  (window_height-y)-15<(window_height-(window_height/20+10)) )
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
            element_index--;
            if(element_index<0)
            {    glColor3f(1, 0, 0);
                drawstring(window_height/80, window_height-25, 0.0, "Nothing to UNDO :)");
                element_index++;
                
            }
            switch(drw[element_index])
            {
                case 1:
                    glColor3f(1,1,1);
                    temp1=(int)(flowchart_element_y[element_index][1]-flowchart_element_y[element_index][0]); //b2-b1
                    temp2=(int)(flowchart_element_x[element_index][1]-flowchart_element_x[element_index][0]); //a2-a1
                    glBegin(GL_LINES);
                    if((abs(temp1)>abs(temp2)))
                    {    glBegin(GL_LINES);
                        glVertex2f(flowchart_element_x[element_index][1],  flowchart_element_y[element_index][1]);  //a2,b2
                        glVertex2f(flowchart_element_x[element_index][1],  flowchart_element_y[element_index][0]);   //a2,b2
                        glEnd();
                    }
                    else{
                        glBegin(GL_LINES);
                        
                        glVertex2f(flowchart_element_x[element_index][1],  flowchart_element_y[element_index][1]);  //a2,b2
                        glVertex2f(flowchart_element_x[element_index][0],  flowchart_element_y[element_index][1]); // a1,b2
                        glEnd();
                    }
                    
                    glFlush();
                    undo=0;
                    break;
                case 2:
                    glColor3f(1, 1, 1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(flowchart_element_x[element_index][0],flowchart_element_y[element_index][0]); //a11 b11
                    glVertex2f(flowchart_element_x[element_index][1],flowchart_element_y[element_index][1]);  //a22 b2
                    glVertex2f(flowchart_element_x[element_index][2],flowchart_element_y[element_index][2]);  //a3 b3
                    glVertex2f(flowchart_element_x[element_index][3],flowchart_element_y[element_index][3]);  //a4 b4
                    glEnd();
                    glFlush();
                    undo=0;
                    break;
                case 3:
                    glColor3f(1, 1, 1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(flowchart_element_x[element_index][0],flowchart_element_y[element_index][0]);   //a1b1
                    glVertex2f(flowchart_element_x[element_index][1],flowchart_element_y[element_index][0]);    //a2b1
                    glVertex2f(flowchart_element_x[element_index][1],flowchart_element_y[element_index][1]);   //a2b2
                    glVertex2f(flowchart_element_x[element_index][0],flowchart_element_y[element_index][1]);   //a1b2
                    glEnd();
                    undo=0;
                    glFlush();
                    break;
                case 4:
                    glColor3f(1, 1 ,1);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(flowchart_element_x[element_index][0],flowchart_element_y[element_index][0]);   //a1b1
                    glVertex2f(flowchart_element_x[element_index][1],flowchart_element_y[element_index][1]);   //a2b2
                    glVertex2f(flowchart_element_x[element_index][2],flowchart_element_y[element_index][2]);   //a3b3
                    glVertex2f(flowchart_element_x[element_index][3],flowchart_element_y[element_index][3]);   //a4b4
                    glEnd();
                    undo=0;
                    glFlush();
                    break;
                case 6:
                    glColor3f(1, 1 ,1);
                    Ellipse(window_height/17.78,window_height/32,flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]-window_height/32);
                    undo=0;
                    break;
                case 7:
                    //printf("drawing circle with %d ,%d",a[m][0],a[m][1]);
                    glColor3f(1, 1 ,1);
                    draw_circle(flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]-30,30);
                    undo=0;
                    break;
                case 8:
                    glColor3f(1, 1 ,1);
                    down_arrow(flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]);
                    undo=0;
                    break;
                case 9:
                    glColor3f(1, 1 ,1);
                    up_arrow(flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]);
                    undo=0;
                    break;
                case 10:
                    glColor3f(1, 1 ,1);
                    left_arrow(flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]);
                    undo=0;
                    break;
                case 11:
                    glColor3f(1, 1 ,1);
                    right_arrow(flowchart_element_x[element_index][0],flowchart_element_x[element_index][1]);
                    undo=0;
                    break;
                    
                    
                    
                    
                default:; //printf("default");
            }
        }
    }
    
    
    if(btn==GLUT_LEFT_BUTTON    &&  state==GLUT_UP)
    {
        glReadBuffer(GL_FRONT);
        
        
        glReadPixels(window_height/10+2,   window_height/10,  window_width-window_height/10-2, window_height-window_height/10-window_height/20-1,GL_RGB,    GL_UNSIGNED_BYTE,   image);
        
        posx=window_height/10+2;
        posy=window_height/10;
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
    
    
    window_width  =   w;
    window_height  =   h;
    
    
    glutPostRedisplay();
    
    
    
    
}



int main(int argc, char ** argv)

{
    textx=50,texty=window_height-25,textz=0.0;
    image   =   (char *)malloc(3*1450*900*sizeof(char));
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE|   GLUT_RGB);
    glutCreateWindow("CG PROJECT");
    glutInitWindowSize(window_width,window_height);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutReshapeFunc(myreshape);
    glutKeyboardFunc(keys);
    glutFullScreen();
    glutMainLoop();
    
}
