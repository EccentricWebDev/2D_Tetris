#include "UtilContainer.h"

void UtilContainer::renderText(void* font, const std::string& text, float x, float y) {

	if (text.empty())
		return;

	glRasterPos2f(x, y);

	for (const auto& ch : text) {

		glutBitmapCharacter(font, ch);

	}

}