#include "3D_tools.h"
#include "draw_scene.h"

#define STB_IMAGE_IMPLEMENTATION
#include "C:\Users\33651\OneDrive\Bureau\Lescours\Open Gl\Proj\stb_image.h"


// VIES
void drawHeart() {
    glPushMatrix();
        glRotatef(45,1, 0,0);
        glBegin(GL_QUADS);
            glVertex3f(0.,-1,-1);
            glVertex3f(0.,1,-1);
            glVertex3f(0., 1,1);
            glVertex3f(0, -1,1);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1/sqrt(2),1/sqrt(2));
        glRotatef(90,0,1,0);
        drawCircle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-1/sqrt(2),1/sqrt(2));
        glRotatef(90,0,1,0);
        drawCircle();
    glPopMatrix();
}

void drawVie(){
    glPushMatrix();
        glColor3f(231./255, 143./255, 204./255);
        glTranslatef(25, 0, 0); //translate au bon endroit sur y et z  
        glScalef(1./2.,1./2.,1./2.); //scale à la bonne taille
        drawHeart();
    glPopMatrix();
}


void vies(etat* jeu){ // dessin des vies sous le couloir
    for(int i=0;i< jeu->vie;i++){
        glPushMatrix();
        glTranslatef(0,-9+i*2,-6.2);
        drawVie();
        glPopMatrix();
    }
}


// Chargement des images
void load_image_pre_boucle1(unsigned* texture, unsigned char* a,int x, int y,int n ){
    a  = stbi_load("../doc/menu_depart-min.png",&x,&y,&n,0);
	if(a == NULL){
		printf("c nul le debut");
		//throw new IOException(STBImage.stbi_failure_reason());
	}
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, a);
	glBindTexture(GL_TEXTURE_2D,0);
}
void load_image_pre_boucle2(unsigned* texture, unsigned char* a,int x, int y,int n ){
    a  = stbi_load("../doc/GAMEOVER-min.png",&x,&y,&n,0);
	if(a == NULL){
		printf("c nul game over");
	}
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, a);
	glBindTexture(GL_TEXTURE_2D,0);
}
void load_image_pre_boucle3(unsigned* texture, unsigned char* a,int x, int y,int n ){
    a  = stbi_load("../doc/fond-min.png",&x,&y,&n,0);
	if(a == NULL){
		printf("c nul le fond");
	}
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, a);
	glBindTexture(GL_TEXTURE_2D,0);
}
void load_image_pre_boucle4(unsigned* texture, unsigned char* a,int x, int y,int n){
    a  = stbi_load("../doc/win1-min.png",&x,&y,&n,0);
	if(a == NULL){
		printf("c nul la win");
	}
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, a);
	glBindTexture(GL_TEXTURE_2D,0);
}

// Render des images
void load_image_boucle1(unsigned* texture){ // pour les menus
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glColor4f(1,1,1,1);
		glBegin(GL_QUADS);
			
			glTexCoord2f(0,0);
			glVertex3f(26.5,-7.5,5);
			glTexCoord2f(1,0);
			glVertex3f(26.5,7.5,5);
			glTexCoord2f(1,1);
			glVertex3f(26.5,7.5,-5);
			glTexCoord2f(0,1);
			glVertex3f(26.5,-7.5,-5);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);
}

void load_image_boucle3(unsigned* texture){ //pour le fond du couloir
    glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glColor4f(1,1,1,1);
		glBegin(GL_QUADS);
			
			glTexCoord2f(0,0);
			glVertex3f(0.1,-10,5);
			glTexCoord2f(1,0);
			glVertex3f(0.1,10,5);
			glTexCoord2f(1,1);
			glVertex3f(0.1,10,-5);
			glTexCoord2f(0,1);
			glVertex3f(0.1,-10,-5);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);
}

// on libère l'espace
void load_image_post_boucle(unsigned* texture,unsigned char* a){
    glDeleteTextures(1,texture);
	stbi_image_free(a);
}
