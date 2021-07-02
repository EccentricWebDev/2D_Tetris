#ifndef UTIL
#define UTIL

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <gl/glut.h>
#include "UtilContainer.h"

enum class GameState { MENU_STATE, PLAY_STATE, OVER_STATE };

enum class TetroShape { L, J, T, S, Z, O, I, NONE, NUM_OF_SHAPES };

class Utilities {

private:
	// Gameplay
	inline static int g_best_score = 0;
	int g_score = 0;
	int g_lines = 0;

	// Sizes & coordinates
	GLfloat g_x = 4.0f;
	GLfloat g_y = 0.0f;

	// Mouse position & button
	GLfloat m_mouse_x = 0.0f;
	GLfloat m_mouse_y = 0.0f;
	int m_button = 0;

public:
	Utilities() = default; 
	void reset(bool full = false);

	int bestScore() const;
	void setBestScore();
	GLfloat x_pos() const { return g_x; }
	GLfloat y_pos() const { return g_y; }
	void setX(GLfloat x) { g_x = x; }
	void setY(GLfloat y) { g_y = y; }
	void setScore(int score) { g_score += score; }
	void setLines(int lines) { g_lines += lines; }

	void renderStatText(void* font, float x, float y);

	void setMouseUtil(GLfloat x, GLfloat y, int button = 0) {
		m_mouse_x = x;
		m_mouse_y = y;
		m_button = button;
	}
	GLfloat xMousePos() const { return m_mouse_x; }
	GLfloat yMousePos() const { return m_mouse_y; }
	int button() const { return m_button; }

};

#endif