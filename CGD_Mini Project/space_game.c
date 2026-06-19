#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_BULLETS 20
#define MAX_ENEMIES 7
#define MAX_STARS 100

float spaceshipX = 0;
float spaceshipSpeed = 0.05;

// Key state
int keyLeft = 0;
int keyRight = 0;
int keyUp = 0;

// Bullet structure
typedef struct {
    float x, y;
    int active;
    float trailY[3];
} Bullet;

Bullet bullets[MAX_BULLETS];
float bulletSpeed = 0.035;

// Enemy structure
typedef struct {
    float x, y;
    float dx;
    int active;
} Enemy;

Enemy enemies[MAX_ENEMIES];

// Star structure
typedef struct {
    float x, y;
    float speed;
} Star;

Star stars[MAX_STARS];

int score = 0;
int gameOver = 0;
float enemySpeed = 0.0008;

// Initialize stars
void initStars() {
    srand(time(NULL));
    for(int i=0;i<MAX_STARS;i++){
        stars[i].x = (float)(rand()%200)/100 -1;
        stars[i].y = (float)(rand()%200)/100 -1;
        stars[i].speed = 0.001 + (float)(rand()%10)/2000;
    }
}

// Initialize enemies
void initEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = (float)(rand()%180)/100 -0.9; // keep away from borders
        enemies[i].y = 0.8f + i*0.15f;
        enemies[i].dx = ((rand()%2) ? 0.004 : -0.004);
        enemies[i].active = 1;
    }
}

// Draw stars
void drawStars() {
    glColor3f(1,1,1);
    glPointSize(2);
    glBegin(GL_POINTS);
    for(int i=0;i<MAX_STARS;i++)
        glVertex2f(stars[i].x, stars[i].y);
    glEnd();
}

// Update stars
void updateStars() {
    for(int i=0;i<MAX_STARS;i++){
        stars[i].y -= stars[i].speed;
        if(stars[i].y < -1) {
            stars[i].y = 1;
            stars[i].x = (float)(rand()%200)/100 -1;
        }
    }
}

// Draw spaceship
void drawSpaceship() {
    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
        glVertex2f(spaceshipX, -0.9);
        glVertex2f(spaceshipX - 0.05, -0.8);
        glVertex2f(spaceshipX + 0.05, -0.8);
    glEnd();
}

// Draw bullets with trail
void drawBullets() {
    glColor3f(1,0,0);
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].active){
            // bullet
            glBegin(GL_QUADS);
                glVertex2f(bullets[i].x - 0.01, bullets[i].y);
                glVertex2f(bullets[i].x + 0.01, bullets[i].y);
                glVertex2f(bullets[i].x + 0.01, bullets[i].y + 0.04);
                glVertex2f(bullets[i].x - 0.01, bullets[i].y + 0.04);
            glEnd();
            // trail
            glColor3f(1,0.5,0);
            for(int t=0;t<3;t++){
                if(bullets[i].trailY[t] > -1){
                    glBegin(GL_QUADS);
                        glVertex2f(bullets[i].x - 0.005, bullets[i].trailY[t]);
                        glVertex2f(bullets[i].x + 0.005, bullets[i].trailY[t]);
                        glVertex2f(bullets[i].x + 0.005, bullets[i].trailY[t]-0.01);
                        glVertex2f(bullets[i].x - 0.005, bullets[i].trailY[t]-0.01);
                    glEnd();
                }
            }
            glColor3f(1,0,0);
        }
    }
}

// Draw alien enemies
void drawEnemies() {
    for(int i=0;i<MAX_ENEMIES;i++){
        if(enemies[i].active){
            glColor3f((float)(rand()%100)/100, (float)(rand()%100)/100, (float)(rand()%100)/100);
            glBegin(GL_POLYGON);
                glVertex2f(enemies[i].x, enemies[i].y+0.05);
                glVertex2f(enemies[i].x -0.05, enemies[i].y);
                glVertex2f(enemies[i].x +0.05, enemies[i].y);
                glVertex2f(enemies[i].x -0.03, enemies[i].y-0.05);
                glVertex2f(enemies[i].x +0.03, enemies[i].y-0.05);
            glEnd();
        }
    }
}

// Draw score
void drawScore() {
    char scoreStr[20];
    sprintf(scoreStr,"Score: %d",score);
    glColor3f(1,1,1);
    glRasterPos2f(-0.95,0.9);
    for(int i=0; scoreStr[i]!='\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, scoreStr[i]);
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStars();
    drawSpaceship();
    drawBullets();
    drawEnemies();
    drawScore();
    glFlush();
}

// Update game state
void update(int value) {
    if(gameOver){
        glutPostRedisplay();
        return;
    }

    // Spaceship continuous movement
    if(keyLeft && spaceshipX > -0.9) spaceshipX -= spaceshipSpeed;
    if(keyRight && spaceshipX < 0.9) spaceshipX += spaceshipSpeed;

    // Continuous shooting
    if(keyUp){
        static int shootDelay = 0;
        shootDelay++;
        if(shootDelay % 5 == 0){
            for(int i=0;i<MAX_BULLETS;i++){
                if(!bullets[i].active){
                    bullets[i].active = 1;
                    bullets[i].x = spaceshipX;
                    bullets[i].y = -0.85;
                    bullets[i].trailY[0] = bullets[i].y-0.01;
                    bullets[i].trailY[1] = bullets[i].y-0.02;
                    bullets[i].trailY[2] = bullets[i].y-0.03;
                    break;
                }
            }
        }
    }

    // Move bullets
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].active){
            bullets[i].trailY[2] = bullets[i].trailY[1];
            bullets[i].trailY[1] = bullets[i].trailY[0];
            bullets[i].trailY[0] = bullets[i].y;

            bullets[i].y += bulletSpeed;
            if(bullets[i].y > 1.0)
                bullets[i].active = 0;
        }
    }

    // Move stars
    for(int i=0;i<MAX_STARS;i++){
        stars[i].y -= stars[i].speed;
        if(stars[i].y < -1) {
            stars[i].y = 1;
            stars[i].x = (float)(rand()%200)/100 -1;
        }
    }

    // Move enemies
    for(int i=0;i<MAX_ENEMIES;i++){
        if(enemies[i].active){
            enemies[i].x += enemies[i].dx;
            enemies[i].y -= enemySpeed;
            if(enemies[i].x > 0.95) enemies[i].x = 0.95, enemies[i].dx = -enemies[i].dx;
            if(enemies[i].x < -0.95) enemies[i].x = -0.95, enemies[i].dx = -enemies[i].dx;
            if(enemies[i].y -0.05 < -1.0) gameOver = 1;
        }
    }

    // Collision detection
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].active){
            for(int j=0;j<MAX_ENEMIES;j++){
                if(enemies[j].active){
                    if(fabs(bullets[i].x - enemies[j].x) < 0.05 &&
                       fabs(bullets[i].y - enemies[j].y) < 0.05){
                        bullets[i].active = 0;
                        enemies[j].active = 0;
                        score += 10;

                        enemies[j].x = (float)(rand()%180)/100 -0.9;
                        enemies[j].y = 1.0f;
                        enemies[j].dx = ((rand()%2) ? 0.004 : -0.004);
                        enemies[j].active = 1;
                        enemySpeed += 0.0002;
                    }
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Key press/release
void keyPress(int key, int x, int y){
    if(key == GLUT_KEY_LEFT) keyLeft = 1;
    if(key == GLUT_KEY_RIGHT) keyRight = 1;
    if(key == GLUT_KEY_UP) keyUp = 1;
}

void keyRelease(int key, int x, int y){
    if(key == GLUT_KEY_LEFT) keyLeft = 0;
    if(key == GLUT_KEY_RIGHT) keyRight = 0;
    if(key == GLUT_KEY_UP) keyUp = 0;
}

// Keyboard for restart/exit
void keyboard(unsigned char key, int x, int y){
    if(key == 'j' || key == 'J'){ // J key to restart
        spaceshipX = 0;
        score = 0;
        enemySpeed = 0.008;
        gameOver = 0;
        initEnemies();
        glutDisplayFunc(display); // restore normal display
    }
    if(key == 27) exit(0); // ESC to quit
}


// Game over display
void displayGameOver() {
    glClear(GL_COLOR_BUFFER_BIT);
    char msg[50];
    sprintf(msg,"GAME OVER! Score: %d",score);
    glColor3f(1,0,0);
    glRasterPos2f(-0.4,0);
    for(int i=0; msg[i]!='\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,msg[i]);
    glFlush();
}

void checkGameOver(int value){
    if(gameOver){
        glutDisplayFunc(displayGameOver);
        glutPostRedisplay();
    } else {
        glutTimerFunc(16, checkGameOver, 0);
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Space Shooting Game");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);

    initEnemies();
    initStars();

    glutDisplayFunc(display);
    glutSpecialFunc(keyPress);
    glutSpecialUpFunc(keyRelease);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);
    glutTimerFunc(16, checkGameOver, 0);

    glutMainLoop();
    return 0;
}
