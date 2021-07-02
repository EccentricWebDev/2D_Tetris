#include <gl/glut.h>
#include <random>

#include "Tetromino.h"
#include "Arena.h"

Utilities g_util = {};
GameState g_state = GameState::MENU_STATE;
Tetromino* g_tetro = nullptr;
Arena* g_arena = nullptr;

void setNewTetro() {

	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, (int)(TetroShape::NUM_OF_SHAPES) - 2);
	dist(gen);

	TetroShape shape = (TetroShape)(dist(gen));
	g_tetro = new Tetromino(shape);
	
}

void handleNewTetro() {

	if (g_util.y_pos() <= 2) {
		g_state = GameState::OVER_STATE;
		g_util.setBestScore();
		return;
	}

	g_tetro->setState(g_arena, FieldState::FREE, TetroShape::NONE);
	g_tetro->setXY(g_util.x_pos(), g_util.y_pos() - 1);
	g_tetro->setState(g_arena, FieldState::FILLED);

	delete g_tetro;
	setNewTetro();
	g_util.reset();
	g_tetro->setXY(g_util.x_pos(), g_util.y_pos());

}

void drawTetro() {

	if ((g_util.y_pos() > 2) || !g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

		g_tetro->setState(g_arena, FieldState::FREE, TetroShape::NONE);
		g_tetro->setXY(g_util.x_pos(), g_util.y_pos());
		g_tetro->setState(g_arena, FieldState::FALLING);
		g_arena->drawGame();

	}

}

void display() {

	switch (g_state) {

		case GameState::MENU_STATE:
			g_arena->drawMenu();
			break;

		case GameState::PLAY_STATE: {

			int levels_cleared = g_arena->clearLevels();
			g_util.setScore(levels_cleared * 10);
			g_util.setLines(levels_cleared);

			drawTetro();
			break;

		}

		case GameState::OVER_STATE:
			g_arena->drawGameover(g_util);
			break;

	}
	glutSwapBuffers();

}

void timerHandle(int value) {

	switch (g_state) {

		case GameState::MENU_STATE:
		case GameState::OVER_STATE:
			break;

		case GameState::PLAY_STATE: {

			g_util.setY(g_util.y_pos() + 1);

			if (g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

				handleNewTetro();

			}
			
			glutPostRedisplay();
			break;

		}

	}
	glutTimerFunc(UtilContainer::game_speed, timerHandle, value);

}

void pressKey(unsigned char key, int x, int y) {

	switch (key) {

		case 'p': {

			if (g_state != GameState::PLAY_STATE) {

				g_state = GameState::PLAY_STATE;
				g_util.reset(true);
				g_arena->reset();

			}

			break;

		}

		case 'm': {

			if (g_state != GameState::MENU_STATE) {

				g_state = GameState::MENU_STATE;
				g_util.reset(true);
				g_arena->reset();
			
			}

			break;

		}

		case '2': {
		
			if (g_arena->zOffset() > -1.7f)
				break;
			g_arena->setZOffset(g_arena->zOffset() + 0.1);
			break;
		
		}

		case '1': {

			g_arena->setZOffset(g_arena->zOffset() - 0.1);
			break;

		}

		case 27:
			exit(0);

	}
	glutPostRedisplay();

}

void pressSpecialKey(int key, int x, int y) {

	switch (key) {

		case GLUT_KEY_DOWN: {
		
			g_util.setY(g_util.y_pos() + 1);
			if(g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

				handleNewTetro();

			} 
			break;
		
		}

		case GLUT_KEY_LEFT: {

			g_util.setX(g_util.x_pos() - 1);
			if (g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

				g_util.setX(g_util.x_pos() + 1);

			}
			break;

		}

		case GLUT_KEY_RIGHT: {

			g_util.setX(g_util.x_pos() + 1);
			if (g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

				g_util.setX(g_util.x_pos() - 1);

			}
			break;

		}

		case GLUT_KEY_UP: {

			g_tetro->setState(g_arena, FieldState::FREE, TetroShape::NONE);
			g_tetro->rotate();
			if (g_tetro->isCollided(g_arena, g_util.x_pos(), g_util.y_pos())) {

				g_tetro->rotate();
				g_tetro->rotate();
				g_tetro->rotate();

			}
			break;

		}

	}
	glutPostRedisplay();

}

void onMouse(int button, int state, int x, int y) {

	g_util.setMouseUtil(x, y, button);
	glutPostRedisplay();

}

void onMouseMotion(int x, int y) {

	switch (g_util.button()) {

		case GLUT_LEFT_BUTTON: {

			g_arena->setRotation(x, y, g_util);
			g_util.setMouseUtil(x, y);

		}

	}
	glutPostRedisplay();

}

void reshape(int width, int height) {
	
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60, width / height, 1.0, 100.0); 
	glMatrixMode(GL_MODELVIEW); 

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("2D Tetris Game");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(pressKey);
	glutSpecialFunc(pressSpecialKey);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	
	glutTimerFunc(UtilContainer::game_speed, timerHandle, 0);

	g_arena = new Arena();

	setNewTetro();

	glutMainLoop();

	return 0;

}