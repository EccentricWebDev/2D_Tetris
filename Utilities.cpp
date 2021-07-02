#include "Utilities.h"

void Utilities::reset(bool full) {

	if (full) {
		g_score = g_lines = 0;
	}
	g_x = 3.0f;
	g_y = 0.0f;

}

int Utilities::bestScore() const {

	std::ifstream in_file { "Result.txt" };
	int best_score;

	if (in_file.peek() == std::ifstream::traits_type::eof()) {

		return 0;

	} else if (in_file) {

		in_file >> best_score;
		return best_score;

	}
	return 0;

}

void Utilities::setBestScore() {

	if (bestScore() < g_score) {

		std::ofstream out_file { "Result.txt" };
		out_file << g_score;

	}

}

void Utilities::renderStatText(void* font, float x, float y) {
	
	double x_pos = 0.1;
	double y_pos = 0.9;

	int best_score = bestScore();

	UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, 
							UtilContainer::stat_strings[0], x_pos + 0.3, y_pos);
	
	UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, 
							UtilContainer::stat_strings[1] + std::to_string(g_score), x_pos, y_pos - 0.05);

	if (best_score != 0) {

		UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, 
								UtilContainer::stat_strings[2] + std::to_string(best_score), x_pos, y_pos - 0.05 * 2);

	} else {

		UtilContainer::renderText(GLUT_BITMAP_TIMES_ROMAN_24, 
								UtilContainer::stat_strings[3], x_pos, y_pos - 0.05 * 2);
		
	}

}