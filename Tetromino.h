#ifndef TETROMINO
#define TETROMINO

#include <vector>
#include <gl/glut.h>
#include "Arena.h"

class Tetromino {

protected:
	TetroShape m_shape;

	// location of tetromino
	int m_x, m_y;
	const int m_cube_count = 4;
	int m_rotation = 0;
	
	// location of each cube
	std::vector<std::vector<int>> m_offset; 
	std::vector<int> m_current_offset;

public:
	Tetromino(const TetroShape& shape);
	~Tetromino();

	void setState(Arena* arena, const FieldState& state);
	void setState(Arena* arena, const FieldState& state, const TetroShape& shape);
	void setXY(int x, int y) {
		m_x = x;
		m_y = y;
	}
	
	bool isCollided(Arena* arena, int xPos, int yPos);
	void rotate();

};

#endif
