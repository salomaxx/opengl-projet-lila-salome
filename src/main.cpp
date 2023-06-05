#define GLFW_INCLUDE_NONE
#include "C:\Users\33651\Downloads\TD04-workflow\third_party\glfw\include\GLFW\glfw3.h"

#include "3D_tools.h"
#include "draw_scene.h"




/* Window properties */
static unsigned int WINDOW_WIDTH = 1200;
static unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The light kittydor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static const float _viewSize = 10.;


//Initialisation des variables
ball* balle = new ball;
etat* jeu = new etat;
bonus liste_bonus[2] = {}; //Liste des deux bonus existants
temps* temps_obs = new temps; //Variables de temps pour les obstacles mouvants (horizontalement et verticalement)




/* Error handling function */
void onError(int error, const char *description)
{
	std::cout << "GLFW Error: " << description << std::endl;
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, aspectRatio, Z_NEAR, Z_FAR);
	WINDOW_WIDTH=width;
	WINDOW_HEIGHT=height;


	/*if( aspectRatio > 1)
	{
		glOrtho(
		-_viewSize / 2. * aspectRatio, _viewSize / 2. * aspectRatio,
		-_viewSize / 2., _viewSize / 2.,-1.0f, 1.0f);
	}
	else
	{
		glOrtho(
		-_viewSize / 2., _viewSize / 2.,
		-_viewSize / 2. / aspectRatio, _viewSize / 2. / aspectRatio,-1.0f, 1.0f);
	}*/


	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GLFW_KEY_KP_9:
			if (dist_zoom < 100.0f)
				dist_zoom *= 1.1;
			std::cout << "Zoom is " << dist_zoom << std::endl;
			break;
		case GLFW_KEY_KP_3:
			if (dist_zoom > 1.0f)
				dist_zoom *= 0.9;
			std::cout << "Zoom is " << dist_zoom << std::endl;
			break;
		case GLFW_KEY_UP:
			if (phy > 2)
				phy -= 2;
			std::cout << "Phy is " << phy << std::endl;
			break;
		case GLFW_KEY_DOWN:
			if (phy <= 88.)
				phy += 2;
			std::cout << "Phy is " << phy << std::endl;
			break;
		case GLFW_KEY_LEFT:
			theta -= 5;
			std::cout<<"theta is"<<theta<<std::endl;
			break;
		case GLFW_KEY_RIGHT:
			theta += 5;
			break;
		// Touches des menus
		case GLFW_KEY_E: // on lance une partie
			if(jeu->a!=1){
				jeu->vie=5;
				jeu->a=1;
				jeu->obs=0;
			}
			break;
		case GLFW_KEY_R: // on quitte le jeu
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		default:
			std::cout << "Touche non gérée (" << key << ")" << std::endl;
		}
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		balle->collee = false;
	}
}

int main()
{

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}
	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	// Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
	// We need to explicitly ask for a 3.3 context on Mac
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	// Make the window's context current
	glfwMakeContextCurrent(window);
	// Callbacks
	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Activate depth so that elements can render in front of others
	glEnable(GL_DEPTH_TEST);

	// Angles de rotation de la caméra : on se place dans le plan (y,z)
	phy = 90;
	theta = 0;

	// Initialisation des variables 
	obstacle liste [10] = {}; //liste de tous les obstacles existants
	obstacle actifs[6]; //liste des obstacles actifs (pris au hasard dans liste, 4 sont draw à la fois)
	float pos[4]={-25/3,0,25/3,2*25/3}; //positions de base des lignes sur les murs et des obstacles
	float pos_lignes[4]={-25/3,0,25/3,2*25/3};
	initBonus(liste_bonus);
	initObstacle(liste,actifs,pos,temps_obs);
	initBalle(balle);
	int angle_rotation_bonus = 0;
	raquette* raq = new raquette;

	// Variables pour afficher les textures
	unsigned texture_debut;
	unsigned texture_fin;
	unsigned texture_couloir;
	unsigned texture_win;
	int xd,yd,nd;
	int xf,yf,nf;
	int xc,yc,nc;
	int xw,yw,nw;
	unsigned char* d;
	unsigned char* f;
	unsigned char* c;
	unsigned char* w;
	// Chargement des textures:
	load_image_pre_boucle1(&texture_debut,d,xd,yd,nd);
	load_image_pre_boucle2(&texture_fin,f,xf,yf,nf);
	load_image_pre_boucle3(&texture_couloir,c,xc,yc,nc);
	load_image_pre_boucle4(&texture_win,w,xw,yw,nw);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.5,0.5,0.5,1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Choix de l'affichage selon l'état du jeu */
		/* 0 : menu de depart, 1 : phase de jeu, 2 : menu de gameover, 3 : menu de win */
		if(jeu->a==0)load_image_boucle1(&texture_debut);
		if(jeu->a==1){
			drawCorridor();
			vies(jeu);
			load_image_boucle3(&texture_couloir);

			moveLines(pos_lignes,balle);
			moveBonus(liste_bonus,angle_rotation_bonus,balle);
			moveObstacles(liste, actifs,pos,balle,temps_obs,jeu);
			
			moveBall(window, WINDOW_WIDTH, WINDOW_HEIGHT,balle,raq,jeu,liste_bonus,actifs,pos);
			raq->taille = 3;
			moveRaquette(window, WINDOW_WIDTH, WINDOW_HEIGHT,raq->taille, raq);
			angle_rotation_bonus += 2;
			}
		if(jeu->a==2)load_image_boucle1(&texture_fin);
		if(jeu->a==3)load_image_boucle1(&texture_win);

		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}
	}
	// on décharge les textures
	load_image_post_boucle(&texture_debut,d);
	load_image_post_boucle(&texture_fin,f);
	load_image_post_boucle(&texture_couloir,c);
	load_image_post_boucle(&texture_win,w);

	glfwTerminate();
	return 0;
}