#ifndef UTILCONTAINER
#define UTILCONTAINER

#include <string>
#include <vector>
#include <array>
#include <gl/glut.h>

namespace UtilContainer {

	const std::array<std::string, 8> menu_strings = {

		"Game Menu",
		"Press 'p' to start the game.",
		"Press 'm' to go back to the menu.",
		"Controls of the gameplay:",
		"1. Press PageDown to bring the block down.",
		"2. Press End to bring the block to the right.",
		"3. Press Home to bring the block to the left.",
		"4. Press PageUp to rotate the block."

	};
	const std::array<std::string, 4> stat_strings = {

		"Game Statistics",
		"Your score is: ",
		"Your best score: ",
		"You don't have any best score yet."

	};

	const std::vector<std::vector<std::vector<int>>> tetro_offset = {

		{

			{
				1, 1, 1, 0,
				1, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 0, 1, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 0, 0,
				0, 0, 0, 0,
			}


		},

		{

			{
				1, 1, 1, 0,
				0, 0, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				1, 1, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 0, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 1, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 0,
			}


		},

		{

			{
				0, 1, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 0, 0, 0,
				1, 1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 1, 1, 0,
				0, 1, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0,
			},


		},

		{

			{
				1, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				1, 1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				1, 1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 0,
			}

		},

		{

			{
				0, 1, 1, 0,
				1, 1, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 1, 0,
				1, 1, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				1, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0,
			}


		},

		{

			{
				1, 1, 0, 0,
				1, 1, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			}

		},

		{

			{
				1, 1, 1, 1,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
			},
			{
				1, 1, 1, 1,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			},
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
			},

		}

	};

	const std::vector<std::array<GLfloat, 3>> tetro_colors = {

		{ 1.0f, 0.0f, 0.0f },

		{ 0.0f, 1.0f, 0.0f },

		{ 1.0f, 0.5f, 0.0f },

		{ 1.0f, 1.0f, 0.0f },

		{ 1.0f, 0.0f, 1.0f },

		{ 0.0f, 0.5f, 1.0f },

		{ 1.0f, 0.0f, 0.5f },

	};
	const std::array<GLfloat, 3> arena_color = { 0.35f, 0.35f, 0.35f };
	const std::array<GLfloat, 3> text_color = { 0.0f, 1.0f, 1.0f };

	const GLfloat block_size = 0.15f;
	const int game_speed = 1000; // in ms
	const int score_coeff = 10;

	void renderText(void* font, const std::string& text, float x, float y);

}

#endif