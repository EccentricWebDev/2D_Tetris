#ifndef ARENA
#define ARENA

#include <vector>
#include <string>
#include <gl/glut.h>
#include "Utilities.h"

enum class FieldState { FREE, FILLED, FALLING };

struct FieldCell {

	FieldState str_state;
	TetroShape str_shape;

};

class Arena {

private:
	const int m_length = 9;
	const int m_height = 14;
	const float m_offset_x = -0.7f;
	const float m_offset_y = -1.0f;
	float m_offset_z = -2.0f;
	float m_rotation_x = 0;
	float m_rotation_y = 0;

	std::vector<FieldCell> m_field;

public:
	Arena();
	void reset();
	
	void drawGame();
	void drawMenu();
	void drawGameover(Utilities& util);
	
	void setField(int index, const FieldState& cell_state, const TetroShape& cell_shape);
	void setZOffset(float new_offset_z) { m_offset_z = new_offset_z; }
	void setRotation(float x, float y, Utilities& util) {
		m_rotation_x += (x - util.xMousePos());
		m_rotation_y += (y - util.yMousePos());
	}

	FieldCell getFieldCell(int index) const { return m_field[index]; }
	int length() const { return m_length; }
	int height() const { return m_height; }
	float zOffset() const { return m_offset_z; }

	bool checkLevel(int level) const;
	int clearLevels();

};

#endif