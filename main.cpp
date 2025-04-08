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

void rec(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);
        glVertex2i(x, y);                  // Bottom Left
        glVertex2i(x + width, y);          // Bottom Right
        glVertex2i(x + width, y + height); // Top Right
        glVertex2i(x, y + height);         // Top Left
    glEnd();
}


void gapboxesX(float x, float y, float width, float height, float endX, int numOfBoxes) {
    if (numOfBoxes <= 1) return;

    float totalWidth = width * numOfBoxes;
    float availableSpace = endX - x;
    float totalGap = availableSpace - totalWidth;
    float gap = totalGap / (numOfBoxes - 1);

    for (int i = 0; i < numOfBoxes; i++) {
        float xpos = x + i * (width + gap);
        rec(xpos, y, width, height);
    }
}


void gapboxesY(float x, float y, float width, float height, float endY, int numOfBoxes) {
    if (numOfBoxes <= 1) return;

    float totalHeight = height * numOfBoxes;
    float availableSpace = endY - y;
    float totalGap = availableSpace - totalHeight;
    float gap = totalGap / (numOfBoxes - 1);

    for (int i = 0; i < numOfBoxes; i++) {
        float ypos = y + i * (height + gap);
        rec(x, ypos, width, height);
    }
}




void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ///circle(50,50,50,50,100);







    /// Bridge
    glColor3f(0.72, 0.72, 0.72);
    glBegin(GL_POLYGON);
    glVertex2i(220, 130);
    glVertex2i(300, 130);
    glVertex2i(300, 170);
    glVertex2i(220, 170);
    glEnd();
    // Bridge Top Black
    glColor3f(0.27, 0.27, 0.27);
    glBegin(GL_POLYGON);
    glVertex2i(220, 170);
    glVertex2i(300, 170);
    glVertex2i(300, 175);
    glVertex2i(220, 175);
    glEnd();

    // Left Bridge Bottom Blank Space

    glColor3f( 1 ,1, 1);
    circle(30,20,260,130,200);
    circle(20,25,260,130,200);
    circle(5,30,260,130,200);


    ///A shaped Roof building
    //base
    glColor3f(0.91, 0.85, 0.76);
    glBegin(GL_POLYGON);
    glVertex2i(295, 190);
    glVertex2i(380, 190);
    glVertex2i(380, 320);
    glVertex2i(295, 320);
    glEnd();

    // black lines
    glColor3f(0.36, 0.36, 0.36);
    glBegin(GL_POLYGON);
    glVertex2i(295, 232);
    glVertex2i(380, 232);
    glVertex2i(380, 235);
    glVertex2i(295, 235);
    glEnd();

    glColor3f(0.36, 0.36, 0.36);
    glBegin(GL_POLYGON);
    glVertex2i(295, 270);
    glVertex2i(380, 270);
    glVertex2i(380, 273);
    glVertex2i(295, 273);
    glEnd();

    glColor3f(0.36, 0.36, 0.36);
    glBegin(GL_POLYGON);
    glVertex2i(292, 307);
    glVertex2i(383, 307);
    glVertex2i(383, 311);
    glVertex2i(292, 311);
    glEnd();

    // Left and Right Slim pillars
    glColor3f(0.62, 0.62, 0.62);
    glBegin(GL_POLYGON);
    glVertex2i(302, 350);
    glVertex2i(310, 350);
    glVertex2i(310, 450);
    glVertex2i(302, 450);
    glEnd();
        //capleft
        glColor3f(0.9, 0.44, 0.06);
        glBegin(GL_POLYGON);
        glVertex2i(303, 455);
        glVertex2i(300, 450);
        glVertex2i(312, 450);
        glVertex2i(309, 455);
        glVertex2i(306, 465);
        glEnd();
    glColor3f(0.62, 0.62, 0.62);
    glBegin(GL_POLYGON);
    glVertex2i(302+60, 350);
    glVertex2i(310+60, 350);
    glVertex2i(310+60, 450);
    glVertex2i(302+60, 450);
    glEnd();
        //capright
        glColor3f(0.9, 0.44, 0.06);
        glBegin(GL_POLYGON);
        glVertex2i(303+60, 455);
        glVertex2i(300+60, 450);
        glVertex2i(312+60, 450);
        glVertex2i(309+60, 455);
        glVertex2i(306+60, 465);
        glEnd();

    // Orange Head
    glColor3f(0.9, 0.44, 0.06);
    glBegin(GL_POLYGON);
    glVertex2i(292, 327);
    glVertex2i(280, 320);
    glVertex2i(392, 320);
    glVertex2i(380, 327);
    glVertex2i(365, 410);
    glVertex2i(310, 410);
    glEnd();
    // Darker Orange shade on roof bottom
    glColor3f(0.8, 0.39, 0.05);
    glBegin(GL_POLYGON);
    glVertex2i(292, 327);
    glVertex2i(280, 320);
    glVertex2i(392, 320);
    glVertex2i(380, 327);
    glEnd();

    ///Simple Small Building
    //base(left)
    glColor3f(0.91, 0.85, 0.76); // White wall
    glBegin(GL_POLYGON);
    glVertex2i(390, 190);
    glVertex2i(430, 190);
    glVertex2i(430, 275);
    glVertex2i(390, 275);
    glEnd();
    // base(right-back)
    glColor3f(0.32, 0.32, 0.32); // Black
    glBegin(GL_POLYGON);
    glVertex2i(430, 190);
    glVertex2i(480, 190);
    glVertex2i(480, 275);
    glVertex2i(455, 335);
    glVertex2i(430, 275);
    glEnd();
    // base(right-frnt)
    glColor3f(0.91, 0.85, 0.76); // baige
    glBegin(GL_POLYGON);
    glVertex2i(433, 190);
    glVertex2i(477, 190);
    glVertex2i(477, 272);
    glVertex2i(455, 325);
    glVertex2i(433, 275);
    glEnd();

    //Orange roof
    glColor3f(0.9, 0.44, 0.06); // White wall
    glBegin(GL_POLYGON);
    glVertex2i(390, 275);
    glVertex2i(430, 275);
    glVertex2i(455, 335);
    glVertex2i(415, 335);
    glEnd();

    //Black Border



    ///Building's Base (Draw Buildings Before this section)
    glColor3f(0.51, 0.51, 0.51);
    glBegin(GL_POLYGON);
    glVertex2i(300, 125);
    glVertex2i(700, 125);
    glVertex2i(700, 185);
    glVertex2i(300, 185);
    glEnd();
    //Building Base Black Top
    glColor3f(0.63, 0.63, 0.63);
    glBegin(GL_POLYGON);
    glVertex2i(300, 185);
    glVertex2i(700, 185);
    glVertex2i(700, 190);
    glVertex2i(300, 190);
    glEnd();


    ///Left Big Tower 2(With flag on top)

    //Orange Hat on top
    glColor3f(0.96, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(165, 335);
    glVertex2i(225, 335);
    glVertex2i(195, 420);
    glEnd();

    //main body
    glColor3f(0.55, 0.55, 0.55);
    glBegin(GL_POLYGON);
    glVertex2i(170, 325); // LT dibs
    glVertex2i(170, 130); // LB
    glVertex2i(220, 130);
    glVertex2i(220, 325); // RT dibs
    glVertex2i(225, 335);
    glVertex2i(225, 340); // RT
    glVertex2i(165, 340); // LT
    glVertex2i(165, 335);
    glEnd();
    //black part on top
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(170, 325); // LT dibs
    glVertex2i(170, 320); // LB
    glVertex2i(220, 320);
    glVertex2i(220, 325); // RT dibs
    glVertex2i(225, 335);
    glVertex2i(165, 335);
    glEnd();

    //Top Gapped Boxes
    glColor3f(0.55, 0.55, 0.55);
    gapboxesX(165, 340, 5, 7, 225, 7); // Two boxes spaced from x=120 to x=220

    /// Bridge Left and Right Tents
            //left tent body
    glColor3f(0.42, 0.42, 0.42);
    glBegin(GL_POLYGON);
    glVertex2i(213, 130);
    glVertex2i(227, 130);
    glVertex2i(227, 145);
    glVertex2i(213, 145);
    glEnd();
            // left tent roof
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(213, 145);
    glVertex2i(227, 145);
    glVertex2i(220, 155);
    glEnd();
            //right tent body
    glColor3f(0.42, 0.42, 0.42);
    glBegin(GL_POLYGON);
    glVertex2i(213+80, 130);
    glVertex2i(227+80, 130);
    glVertex2i(227+80, 145);
    glVertex2i(213+80, 145);
    glEnd();
            // right tent roof
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(213+80, 145);
    glVertex2i(227+80, 145);
    glVertex2i(220+80, 155);
    glEnd();


    //////////////////////////////////////////////////////
    //////////////////////// Wall/////////////////////////
    //////////////////////////////////////////////////////
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
    glVertex2i(90, 135);  // top right
    glVertex2i(55, 135);  // top left
    glEnd();

    // Roof
    glColor3f(0.2, 0.2, 0.2); // dark gray
    glBegin(GL_TRIANGLES);
    glVertex2i(50, 135);  // left
    glVertex2i(95, 135);  // right
    glVertex2i(72.5, 170);  // top
    glEnd();

    /// Right tent
    // Base tower body
    glColor3f(0.65, 0.68, 0.68); // light gray
    glBegin(GL_POLYGON);
    glVertex2i(45+775, 40);  // bottom left
    glVertex2i(100+775, 40);  // bottom right
    glVertex2i(90+775, 135);  // top right
    glVertex2i(55+775, 135);  // top left
    glEnd();

    // Roof
    glColor3f(0.2, 0.2, 0.2); // dark gray
    glBegin(GL_TRIANGLES);
    glVertex2i(50+775, 135);  // left
    glVertex2i(95+775, 135);  // right
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
    // MidTopPillar
    glColor3f(0.41, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2i(132, 190);
    glVertex2i(158, 190);
    glVertex2i(158, 215);
    glVertex2i(132, 215);
    glEnd();
                //small left
            glColor3f(0.71, 0.72, 0.72);
            glBegin(GL_POLYGON);
            glVertex2i(132, 238);  // BR
            glVertex2i(128, 238);  // BL
            glVertex2i(128, 248);  // TL
            glVertex2i(132, 248);  // TR
            glEnd();
            //small right
            glBegin(GL_POLYGON);
            glVertex2i(158, 238);  // BL
            glVertex2i(162, 238);  // BR
            glVertex2i(162, 248);  // TR
            glVertex2i(158, 248);  // TL
            glEnd();

    // MidTopPillarOrangeCap
    glColor3f(0.96, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(130, 253);
    glVertex2i(125, 248);
    glVertex2i(165, 248);
    glVertex2i(160, 253);
    glVertex2i(145, 290);
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
