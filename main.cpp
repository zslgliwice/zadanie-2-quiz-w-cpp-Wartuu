/**
 * @file: main.cpp
 * @author: Michal Marzec
 * Used compiler: msvc (visual studio 2022)
 * Repository: github.com/Wartuu
 */

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>

// basic defines for colors for easier terminal usage

#define color_black      0
#define color_dark_blue  1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red   4
#define color_magenta    5
#define color_orange     6
#define color_light_gray 7
#define color_gray       8
#define color_blue       9
#define color_green     10
#define color_cyan      11
#define color_red       12
#define color_pink      13
#define color_yellow    14
#define color_white     15


// basic struct for questions
struct Question {
	std::string question;
	std::string answers[4];
	int correctAnswer;
};

// global variables
HANDLE console;
std::string username;
int score = 0;


// all questions are stored in similar way to JSON, i used here
// just a basic struct array
Question questions[] = {
	{
		"what is c++",
		{"language", "coffe", "book", "editor"},
		0
	},
	{
		"what is pointer",
		{"address to fish", "address to my home", "address to memory", "point"},
		2
	},
	{
		"what is g++",
		{"a dish", "Global++", "language helper", "compiler"},
		3
	},
	{
		"can void represent any data?",
		{"no, it's void", "no, it means nothing", "yes, it can be pointer to unkown type address", "no once again"},
		2
	}
};

// was called too often, changed this into function
void sleepAndClear(int milis) {
	Sleep(milis);
	system("cls");
}


// was writing a lot of color text, function for this implemented
// could add inside "color | FOREGROUND_INTENSITY" but its better to keep without it
void writeColor(std::string data, int color) {
	SetConsoleTextAttribute(console, color);
	std::cout << data;
}


// void: not taking any arguments
int main(void) {
	// getting terminal Handle located int STD_OUTPUT_HANDLE
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	writeColor("what is your name?: ", color_black | FOREGROUND_INTENSITY);
	SetConsoleTextAttribute(console, color_magenta | FOREGROUND_INTENSITY);
	std::getline(std::cin, username);

	sleepAndClear(1250);

	for (Question q : questions) {
		writeColor("score: ", color_black | FOREGROUND_INTENSITY);
		writeColor(std::to_string(score) + "\n\n", color_light_blue | FOREGROUND_INTENSITY);

		writeColor(q.question + "\n", color_light_blue);
		for (int i = 0; i < 4; i++) {
			std::string prefixLetter(1, 97 + i);
			writeColor(prefixLetter + ") ", color_black | FOREGROUND_INTENSITY);
			writeColor(q.answers[i] + '\n', color_black | FOREGROUND_INTENSITY);
		}
		writeColor("\n", color_white);



		std::string quess; // used to avoid multiple char input
		std::getline(std::cin, quess);
		char cQuess = tolower(quess.at(0));
		int answer = cQuess - 97;

		if (answer == q.correctAnswer) {
			writeColor("\ncorrect answer!", color_green | FOREGROUND_INTENSITY);
			score += 1;
		}
		else {
			writeColor("\nwrong answer!", color_red | FOREGROUND_INTENSITY);
		}

		sleepAndClear(2000);
	}

	int questionSize = sizeof(questions) / sizeof(questions[0]);

	writeColor("congratulations " + username + "!\nyou finished your quiz\n\n", color_white);

	if (questionSize / 2 < score) writeColor("you scored " + std::to_string(score) + "/" + std::to_string(questionSize) + "\n", color_green);
	else writeColor("you scored " + std::to_string(score) + "/" + std::to_string(questionSize) + "\n", color_red);

	sleepAndClear(5000);

	// set terminal to black and white (defualt) to make user not write in awfull colors
	SetConsoleTextAttribute(console, color_white);
}
