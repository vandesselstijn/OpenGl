#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "./jpeg/InitJPG.h"

GLdouble xlens = 3, ylens = 3, zlens = 10;
GLdouble xref = 1.0, yref = 1.0, zref = 0.0;
GLdouble xvw = 0.0, yvw = 1.0, zvw = 0.0;
GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0;
GLdouble near = 1.0, far = 100;
GLdouble hoek = 60.0;
GLfloat ttx = 0.25, tty = 0.25, ttz = 0.25;
GLint lijnen = 0;
GLubyte projectie = 'p';
GLdouble verhouding = 0;
GLdouble h = 0;
GLdouble h_deg = 0;

GLdouble xelips [] = {0.00, 4.06, 5.68, 7.01, 8.42, 10.66, 12.26, 13.96, 15.41};
GLdouble zelips [] = {0.00, 3.06, 5.00, 7.71, 9.42, 10.00, 11.26, 14.46, 16.41};
GLdouble hoeksnelh [] = {0.0, 0.2, 0.6, 1.0, 1.9, 11.9, 29.5, 84, 164.8};
GLdouble planhoek[] =  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLdouble straal [] = {1.0, 0.3, 0.50,  0.55, 0.4, 1.05, 1.03, 0.85, 0.825};

GLfloat wit[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat zwart[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lichtpunt0 [] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat r [] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat g [] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat b [] = { 0.0, 0.0, 1.0, 1.0 };


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
    case 'j' : xvw = 1.0; yvw = zvw = 0.0;   break;
    case 'k' : yvw = 1.0; xvw = zvw = 0.0;   break;
    case 'l' : zvw = 1.0; yvw = xvw = 0.0;   break;
    case 'i' : xlens = ylens = zlens = 3.0; 
            xvw  = zvw  = 0.0;  yvw = 1.0;  
            xref = yref =  zref = 0.0;    break;
    case '0' : lijnen = !lijnen;         break;
    case 'q' : exit(0);                break;
  }
  
  //printf("Oog bl%5.1f gr%5.1f rd%5.1f ", xlens, ylens, zlens );
  //printf("  Ref %5.1f %5.1f %5.1f ViR %4.1f %4.1f %4.1f\n", xref, yref, zref, xvw,yvw,zvw);
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

#define slices  16
#define stacks  16

#define tire_diameter 2
#define tire_height   0.8
#define tire_width    1.5
void wiel()
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

//Drawing funciton
void zeepkist(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xlens,ylens,zlens, xref,yref,zref, xvw, yvw, zvw);
  
  //assen tekenen
  assen();

  wiel();

  
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
  h += 1;
  
  for(int i = 1; i<8; i++)
  {
    planhoek[i]= h*(1/hoeksnelh[i])*(M_PI/180);
    
  }
    
  /*h_deg = h*(M_PI/180);*/
  glutPostRedisplay();
}

//Main program
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  //Simple buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition(50,25);
  glutInitWindowSize(500,250);
  glutCreateWindow("Zeepkist");
    myinit();
  glutKeyboardFunc(toetsen);
  glutReshapeFunc(herschaal);
  //Call to the drawing function
  glutDisplayFunc(zeepkist);
  glutIdleFunc(animate);
  glutMainLoop();
  return 0;
}
