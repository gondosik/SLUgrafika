#include <iostream>
#include <SDL.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>

const int CONSOLE_POSITION_X = 10;
const int CONSOLE_POSITION_Y = 0;
const int CONSOLE_WIDTH = 500;
const int CONSOLE_HEIGHT = 200;
const int WINDOW_POSITION_X = 30;
const int WINDOW_POSITION_Y = 250;
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

double getStep(double, double);
double getD(double, double);
void drawLineDDA(double, double, double, double , SDL_Renderer*);
void drawCircleUsingLines(double, SDL_Renderer*);

double getStep(double dx, double dy) {
	return ((dx > dy) ? dx : dy);
}
double getD(double num0, double num1) {
	return num1 - num0;
}
void drawLineDDA(double x0, double y0, double x1, double y1, SDL_Renderer* renderer) {
	double x, y, i, dx, dy, XP, YP, steps;
	int MX, MY;
	
	dx = getD(x0, x1);
	dy = getD(y0, y1);
	if (!dx && !dy) {
		SDL_RenderDrawPoint(renderer, x0, y0);
		SDL_RenderPresent(renderer);
		exit;
	}
	steps = getStep(abs(dx), abs(dy));
	XP = abs(dx) / steps;
	YP = abs(dy) / steps;

	if (dx >= 0) {
		MX = 1;
	}
	else {
		MX = -1;
	}
	if (dy >= 0) {
		MY = 1;
	}
	else {
		MY = -1;
	}
	x = x0;
	y = y0;

	XP = (XP * MX);
	YP = (YP * MY);

	for(int i = 0; i <= steps; i++)
	{
		SDL_RenderDrawPoint(renderer, round(x), round(y));
		Sleep(2);
		if (MX > 0)
			x++;
		else
			x--;
		y += YP;
		SDL_RenderPresent(renderer);
	}
}

void drawCircleUsingLines(double r, SDL_Renderer *renderer) {
	double circleXcenter = WINDOW_WIDTH / 2;
	double circleYcenter = WINDOW_HEIGHT / 2;
	double alpha = 1 / r;
	double sinAlpha = sin(alpha);
	double cosAlpha = cos(alpha);
	double x0 = (r * cosAlpha);  
	double y0 = (r * sinAlpha);
	double x1 = 0.0, y1 = 0.0;

	for (double angle = alpha; angle < 2 * M_PI; angle += alpha) {
		x1 = (x0 * cosAlpha) - (y0 * sinAlpha);
		y1 = (x0 * sinAlpha) + (y0 * cosAlpha);
	    drawLineDDA(x0 + circleXcenter, y0 + circleYcenter, x1 + circleXcenter, y1 + circleYcenter, renderer);
		SDL_RenderPresent(renderer);
		x0 = x1;
		y0 = y1;
	}

}
int main(int argc, char** args) {
	HWND consoleWindow = GetConsoleWindow();
	double r = 0.0;
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
 
	SetWindowPos(consoleWindow, 0, CONSOLE_POSITION_X, CONSOLE_POSITION_Y, CONSOLE_WIDTH, CONSOLE_HEIGHT, 0);


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Chyba pri inicializaci SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "PS-SLU-CircleLineDrawer");
	SDL_SetWindowPosition(window, WINDOW_POSITION_X, WINDOW_POSITION_Y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	std::cout << "Parametry vykreslovaciho okna jsou:" << std::endl << "Sirka: " << WINDOW_WIDTH << std::endl << "Vyska: " << WINDOW_HEIGHT << std::endl;
	std::cout << "Hodnoty museji mit hodnotu vetsi nez 0!" << std::endl << "Maji datovy typ double." << std::endl;

	do {
		std::cout << "Zadejte hodnotu polomeru r kruznice" << std::endl;
		std::cin >> r;
	} while (!r);

	std::cout << "Vykresluji kruznici na zaklade polomeru r " << r << " a prirustku alfa (1/r) " << (1/r)  << " ." << std::endl;
	std::cout << std::endl;
	drawCircleUsingLines(r, renderer);

	if (!window) {
		std::cout << "Chyba pri vytvareni grafickeho okna: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	winSurface = SDL_GetWindowSurface(window);

	if (!winSurface) {
		std::cout << "Chyba pri ziskavani vykreslovaci oblasti: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	system("pause");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}