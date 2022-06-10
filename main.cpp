#include <GL/glut.h> //openGL -open source graphics library
#include <cmath>
#include <algorithm>
#include<stdio.h>

using namespace std;
bool pick=FALSE;
double x=3;
double y=5;
double z=3;

// angles = { Y rotation at shoulder, Z rotation at shoulder, Z rotation at elbow, X rotation at wrist }
int arm_angles[5] = {-135, 55, 85 , 0, 60};
enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };

void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
    arm_angles[angle] = (arm_angles[angle] + delta) % 360;
    arm_angles[angle] = max(arm_angles[angle], minimum);
    arm_angles[angle] = min(arm_angles[angle], maximum);
    printf("1. %d, 2. %d, 3. %d 5. %d\n",arm_angles[0],arm_angles[1],arm_angles[2],arm_angles[4] );
}

GLfloat randomFloat() {
  return 6+((GLfloat)rand() / RAND_MAX)*2;
}
double cone_z=randomFloat();
double cone_x=randomFloat();


class Robot {
public:
    void draw()
    {
    glPushMatrix();
        glTranslatef(0., 0., 8.);
        glRotatef((GLfloat) arm_angles[SHOULDER_Y], 0., 1., 0.);
        glRotatef((GLfloat) arm_angles[SHOULDER_Z], 0., 0., 1.);

        glTranslatef(2., 0., 0.);
        glPushMatrix();
            glScalef(4.0, 0.4, 1.0);
            glColor3f(0.4f, 0.4f, 0.4f);
            glutSolidCube(1.);       // shoulder
            //glutWireCube(1.);
        glPopMatrix();

        glTranslatef(2., 0., 0.);
        glRotatef((GLfloat) arm_angles[ELBOW_Z], 0., 0., 1.);
        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(249./255., 238./255., 153./255.);
            glutSolidCube(1.);       // elbow
            //glutWireCube(1.);
        glPopMatrix();

        glTranslatef(1., 0., 0.);
        glRotatef((GLfloat) arm_angles[WRIST_Z], 0., 0., 1.);
        glRotatef((GLfloat) arm_angles[WRIST_X], 1., 0., 0.);

        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(207./255., 106./255., 76./255.);
            glutSolidCube(1.);       // wrist
            //glutWireCube(1.);
        glPopMatrix();
        if(pick==TRUE)
        {
            glTranslatef(1., 0., 0.);
            glPushMatrix();
                glColor3d(1,0,0);
                glutSolidSphere(0.3,30,30);
            glPopMatrix();

        }

    glPopMatrix();
    }

};

// A camera.  It moves horizontally in a circle centered at the origin of
// radius 15.  It moves vertically straight up and down.
class Camera {
  double theta;      // determines the x and z positions
  double y;          // the current y position
  double dTheta;     // increment in theta for swinging the camera around
  double dy;         // increment in y for moving the camera up/down
public:
  Camera(): theta(0), y(3), dTheta(0.04), dy(0.2) {}
  double getX() {return 15 * cos(theta);}
  double getY() {return y;}
  double getZ() {return 15 * sin(theta);}
  void moveRight() {theta += dTheta;}
  void moveLeft() {theta -= dTheta;}
  void moveUp() {y += dy;}
  void moveDown() {if (y > dy) y -= dy;}
};

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.
class Ball {
  double radius;
  double maximumHeight;
public:

    Ball(double r, double h):
      radius(r), maximumHeight(h){}

  void update() {
    y += -1 * 0.05;
    if (y < radius) {
      y = radius;
    }
    glPushMatrix();
        glTranslated(x, y, z);
        glColor3d(1,0,0);
        glutSolidSphere(radius, 30, 30);
    glPopMatrix();


  }
};


class Plane {
  int displayListId;
  int width;
  int depth;
public:
  Plane(int width, int depth): width(width), depth(depth) {}
  double centerx() {return width / 2;}
  double centerz() {return depth / 2;}
  void create() {
    glPushMatrix();

        glBegin(GL_QUADS);
            glNormal3d(0, 1, 0);

            glColor3d(1,1,1);
            glVertex3d(0, 0, 0);
            glVertex3d(width, 0, 0);
            glVertex3d(width, 0, depth);
            glVertex3d(0, 0, depth);
        glEnd();

    glPopMatrix();
  }

};

// Global variables: a camera, a checkerboard and some balls.
Plane checkerboard(8, 8);
Camera camera;
Ball balls[] = {
    Ball(0.3, 5)
    //Ball(0.4, 5, 0,8)
};
Robot robo_arm;

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void basket()
{
    glPushMatrix();
        //x=randomFloat();
        //y=randomFloat();
        glTranslatef(cone_x, 0.5, cone_z);
        glRotatef(90, 1, 0, 0);
        glColor3f(0, 1, 0);
        glutWireCone(1, 0.5, 25, 25);
    glPopMatrix();
}

void display() {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
            checkerboard.centerx(), 0.0, checkerboard.centerz(),
            0.0, 1.0, 0.0);
    checkerboard.create();

    basket();
    if (pick == FALSE)
    {
        for (int i = 0; i < sizeof balls / sizeof(Ball); i++)
            balls[i].update();
    }

    robo_arm.draw();
    glFlush();
    glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
    case GLUT_KEY_HOME: pick=!pick;y=0.6;z=cone_z;x=cone_x;break;

  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int delta = 5;

    switch (key) {
        case 27: //ESC
            exit(0);
        case 'q':
            change_angle(SHOULDER_Y, delta, -180, 180);
            break;
        case 'a':
            change_angle(SHOULDER_Y, -delta, -180, 180);
            break;
        case 'w':
            change_angle(SHOULDER_Z, delta, -180, 180);
            break;
        case 's':
            change_angle(SHOULDER_Z, -delta, -180, 180);
            break;
        case 'e':
            change_angle(ELBOW_Z, delta, 0, 135);
            break;
        case 'd':
            change_angle(ELBOW_Z, -delta, 0, 135);
            break;
        case 'r':
            change_angle(WRIST_X, delta, -45, 45);
            break;
        case 'f':
            change_angle(WRIST_X, -delta, -45, 45);
            break;
        case 't':
            change_angle(WRIST_Z, delta, -15, 90);
            break;
        case 'g':
            change_angle(WRIST_Z, -delta, -15, 90);
            break;

    }
    glutPostRedisplay();
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Robotic Arm Simulator");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(100, timer, 0);
  glutMainLoop();
}
