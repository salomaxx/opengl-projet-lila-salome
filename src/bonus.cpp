#include "3D_tools.h"
#include "draw_scene.h"

void drawBonus1(int angle){

    glColor3f(43./255, 52./255, 62./255);
    glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(angle,1,1,1);

        glBegin(GL_LINES);
            // Face du dessus
            glVertex3f(-1, -1, 1);
            glVertex3f(1, -1, 1);
            glVertex3f(1, -1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, -1, 1);

            // Face du dessous
            glVertex3f(-1, -1, -1);
            glVertex3f(1, -1, -1);
            glVertex3f(1, -1, -1);
            glVertex3f(1, 1, -1);
            glVertex3f(1, 1, -1);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, 1, -1);
            glVertex3f(-1, -1, -1);

            // Arêtes
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, -1);
            glVertex3f(-1, -1, 1);
            glVertex3f(-1, -1, -1);
            glVertex3f(-1, 1, 1);
            glVertex3f(-1, 1, -1);
            glVertex3f(1, -1, 1);
            glVertex3f(1, -1, -1);
        glEnd();
    glPopMatrix();
}

void drawBonus2(int angle){

    glColor3f(186./255, 38./255, 157./255);
    glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(angle,1,1,1);

        glBegin(GL_LINES);
            // Face du dessus
            glVertex3f(-0.7, -0.7, 0.7);
            glVertex3f(0.7, -0.7, 0.7);
            glVertex3f(0.7, -0.7, 0.7);
            glVertex3f(0.7, 0.7, 0.7);
            glVertex3f(0.7, 0.7, 0.7);
            glVertex3f(-0.7, 0.7, 0.7);
            glVertex3f(-0.7, 0.7, 0.7);
            glVertex3f(-0.7, -0.7, 0.7);

            // Face du dessous
            glVertex3f(-0.7, -0.7, -0.7);
            glVertex3f(0.7, -0.7, -0.7);
            glVertex3f(0.7, -0.7, -0.7);
            glVertex3f(0.7, 0.7, -0.7);
            glVertex3f(0.7, 0.7, -0.7);
            glVertex3f(-0.7, 0.7, -0.7);
            glVertex3f(-0.7, 0.7, -0.7);
            glVertex3f(-0.7, -0.7, -0.7);

            // Arêtes
            glVertex3f(0.7, 0.7, 0.7);
            glVertex3f(0.7, 0.7, -0.7);
            glVertex3f(-0.7, -0.7, 0.7);
            glVertex3f(-0.7, -0.7, -0.7);
            glVertex3f(-0.7, 0.7, 0.7);
            glVertex3f(-0.7, 0.7, -0.7);
            glVertex3f(0.7, -0.7, 0.7);
            glVertex3f(0.7, -0.7, -0.7);
        glEnd();
    glPopMatrix();
}

void collisionBonus(ball* balle, bonus liste_bonus[2]){ // collision avec la balle : ne change rien à la trajectoire de la balle mais change les paramètres des bonus (actif ou visible)
    for(int i=0;i<2;i++){
        if(liste_bonus[i].visible==true && balle->y > liste_bonus[i].y-liste_bonus[i].largeur/2-balle->taille/2  &&  balle->y < liste_bonus[i].y+balle->taille/2+liste_bonus[i].largeur/2  &&  balle->z > liste_bonus[i].z-liste_bonus[i].hauteur/2-balle->taille/2  &&  balle->z < liste_bonus[i].z+balle->taille/2+liste_bonus[i].hauteur/2 && abs(balle->x-liste_bonus[i].x)< balle->taille/2){
        liste_bonus[i].actif=true;
        liste_bonus[i].visible=false;
        }
    }
}

void initBonus(bonus liste_bonus[2]){
    bonus bonus1;
    bonus1.x = 15;
    bonus1.y = 3;
    bonus1.z = -2;
    bonus1.hauteur = 2;
    bonus1.largeur = 2;
    bonus1.type = 1;
    bonus1.vx = 0.01;
    bonus1.visible = true;
    bonus1.actif = false;

    bonus bonus2;
    bonus2.x = 0;
    bonus2.y = -7;
    bonus2.z = -2;
    bonus2.hauteur = 2;
    bonus2.largeur = 2;
    bonus2.type = 2;
    bonus2.vx = 0.01;
    bonus2.visible = false;

    liste_bonus[0]=bonus1;
    liste_bonus[1]=bonus2;
}

void moveBonus(bonus liste_bonus[2],int angle,ball* balle){
    // on fait avancer un bonus selon si il doit etre visible et que la balle est en mouvement
    for(int i=0;i<2;i++){
        glPushMatrix();
        glTranslatef(liste_bonus[i].x,liste_bonus[i].y,liste_bonus[i].z);
        if(i==0 && liste_bonus[i].visible==true){drawBonus1(angle);
            if(!balle->collee)liste_bonus[i].x += liste_bonus[i].vx;}
        if(i==1 && liste_bonus[i].visible==true){drawBonus2(angle);
            if(!balle->collee)liste_bonus[i].x += liste_bonus[i].vx;}
        glPopMatrix();
        if(liste_bonus[i].x> 25-liste_bonus[i].largeur/2){
            liste_bonus[i].x = liste_bonus[i].largeur/2+1;
        }
    }
    // Conditions d'apparition des bonus : si le precedent n'est ni actif ni visible et que lui même n'est pas actif
    if(liste_bonus[0].visible==false && liste_bonus[0].actif==false && liste_bonus[1].actif==false) liste_bonus[1].visible=true;
    if(liste_bonus[1].visible==false && liste_bonus[1].actif==false && liste_bonus[0].actif==false) liste_bonus[0].visible=true;
}