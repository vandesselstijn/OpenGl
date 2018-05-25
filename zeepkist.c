////////////////////////////////////////
//Zeepkist Van Dessel Stijn           //
//Academiejaar 2017-2017              //
//Project Computergrafieken           //
////////////////////////////////////////


//// !!! Let er op dat de code voor het  renderen van afbeeldingen uitgecomment is      !!!///
//// !!! Dit werkt op LAUREL maar niet thuis aangezien de juist lib niet aanwezeig was  !!!///


#include "zeepkist.h"

GLint move = 0, race = 0, lijnenmash = 0, n=1, mist=0, smooth=0, lichthoogte = 8, volgen = 0;
GLint spotHoek = 0;
GLint shininess = 10;
GLint spotExp = 20;
GLint glas=0;

GLdouble xlens = 9, ylens = 9, zlens = 30;
GLdouble xref = 1.0, yref = 1.0, zref = 0.0;
GLdouble xvw = 0.0, yvw = 1.0, zvw = 0.0;
GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0;
GLdouble near = 1.0, far = 1000;
GLdouble hoek = 60.0;
GLfloat ttx = 0.25, tty = 0.25, ttz = 0.25;
GLint lijnen = 0;
GLubyte projectie = 'p';
GLdouble verhouding = 0;
GLdouble zeepkist_x[MAX_AANTAL] = {0};
GLubyte texVier[ZESTIEN][ZESTIEN][4];
static GLuint texNaam[ZES];
char rim[80] = 		"./textures/falken_rim.jpg";
char profiel[80] = 	"./textures/tire_profile.jpg";


GLfloat pos_licht_0[]   = {-10, 10, 10, 1};
GLfloat pos_licht_1[]   = {10, 10, 10, 1};
GLfloat pos_licht_2[]   = {0, 5, 5, 1};
GLfloat pos_licht_3[]   = {0, 6, 8, 1};
GLfloat richt_licht_3[] = {0, 0, -1};

GLfloat lightBlack[] = {0, 0, 0, 1};

GLfloat grijs [][4] = {   // Grijs
        {0.22, 0.22, 0.22, 0.3},            // Ambiant
        {0.33, 0.33, 0.33, 0.3},            // Diffuse
        {0.11, 0.11, 0.11, 0.3}             // Specular
};

GLfloat wit [][4] = {   // Wit
        { 0.66, 0.66, 0.66, 0.3 },            // Ambiant
        { 0.77, 0.77, 0.77, 0.3 },            // Diffuse
        { 0.55, 0.55, 0.55, 0.3 }             // Specular
};

GLfloat chroom [][4] = {   // Chroom
        {0.25, 0.25, 0.25, 1},              // Ambiant
        {0.4, 0.4, 0.4, 1},                 // Diffuse
        {0.77, 0.77, 0.77, 1}              // Specular
};

GLfloat brons [][4] = {   // Brons
        {0.21, 0.13, 0.10, 1},              // Ambiant
        {0.39, 0.27, 0.17, 1},              // Diffuse
        {0.71, 0.43, 0.18, 1},              // Specular
};

GLfloat geel [][4] = {   // Geel
        {0.65, 0.55, 0.15, 1},              // Ambiant
        {0.75, 0.45, 0.15, 1},              // Diffuse
        {0.85, 0.35, 0.15, 1},              // Specular
};

GLfloat lila [][4] =     {   // Lila
        {0.45, 0.15, 0.75, 1},              // Ambiant
        {0.55, 0.15, 0.65, 1},              // Diffuse
        {0.35, 0.15, 0.85, 1},              // Specular
};

GLfloat zwart [][4] =     {   // Lila
        {0, 0, 0, 1},              // Ambiant
        {0, 0, 0, 1},              // Diffuse
        {0, 0, 0, 1},              // Specular
};


//init functie licht
void initLicht()
{
    //instellingen licht
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightBlack);

    // Licht 0 -- Ambient wit licht
    GLfloat lightWhite[] = {1, 1, 1, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightBlack);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightBlack);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightWhite);

    // Licht 1 -- Diffuus groen-blauw licht
    GLfloat lightGreenBlue[] = {0, 0.7, 0.8, 1};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightGreenBlue);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightBlack);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightBlack);

    // Licht 2 -- specular rood licht
    GLfloat lightRed[] = {1, 0, 0, 1};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightBlack);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightRed);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightBlack);

    // Licht 3 -- gele spot
    GLfloat lightYellow[] = {1, 1, 0, 1};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightYellow);
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightYellow);
    glLightfv(GL_LIGHT3, GL_AMBIENT, lightYellow);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
}

//init functie mist
void initFog()
{
    //mist
    GLfloat kleur[] = {0.6, 0.5, 0.4, 1};
    glFogfv(GL_FOG_COLOR, kleur);

    glFogf(GL_FOG_DENSITY, 0.4);
    glFogf(GL_FOG_START, 20);
    glFogf(GL_FOG_END, 50);
}

//init functie voor textuur
//werkend op laurel
void initTextuur()
{
    tImageJPG *pImage;
    tImageJPG *rImage;

    int i;
    pImage = LoadJPG(rim);
    rImage = LoadJPG(profiel);

    //groote afbeelding afdrukken
    fprintf(stderr, "prent %s : %d x %d\n", rim, pImage->sizeX, pImage->sizeY);
    fprintf(stderr, "prent %s : %d x %d\n", profiel, rImage->sizeX, rImage->sizeY);

    glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(2, texNaam);
    glBindTexture(GL_TEXTURE_2D, texNaam[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
    glBindTexture(GL_TEXTURE_2D, texNaam[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rImage->sizeX, rImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, rImage->data);
}

//init funtion
void myinit(void)
{
    glClearColor(0.3, 0.3, 0.3, 0.0); //background
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    initFog();
    initLicht();
    initTextuur();
}


//Acties toetsen
void toetsen( unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 'x' : xlens++;  break; //Camera pos
        case 'X' : xlens--;  break;
        case 'y' : ylens++;  break;
        case 'Y' : ylens--;  break;
        case 'z' : zlens++;  break;
        case 'Z' : zlens--;  break;

        case 'a': glEnable(GL_LIGHT0); break;
        case 'A': glDisable(GL_LIGHT0); break;  // Licht 0
        case 'b': glEnable(GL_LIGHT1); break;
        case 'B': glDisable(GL_LIGHT1); break;  // Licht 1
        case 'c': glEnable(GL_LIGHT2); break;
        case 'C': glDisable(GL_LIGHT2); break;  // Licht 2
        case 'd': glEnable(GL_LIGHT3); break;
        case 'D': glDisable(GL_LIGHT3); break;  // Licht 3

        case 's': glShadeModel(GL_FLAT); break;
        case 'S': glShadeModel(GL_SMOOTH); break;   // Shading

        case 'h': lichthoogte++; break;
        case 'H': lichthoogte--; break;          // Spot hooghte

        case 'e': shininess+= 5; break;
        case 'E': shininess-= 5; break;             // Shininess

        case 'f': glas = !glas; break;    //doorzichtig

        case 'g' : move = 0 ;   break;
        case 'G' : move = 1;    break;
        case 'l' : lijnenmash = 0 ; break;
        case 'L' : lijnenmash = 1;  break;
        case 'n' : n-- ;        break;
        case 'N' : n++;         break;
        case 'm' : mist=0;      break;
        case 'M' : mist=1;      break;
        case 'j' : xvw = 1.0; yvw = zvw = 0.0;   break;
        case 'k' : yvw = 1.0; xvw = zvw = 0.0;   break;

        case 'u' : xref++;   break;
        case 'U' : xref--;   break;
        case 'v' : yref++;   break;
        case 'V' : yref--;   break;
        case 'w' : zref++;   break;
        case 'W' : zref--;   break;

        case '0' : lijnen = !lijnen;             break;

        case '1' :  xlens =  -90; ylens = 64; zlens = 30; break;
        case '2' :  xlens =  1; ylens = 63; zlens = 11; break;
        case '3' :  xlens =  -17; ylens = 11; zlens = -9; break;

        //Kijken naar finish of start
        case '4' :  volgen = 0; xref =  150; yref= 3.5; zref = 0; break;
        case '5' :  volgen = 0; xref =  1.0; yref= 1.0; zref = 0; break;
        case '6' :  volgen = !volgen; xref=zeepkist_x[0]; break;

        case '7' :  xlens =  149; ylens = 99; zlens = 0; break;
        case '8' :  xlens =  180; ylens = 14; zlens = 11; break;
        case '9' :  xlens =  154; ylens = 18; zlens = -31; break;

        case 'q' : exit(0);                      break;
    }

    if(n<1) //voorkomen dat er minder dan 1 zeepkist kan aangemaakt worden
        n=1;

    //Positie van oog opgeven
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
    glDisable(GL_LIGHTING);

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

    glEnable(GL_LIGHTING);
}

//tekenen van 1 wiel
void wiel(float tire_width)
{
    GLUquadricObj *tire;
    tire = gluNewQuadric();
    glColor3f(0.0,0.0,0.0);

    //textuur voor velg klaarzetten
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNaam[0]);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    gluQuadricTexture(tire,GL_TRUE);
    gluQuadricDrawStyle(tire,GLU_FILL);

    //tire walls
    glPushMatrix();
    glRotatef(zeepkist_x[0]*10, 0.0, 0.0, 1.0);
    gluDisk(tire, 0, tire_diameter,  slices, stacks);
    glTranslatef(0, 0, tire_width);
    gluDisk(tire, 0, tire_diameter,  slices, stacks);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //textuur voor band klaarzetten(bandenprofiel)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNaam[1]);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //loopvlak + binnekant
    gluCylinder( tire, tire_diameter, tire_diameter, tire_width, slices, stacks);
    gluCylinder( tire, tire_diameter-tire_height, tire_diameter-tire_height, tire_width, slices, stacks);

    glDisable(GL_TEXTURE_2D);
}


//helper functie voor het teken van 1 tuben van het onderstel met een bepaalde lengte
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

//teken van het zitje
void zitje(float seat_height, float seat_width)
{
    GLUquadricObj *top;
    top = gluNewQuadric();

    glPushMatrix();
    glTranslated(0 ,seat_height,frame_width/2);
    glRotated(90, 1, 0, 0);
    glutSolidCone(seat_width,seat_height, slices, stacks);
    gluDisk(top, 0, seat_width,  slices, stacks); //cone --> bovenkant is dicht dus 0
    glPopMatrix();
}

//Tekenen van het volledige onderstel
void onderstel()
{
    GLUquadricObj *stuur;
    stuur = gluNewQuadric();

    //Zetten van de materiaaleigenschappen
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, zwart[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, zwart[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, zwart[SPECULAR]);
    wiel(tire_width_b);

    //Tube breedte richting
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, chroom[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, chroom[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, chroom[SPECULAR]);
    onderstel_tube(frame_width);

    //Tube lengte richting
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(-frame_width/2 , 0, 0);
    onderstel_tube(frame_lengt);
    glPopMatrix();

    //Zitje
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, brons[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, brons[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, brons[SPECULAR]);
    zitje(frame_width/8,frame_width/6);

    //2de wiel
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, zwart[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, zwart[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, zwart[SPECULAR]);
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
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, chroom[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, chroom[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, chroom[SPECULAR]);
    glPushMatrix();
    glTranslatef(frame_lengt , 0, frame_width/2);
    glRotatef(60.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    onderstel_tube(stack_height);
    glPopMatrix();

    //stuurstang + stuur
    glPushMatrix();
    glTranslatef(frame_lengt , 0, frame_width/2);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0 , stack_height, -tire_diameter);
    onderstel_tube(tire_diameter);
    gluDisk(stuur, stuurdiameter-0.2, stuurdiameter,  slices, stacks);
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

    //punten voor het vormen van de carrosserie
    GLfloat carroseriepunten[4][6][3] = {
            { {-7,-0.5,3.5}, {3,-1,0.5}, {4,-1,1.5}, {6,-1,1.9},  {8,-1,1.9},   {10,-1,3.5}},
            { {-7,3, 3.5}, {3, 1,0.5}, {4,1,1.7},  {5.8,1,2.3},   {7.7,1,2.3},  {9.5,1,3.5}},
            { {-7,4, 3.5}, {3, 2,0.5}, {4,2,1.9},  {5.4,2.7},   {7.3,2,2.9},  {8,2,3.5}},
            { {-7,5, 3.5}, {3, 3,0.5}, {4,3,3.5},  {5,3.5},   {6.4,3,3.5},  {7.2,3,3.5}},
    };

    //plotten van de controlepunten
    if(lijnen)
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
    }

    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, grijs[0]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, grijs[1]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, grijs[2]);

    glPushMatrix();
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 6, 0, 1, 18, 4, &carroseriepunten[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);

    //tekenen van de lijnenmach
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    if(lijnenmash == 0)
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    else
        glEvalMesh2(GL_LINE, 0, 20, 0, 20);
    glDisable(GL_MAP2_VERTEX_3);

    glPopMatrix();
}

//tekenen van het complex bspline vlak
void BplineCurve(){
    GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
    int i, j;

    //dit mag boveneaan
    GLUnurbsObj *theNurb;
    //mag in init
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    //gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);

    GLfloat ctlpoints[4][4][3] = {
            { {2,0,0 },{3,0,boog_diameter*SIN45},{4,0,boog_diameter*SIN45},{5,0,0}},
            { {1.8,1,0},{2.5,1.5,boog_diameter*SIN45},{3.5,2.2,boog_diameter*SIN45},{4.2,2.5,0}},
            { {1,1.8,0},{1.5,2.5,boog_diameter*SIN45},{2.2,3.5,boog_diameter*SIN45},{2.5,4.2,0}},
            { {0,2,0},{0,3,boog_diameter*SIN45},{0,4,boog_diameter*SIN45},{0,5,0}},
    };

    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);

    if(lijnen)
    {
        glPointSize(7.0);
        glColor3f(1.0, 1.0, 0.0 );
        glBegin(GL_POINTS);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                glVertex3f(ctlpoints[i][j][0],
                           ctlpoints[i][j][1], ctlpoints[i][j][2]);
            }
        }
        glEnd();
    }
}

//2 bsplines samenvoegen tot een volledige bocht
void bocht()
{
    glPushMatrix();
    BplineCurve();
    glScaled(1,1,-1);
    BplineCurve();
    glPopMatrix();
}

//Tekenen van de volledige finishboog
void boog()
{
    glColor3f(0.0,0.8,0);

    GLUquadricObj *boogpaal;
    boogpaal = gluNewQuadric();


    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, geel[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, geel[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, geel[SPECULAR]);

    glPushMatrix();
    glTranslatef(150, 0, 0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glTranslatef(0, frame_width, 0);
    gluCylinder(boogpaal, boog_diameter/2, boog_diameter/2, boog_hoogte, slices, stacks);
    glTranslatef(0, -3*frame_width-2*(n-1)*frame_width, 0);
    gluCylinder(boogpaal, boog_diameter/2, boog_diameter/2, boog_hoogte, slices, stacks);

    glPopMatrix();
    glPushMatrix();

    //glTranslatef(-2*boog_diameter, boog_hoogte, -frame_width);


    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, lila[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, lila[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, lila[SPECULAR]);

    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(frame_width-5+boog_diameter, boog_hoogte, 0);
    bocht();

    glRotatef(180.0, 0.0, 1.0, 0.0);
    glTranslatef(n*2*frame_width, 0, 0);
    bocht();

    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, geel[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, geel[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, geel[SPECULAR]);

    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glTranslatef(0, 4, 0);
    gluCylinder(boogpaal, boog_diameter/2, boog_diameter/2, n*2*frame_width, slices, stacks);

    glPopMatrix();
    glPopMatrix();
}

//Tekenen van het zwart asfalt oppervlak
void asfalt() {
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0, 0, -frame_width);

    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, wit[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, wit[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, wit[SPECULAR]);
    glColor3f(1, 1, 1);

    //witte lijn teken
    for (int i = -1; i < 1; ++i) {
        for (int j = -30; j < race_lengt; ++j) {
            glBegin(GL_QUADS);
                glVertex3f(0, 0, 0);
                glVertex3f(j, 0, 0);
                glVertex3f(j, 0, i);
                glVertex3f(0, 0, i);
            glEnd();
        }
    }

    //asfalt tekenen
    glPushMatrix();
    glTranslatef(0, 0, frame_width+2*n*frame_width+1);
    for (int i = -1; i < 1; ++i) {
        for (int j = -30; j < race_lengt; ++j) {
            glBegin(GL_QUADS);
                glVertex3f(0, 0, 0);
                glVertex3f(j, 0, 0);
                glVertex3f(j, 0, i);
                glVertex3f(0, 0, i);
            glEnd();
        }
    }
    glPopMatrix();

    //volgende witte lijn tekenen
    glPushMatrix();
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, zwart[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, zwart[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, zwart[SPECULAR]);
    glColor3f(0.1, 0.1, 0.1);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < 3*frame_width+boog_diameter-1; ++i) {
            for (int j = -30; j < race_lengt; j+=15) {
                glBegin(GL_QUADS);
                    glVertex3f(0, 0, 0);
                    glVertex3f(j, 0, 0);
                    glVertex3f(j, 0, i);
                    glVertex3f(0, 0, i);
                glEnd();
            }
        }
        glTranslatef(0, 0, 2*frame_width);
    }
    glPopMatrix();


    glEnd();

    //Tekenen van de start streep
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, wit[DIFFUSE]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, wit[AMBIENT]);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, wit[SPECULAR]);
    glColor3f(1, 1, 1);
    for (int i = 0; i < 3*frame_width+boog_diameter+2*(n-1)*frame_width; ++i) {
        for (int j = 0; j < 2; ++j) {
            glBegin(GL_QUADS);
                glVertex3f(0, 0.01, 0);
                glVertex3f(j, 0.01, 0);
                glVertex3f(j, 0.01, i);
                glVertex3f(0, 0.01, i);
            glEnd();
        }
    }


    //Tekenen van de finish
    glTranslatef(150, 0, 0);
    glColor3f(1, 1, 1);
    for (int i = 0; i < 3*frame_width+boog_diameter+2*(n-1)*frame_width; ++i) {
        for (int j = 0; j < 2; ++j) {
            glBegin(GL_QUADS);
            glVertex3f(0, 0.01, 0);
            glVertex3f(j, 0.01, 0);
            glVertex3f(j, 0.01, i);
            glVertex3f(0, 0.01, i);
            glEnd();
        }
    }
    glPopMatrix();

}

//Mist functie
void initmist(void)
{
    GLfloat kleur[] = {0.6, 0.5, 0.4, 1};
    glFogfv(GL_FOG_COLOR, kleur);

    glFogf(GL_FOG_MODE, GL_LINEAR);

    glFogf(GL_FOG_DENSITY, 0.3);
    glFogf(GL_FOG_START, 100);
    glFogf(GL_FOG_END, 150);
}

void zeepkist()
{
    glPushMatrix();
    glTranslatef(0 , tire_diameter, 0); //op straat niveau brengen


    if(glas)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    for (int j = 0; j < n; j++) {
        glPushMatrix();
        glTranslatef(zeepkist_x[j] , 0, j*2*frame_width);
        onderstel();
        carrosserie();
        glScaled(1,1,-1);
        glTranslatef(0, 0 ,-frame_width);
        carrosserie();
        glPopMatrix();
    }

    if(glas)
        glDisable(GL_BLEND);

    glPopMatrix();
}

void licht()
{
    pos_licht_3[3] = lichthoogte;

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, pos_licht_0);
    glLightfv(GL_LIGHT1, GL_POSITION, pos_licht_1);
    glLightfv(GL_LIGHT2, GL_POSITION, pos_licht_2);
    glLightfv(GL_LIGHT3, GL_POSITION, pos_licht_3);

    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, richt_licht_3);
    glLightf(GL_LIGHT3,  GL_SPOT_EXPONENT, spotExp);
}

//De algemene tekenfunctie
void wedstrijd(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xlens,ylens,zlens, xref,yref,zref, xvw, yvw, zvw);
    licht();

    //assen tekenen
    if(lijnen)
        assen();

    if(mist)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);


    boog();
    asfalt();
    zeepkist();

    glutSwapBuffers();
}

void herschaal(GLint n_w, GLint n_h) {
    GLdouble grens;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (projectie) {
        case 'o':
            glOrtho(xmin, xmax, ymin, ymax, near, far);
            break;
        case 'f':
            glFrustum(xmin, xmax, ymin, ymax, 2 * near, 8 * far);
            break;

        case 'p':
            gluPerspective(hoek, 1.0, near, far);
            break;

        default:
        case 'F':
            grens = near * tan(M_PI * (hoek / 2.0) / 180.0);
            glFrustum(-grens, grens, -grens, grens, near, far);
            break;
    }

    verhouding = xmax / ymax;

    if (n_w <= n_h * verhouding) {
        glViewport(0, 0, n_w, n_w / verhouding);
    } else {
        glViewport(0, 0, verhouding * n_h, n_h);
    }
}

//animatie functie
void animate()
{
    float random = 0;


    if(move)
    {
        for (int i = 0; i < n; ++i) {
            random = (((double) rand() / (RAND_MAX)));
            random = random/10;
            random += 0.4;
            zeepkist_x[i] += random;

            if(volgen)
                xref = zeepkist_x[0];
        }

        if(zeepkist_x[0] >= 195)
        {
            for (int i = 0; i < MAX_AANTAL; ++i) {
                zeepkist_x[i] = -10;
            }
        }
        glutPostRedisplay();
    }
}

//Main program
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition(0,0);    //positie
    glutInitWindowSize(1366,768);   //groote
    glutCreateWindow("Zeepkist");myinit();  //heading
    glutKeyboardFunc(toetsen);              //calback voor toetsen
    glutReshapeFunc(herschaal);             //calback voor herschalen

    //Call to the drawing function
    glutDisplayFunc(wedstrijd);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}