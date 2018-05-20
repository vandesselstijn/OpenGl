#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "./jpeg/InitJPG.h"

GLint move = 0, race = 0;
GLdouble zeepkist_x = 0;
//GLdouble xlens = 3, ylens = 3, zlens = 10;
GLdouble xlens = 9, ylens = 9, zlens = 30;
//GLdouble xlens = 6, ylens = 6, zlens = 20;
//GLdouble xlens = 1, ylens = 17, zlens = 1; //top
GLdouble xref = 1.0, yref = 1.0, zref = 0.0;
GLdouble xvw = 0.0, yvw = 1.0, zvw = 0.0;
GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0;
GLdouble near = 1.0, far = 1000;
GLdouble hoek = 60.0;
GLfloat ttx = 0.25, tty = 0.25, ttz = 0.25;
GLint lijnen = 0;
GLubyte projectie = 'p';
GLdouble verhouding = 0;

#define ZESTIEN 16
#define ZES 6
char roos[80] = "falken_rim.jpg";
GLubyte texVier[ZESTIEN][ZESTIEN][4];
static GLuint texNaam[ZES];

void myinit(void)
{
  glClearColor(0.9, 0.9, 0.9, 0.0);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  
  /*tImageJPG *pImage;
  int i;
  pImage = LoadJPG(roos);
  fprintf(stderr, "prent %s : %d x %d\n", roos, pImage->sizeX, pImage->sizeY);
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(2, texNaam);
  glBindTexture(GL_TEXTURE_2D, texNaam[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY,
                        0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
  glBindTexture(GL_TEXTURE_2D, texNaam[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ZESTIEN, ZESTIEN,
                        0, GL_RGBA, GL_UNSIGNED_BYTE, texVier);*/
}

void toetsen( unsigned char key, int x, int y)
{
  switch ( key )
  {
    case 'x' : xlens++;  break;     case 'X' : xlens--;  break;
    case 'y' : ylens++;  break;     case 'Y' : ylens--;  break;
    case 'z' : zlens++;  break;     case 'Z' : zlens--;  break;
    case 'u' : xref++;   break;     case 'U' : xref--;   break;
    case 'v' : yref++;   break;     case 'V' : yref--;   break;
    case 'w' : zref++;   break;     case 'W' : zref--;   break;
    case 'm' : move = 0 ;   break;  case 'M' : move = 1; break;
    case 'r' : race = 0 ;   break;  case 'R' : race = 1; break;
    case 'j' : xvw = 1.0; yvw = zvw = 0.0;   break;
    case 'k' : yvw = 1.0; xvw = zvw = 0.0;   break;
    case 'l' : zvw = 1.0; yvw = xvw = 0.0;   break;
    case 'i' : xlens = ylens = zlens = 3.0; 
            xvw  = zvw  = 0.0;  yvw = 1.0;  
            xref = yref =  zref = 0.0;    break;
    case '0' : lijnen = !lijnen;         break;
    case 'q' : exit(0);                break;
  }
  
  printf("Oog bl%5.1f gr%5.1f rd%5.1f ", xlens, ylens, zlens );
  printf("  Ref %5.1f %5.1f %5.1f ViR %4.1f %4.1f %4.1f\n", xref, yref, zref, xvw,yvw,zvw);
  glutPostRedisplay();
}

//tekenen van 1 as
void as()
{
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 5.0);
  glEnd();
}

//assen-stelsel
void assen()
{
  glLineWidth(1.0);
  glColor3f(0.0, 0.1, 0.8);
  as();       // z-as
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glColor3f(0.8, 0.1, 0.0);
  as();       // x-as
  glPopMatrix();
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glColor3f(0.0, 0.8, 0.1);
  as();       // y-as
  glPopMatrix();
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(ttx, tty, ttz);
  glPopMatrix();
}

#define slices  30
#define stacks  30

#define tire_diameter 2
#define tire_height   0.8
#define tire_width_b  1.5
#define tire_width_s  0.3

void wiel(float tire_width)
{
  GLUquadricObj *tire;
  tire = gluNewQuadric();
  glColor3f(0.0,0.0,0.0);

  /*glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texNaam[0]);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  
  gluQuadricTexture(tire,GL_TRUE);
  gluQuadricDrawStyle(tire,GLU_FILL);*/


  //tire walls
  glPushMatrix();
  gluDisk(tire, tire_diameter-tire_height, tire_diameter,  slices, stacks); 

  //glDisable(GL_TEXTURE_2D);
  glTranslatef(0, 0, tire_width);
  gluDisk(tire, tire_diameter-tire_height, tire_diameter,  slices, stacks);
  glPopMatrix(); 

  //loopvlak + binnekant
  gluCylinder( tire, tire_diameter, tire_diameter, tire_width, slices, stacks);
  gluCylinder( tire, tire_diameter-tire_height, tire_diameter-tire_height, tire_width, slices, stacks);
}

#define wheel_ofset     1
#define tube_diameter   0.1
#define frame_width     7.0
#define frame_lengt     4.0
#define small_gap       0.5
#define head_tube       0.4
#define stack_height    1.5

void onderstel_tube(float tube_lengt)
{
    GLUquadricObj *frame;
    frame = gluNewQuadric();
    glColor3f(1.0,0.0,0.0);

    //tube end
    glPushMatrix();
    gluDisk(frame, 0, tube_diameter,  slices, stacks);

    glTranslatef(0, 0, tube_lengt);
    gluDisk(frame, 0, tube_diameter,  slices, stacks);
    glPopMatrix();

    //tube
    gluCylinder( frame, tube_diameter, tube_diameter, tube_lengt, slices, stacks);
}

void zitje(float seat_height, float seat_width)
{
    GLUquadricObj *top;
    top = gluNewQuadric();

    glPushMatrix();
    glTranslated(0 ,seat_height,frame_width/2);
    glRotated(90, 1, 0, 0);
    glutSolidCone(seat_width,seat_height, slices, stacks);
    gluDisk(top, 0, seat_width,  slices, stacks);
    //Todo: als extra een Rugleuning
    glPopMatrix();
}

void onderstel()
{
    wiel(tire_width_b);

    //Tube breedte richting
    onderstel_tube(frame_width);

    //Tube lengte richting
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(-frame_width/2 , 0, 0);
    onderstel_tube(frame_lengt);
    glPopMatrix();

    //Zitje
    zitje(frame_width/8,frame_width/6);

    //2de wiel
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glTranslatef(0 , 0, -frame_width);
    wiel(tire_width_b);
    glPopMatrix();

    //3de (klein) wiel
    glPushMatrix();
    glTranslatef(frame_lengt+tire_diameter+wheel_ofset , 0, frame_width/2-tire_width_s/2);
    wiel(tire_width_s);
    glPopMatrix();

    //staane buis stuurinrichting
    glPushMatrix();
    glTranslatef(frame_lengt , 0, frame_width/2);
    glRotatef(60.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    onderstel_tube(stack_height);
    glPopMatrix();

    //stuurstang
    glPushMatrix();
    glTranslatef(frame_lengt , 0, frame_width/2);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0 , stack_height, -tire_diameter);
    onderstel_tube(tire_diameter);
    glPopMatrix();

    //vork
    glPushMatrix();
    glTranslatef(frame_lengt , 0, frame_width/2);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0 , stack_height, 0);
    onderstel_tube(head_tube);
    glPushMatrix();
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glTranslatef(head_tube , 0, -tire_width_s/2-small_gap);
    onderstel_tube(tire_width_s+2*small_gap);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-tire_width_s/2-small_gap , 0, head_tube);
    onderstel_tube(tire_diameter+small_gap);
    glTranslatef(tire_width_s+2*small_gap, 0, 0);
    onderstel_tube(tire_diameter+small_gap);
    glPopMatrix();
    glPopMatrix();
}

//Carrosserie - Complex vlak met bezier
void carrosserie()
{
    glColor3f(0.1, 0.1, 0.8);

    //Punten carroserie
    GLfloat carroseriepunten[4][6][3] = {
            { {-2.5,-1,-1}, {3,-1,-1}, {4,-1,1.5}, {6,-1,1.9},  {8,-1,1.9},   {10,-1,3.5}},
            { {-2.5,2, -1}, {3, 1,-1}, {4,1,1.7},  {5.8,1,2.3},   {7.7,1,2.3},  {9.5,1,3.5}},
            { {-2.5,3, -1}, {3, 2,-1}, {4,2,1.9},  {5.4,2.7},   {7.3,2,2.9},  {8,2,3.5}},
            { {-2.5,5, -1}, {3, 3,-1}, {4,3,3.5},  {5,3.5},   {6.4,3,3.5},  {7.2,3,3.5}},
    };

    /*if(0)
    {
        glColor3f(0,0.5,1);
        glPointSize(2);

        glBegin(GL_POINTS);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 6; j++)
            {
                glVertex3f(carroseriepunten[i][j][0], carroseriepunten[i][j][1], carroseriepunten[i][j][2]);
            }
        }
        glEnd();
    }*/

    glPushMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 6, 0, 1, 18, 4, &carroseriepunten[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glDisable(GL_MAP2_VERTEX_3);
    glPopMatrix();

    glColor3f(0.8, 0.1, 0.1);
    glBegin(GL_QUADS);
        glVertex3f(-2.5,-1,-1);
        glVertex3f(-2.5, 5,-1);
        glVertex3f(-2.5, 5, 8);
        glVertex3f(-2.5,-1, 8);
    glEnd();
}

void boog()
{
    glColor3f(0.1, 0.8, 0.0);

    GLUnurbsObj *boog;
    bog = gluNewNurbsRenderer();
    gluNurbsProperty(boog, GLU_DISPLAY_MODE, GLU_FILL);

    //Punten boog
    GLfloqt boogpunten[4][6][3] = {
            { {-2.5,-1,-1}, {3,-1,-1}, {4,-1,1.5}, {6,-1,1.9},  {8,-1,1.9},   {10,-1,3.5}},
            { {-2.5,2, -1}, {3, 1,-1}, {4,1,1.7},  {5.8,1,2.3},   {7.7,1,2.3},  {9.5,1,3.5}},
            { {-2.5,3, -1}, {3, 2,-1}, {4,2,1.9},  {5.4,2.7},   {7.3,2,2.9},  {8,2,3.5}},
            { {-2.5,5, -1}, {3, 3,-1}, {4,3,3.5},  {5,3.5},   {6.4,3,3.5},  {7.2,3,3.5}},
    };

    if(1)
    {
        glColor3f(0,0.5,1);
        glPointSize(2);

        glBegin(GL_POINTS);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 6; j++)
            {
                glVertex3f(boogpunten[i][j][0], boogpunten[i][j][1], boogpunten[i][j][2]);
            }
        }
        glEnd();
    }

    gluBeginSurface(opp);
        gluNurbsSurface(boog, 8, knots, 8, knots, 5*3, 3, &arcs[0][0][0], 3, 3, GL_MAP2_VERTEX_3);
    gluEndSurface(opp);
}

//Drawing funciton
void zeepkist(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xlens,ylens,zlens, xref,yref,zref, xvw, yvw, zvw);

    //assen tekenen
    //assen();

    glPushMatrix();
    glTranslatef(zeepkist_x , 0, 0);
    onderstel();
    carrosserie();
    glScaled(1,1,-1);
    glTranslatef(0, 0 ,-frame_width);
    carrosserie();


    glPopMatrix();

    if(race)
    {
        glPushMatrix();
        glTranslatef(zeepkist_x , 0, frame_width+tire_width_b);
        onderstel();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(zeepkist_x , 0, -frame_width-tire_width_b);
        onderstel();
        glPopMatrix();
    }

    glutSwapBuffers();
}

void herschaal(GLint n_w, GLint n_h) 
{
  GLdouble grens;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  switch ( projectie )
  {
    case 'o':
        glOrtho(xmin, xmax,  ymin, ymax, near, far);
        break;
    case 'f':
        glFrustum(xmin, xmax,  ymin, ymax, 2*near, 8*far);
        break;
        
    case 'p': gluPerspective(hoek, 1.0,  near, far);
        break;

    default:
    case 'F': grens = near*tan(M_PI*(hoek/2.0)/180.0);
        glFrustum(-grens, grens,  -grens, grens, near, far);
        break;
    }
  
    verhouding = xmax/ymax;
  
    if(n_w <= n_h * verhouding)
    {
        glViewport(0,0, n_w, n_w/verhouding);
    }
    else
    {
        glViewport(0,0, verhouding*n_h, n_h);
    }
    //glViewport(0, 0, n_w, n_h);
}

void animate()
{
    if(move)
    {
        zeepkist_x += 0.1;
        if(zeepkist_x >= 100)
            zeepkist_x = 0;
        glutPostRedisplay();
    }
}

//Main program
int main(int argc, char **argv)
{
      glutInit(&argc, argv);
      //Simple buffer
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
      glutInitWindowPosition(0,0);
      glutInitWindowSize(1366,768);
      glutCreateWindow("Zeepkist");myinit();
      glutKeyboardFunc(toetsen);
      glutReshapeFunc(herschaal);
      //Call to the drawing function
      glutDisplayFunc(zeepkist);
      glutIdleFunc(animate);
      glutMainLoop();
      return 0;
}
