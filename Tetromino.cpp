#include "Tetromino.h"

Tetromino::Tetromino(const TetroShape& shape) {

	m_x = 0.0;
	m_y = 0.0;

	m_shape = shape;
	m_offset = UtilContainer::tetro_offset[(int)shape];
	m_current_offset = m_offset[0];

}

Tetromino::~Tetromino() {

	m_shape = TetroShape::NONE;

}

void Tetromino::setState(Arena* arena, const FieldState& state) {

	setState(arena, state, m_shape);

}

void Tetromino::setState(Arena* arena, const FieldState& state, const TetroShape& shape) {

	for (int y = 0; y < m_cube_count; ++y) {

		for (int x = 0; x < m_cube_count; ++x) {

			int index = x + y * m_cube_count;
			if ((m_current_offset[index] != 0)) {

				arena->setField(((m_x + x) + (m_y + y) * arena->length()), state, shape);

			}

		}

	}

}

bool Tetromino::isCollided(Arena* arena, int xPos, int yPos) {

	int left_most = 900;
	int right_most = -900;
	int bottom_most = -900;

	for (int y = 0; y < m_cube_count; ++y) {

		for (int x = 0; x < m_cube_count; ++x) {

			int cube_index = x + y * m_cube_count;
			int tetro_index = (xPos + x) + (yPos + y) * arena->length();

			if ((yPos + y >= 0) && (yPos + y < arena->height())) {

				if ((xPos + x >= 0) && (xPos + x < arena->length())) {

					if ((m_current_offset[cube_index] == 1) &&
						(arena->getFieldCell(tetro_index).str_state == FieldState::FILLED)) {

						return true;

					}

				}

			}

			if (m_current_offset[cube_index] == 1) {

				if (x < left_most) {
					left_most = x;
				}

				if (x > right_most) {
					right_most = x;
				}

				if (y > bottom_most) {
					bottom_most = y;
				}

			}

		}

	}

	if (xPos + left_most < 0) {
		return true;
	}
	
	if (xPos + right_most > arena->length() - 1) {
		return true;
	}

	if (yPos + bottom_most > arena->height() - 1) {
		return true;
	}

	return false;

}

void Tetromino::rotate() {

	if (m_shape == TetroShape::O)
		return;
	
	if (m_rotation < 3) {

		++m_rotation;

	} else {
	
		m_rotation = 0;

	}

	m_current_offset = m_offset[m_rotation];

}