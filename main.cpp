#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>

void init(void)
{
    glClearColor(0.81, 0.96, 1,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
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

// Function to draw a bush using multiple circles
void drawBush(GLfloat centerX, GLfloat centerY, GLfloat size) {
    // Set green color for the bush
    glColor3f(0.0, 0.5, 0.0); // Dark green

    // Scale factor for radii and offsets (relative to size)
    GLfloat scale = size / 100.0; // Normalize based on a reference size of 100

    // Base circles for the bush structure, scaled by size
    circle(20.0 * scale, 30.0 * scale, centerX - 30 * scale, centerY - 10 * scale, 100);  // Left base
    circle(25.0 * scale, 35.0 * scale, centerX, centerY, 100);                            // Center base
    circle(20.0 * scale, 30.0 * scale, centerX + 30 * scale, centerY - 5 * scale, 100);   // Right base

    // Additional smaller circles for fullness
    circle(15.0 * scale, 20.0 * scale, centerX - 20 * scale, centerY + 20 * scale, 100);  // Upper left
    circle(15.0 * scale, 20.0 * scale, centerX + 10 * scale, centerY + 25 * scale, 100);  // Upper center
    circle(15.0 * scale, 20.0 * scale, centerX + 20 * scale, centerY + 15 * scale, 100);  // Upper right

    // Even smaller circles for texture
    circle(10.0 * scale, 15.0 * scale, centerX - 10 * scale, centerY + 30 * scale, 100);  // Top left detail
    circle(10.0 * scale, 15.0 * scale, centerX + 15 * scale, centerY + 35 * scale, 100);  // Top center detail
}

void rec(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);
        glVertex2i(x, y);                  // Bottom Left
        glVertex2i(x + width, y);          // Bottom Right
        glVertex2i(x + width, y + height); // Top Right
        glVertex2i(x, y + height);         // Top Left
    glEnd();
}

void pillar(int x) {
    // Base support (wider foundation for stability)
    glColor3f(0.55, 0.55, 0.55); // Slightly darker gray for the base
    glBegin(GL_POLYGON);
    glVertex2i(x - 10, 430);     // Wider base left
    glVertex2i(x + 40, 430);     // Wider base right
    glVertex2i(x + 35, 420);     // Tapered bottom right
    glVertex2i(x - 5, 420);      // Tapered bottom left
    glEnd();

    // Mid small spike (main body of the pillar)
    glColor3f(0.6, 0.6, 0.6);    // Original gray color
    glBegin(GL_POLYGON);
    glVertex2i(x, 500);
    glVertex2i(x, 430);
    glVertex2i(x + 30, 430);
    glVertex2i(x + 30, 500);
    glVertex2i(x + 33, 503);
    glVertex2i(x + 33, 520);
    glVertex2i(x - 3, 520);
    glVertex2i(x - 3, 503);
    glEnd();

    // Side detail 1 (left side trapezoid for architectural flair)
    glColor3f(0.65, 0.65, 0.65); // Slightly lighter gray for contrast
    glBegin(GL_POLYGON);
    glVertex2i(x - 5, 480);      // Left side, higher up
    glVertex2i(x, 480);          // Connect to pillar body
    glVertex2i(x, 460);          // Lower on the pillar
    glVertex2i(x - 5, 460);      // Left side, lower
    glEnd();
        glColor3f(0.37, 0.37, 0.37);
        rec(x+9,460, 12, 25);
    // Side detail 2 (right side trapezoid for symmetry)
    glColor3f(0.65, 0.65, 0.65); // Same lighter gray
    glBegin(GL_POLYGON);
    glVertex2i(x + 30, 480);     // Right side, higher up
    glVertex2i(x + 35, 480);     // Extend outward
    glVertex2i(x + 35, 460);     // Right side, lower
    glVertex2i(x + 30, 460);     // Connect to pillar body
    glEnd();

    // Decorative bar below the orange hat
    glColor3f(0.5, 0.5, 0.5);    // Darker gray for the bar
    glBegin(GL_POLYGON);
    glVertex2i(x - 5, 520);      // Left edge
    glVertex2i(x + 35, 520);     // Right edge
    glVertex2i(x + 35, 510);     // Bottom right
    glVertex2i(x - 5, 510);      // Bottom left
    glEnd();

    // Orange Hat on top
    glColor3f(0.6, 0.29, 0.04);  // Original orange color
    glBegin(GL_POLYGON);
    glVertex2i(x - 5, 520);
    glVertex2i(x + 35, 520);
    glVertex2i(x + 15, 570);
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
    glVertex2i(295, 190);   //statrt
    glVertex2i(380, 190);   //finish
    glVertex2i(380, 320);
    glVertex2i(295, 320);
    glEnd();

        //windows
        glColor3f(0.33, 0.25, 0.2);
        gapboxesX(300,245,5,7,375,5); //lower
        gapboxesX(300,283,5,7,375,5); //upper



    // black lines
    glColor3f(0.36, 0.36, 0.36);    //lower
    glBegin(GL_POLYGON);
    glVertex2i(295, 232);
    glVertex2i(380, 232);
    glVertex2i(380, 235);
    glVertex2i(295, 235);
    glEnd();

    glColor3f(0.36, 0.36, 0.36);    //upper
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
    glVertex2i(280, 320);   //lb
    glVertex2i(392, 320);   //rb
    glVertex2i(380, 327);
    glVertex2i(365, 410);
    glVertex2i(310, 410);
    glEnd();
        //RoofWindow
        glColor3f(0.4, 0.4, 0.4);
        rec(325,350,22,5);

        glColor3f(0.86, 0.86, 0.86);
        glBegin(GL_POLYGON);
        glVertex2i(327, 355);
        glVertex2i(345, 355);
        glVertex2i(345, 365);
        glVertex2i(336, 375);
        glVertex2i(327, 365);
        glEnd();
                            //rec(327,355,18,15);
    // Darker Orange shade on roof bottom
    glColor3f(0.8, 0.39, 0.05);
    glBegin(GL_POLYGON);
    glVertex2i(292, 327);
    glVertex2i(280, 320);
    glVertex2i(392, 320);
    glVertex2i(380, 327);
    glEnd();

    ///Slim gray pillar at back


    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
    glVertex2i(400, 300);
    glVertex2i(435, 300);
    glVertex2i(435, 460);
    glVertex2i(400, 460);
    glEnd();
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
    glVertex2i(395, 460);
    glVertex2i(440, 460);
    glVertex2i(440, 480);
    glVertex2i(395, 480);
    glEnd();
        //Window
        glColor3f(0.32, 0.28, 0.28);
        rec(413,440,10,20);
        glColor3f(0.86, 0.86, 0.86);
        circle(5,5,418,460,200);

        glColor3f(0.3, 0.3, 0.3);
        gapboxesY(400,350,10,5,430,4);
        gapboxesY(425,350,10,5,430,4);
    //orange top
    glColor3f(0.9, 0.44, 0.06);
    glBegin(GL_POLYGON);
    glVertex2i(400, 485);
    glVertex2i(395, 480);
    glVertex2i(440, 480);
    glVertex2i(435, 485);
    glVertex2i(417.5, 590);
    glEnd();

    ///LARGEST BUILDING AT BACK

    pillar(465);
    pillar(600);


    glColor3f(0.81, 0.79, 0.7);
    glBegin(GL_POLYGON);
    glVertex2i(470, 190);
    glVertex2i(620, 190);
    glVertex2i(620, 490);
    glVertex2i(580, 640); //mid er ta..620-40
    glVertex2i(510, 640);
    glVertex2i(470, 490);
    glEnd();

    glColor3f(0.66, 0.64, 0.52);
    glBegin(GL_POLYGON);
    glVertex2i(470, 190);
    glVertex2i(540, 190);
    glVertex2i(540, 490);
    glVertex2i(470, 490);
    glEnd();

    glColor3f(0.58, 0.44, 0.32);
    gapboxesX(480,440,15,20,530,2);
    gapboxesX(480,440-60,15,20,530,2);
    gapboxesX(480,440-60-60,15,20,530,2);
    //Orange Roof
    glColor3f(0.9, 0.44, 0.06);
    glBegin(GL_POLYGON);
    glVertex2i(470, 490);
    glVertex2i(540, 490);
    glVertex2i(580, 640);
    glVertex2i(510, 640);
    glEnd();
        //borderline
        glColor3f( 0.31, 0.28, 0.25);
        glBegin(GL_LINES);
        glVertex2i(540, 490);
        glVertex2i(580, 640);
        glEnd();

        glBegin(GL_LINES);
        glVertex2i(580, 640);
        glVertex2i(620, 490);
        glEnd();

        glBegin(GL_LINES);
        glVertex2i(540, 490);
        glVertex2i(620, 490);
        glEnd();

            //big line
            glBegin(GL_LINES);
            glVertex2i(470, 470);
            glVertex2i(620, 470);
            glEnd();

            gapboxesX(475,470,2,3,615,15);


    //pillars
    pillar(520);



    ///Huge Building at back

    glColor3f(0.91, 0.86, 0.69);
    glBegin(GL_POLYGON);
    glVertex2i(510, 190);
    glVertex2i(690, 190);
    glVertex2i(690, 290);
    glVertex2i(640, 410);
    glVertex2i(550, 410);
    glVertex2i(510, 290);
    glEnd();

    //roof
    glColor3f(0.9, 0.44, 0.06);
    glBegin(GL_POLYGON);
    glVertex2i(550, 410);
    glVertex2i(640, 410);
    glVertex2i(690, 290);
    glVertex2i(600, 290);
    glEnd();


                            ///RIGHT OUTER BRIGE
    glColor3f(0.67, 0.67, 0.67);
    gapboxesX(780,40,10,150,1140,14);

    //Horizontal Line
    glBegin(GL_POLYGON);
    glVertex2i(780, 190);
    glVertex2i(1140, 190);
    glVertex2i(1140, 220);
    glVertex2i(780, 220);
    glEnd();

    glColor3f(0.35, 0.35, 0.35);
    gapboxesX(785,200,6,7,1135,39);

    //Horizontal Line (Top Black)
    glBegin(GL_POLYGON);
    glVertex2i(780, 220);
    glVertex2i(1140, 220);
    glVertex2i(1140, 225);
    glVertex2i(780, 225);
    glEnd();

    //Orange Top horizontal bars
    glColor3f(0.9, 0.44, 0.06);
    gapboxesX(790, 225, 10, 2, 1130, 15);
    gapboxesX(794, 227, 2, 7, 1126, 15);
    //GLLINES
	glBegin(GL_LINES);
	glVertex2i(794,233);
	glVertex2i(1126,233);
	glEnd();


    ///Right Tall Spike Tower
    glColor3f(0.59, 0.59, 0.59);
    glBegin(GL_POLYGON);
    glVertex2i(710, 120);
    glVertex2i(800, 120);
    glVertex2i(770, 450);
    glVertex2i(740, 450);
    glEnd();

    //Orange Top
    glColor3f(0.9, 0.44, 0.06);
    glBegin(GL_POLYGON);
    glVertex2i(742, 460); //left edge
    glVertex2i(735, 450);
    glVertex2i(775, 450);
    glVertex2i(768, 460); //Right edge
    glVertex2i(755, 510);
    glEnd();

        //TopBlack part
    glColor3f(0.29, 0.29, 0.29);
    glBegin(GL_POLYGON);
    glVertex2i(740, 445);
    glVertex2i(735, 450); //lbhat
    glVertex2i(775, 450); //rbhat
    glVertex2i(770, 445);
    glVertex2i(775, 420);
    glVertex2i(735, 420);
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

    ///Center Watchtower
    //base
    glColor3f(0.67, 0.67, 0.67);
    glBegin(GL_POLYGON);
    glVertex2i(465, 125);
    glVertex2i(540, 125);
    glVertex2i(530, 230);
    glVertex2i(475, 230);
    glEnd();


    //crown

    glColor3f(0.67, 0.67, 0.67);
    glBegin(GL_POLYGON);
    glVertex2i(465, 230);
    glVertex2i(540, 230);
    glVertex2i(540, 245);
    glVertex2i(465, 245);
    glEnd();

    glColor3f(0.27, 0.27, 0.27);
    glBegin(GL_POLYGON);
    glVertex2i(465, 230);
    glVertex2i(540, 230);
    glVertex2i(540, 235);
    glVertex2i(465, 235);
    glEnd();
//gapped boxes
    glColor3f(0.67, 0.67, 0.67);
    gapboxesX(465, 245, 10, 10, 540, 5);

    glColor3f(0.33, 0.33, 0.33);
    gapboxesX(480, 237, 5, 3, 525, 3);

    //body gapped boxes
    gapboxesX(480, 220-5, 7, 7, 525, 3);
    gapboxesX(480-5, 180-5, 7, 7, 525+5, 3);
    gapboxesX(480-5-5, 140-5, 7, 7, 525+5+5, 3);


    ///Slim Tower at center
    //slim base
    glColor3f(0.67, 0.67, 0.67);
    glBegin(GL_POLYGON);
    glVertex2i(565, 125);
    glVertex2i(610, 125);
    glVertex2i(610, 310);
    glVertex2i(565, 310);
    glEnd();

    glColor3f(0.67, 0.67, 0.67);
    glBegin(GL_POLYGON);
    glVertex2i(555, 310);
    glVertex2i(620, 310);
    glVertex2i(620, 350);
    glVertex2i(555, 350);
    glEnd();

    glColor3f(0.96, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2i(625, 350);
    glVertex2i(550, 350);
    glVertex2i(587.5, 470);
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
    glColor3f(0.57, 0.55, 0.55);
    glBegin(GL_POLYGON);
    glVertex2i(170, 325); // LT dibs
    glVertex2i(170, 130);       // LB
    glVertex2i(220, 130);       // RB
    glVertex2i(220, 325); // RT dibs
    glVertex2i(225, 335);
    glVertex2i(225, 340); // RT
    glVertex2i(165, 340); // LT
    glVertex2i(165, 335);
    glEnd();

    //lefthangingpart
    glColor3f(0.49, 0.48, 0.48);
    glBegin(GL_POLYGON);
    glVertex2i(160, 280);
    glVertex2i(175, 270);
    glVertex2i(175, 300);
    glVertex2i(160, 300);
    glEnd();
    glColor3f(0.96, 0.6, 0.3);
    circle(7.5,8,167.5,300,200);

        //two howiontal lines
        glColor3f(0.33, 0.33, 0.33);
        rec(170,200,50, 3);
        rec(170,200+70,50, 3);

            //windows
            rec(190,280,5,7);
            rec(200,300,5,7);
            rec(190,210,5,7);
            rec(200,230,5,7);
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
        //Single Window
        rec(60,100,10,6);

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

    glColor3f(0.24, 0.25, 0.25);
    gapboxesY(120,45,5,2,165,11); //long
    gapboxesY(120,50,2,2,170,11); //short
    gapboxesY(165,45,5,2,165,11); //long
    gapboxesY(168,50,2,2,170,11); //short
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
 glColor3f(0.96, 0.6, 0.3);   glBegin(GL_POLYGON);
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
        glColor3f(0.43, 0.43, 0.43);
        rec(113,170,5,10);
        //Left Orange hat
        glColor3f(0.96, 0.6, 0.3);
        glBegin(GL_POLYGON);
        glVertex2i(110-2, 200);
        glVertex2i(120+2, 200);
        glVertex2i(115, 210);
        glEnd();
    // Right Weird thingy
    glColor3f(0.72, 0.74, 0.74);
    glBegin(GL_POLYGON);
    glVertex2i(170, 140);  // top left
    glVertex2i(180, 148);  // top right
    glVertex2i(180, 200);  // top right
    glVertex2i(170, 200);  // top left
    glEnd();
        glColor3f(0.43, 0.43, 0.43);
        rec(173,170,5,10);
        //Right Orange hat
        glColor3f(0.96, 0.6, 0.3);
        glBegin(GL_POLYGON);
        glVertex2i(170-2, 200);
        glVertex2i(180+2, 200);
        glVertex2i(175, 210);
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

        //Inner Box
        glColor3f(0.85, 0.85, 0.85);
        rec(140,195,10,15);
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

    //BottomBlackbars
    glColor3f(0.34, 0.34, 0.34);
    gapboxesX(130,246,2,2,160,5);
    gapboxesX(135,230,3,5,155,4);

    ///Right Big Gate Tower


    glColor3f(0.41, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex2i(650, 40);
    glVertex2i(790, 40);
    glVertex2i(770, 160);
    glVertex2i(670, 160);
    glEnd();

    //Gate Square
    glColor3f(0.23, 0.23, 0.23);
    glBegin(GL_POLYGON);
    glVertex2i(670, 40);
    glVertex2i(770, 40);
    glVertex2i(750, 100);
    glVertex2i(690, 100);
    glEnd();

    circle(30,20,720,100,200);
    circle(20,20,720,110,200);
    circle(10,20,720,120,200);

    //Gate Square Top Design
    glColor3f(0.23, 0.23, 0.23);
    rec(670, 160, 100, 10);
    glColor3f(0.41, 0.4, 0.4);
    rec(660, 170, 120, 10);

    //Triange Top Cut
    glColor3f(0.23, 0.23, 0.23);
    glBegin(GL_POLYGON);
    glVertex2i(650, 180);
    glVertex2i(790, 180);
    glVertex2i(730, 240);
    glVertex2i(710, 240);
    glEnd();


    ///RIGHT ROCKS

    //Outer border
    glColor3f(0.71, 0.7, 0.65);
    glBegin(GL_POLYGON);
    glVertex2i(1280, 20);
    glVertex2i(1280, 270);
    glVertex2i(1250, 270);
    glVertex2i(1200, 250);
    glVertex2i(1150, 210);
    glVertex2i(1100, 140);
    glVertex2i(1050, 120);
    glVertex2i(1000, 130);
    glVertex2i(970, 120);
    glVertex2i(950, 50);
    glVertex2i(900, 40);
    glVertex2i(860, 30);
    glVertex2i(840, 40);
    glVertex2i(840, 40);
    glVertex2i(830, 20);
    glEnd();


glColor3f(0.4, 0.34, 0.28); // Dark Gray
glBegin(GL_POLYGON);

    glVertex2i(860, 30);
    glVertex2i(840, 40);
    glVertex2i(840, 40);
    glVertex2i(830, 20);
    glVertex2i(970, 20);
glEnd();
    ////////////////TEST

// Polygon 1 - Dark Gray Rock
glColor3f(0.4, 0.4, 0.4); // Dark Gray
glBegin(GL_POLYGON);
glVertex2i(850+300, 50);
glVertex2i(900+300, 80);
glVertex2i(950+300, 70);
glVertex2i(920+300, 40);
glVertex2i(880+300, 30);
glEnd();

// Polygon 2 - Medium Gray Rock
glColor3f(0.6, 0.6, 0.6); // Medium Gray
glBegin(GL_POLYGON);
glVertex2i(1000, 130);
glVertex2i(1050, 150);
glVertex2i(1100, 140);
glVertex2i(1070, 120);
glVertex2i(1020, 110);
glEnd();

// Polygon 3 - Light Gray Rock
glColor3f(0.8, 0.8, 0.8); // Light Gray
glBegin(GL_POLYGON);
glVertex2i(1150, 210);
glVertex2i(1200, 230);
glVertex2i(1250, 220);
glVertex2i(1220, 190);
glVertex2i(1170, 200);
glEnd();



// Polygon 4 - Brownish Rock
glColor3f(0.5, 0.4, 0.3); // Brownish Tone
glBegin(GL_POLYGON);
glVertex2i(1300+20, 300-100);
glVertex2i(1350+20, 320-100);
glVertex2i(1400+20, 310-100);
glVertex2i(1370+20, 280-100);
glVertex2i(1320+20, 290-100);
glEnd();

// Polygon 5 - Muted Greenish Rock
glColor3f(0.45, 0.5, 0.4); // Muted Greenish Gray
glBegin(GL_POLYGON);
glVertex2i(950+20, 120-50);
glVertex2i(1000+20, 140-50);
glVertex2i(1050+20, 130-50);
glVertex2i(1020+20, 100-50);
glVertex2i(970+20, 110-50);
glEnd();

// Polygon 6 - Light Brown Rock
glColor3f(0.7, 0.6, 0.5); // Light Brown
glBegin(GL_POLYGON);
glVertex2i(1100, 140);
glVertex2i(1150, 160);
glVertex2i(1200, 150);
glVertex2i(1170, 130);
glVertex2i(1120, 120);
glEnd();

// Polygon 7
glColor3f(0.8, 0.8, 0.8);
glBegin(GL_POLYGON);
glVertex2i(1150-80, 210-120);
glVertex2i(1200-80, 230-120);
glVertex2i(1250-80, 220-120);
glVertex2i(1220-80, 190-120);
glVertex2i(1170-80, 200-120);
glEnd();

// Polygon 8
glColor3f(0.4, 0.34, 0.28);
glBegin(GL_POLYGON);
glVertex2i(1100+90, 140-30);
glVertex2i(1150+90, 160-30);
glVertex2i(1200+90, 150-30);
glVertex2i(1170+90, 130-30);
glVertex2i(1120+90, 120-30);
glEnd();

    //BUSH LEFT
    glColor3f(0.45, 0.5, 0.4);
    drawBush(250.0, 40.0, 80.0); //left single
    drawBush(200.0, 20.0, 80.0); //left single
    ///Outer Road

    glColor3f( 0.43, 0.43, 0.43);
    glBegin(GL_POLYGON);
    glVertex2i(0,0);
    glVertex2i(1280,0);
    glVertex2i(1280,40);
    glVertex2i(0,40);
    glEnd();
    ////////////////TEST





    drawBush(850.0, 10.0, 100.0);
    drawBush(850.0+80, 10.0, 100.0);
    drawBush(850.0+80+80, 10.0, 100.0);
    drawBush(850.0+80+80+80, 10.0, 100.0);
    drawBush(850.0+80+80+80+80, 10.0, 100.0);
    drawBush(850.0+80+80+80+80+80, 10.0, 100.0);





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
