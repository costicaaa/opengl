#include<windows.h>
#include <gl/freeglut.h>
#include <iostream>

using namespace std;

bool dev = false; // false true

#define NR_OBSTACLES 8

int nr_obstacles = NR_OBSTACLES;
struct obstacles {
	// type 1 => sus 
	// type 0 => jos 
	double x_left, x_right, height, type;
} obstacles[NR_OBSTACLES];



double x_tr_move_speed = 3.5;
double x_tr = -500.0;
double y_tr = -150;
double rotate_angle = 360;

double alpha = 1;
double SQUARE_SIZE = 50;
double precision_pixel = 48; // reglaj fin , tried 25, 35, 42, 50 , 49,8  
int jj; //iterator


double infinit = 2222;


void youLost()
{
	if (dev)
	{
		glColor3f(1, 0, 1);
	}
	else
	{
		glutDestroyWindow(1);
		cout << "You lost";
		//cin >> x_tr;
	}
	
	
}

void youWon()
{
		glutDestroyWindow(1);
		cout << "CONGRATZ, YOU WON !!!";
		cin >> x_tr;
}

void init(void)
{
	glClearColor(0.65, 0.8, 255, 0.0);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);

}
void deseneazaScena(void)
{
	obstacles[1].type = 1;
	obstacles[1].x_left = -400;
	obstacles[1].x_right = -350;
	obstacles[1].height = -150;


	obstacles[2].type = 1;
	obstacles[2].x_left = -200;
	obstacles[2].x_right = -150;
	obstacles[2].height = 50;

	obstacles[3].type = 0;
	obstacles[3].x_left = -200;
	obstacles[3].x_right = -150;
	obstacles[3].height = -150;

	obstacles[4].type = 1;
	obstacles[4].x_left = -50;
	obstacles[4].x_right = 50;
	obstacles[4].height = -50;

	obstacles[5].type = 0;
	obstacles[5].x_left = -50;
	obstacles[5].x_right = 0;
	obstacles[5].height = -300;

	obstacles[6].type = 0;
	obstacles[6].x_left = 150;
	obstacles[6].x_right = 175;
	obstacles[6].height = -100;
	
	obstacles[7].type = 1;
	obstacles[7].x_left = 290;
	obstacles[7].x_right = 320;
	obstacles[7].height = -120;

	obstacles[8].type = 0;
	obstacles[8].x_left = 430;
	obstacles[8].x_right = 600;
	obstacles[8].height = -95;



	x_tr += 2;
	//cout << "x_tr_value : " << x_tr << " ; y_tr_value : " << y_tr << " ; " << " rotate_angle : " << rotate_angle << " ; \n";
	
	glColor3f(0, 0, 0);
	for (jj = 1; jj <= nr_obstacles; jj++)
	{
		if (x_tr + precision_pixel >= obstacles[jj].x_left && x_tr <= obstacles[jj].x_right)
		{
			if (obstacles[jj].type)
			{
				if (y_tr + precision_pixel >= obstacles[jj].height)
				{
					youLost();
				}
			}
			else
			{
				if (y_tr <= obstacles[jj].height)
				{
					youLost();
				}
			}
			
		}
	}


	if (x_tr >= 560)
	{
		youWon();
	}
	

	glClear(GL_COLOR_BUFFER_BIT);
	// axa de rostogolire in afara transformarii
	

	//linii shto
	glBegin(GL_LINES);
		/*glVertex2i(-500, 0);
		glVertex2i(500, 0);*/
	glEnd();

	//s1 
	glBegin(GL_LINES);
	for (jj = 1; jj <= nr_obstacles; jj++)
	{
		
		// left     x_left					Infinit
		glVertex2i(obstacles[jj].x_left, obstacles[jj].type ? infinit : -infinit);
		//			x_left					height
		glVertex2i(obstacles[jj].x_left, obstacles[jj].height);
		//glVertex2i(-400, -150);

		// right
		//         x _right					infinit 
		glVertex2i(obstacles[jj].x_right, obstacles[jj].type ? infinit : -infinit);
		////		   x_right					height
		glVertex2i(obstacles[jj].x_right, obstacles[jj].height);


		// middle shto
		//		   x_left					height
		glVertex2i(obstacles[jj].x_left, obstacles[jj].height);
		////			x_right					height 
		glVertex2i(obstacles[jj].x_right, obstacles[jj].height);
	}
	glEnd();

	// patratul
	glColor3f(1, 0.5, 0.5);
		glPushMatrix();
			glTranslated(x_tr, y_tr, 0.0);
		glPushMatrix();
			glRotated(rotate_angle, 0.0, 0.0, 1.0);
			glRecti(0, 0, 50, 50);
			
	glPopMatrix();
	glPopMatrix();


	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscad(void)
{
	y_tr += alpha;

	rotate_angle = 5;
	glutPostRedisplay();
}

void miscas(void)
{
	y_tr += alpha;
	rotate_angle = -5;

	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			alpha = -x_tr_move_speed;
		}
		glutIdleFunc(miscas);
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			alpha = x_tr_move_speed;
		}
		glutIdleFunc(miscad);
		break;
	default:
		break;
	}
}



void main(int argc, char** argv)
{
	



	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(900, 100);
	glutCreateWindow("Patrat care se rostogoleste");
	init();
	glutDisplayFunc(deseneazaScena);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
}
