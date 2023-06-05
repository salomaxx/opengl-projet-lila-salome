#include "3D_tools.h"
#include "draw_scene.h"

// Les premières fonctions dessinent les obstacles, les deux dernières les font avancer et les initialisent

void drawObstacle1(){   // dessine un obstacle en bas
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,-2);
        glVertex3f(-25/3,10,-2);
        glVertex3f(-25/3,10,-5);
        glVertex3f(-25/3,-10,-5);
    glEnd();
}

void drawObstacle2(){   // dessine un obstacle en haut
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,5);
        glVertex3f(-25/3,10,5);
        glVertex3f(-25/3,10,2);
        glVertex3f(-25/3,-10,2);
    glEnd();
}

void drawObstacle3(){   // dessine un obstacle à droite
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,5,5);
        glVertex3f(-25/3,10,5);
        glVertex3f(-25/3,10,-5);
        glVertex3f(-25/3,5,-5);
    glEnd();
}

void drawObstacle4(){   // dessine un obstacle à gauche
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,5);
        glVertex3f(-25/3,-5,5);
        glVertex3f(-25/3,-5,-5);
        glVertex3f(-25/3,-10,-5);
    glEnd();
}

void drawObstacle5(){   // dessine un obstacle sur les bords verticaux
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,5);
        glVertex3f(-25/3,-6,5);
        glVertex3f(-25/3,-6,-5);
        glVertex3f(-25/3,-10,-5);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-25/3,6,5);
        glVertex3f(-25/3,10,5);
        glVertex3f(-25/3,10,-5);
        glVertex3f(-25/3,6,-5);
    glEnd();
}

void drawObstacle6(){   // dessine un obstacle sur les bords horizontaux
    glColor3f(231./255, 143./255, 204./255);
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,5);
        glVertex3f(-25/3,10,5);
        glVertex3f(-25/3,10,3);
        glVertex3f(-25/3,-10,3);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,-3);
        glVertex3f(-25/3,10,-3);
        glVertex3f(-25/3,10,-5);
        glVertex3f(-25/3,-10,-5);
    glEnd();
}

// pour l'obstacle 7
float t=0; 
//float* p =&t;

void drawObstacle7(temps* temps_obs){   // dessine un obstacle qui bouge horizontalement

        glColor3f(231./255, 143./255, 204./255);
        glPushMatrix();
        glTranslatef(0,temps_obs->t/10,0);

        glBegin(GL_QUADS);
            glVertex3f(-25/3,-10,5);
            glVertex3f(-25/3,-5,5);
            glVertex3f(-25/3,-5,-5);
            glVertex3f(-25/3,-10,-5);
        glEnd();
        glPopMatrix();
}

void updateObstacle7Pos(temps* temps_obs) {
    static bool increment = true;
        
    if (temps_obs->t == 15*10) {
        increment = false;
    } else if (temps_obs->t == 0) {
        increment = true;
    }
    
    if (increment == false) {
        temps_obs->t-=1;
    } else {
        temps_obs->t+=1;
    }
}

// pour l'obstacle 8
float u=0; 

void drawObstacle8(temps* temps_obs){   // dessine un obstacle qui bouge verticalement
    glColor3f(231./255, 143./255, 204./255);
    glPushMatrix();
    glTranslatef(0,0,temps_obs->u/10);

    glBegin(GL_QUADS);
        glVertex3f(-25/3,-10,5);
        glVertex3f(-25/3,10,5);
        glVertex3f(-25/3,10,2);
        glVertex3f(-25/3,-10,2);
    glEnd();
    glPopMatrix();
}

void updateObstacle8Pos(temps* temps_obs) {
    static bool increment = true;
    
    if (temps_obs->u == -7*10) {
        increment = false;
    } else if (temps_obs->u == 0) {
        increment = true;
    }
    
    if (increment == false) {
        temps_obs->u++;
    } else {
        temps_obs->u--;
    }
} 


void moveObstacles(obstacle liste [10],obstacle actifs[6],float pos[4],ball* balle,temps* temps_obs,etat* jeu){
    // 4 obstacles sont toujours affichés
    // ils sont choisis au hasard et ajoutés dans la liste actifs
    for(int i=0; i<4;i++){ // dessin des 4  obstacles actifs
        glPushMatrix();
        glTranslatef(pos[i]+25/3,0,0);
        if(actifs[i].num==1){
            drawObstacle1();
        }
        if(actifs[i].num==2){
            drawObstacle2();
        }
        if(actifs[i].num==3){
            drawObstacle3();
        }
        if(actifs[i].num==4){
            drawObstacle4();
        }
        if(actifs[i].num==5){
            drawObstacle5();
        }
        if(actifs[i].num==6){
            drawObstacle6();
        }
        if(actifs[i].num==7){ // si l'obstacle bouge, on update sa position via une variable de temps dans temps_obs
            actifs[i].y=-10+temps_obs->t/10;
            drawObstacle7(temps_obs);
            updateObstacle7Pos(temps_obs);
        }
        if(actifs[i].num==8){
            actifs[i].z=2+temps_obs->u/10; 
            drawObstacle8(temps_obs);
            updateObstacle8Pos(temps_obs);  
        }
        glPopMatrix();
    }
    int aleat;
    for(int i=0;i<4;i++){
        // si l'obstacle sort de l'écran, on le supprime et en ajoute un autre à la file aléatoirement
        if(actifs[i].x >= 25){
            //on vérifie si l'obstacle est en deux parties, auquel cas on supprime la deuxième partie stockée dans actifs 4 et 5 (on la remplace par un obstacle vide)
            obstacle obs;
            if(actifs[i].num==5) actifs[4]=obs;
            if(actifs[i].num==6) actifs[5]=obs;

            // on choisit aléatoirement le prochain obstacle, si il est double, on assigne la deuxième partie de l'obstacle à actifs 4 ou 5
            aleat = rand()%8;
            // si on arrive à la fin du couloir, on arrete d'ajouter des obstacles
            if(jeu->obs>=40){
                obstacle obs;
                actifs[i]=obs;
            }
            else if(aleat==0){
            actifs[i] = liste[0];
            }
            else if(aleat==1){
                actifs[i] = liste[1];
            }
            else if(aleat==2){
                actifs[i] = liste[2];
            }
            else if(aleat==3){
                actifs[i] = liste[3];
            }
            else if(aleat==4){
                actifs[i] = liste[4];
                actifs[4] = liste[5];
            }
            else if(aleat==5){
                actifs[i] = liste[6];
                actifs[5] = liste[7];
            }
            else if(aleat==6){
                // pour éviter des problèmes de vitesse sur les obstacles mouvants, on vérifie qu'ils ne soient présent qu'une fois chacun en même temps
                int verif=0;
                for(int j=0;j<4;j++){
                    if(actifs[j].num==7) verif=1;
                }
                if(verif==0) actifs[i] = liste[8];
                else actifs[i] = liste[0];
            }
            else if(aleat==7){
                int verif=0;
                for(int j=0;j<4;j++){
                    if(actifs[j].num==8) verif=1;
                }
                if(verif==0) actifs[i] = liste[9];
                else actifs[i] = liste[1];
                }
            // on l'envoie à la position initiale
            pos[i]=-25/3;
            actifs[i].x = pos[i];
            // on ajoute un point au jeu
            jeu->obs+=1;
            // si le nombre de point est maximal, écran de win
            if(jeu->obs==45) jeu->a = 3;
        }
        if(!balle->collee){
            pos[i]+=0.05;
            actifs[i].x=pos[i];
            // si l'obstacle est composé de deux parties, on update aussi la position de la deuxième partie
            if(actifs[i].num==5) actifs[4].x=actifs[i].x;
            if(actifs[i].num==6) actifs[5].x=actifs[i].x;
        }
        
    }
}

void initObstacle(obstacle liste [10],obstacle actifs[6],float pos[4],temps* temps_obs){
    obstacle obs1;
    obstacle obs2;
    obstacle obs3;
    obstacle obs4;
    obstacle obs5;
    obstacle obs51;
    obstacle obs6;
    obstacle obs61;
    obstacle obs7;
    obstacle obs8;

    obs1.x = 0;
    obs1.y = -10;
    obs1.z = -5;
    obs1.hauteur = 3;
    obs1.largeur = 20;
    obs1.num=1;

    obs2.x = 0;
    obs2.y = -10;
    obs2.z = 2;
    obs2.hauteur = 3;
    obs2.largeur = 20;
    obs2.num=2;

    obs3.x = 0;
    obs3.y = 5;
    obs3.z = -5;
    obs3.hauteur = 10;
    obs3.largeur = 5;
    obs3.num=3;

    obs4.x = 0;
    obs4.y = -10;
    obs4.z = -5;
    obs4.hauteur = 10;
    obs4.largeur = 5;
    obs4.num=4;

    obs5.x = 0;
    obs5.y = -10;
    obs5.z = -5;
    obs5.hauteur = 10;
    obs5.largeur = 4;
    obs5.num=5;

    obs51.x = 0;
    obs51.y = 6;
    obs51.z = -5;
    obs51.hauteur = 10;
    obs51.largeur = 4;
    obs51.num=5.1;

    obs6.x = 0;
    obs6.y = -10;
    obs6.z = 3;
    obs6.hauteur = 2;
    obs6.largeur = 20;
    obs6.num=6;

    obs61.x = 0;
    obs61.y = -10;
    obs61.z = -5;
    obs61.hauteur = 2;
    obs61.largeur = 20;
    obs61.num=6.1;

    obs7.x = 0;
    obs7.y = -10+temps_obs->t/10;
    obs7.z = -5;
    obs7.hauteur = 10;
    obs7.largeur = 5;
    obs7.num=7;

    obs8.x = 0;
    obs8.y = -10;
    obs8.z = 2+temps_obs->u/10;
    obs8.hauteur = 3;
    obs8.largeur = 20;
    obs8.num=8;

    liste[0] = obs1;
    liste[1] = obs2;
    liste[2] = obs3;
    liste[3] = obs4;
    liste[4] = obs5;
    liste[5] = obs51;
    liste[6] = obs6;
    liste[7] = obs61;
    liste[8] = obs7;
    liste[9] = obs8;

    actifs[0] = obs1;
    actifs[1] = obs3;
    actifs[2] = obs2;
    actifs[3] = obs7;

    actifs[0].x=pos[0];
    actifs[1].x=pos[1];
    actifs[2].x=pos[2];
    actifs[3].x=pos[4];
}
