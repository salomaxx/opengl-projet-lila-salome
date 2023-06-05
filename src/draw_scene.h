#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <string.h>


struct ball{
    // position
	float x,y,z;
    // si la balle est collée à la raquette
    bool collee = true;
    // vitesse
    float vx,vy,vz;
    float taille;
};

struct obstacle{
    // coordonnées du point inférieur gauche du rectangle
    float x,y,z;
    // largeur et hauteur du rectangle
    float largeur, hauteur;
    float num;
};

struct raquette{
    float y,z;
    float taille;
};

struct etat{
    // l'état du jeu
    // 0 : menu de départ ; 1 : jeu ; 2 : Game Over ; 3 : Win ;
    int a = 0;
    // nombre de vie
    int vie = 5;
    // nombre d'obstacles passés
    int obs = 0;
};

struct bonus{
    // coordonnées du centre du bonus
    float x,y,z;
    // largeur et hauteur
    float largeur, hauteur;
    // Type du bonus = {1,2} ; 1 : bonus de la colle
    int type;
    // vitesse
    float vx;
    // visible ou non dans le couloir
    bool visible;
    // actif ou non
    bool actif = false;
};

struct coords{
    float x,y,z;
};

struct temps{
    float u,t = 0;
};



// Dans setup.cpp : les fonctions dessinant le couloir, la balle et la raquette
void drawAxes();
void drawRectSol(int x, int y, int height, int width);
void drawRectFond(int y, int z, int height, int width);
void drawRectSides(int x, int z, int height, float width);
void drawCorridor();
void drawRaquette(float y, float z, int size);
void drawLines();
void moveLines(float pos[4],ball* balle);
void drawBall();
void initBalle(ball* balle);
void moveRaquette(GLFWwindow *window,int width, int height,int size,raquette* raq);

// Dans collisions.cpp : la fonction qui fait bouger la balle, et les fonctions de collisions contre les différents obbjets qui lui sont associées
void collisionMurs(ball* balle);
void collisionObstacles(ball* balle,obstacle actifs[6], float pos[4]);
void collisionRaquette(ball* balle, raquette* raq,bonus liste_bonus[2],etat* jeu);
void moveBall(GLFWwindow *window, int width, int height,ball* balle,raquette* raq, etat* jeu,bonus liste_bonus[2],obstacle actifs[6],float pos[4]);

// Dans obstacles.cpp : le dessin des obstacles, leur initialisation et mouvement
void drawObstacle1();
void drawObstacle2();
void drawObstacle3();
void drawObstacle4();
void drawObstacle5();
void drawObstacle6();
void drawObstacle7(temps* temps_obs);
void updateObstacle7Pos(temps* temps_obs);
void drawObstacle8(temps* temps_obs);
void updateObstacle8Pos(temps* temps_obs);
void moveObstacles(obstacle liste [10],obstacle actifs[6],float pos[4],ball* balle,temps* temps_obs,etat* jeu);
void initObstacle(obstacle liste [10],obstacle actifs[6],float pos[4],temps* temps_obs);


// Dans bonus.cpp : le dessin des bonus, leur initialisation, mouvement, et collision avec la raquette
void drawBonus1(int angle);
void drawBonus2(int angle);
void collisionBonus(ball* balle, bonus liste[2]);
void initBonus(bonus liste[2]);
void moveBonus(bonus liste[2],int angle,ball* balle);


// Dans menus.cpp : dessin des vies et chargement/render/déchargement des textures
void drawHeart();
void drawVie();
void vies(etat* jeu);
void load_image_pre_boucle1(unsigned* texture, unsigned char* a,int x, int y,int n);
void load_image_pre_boucle2(unsigned* texture, unsigned char* a,int x, int y,int n);
void load_image_pre_boucle3(unsigned* texture, unsigned char* a,int x, int y,int n);
void load_image_pre_boucle4(unsigned* texture, unsigned char* a,int x, int y,int n);
void load_image_boucle1(unsigned* texture);
void load_image_boucle3(unsigned* texture);
void load_image_post_boucle(unsigned* texture,unsigned char* a);

