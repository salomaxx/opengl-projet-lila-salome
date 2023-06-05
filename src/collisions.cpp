#include "3D_tools.h"
#include "draw_scene.h"



/* Fonctions gérants les différents types de collisions (contre couloir, raquette, obstacles)
puis fonction moveBall gérant tous les mouvements de la ball */

void collisionMurs(ball* balle){
    if(balle->x < balle->taille/2){
        balle->vx = -balle->vx;
        balle->x =+ balle->taille/2;
    }
    if(balle->y <-10+balle->taille/2){
        balle->vy = -balle->vy;
        balle->y = -10+balle->taille/2;
    }
    if(balle->y >10-balle->taille/2){
        balle->vy = -balle->vy;
        balle->y = 10-balle->taille/2;
    }
    if(balle->z >5-balle->taille/2){
        balle->vz = -balle->vz;
        balle->z = 5-balle->taille/2;
    }
    if(balle->z <-5+balle->taille/2){
        balle->vz = -balle->vz;
        balle->z = -5+balle->taille/2;
    }
}

void collisionObstacles(ball* balle,obstacle actifs[6], float pos[4]){

        for(int i=0;i<4;i++){
        // si la balle rencontre l'obstacle en allant vers le fond du couloir
        // Pour la coordonnée en x, on vérifie si la balle touche l'obstacle et ne le touchait pas la frame d'avant
        if((balle->x-balle->taille/2>pos[i]-balle->taille/2)&&(balle->x-balle->taille/2<=pos[i] && balle->x-balle->taille/2-balle->vx<=pos[i]) && (balle->y+balle->taille/2>actifs[i].y && balle->y-balle->taille/2<actifs[i].y+actifs[i].largeur) && (balle->z+balle->taille/2>actifs[i].z && balle->z-balle->taille/2<actifs[i].z+actifs[i].hauteur)){ 
            balle->vx = -balle->vx;
            balle->x = pos[i]+balle->taille/2;
        }
        // si la balle rencontre l'obstacle en allant vers nous
        if((balle->x+balle->taille/2<pos[i]+balle->taille/2)&&(balle->x+balle->taille/2>=pos[i] && balle->x+balle->taille/2-balle->vx<=pos[i]) && (balle->y+balle->taille/2>actifs[i].y && balle->y-balle->taille/2<actifs[i].y+actifs[i].largeur) && (balle->z+balle->taille/2>actifs[i].z && balle->z-balle->taille/2<actifs[i].z+actifs[i].hauteur)){ 
            balle->vx = -balle->vx;
            balle->x = pos[i]-balle->taille/2  ;
        }

        // si l'obstacles est composé de deux parties, on vérifie les parties restantes
        if(actifs[i].num==5 || actifs[i].num==6){
            obstacle obs;
            if(actifs[i].num==5) obs = actifs[4];
            if(actifs[i].num==6) obs = actifs[5];
            
            if((balle->x-balle->taille/2>pos[i]-balle->taille/2)&&(balle->x-balle->taille/2<=pos[i] && balle->x-balle->taille/2-balle->vx<=pos[i]) && (balle->y+balle->taille/2>obs.y && balle->y-balle->taille/2<obs.y+actifs[i].largeur) && (balle->z+balle->taille/2>obs.z && balle->z-balle->taille/2<obs.z+obs.hauteur)){ 
                balle->vx = -balle->vx;
                balle->x = pos[i]+balle->taille/2;
            }
            if((balle->x+balle->taille/2<pos[i]+balle->taille/2)&&(balle->x+balle->taille/2>=pos[i] && balle->x+balle->taille/2-balle->vx<=pos[i]) && (balle->y+balle->taille/2>obs.y && balle->y-balle->taille/2<obs.y+obs.largeur) && (balle->z+balle->taille/2>obs.z && balle->z-balle->taille/2<obs.z+obs.hauteur)){ 
                balle->vx = -balle->vx;
                balle->x = pos[i]-balle->taille/2;
            }
        }
    }
}

void collisionRaquette(ball* balle, raquette* raq,bonus liste_bonus[2], etat* jeu){
    // si la balle sors duu couloir (avec 0.5 de marge)
    if(balle->x >=25.5-balle->taille/2){
        if((balle->y >raq->y-raq->taille/2-balle->taille/2) && (balle->y <raq->y+raq->taille/2+balle->taille/2) && (balle->z >raq->z-raq->taille/2-balle->taille/2) && (balle->z <raq->z+raq->taille/2+balle->taille/2)){
            balle->vx = -balle->vx;
            balle->x = 25-balle->taille/2;
            // Les vitesses en x et y dépendent de l'écart entre le centre de la raquette et de la balle
            // La vitesse est proportionnelle à l'écart, avec pour valeur max 0.12
            balle->vy = 0.12*abs(raq->y-balle->y)/(raq->taille/2+balle->taille/2);
            if(balle->y<raq->y) balle->vy = -balle->vy;
            balle->vz = 0.12*abs(raq->z-balle->z)/(raq->taille/2+balle->taille/2);
            if(balle->z<raq->z) balle->vz = -balle->vz;

            // on vérifie si le bonus de colle est actif, auquel cas on change l'état de la balle
            if(liste_bonus[0].actif) {
                balle->collee=true;
                liste_bonus[0].actif = false;
                liste_bonus[1].x = 5;
            }
        }
        else{ // on perd une vie
            jeu->vie-=1;
            if(jeu->vie==0) jeu->a = 2; // si on a plus de vie : écran de game over
            balle->collee = true; // la balle sors et se recolle à la raquette
        }
    }
}




void moveBall(GLFWwindow *window, int width, int height,ball* balle,raquette* raq, etat* jeu,bonus liste_bonus[2],obstacle actifs[6],float pos[4]){
    // Gestion de la position de la souris, semblable à celle dans moveRaquette
    double mouseY, mouseZ;
    glfwGetCursorPos(window,&mouseY,&mouseZ);
    //les dimensions du plan dans lequel se trouve la souris
    float h_plan, w_plan; 
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

    
    // avant que la balle aie été lancée
    if(balle->collee){
        glPushMatrix();
        glTranslatef(25-balle->taille/2,y,z);
        drawBall();
        glPopMatrix();
        balle->y=y;
        balle->z=z;
    }
    else{ // si l aballe est en mouvement
    // update de sa position
        balle->x += balle->vx;
        balle->y += balle->vy;
        balle->z += balle->vz;
    // check des collisions
        collisionMurs(balle);
        collisionObstacles(balle,actifs,pos);
        collisionRaquette(balle,raq,liste_bonus,jeu);
        collisionBonus(balle,liste_bonus);

    // effet du bonus de vie
        if(liste_bonus[1].actif){
			liste_bonus[1].actif=false;
			liste_bonus[1].visible=false;
			liste_bonus[0].visible = true;
			liste_bonus[0].x=5;
			if(jeu->vie<7)
			jeu->vie += 1;}

        glPushMatrix();
        glTranslatef(balle->x,balle->y,balle->z);
        drawBall();
        glPopMatrix();
    }
}
