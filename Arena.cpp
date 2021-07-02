#include "Arena.h"

Arena::Arena() {
	
	m_field.resize(m_height * m_length);
	reset();

}

void Arena::drawMenu() {

	std::array<GLfloat, 3> arena_color = UtilContainer::arena_color;
	std::array<GLfloat, 3> text_color = UtilContainer::text_color;

	glClearColor(arena_color[0], arena_color[1], arena_color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(text_color[0], text_color[1], text_color[2]);
	
	for (int i = 0; i < UtilContainer::menu_strings.size(); ++i) {

		if (i == 0) {
			UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, UtilContainer::menu_strings[i], 0.4, 0.9);
			continue;
		}

		UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, UtilContainer::menu_strings[i], 0.1, 0.9 - (i * 0.05));

	}
	
	glPopMatrix();

}

void Arena::drawGameover(Utilities& util) {

	std::array<GLfloat, 3> arena_color = UtilContainer::arena_color;
	std::array<GLfloat, 3> text_color = UtilContainer::text_color;

	glClearColor(arena_color[0], arena_color[1], arena_color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(text_color[0], text_color[1], text_color[2]);

	util.renderStatText(GLUT_BITMAP_TIMES_ROMAN_24, 0.1, 0.9);

	glPopMatrix();

}

void Arena::drawGame() {

	GLfloat blockSize = UtilContainer::block_size;
	std::array<GLfloat, 3> arena_color = UtilContainer::arena_color;

	glClearColor(arena_color[0], arena_color[1], arena_color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 800 / 800, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Drawing the Arena

	glTranslatef(m_offset_x, m_offset_y, m_offset_z);
	glRotatef(m_rotation_x, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotation_y, 1.0f, 0.0f, 0.0f);

	int count = 0;

	for (int i = 0; i < m_height; ++i) {
		
		for (int j = 0; j < m_length; ++j) {
			
			if (count % 2)
				glColor3f(arena_color[0] - 0.05, arena_color[1] - 0.05, arena_color[2] - 0.05);
			else
				glColor3f(arena_color[0] - 0.08, arena_color[1] - 0.08, arena_color[2] - 0.08);

			++count;

			glBegin(GL_QUADS);
				glVertex3f(blockSize * j + blockSize, blockSize * i + blockSize, m_offset_z * blockSize);
				glVertex3f(blockSize * j + blockSize, blockSize * i, m_offset_z * blockSize);
				glVertex3f(blockSize * j, blockSize * i, m_offset_z * blockSize);
				glVertex3f(blockSize * j, blockSize * i + blockSize, m_offset_z * blockSize);
			glEnd();
		}
	
	}

	// Drawing the Blocks
	
	for (int i = 0; i < m_height; ++i) {

		for (int j = 0; j < m_length; ++j) {

			int index = j + i * m_length;
			if ((m_field[index].str_state == FieldState::FILLED) || 
				(m_field[index].str_state == FieldState::FALLING)) {

				std::array<GLfloat, 3> color_args = UtilContainer::tetro_colors[(int)m_field[index].str_shape];
				glColor3f(color_args[0], color_args[1], color_args[2]);
				glPushMatrix();
					glTranslatef(j * blockSize + 0.5 * blockSize, 
								-i * blockSize - 0.5 * blockSize + blockSize * m_height, 
								m_offset_z * blockSize);
					glutWireCube(blockSize);
				glPopMatrix();

			}

		}

	}
	glPopMatrix();

}

void Arena::setField(int index, const FieldState& cell_state, const TetroShape& cell_shape) {

	if ((index >= 0) && (index < (m_length * m_height))) {

		m_field[index] = { cell_state, cell_shape };

	}

}

bool Arena::checkLevel(int level) const {

	for (int i = 0; i < m_length; ++i) {

		int index = i + level * m_length;
		if (m_field[index].str_state != FieldState::FILLED) {
			return false;
		}

	}
	return true;

}

int Arena::clearLevels() {

	int levels_cleared = 0;
	for (int i = 0; i < m_height; ++i) {

		if (checkLevel(i)) {

			++levels_cleared;
			for (int j = 0; j < m_length; ++j) {

				for (int k = i; k > 0; --k) {

					int index = j + k * m_length;
					int before_index = j + (k - 1) * m_length;
					m_field[index] = m_field[before_index];

				}
				m_field[j].str_state = FieldState::FREE;
				m_field[j].str_shape = TetroShape::NONE;

			}

		}

	}
	return levels_cleared;

}

void Arena::reset() {

	for (auto& block : m_field) {

		block = { FieldState::FREE, TetroShape::NONE };

	}

	m_offset_z = -2.0f;
	m_rotation_x = 0;
	m_rotation_y = 0;

}