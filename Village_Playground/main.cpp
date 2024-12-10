#include<windows.h>
#ifdef __APPLE__
#include<GLUT/glut.h>
#else

#include<GL/glut.h>
#endif

#include<stdlib.h>
#include<math.h>

float c1= -100;
float c2= -150;
float c3= 1300;
float sun_y;
float moon_y;
float b1=1300;
float b2=1200;
float b3= 1300;
float bot1= 280;
float bot2= -100;
float ball1= 300;
float angle = 0.0f;
bool isSpinning = true;
bool isBoatRun = true;
bool isBallrun = true;
// Function to draw a circle
void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


// Draw sky
float skyR = 0.53, skyG = 0.81, skyB = 0.98; // Initial daytime sky color
int transitioningToNight = 1; // 1 for transitioning to night, 0 for transitioning to day
float colorChangeSpeed = 0.0003;



//Function to draw the sun
void sun(float sun_x, float sun_y)
{
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    drawCircle(sun_x, sun_y, 100, 100); // Scaled for pixels
}

// Function to draw the moon
void moon(float moon_x, float moon_y)
{
    glColor3f(0.9, 0.9, 0.9); // Light gray color
    drawCircle(moon_x, moon_y, 70, 100);

}
// Function cloud
void cloud1(float c1, float y)
{
    glColor3f(1.0, 1.0, 1.0); // White color
    drawCircle(c1, y, 50, 25);
    drawCircle(c1 + 50, y + 10, 40, 20);
    drawCircle(c1 - 50, y + 10, 40, 20);
}
void cloud2(float c2, float y)
{
    glColor3f(1.0, 1.0, 1.0); // White color
    drawCircle(c2, y, 50, 25);
    drawCircle(c2 + 50, y + 10, 40, 20);
    drawCircle(c2 - 50, y + 10, 40, 20);
}
void cloud3(float c3, float y)
{
    glColor3f(1.0, 1.0, 1.0); // White color
    drawCircle(c3, y, 50, 25);
    drawCircle(c3 + 50, y + 10, 40, 20);
    drawCircle(c3 - 50, y + 10, 40, 20);
}

// Function  Bird//
void bird1(float b1, float y, float s)
{

    //head//
    glColor3f(0.99, 0.19, 0);
    glBegin(GL_TRIANGLES);
    glVertex2d(b1+16,y+10);
    glVertex2d(b1+26,y+4);
    glVertex2d(b1+16,y-4);
    glEnd();
    // Draw the curved base of the bird
    glColor3f(0.99, 0.5, 0);
    glBegin(GL_POLYGON);
    for (float angle = M_PI; angle <= 2 * M_PI; angle += 0.01)
    {
        float bx = b1 + s * 20 * cos(angle);
        float by = y + s * 10 * sin(angle);
        glVertex2f(bx, by);
    }
    glEnd();

    //propeler//
    glColor3f(0.22, 0.32, 0.95); // Dark gray color for the base
    glBegin(GL_QUADS);
    glVertex2d(b1-10,y+10);
    glVertex2d(b1,y+10);
    glVertex2d(b1+10,y);
    glVertex2d(b1,y);
    glEnd();

}
void bird2(float b2, float y, float s)
{

    //head//
    glColor3f(0.99, 0.19, 0);
    glBegin(GL_TRIANGLES);
    glVertex2d(b2+16,y+10);
    glVertex2d(b2+26,y+4);
    glVertex2d(b2+16,y-4);
    glEnd();
    // Draw the curved base of the bird
    glColor3f(0.99, 0.5, 0);
    glBegin(GL_POLYGON);
    for (float angle = M_PI; angle <= 2 * M_PI; angle += 0.01)
    {
        float bx = b2 + s * 20 * cos(angle);
        float by = y + s * 10 * sin(angle);
        glVertex2f(bx, by);
    }
    glEnd();

    //propeler//
    glColor3f(0.22, 0.32, 0.95); // Dark gray color for the base
    glBegin(GL_QUADS);
    glVertex2d(b2-10,y+10);
    glVertex2d(b2,y+10);
    glVertex2d(b2+10,y);
    glVertex2d(b2,y);
    glEnd();

}
void bird3(float b3, float y, float s)
{

    //head//
    glColor3f(0.99, 0.19, 0);
    glBegin(GL_TRIANGLES);
    glVertex2d(b3+16,y+10);
    glVertex2d(b3+26,y+4);
    glVertex2d(b3+16,y-4);
    glEnd();
    // Draw the curved base of the bird
    glColor3f(0.99, 0.5, 0);
    glBegin(GL_POLYGON);
    for (float angle = M_PI; angle <= 2 * M_PI; angle += 0.01)
    {
        float bx = b3 + s * 20 * cos(angle);
        float by = y + s * 10 * sin(angle);
        glVertex2f(bx, by);
    }
    glEnd();

    //propeler//
    glColor3f(0.22, 0.32, 0.95); // Dark gray color for the base
    glBegin(GL_QUADS);
    glVertex2d(b3-10,y+10);
    glVertex2d(b3,y+10);
    glVertex2d(b3+10,y);
    glVertex2d(b3,y);
    glEnd();

}



void tree(float x, float y, float s)
{

    // Back forest foliage
    glColor3f(0.14, 0.43, 0.18); // Green color
    drawCircle(x - 50 * s, y + 100 * s, 60 * s, 50);
    drawCircle(x + 50 * s, y + 100 * s, 60 * s, 50);

    // Draw trunk
    glColor3f(0.55, 0.27, 0.07); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(x - 20 * s, y);
    glVertex2f(x + 20 * s, y);
    glVertex2f(x + 20 * s, y + 200 * s);
    glVertex2f(x - 20 * s, y + 200 * s);
    glEnd();

    // Draw main foliage
    glColor3f(0.0, 0.5, 0.0); // Green color
    drawCircle(x, y + 250 * s, 100 * s, 50);
    drawCircle(x - 50 * s, y + 200 * s, 80 * s, 50);
    drawCircle(x + 50 * s, y + 200 * s, 80 * s, 50);


}

// Function Playground(quarter-circle)
void playground(float centerX, float centerY, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);

    for (float angle = 3.14159f / 2; angle <= 3.14159f; angle += 0.01f)
    {
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function River(quarter-circle)
void river(float centerX, float centerY, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (float angle = 3.14159f / 2; angle <= 3.14159f; angle += 0.01f)
    {
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function  boat
void boat1(float bot1, float y, float s)
{
    // Draw the curved base of the boat
    glColor3f(0.19, 0.22, 0.18); // Dark gray color for the base
    glBegin(GL_POLYGON);
    for (float angle = M_PI; angle <= 2 * M_PI; angle += 0.01)
    {
        float bx = bot1 + s * 150 * cos(angle);
        float by = y + s * 50 * sin(angle);
        glVertex2f(bx, by);
    }
    glEnd();

    glColor3f(0.9, 0.4, 0.06);
    glBegin(GL_POLYGON); // Use GL_POLYGON for a filled half-circle
    for (float angle = 0; angle <= M_PI; angle += 0.01)   // 0 to 180 degrees in radians
    {
        float hx = bot1 + s* 90 * cos(angle); // Calculate x-coordinate
        float hy = y + s* 30 * sin(angle); // Calculate y-coordinate
        glVertex2f(hx, hy);
    }
    glEnd();

    glColor3f(0.58, 0.35, 0.14);
    glBegin(GL_POLYGON); // Use GL_POLYGON for a filled half-circle
    for (float angle = 0; angle <= M_PI; angle += 0.01)   // 0 to 180 degrees in radians
    {
        float hx = bot1-60 + s* 30 * cos(angle); // Calculate x-coordinate
        float hy = y + s* 25 * sin(angle); // Calculate y-coordinate
        glVertex2f(hx, hy);
    }
    glEnd();


}
void boat2(float bot2, float y, float s)
{
    // Draw the curved base of the boat
    glColor3f(0.19, 0.22, 0.18); // Dark gray color for the base
    glBegin(GL_POLYGON);
    for (float angle = M_PI; angle <= 2 * M_PI; angle += 0.01)
    {
        float bx = bot2 + s * 150 * cos(angle);
        float by = y + s * 50 * sin(angle);
        glVertex2f(bx, by);
    }
    glEnd();

    glColor3f(0.9, 0.4, 0.06);
    glBegin(GL_POLYGON); // Use GL_POLYGON for a filled half-circle
    for (float angle = 0; angle <= M_PI; angle += 0.01)   // 0 to 180 degrees in radians
    {
        float hx = bot2 + s* 90 * cos(angle); // Calculate x-coordinate
        float hy = y + s* 30 * sin(angle); // Calculate y-coordinate
        glVertex2f(hx, hy);
    }
    glEnd();

    glColor3f(0.58, 0.35, 0.14);
    glBegin(GL_POLYGON); // Use GL_POLYGON for a filled half-circle
    for (float angle = 0; angle <= M_PI; angle += 0.01)   // 0 to 180 degrees in radians
    {
        float hx = bot2-60 + s* 30 * cos(angle); // Calculate x-coordinate
        float hy = y + s* 25 * sin(angle); // Calculate y-coordinate
        glVertex2f(hx, hy);
    }
    glEnd();


}


// Function football player
void player1(float x, float y, float scale)
{
    // Head
    glColor3f(1.0, 0.8, 0.6); // Skin color
    drawCircle(x, y + scale * 80, scale * 20, 50);

    // Body
    glColor3f(0.0, 0.0, 1.0); // Blue shirt
    glBegin(GL_QUADS);
    glVertex2f(x - scale * 20, y + scale * 60);
    glVertex2f(x + scale * 20, y + scale * 60);
    glVertex2f(x + scale * 20, y);
    glVertex2f(x - scale * 20, y);
    glEnd();

    // Arms
    glColor3f(1.0, 0.8, 0.6); // Skin color
    glBegin(GL_QUADS);
    // Left arm
    glVertex2f(x - scale * 20, y + scale * 50);
    glVertex2f(x - scale * 50, y + scale * 30);
    glVertex2f(x - scale * 45, y + scale * 20);
    glVertex2f(x - scale * 20, y + scale * 40);
    // Right arm
    glVertex2f(x + scale * 20, y + scale * 50);
    glVertex2f(x + scale * 50, y + scale * 30);
    glVertex2f(x + scale * 45, y + scale * 20);
    glVertex2f(x + scale * 20, y + scale * 40);
    glEnd();

    // Legs
    glColor3f(0.0, 0.0, 0.0); // Black shorts
    glBegin(GL_QUADS);
    // Left leg
    glVertex2f(x - scale * 15, y);
    glVertex2f(x - scale * 5, y);
    glVertex2f(x - scale * 5, y - scale * 40);
    glVertex2f(x - scale * 15, y - scale * 40);
    // Right leg
    glVertex2f(x + scale * 15, y);
    glVertex2f(x + scale * 5, y);
    glVertex2f(x + scale * 5, y - scale * 40);
    glVertex2f(x + scale * 15, y - scale * 40);
    glEnd();

    // Shoes
    glColor3f(0.3, 0.3, 0.3); // Gray color for shoes
    glBegin(GL_QUADS);
    // Left shoe
    glVertex2f(x - scale * 20, y - scale * 40);
    glVertex2f(x - scale * 5, y - scale * 40);
    glVertex2f(x - scale * 5, y - scale * 45);
    glVertex2f(x - scale * 20, y - scale * 45);
    // Right shoe
    glVertex2f(x + scale * 20, y - scale * 40);
    glVertex2f(x + scale * 5, y - scale * 40);
    glVertex2f(x + scale * 5, y - scale * 45);
    glVertex2f(x + scale * 20, y - scale * 45);
    glEnd();


}

void player2(float x, float y, float scale)
{
    // Head
    glColor3f(1.0, 0.8, 0.6); // Skin color
    drawCircle(x, y + scale * 80, scale * 20, 50);

    // Body
    glColor3f(0.89, 0.89, 0.06); // yello shirt
    glBegin(GL_QUADS);
    glVertex2f(x - scale * 20, y + scale * 60);
    glVertex2f(x + scale * 20, y + scale * 60);
    glVertex2f(x + scale * 20, y);
    glVertex2f(x - scale * 20, y);
    glEnd();

    // Arms
    glColor3f(1.0, 0.8, 0.6); // Skin color
    glBegin(GL_QUADS);
    // Left arm
    glVertex2f(x - scale * 20, y + scale * 50);
    glVertex2f(x - scale * 50, y + scale * 30);
    glVertex2f(x - scale * 45, y + scale * 20);
    glVertex2f(x - scale * 20, y + scale * 40);
    // Right arm
    glVertex2f(x + scale * 20, y + scale * 50);
    glVertex2f(x + scale * 50, y + scale * 30);
    glVertex2f(x + scale * 45, y + scale * 20);
    glVertex2f(x + scale * 20, y + scale * 40);
    glEnd();

    // Legs
    glColor3f(0.0, 0.0, 0.0); // Black shorts
    glBegin(GL_QUADS);
    // Left leg
    glVertex2f(x - scale * 15, y);
    glVertex2f(x - scale * 5, y);
    glVertex2f(x - scale * 5, y - scale * 40);
    glVertex2f(x - scale * 15, y - scale * 40);
    // Right leg
    glVertex2f(x + scale * 15, y);
    glVertex2f(x + scale * 5, y);
    glVertex2f(x + scale * 5, y - scale * 40);
    glVertex2f(x + scale * 15, y - scale * 40);
    glEnd();

    // Shoes
    glColor3f(0.3, 0.3, 0.3); // Gray color for shoes
    glBegin(GL_QUADS);
    // Left shoe
    glVertex2f(x - scale * 20, y - scale * 40);
    glVertex2f(x - scale * 5, y - scale * 40);
    glVertex2f(x - scale * 5, y - scale * 45);
    glVertex2f(x - scale * 20, y - scale * 45);
    // Right shoe
    glVertex2f(x + scale * 20, y - scale * 40);
    glVertex2f(x + scale * 5, y - scale * 40);
    glVertex2f(x + scale * 5, y - scale * 45);
    glVertex2f(x + scale * 20, y - scale * 45);
    glEnd();


}

void ball(float ball1, float y, float scale)
{
    // Football
    glColor3f(0.0, 0.0, 0.0); // Black color for ball
    drawCircle(ball1, y - scale * 60, scale * 10, 50); // Ball below the player

}

///spinner
void spin(float x, float y, float scale)
{

    glColor3f(0.3, 0.3, 0.3); // Gray color for the cross
    glBegin(GL_QUADS);

// Horizontal bar
    glVertex2f(x - scale * 60, y + scale * 10); // Top-left corner of horizontal bar
    glVertex2f(x + scale * 60, y + scale * 10); // Top-right corner of horizontal bar
    glVertex2f(x + scale * 60, y - scale * 10); // Bottom-right corner of horizontal bar
    glVertex2f(x - scale * 60, y - scale * 10); // Bottom-left corner of horizontal bar

// Vertical bar
    glVertex2f(x - scale * 10, y + scale * 60); // Top-left corner of vertical bar
    glVertex2f(x + scale * 10, y + scale * 60); // Top-right corner of vertical bar
    glVertex2f(x + scale * 10, y - scale * 60); // Bottom-right corner of vertical bar
    glVertex2f(x - scale * 10, y - scale * 60); // Bottom-left corner of vertical bar

    glEnd();

}
void spinpil(float x, float y, float scale)
{

    glColor3f(0.8, 0.4, 0.23);
    glBegin(GL_QUADS);
    glVertex2f(x - scale * 15, y + scale * 70); // Top-left corner of vertical bar
    glVertex2f(x + scale * 15, y + scale * 70); // Top-right corner of vertical bar
    glVertex2f(x + scale * 15, y - scale * 70); // Bottom-right corner of vertical bar
    glVertex2f(x - scale * 15, y - scale * 70); // Bottom-left corner of vertical bar

    glEnd();




}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Sky//
    glColor3f(skyR, skyG, skyB); // Dynamic sky color
    glBegin(GL_POLYGON);
    glVertex2f(0, 540); // Adjusted to match pixel coordinates
    glVertex2f(1080, 540);
    glVertex2f(1080, 1080);
    glVertex2f(0, 1080);
    glEnd();
    //glEnd();
    sun(900,sun_y);

    //moon//
    moon(900,moon_y);
    //Cloud//
    cloud1(c1, 1060);
    cloud2(c2, 950);
    cloud3(c3, 900);

    //bird//
    bird1(b1, 900,1.0);
    bird2(b2-30, 950, 1.0);
    bird2(b2-30, 850, 1.0);
    bird3(b3, 1000, 1.0);

    //tree//
    tree(1080, 710, 0.12);
    tree(1060, 709, 0.15);
    tree(1030, 705, 0.18);
    tree(1000, 704, 0.19);
    tree(970, 704, 0.19);
    tree(933, 704, 0.20);
    tree(893, 703, 0.22);
    tree(855, 702, 0.23);
    tree(818, 700, 0.24);
    tree(780, 698, 0.25);
    tree(740, 695, 0.26);
    tree(700, 692, 0.28);
    tree(690, 688, 0.30);
    tree(640, 686, 0.33);
    tree(590, 682, 0.36);
    tree(530, 679, 0.40);
    tree(470, 670, 0.45);
    tree(400, 658, 0.50);
    tree(320, 645, 0.62);
    tree(220, 610, 0.75);
    tree(80, 580, 0.88);


// PlayGround//
    glColor3f(0.16, 0.77, 0.18);
    glPushMatrix();
    glScalef(15, 4, 1.0); // Adjusted scaling
    playground(80, -20, 200);
    glPopMatrix();
    glEnd();

    //River//
    glColor3f(0.16, 0.38, 0.77);
    glPushMatrix();
    glScalef(7, 2.5, 1.0); // Adjusted scaling
    playground(180, 0, 200);
    glPopMatrix();
    glEnd();

    // boat//
    glPushMatrix();
    boat1(bot1, 300,1.0);
    glPopMatrix();
    boat2(bot2,100,1.0);

    glPushMatrix();
    player1(300, 500,0.6); // Draw the player at position (300, 300)
    glPopMatrix();

    glPushMatrix();
    player2(600, 500,0.6); // Draw the player at position (300, 300)
    glPopMatrix();



    ball(ball1,550,1);



    spinpil(900, 700, 1.0);
    glPushMatrix();
    glTranslatef(900, 760, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 0.10f);
    spin(0, 0,1.4);
    glPopMatrix();
    glutSwapBuffers();


//glTranslatef(0.0f, 0.0f, 0.0f);
//glRotatef(angle, 0.0f, .0f, 0.10f);
//glutSwapBuffers();
    glFlush();
}

void skyColor(int value)
{
    if (transitioningToNight)
    {
        // Transition to night
        if (skyR > 0.1) skyR -= colorChangeSpeed;
        if (skyG > 0.1) skyG -= colorChangeSpeed;
        if (skyB > 0.2) skyB -= colorChangeSpeed;

        if (skyR <= 0.1 && skyG <= 0.1 && skyB <= 0.2)
        {
            transitioningToNight = 0; // Start transitioning back to day
        }
    }
    else
    {
        // Transition to day
        if (skyR < 0.53) skyR += colorChangeSpeed;
        if (skyG < 0.81) skyG += colorChangeSpeed;
        if (skyB < 0.98) skyB += colorChangeSpeed;

        if (skyR >= 0.53 && skyG >= 0.81 && skyB >= 0.98)
        {
            transitioningToNight = 1; // Start transitioning back to night
        }
    }

    glutPostRedisplay(); // Trigger a redraw
    glutTimerFunc(16, skyColor, 0); // Call this function every 16ms (~60 FPS)
}




void uc1(int value)
{
    if(c1<=1300)
    {
        c1+=1;
    }
    else
    {
        c1=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, uc1, 0);
}
void uc2(int value)
{
    if(c2<=1300)
    {
        c2+=1.7;
    }
    else
    {
        c2=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, uc2, 0);
}
void uc3(int value)
{
    if(c3>=-100)
    {
        c3-=1.5;
    }
    else
    {
        c3=1300;
    }
    glutPostRedisplay();
    glutTimerFunc(16, uc3, 0);
}

void uSun(int value)
{
    if(sun_y<=1280 && sun_y>=-100)
    {
        sun_y-=0.32;
    }
    else
    {
        sun_y=1280;
    }
    glutPostRedisplay();
    glutTimerFunc(16, uSun, 0);
}

void umoon(int value)
{
    if(moon_y<=2380 && moon_y>=100)
    {
        moon_y-=0.32;
    }
    else
    {
        moon_y=2380;
    }
    glutPostRedisplay();
    glutTimerFunc(16, umoon, 0);
}

void ub1(int value)
{
    if(b1<=1300)
    {
        b1+=1.9;
    }
    else
    {
        b1=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, ub1, 0);
}
void ub2(int value)
{
    if(b2<=1200)
    {
        b2+=1.9;
    }
    else
    {
        b2=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, ub2, 0);
}

void ub3(int value)
{
    if(b3<=1300)
    {
        b3+=4;
    }
    else
    {
        b3=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, ub3, 0);
}

int bot1Direction = 1;
void ubot1(int value)
{
    if(isBoatRun){
    if (bot1Direction == 1)   // Moving right
    {
        bot1 += 4;
        if (bot1 >= 1300)     // Reached the right boundary
        {
            bot1Direction = -1; // Change direction to left
        }
    }
    else     // Moving left
    {
        bot1 -= 4;
        if (bot1 <= 300)      // Reached the left boundary
        {
            bot1Direction = 1; // Change direction to right
        }
    }

    glutPostRedisplay();
    }
    glutTimerFunc(16, ubot1, 0);
}


void ubot2(int value)
{
    if(bot2<=1300)
    {
        bot2+=2;
    }
    else
    {
        bot2=-100;
    }
    glutPostRedisplay();
    glutTimerFunc(16, ubot2, 0);
}

int ball1Direction = 1;
void uball1(int value)
{
    if(isBallrun){
    if (ball1Direction == 1)   // Moving right
    {
        ball1 += 3;
        if (ball1 >= 600)     // Reached the right boundary
        {
            ball1Direction = -1; // Change direction to left
        }
    }
    else     // Moving left
    {
        ball1 -= 3;
        if (ball1 <= 300)      // Reached the left boundary
        {
            ball1Direction = 1; // Change direction to right
        }
    }

    glutPostRedisplay();
    }       // Trigger a redraw
    glutTimerFunc(16, uball1, 0);
}


///spinner rotation func
void spinfunc(int value)
{
    if(isSpinning)
    {
        angle += 0.5f; // Increment angle by 2 degrees
        if (angle > 360.0f)
        {
            angle -= 360.0f; // Reset angle after a full rotation
        }
        glutPostRedisplay();
    } // Request redraw
    glutTimerFunc(16, spinfunc, 0); // Call update again in ~16ms (60 FPS)

}


///keyboard function

///spinner
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'S')
    {
        isSpinning = true;  // Start spinning
    }
    else if (key == 's' )
    {
        isSpinning = false;  // Stop spinning
    }

    ///boat
    if (key == 'B')
    {
        isBoatRun = true;  // Boat run
    }
    else if (key == 'b' )
    {
        isBoatRun = false;  // Boat Stop
    }

    ///foot ball
    if (key == 'F')
    {
        isBallrun = true;  // Boat run
    }
    else if (key == 'f' )
    {
        isBallrun = false;  // Boat Stop
    }
}



void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1080, 0, 1080); // Set up pixel coordinates
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000); // Matches pixel resolution
    glutCreateWindow("Beautiful Village Playground");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, skyColor, 0);
    glutTimerFunc(16, uc1, 0);
    glutTimerFunc(16, uc2, 0);
    glutTimerFunc(16, uc3, 0);
    glutTimerFunc(16, uSun, 0);
    glutTimerFunc(16, umoon, 0);
    glutTimerFunc(16, ub1, 0);
    glutTimerFunc(16, ub2, 0);
    glutTimerFunc(16, ub3, 0);
    glutTimerFunc(16, ubot1, 0);
    glutTimerFunc(16, ubot2, 0);
    glutTimerFunc(16, uball1, 0);
    glutTimerFunc(16, spinfunc, 0);
    glutMainLoop();
    return 0;
}

