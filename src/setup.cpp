#include "3D_tools.h"
#include "draw_scene.h"

void drawAxes(){
    
    glColor3f(1.,0.,0.);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
    glColor3f(0.,1.,0.);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
    glEnd();
    glColor3f(0.,0.,1.);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();
}


void drawRectSol(int x, int y, int height, int width){
    // x,y les coordonnées du point en bas à gauche
    glBegin(GL_QUADS);
		glVertex3f(x,y,0.0);
		glVertex3f(x+width,y,0.0);
		glVertex3f(x+width, y+height,0.0);
		glVertex3f(x, y+height,0.0);
	glEnd();
}

void drawRectFond(int y, int z, int height, int width){
    // y,z les coordonnées du point en bas à gauche
    glBegin(GL_QUADS);
		glVertex3f(0.,y,z);
		glVertex3f(0.,y+width,z);
		glVertex3f(0., y+width,z+height);
		glVertex3f(0, y,z+height);
	glEnd();
}

void drawRectSides(int x, int z, int height, float width){
    // x,z les coordonnées du point en bas derrière
    glBegin(GL_QUADS);
		glVertex3f(x,0,z);
		glVertex3f(x+width,0,z);
		glVertex3f(x+width, 0,z+height);
		glVertex3f(x, 0,z+height);
	glEnd();
}

void drawCorridor(){
    int longueur_mur = 25;
    glColor3f(231./255, 172./255, 218./255);
    glPushMatrix();
    glTranslatef(0,0,-5);
    drawRectSol(0,-10,20,longueur_mur);
    glTranslatef(0,0,10);
    drawRectSol(0,-10,20,longueur_mur);
    glPopMatrix();

    glColor3f(227./255, 120./255, 206./255);
    glPushMatrix();
    glTranslatef(0,-10,-5);
    drawRectSides(0,0,10,longueur_mur);
    glTranslatef(0,20,0);
    drawRectSides(0,0,10,longueur_mur);
    glPopMatrix();

    glColor3f(231./255, 172./255, 218./255);
    drawRectFond(-10,-5,10,20);
}


void drawRaquette(float y, float z, int size){
    // y,z les coordonnées du point en bas à gauche
    glColor3f(1.,1.,1.);
    glPushMatrix();
        glTranslatef(25,0,0);
        glBegin(GL_LINES);
            glVertex3f(0,y,z);
            glVertex3f(0,y+size,z);
            glVertex3f(0,y+size,z);
            glVertex3f(0,y+size,z+size);
            glVertex3f(0,y+size,z+size);
            glVertex3f(0,y,z+size);
            glVertex3f(0,y,z+size);
            glVertex3f(0,y,z);
        glEnd();
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.,1.,1.,0.1); 
    glPushMatrix();
        glTranslatef(25,0,0);
        glBegin(GL_QUADS);
            glVertex3f(0,y,z);
            glVertex3f(0,y+size,z);
            glVertex3f(0,y+size,z+size);
            glVertex3f(0,y,z+size);
        glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
}


void drawLines(){  //dessine une ligne sur chaque mur
    glColor3f(250,250,250);
    glPushMatrix();
    //glTranslatef(-25/3,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,-9.9,4.9);
        glVertex3f(0,9.9,4.9);

        glVertex3f(0,9.9,4.9);
        glVertex3f(0,9.9,-4.9);

        glVertex3f(0,9.9,-4.9);
        glVertex3f(0,-9.9,-4.9);

        glVertex3f(0,-9.9,-4.9);
        glVertex3f(0,-9.9,4.9);
    glEnd();
    glPopMatrix();
}

void moveLines(float pos[4],ball* balle){
    for(int i=0; i<4;i++){
        glPushMatrix();
        glTranslatef(pos[i],0,0);
        drawLines();
        glPopMatrix();
    }
    
	for(int i=0;i<4;i++){
        if(pos[i] >= 25){pos[i] = -25/3;}
		if(!balle->collee){pos[i]+=0.05;}
	}
}


void drawBall() {
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,0,0);
    drawSphere();
    glPopMatrix();
    }

void initBalle(ball* balle){
    balle->x = 25;
    balle->y = 0;
    balle->z = 0;
    balle->vx = -0.1;
    balle->vy = 0;
    balle->vz = 0;
    balle->taille = 2;
}


/*void moveRaquette(GLFWwindow *window,int width, int height,int size,raquette* raq){
    // Coordonnées de la souris dans [0, windows height/width] dans le plan (y,z)
	double mouseY, mouseZ;
    glfwGetCursorPos(window,&mouseY,&mouseZ);
    float h_plan, w_plan; //les dimensions du plan dans lequel se trouve la souris
    h_plan = 2*0.16*tan(110/2); //  110 l'angle donné dans gluPerspective
    w_plan = width*h_plan/height;

    // les coordonnées de la raquette par défaut (si ils sont dans le couloir)
    float y = -(w_plan*mouseY/width-w_plan/2);
    float z = h_plan*mouseZ/height-h_plan/2;
    // modification des coordonnées si ils sont hors du couloir
    if(y<-9){y = -9;}
    if(y>9){y= 9;}
    if(z<-4){z = -4;}
    if(z>4){z = 4;}

    glPushMatrix();
    glTranslatef(0,y,z);
    drawRaquette(-1,-1,size);
    glPopMatrix();

    raq->y=y;
    raq->z=z;
}*/
void moveRaquette(GLFWwindow *window,int width, int height,int size,raquette* raq){
    // Coordonnées de la souris dans [0, windows height/width] dans le plan (y,z)
    double mouseY, mouseZ;
    glfwGetCursorPos(window,&mouseY,&mouseZ);
    float h_plan, w_plan; //les dimensions du plan dans lequel se trouve la souris
    h_plan = 2*0.16*tan(110/2); //  110 l'angle donné dans gluPerspective
    w_plan = width*h_plan/height;

    // les coordonnées de la raquette par défaut (si ils sont dans le couloir)
    float y = -(w_plan*mouseY/width-w_plan/2);
    float z = h_plan*mouseZ/height-h_plan/2;
    // modification des coordonnées si ils sont hors du couloir
    if(y<-8.5){y = -8.5;}
    if(y>8.5){y= 8.5;}
    if(z<-3.5){z = -3.5;}
    if(z>3.5){z = 3.5;}

    glPushMatrix();
    glTranslatef(0,y,z);
    drawRaquette(-1.5,-1.5,size);
    glPopMatrix();

    raq->y=y;
    raq->z=z;
} 