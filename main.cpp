#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>

void init(void)
{
    glClearColor(1, 1, 1,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
    glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
    glLoadIdentity();
    glOrtho(0.0, 1280.0, 0.0, 720.0, -1.0, 1.0);
    //gluOrtho2D(0.0,300.0,0.0,300.0); // Orthographic representation; multiply the current matrix by an orthographic matrix 2D= left right,bottom,top equivalent near=-1,far=1
}
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy , GLfloat rad)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);

    for(int i=0; i<=100; i++)
    {
        float angle = 2*3.14*i/rad;
        float x = rx*cosf(angle);
        float y = ry*sinf(angle);
        glVertex2f(x+cx,y+cy);
    }
    glEnd();
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ///circle(50,50,50,50,100);

    // Wall
    glColor3f( 0.48 ,0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(70,40);
    glVertex2i(70,125);
    glVertex2i(850,125);
    glVertex2i(850,40);
    glEnd();

    // WallTopLightGray
    glColor3f( 0.87, 0.86, 0.86);
    glBegin(GL_POLYGON);
    glVertex2i(70,125);
    glVertex2i(850,125);
    glVertex2i(850,130);
    glVertex2i(70,130);

    glEnd();

    /// Left tent
    // Base tower body
    glColor3f(0.65, 0.68, 0.68); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(45, 40);  // bottom left
    glVertex2i(100, 40);  // bottom right
    glVertex2i(90, 132);  // top right
    glVertex2i(55, 132);  // top left
    glEnd();

    // Roof
    glColor3f(0.2, 0.2, 0.2); // dark gray
    glBegin(GL_TRIANGLES);
    glVertex2i(50, 130);  // left
    glVertex2i(95, 130);  // right
    glVertex2i(72.5, 170);  // top
    glEnd();

    /// Right tent
    // Base tower body
    glColor3f(0.65, 0.68, 0.68); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(45+775, 40);  // bottom left
    glVertex2i(100+775, 40);  // bottom right
    glVertex2i(90+775, 132);  // top right
    glVertex2i(55+775, 132);  // top left
    glEnd();

    // Roof
    glColor3f(0.2, 0.2, 0.2); // dark gray
    glBegin(GL_TRIANGLES);
    glVertex2i(50+775, 130);  // left
    glVertex2i(95+775, 130);  // right
    glVertex2i(72.5+775, 170);  // top
    glEnd();


    ///Left Small Gate Tower
    // Base tower body
    glColor3f(0.65, 0.68, 0.68); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(120, 40);  // bottom left
    glVertex2i(170, 40);  // bottom right
    glVertex2i(170, 172);  // top right
    glVertex2i(120, 172);  // top left
    glEnd();

    // gateTop
    glColor3f(0.24, 0.25, 0.25); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(130, 60);  // bottom left
    glVertex2i(160, 60);  // bottom right
    glVertex2i(156, 70);  // top right
    glVertex2i(134, 70);  // top left
    glEnd();
    // gateSecondary
    glColor3f(0.24, 0.25, 0.25); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(137, 40);  // bottom left
    glVertex2i(153, 40);  // bottom right
    glVertex2i(153, 50);  // bottom right
    glVertex2i(145, 57);  // top right
    glVertex2i(137, 50);  // top left
    glEnd();
    // OrangeRoof
    glColor3f(0.96, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(120, 172);  // top left
    glVertex2i(170, 172);  // top right
    glVertex2i(170, 176);  // top right
    glVertex2i(120, 176);  // top left
    glEnd();

    // Left Weird thingy
    glColor3f(0.72, 0.74, 0.74);
    glBegin(GL_POLYGON);
    glVertex2i(120, 138);  // top left
    glVertex2i(110, 148);  // top right
    glVertex2i(110, 200);  // top right
    glVertex2i(120, 200);  // top right
    glEnd();
    // Right Weird thingy
    glColor3f(0.72, 0.74, 0.74);
    glBegin(GL_POLYGON);
    glVertex2i(170, 140);  // top left
    glVertex2i(180, 148);  // top right
    glVertex2i(180, 200);  // top right
    glVertex2i(170, 200);  // top left
    glEnd();
    // MidTopPillar
    glColor3f(0.71, 0.72, 0.72);
    glBegin(GL_POLYGON);
    glVertex2i(132, 176);  // top left
    glVertex2i(158, 176);  // top right
    glVertex2i(158, 248);  // top right
    glVertex2i(132, 248);  // top right
    glEnd();
            //small right
            glBegin(GL_POLYGON);
            glVertex2i(158, 238);  // top left
            glVertex2i(162, 238);  // top right
            glVertex2i(162, 248);  // top right
            glVertex2i(158, 248);  // top right
            glEnd();
            //small left
            glBegin(GL_POLYGON);
            glVertex2i(132, 238);  // top left
            glVertex2i(128, 238);  // top left
            glVertex2i(128, 248);  // top left
            glVertex2i(132, 248);  // top left
            glEnd();
    //Orange Hat o top
    glColor3f(0.96, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(125, 248);  // top left
    glVertex2i(170, 248);  // top left
    glVertex2i(165, 255);  // top left
    glVertex2i(145, 290);  // top left
    glEnd();

    glutSwapBuffers();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Lab Final");
    init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
