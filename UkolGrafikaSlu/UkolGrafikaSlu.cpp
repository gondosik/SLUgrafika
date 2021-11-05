#include <iostream>
#include <SDL.h>
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
void drawLine(double, double, double, double , SDL_Renderer*);

double getStep(double dx, double dy) {
	return ((dx > dy) ? dx : dy);
}
double getD(double num0, double num1) {
	return num1 - num0;
}
void drawLine(double x0, double y0, double x1, double y1, SDL_Renderer* renderer) {
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

	std::cout << "Data o promennych: " << std::endl;
	std::cout << "Pocatek: [" << x << ";" << y << "]" << std::endl;
	std::cout << "Pocet kroku: " << steps << std::endl;
	std::cout << "Prirustek X: " << XP << std::endl;
    std::cout << "Prirustek Y: " << YP << std::endl;
	std::cout << "Hodnota MX: " << MX << std::endl;
	std::cout << "Hodnota MY: " << MY << std::endl;

	XP = (XP * MX);
	YP = (YP * MY);

	for(int i = 0; i <= steps; i++)
	{
		SDL_RenderDrawPoint(renderer, round(x), round(y));
		Sleep(10);
		if (MX > 0)
			x++;
		else
			x--;
		y += YP;
		SDL_RenderPresent(renderer);
	}
}
int main(int argc, char** args) {
	HWND consoleWindow = GetConsoleWindow();
	double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;
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
	SDL_SetWindowTitle(window, "PS-SLU-LineDrawer");
	SDL_SetWindowPosition(window, WINDOW_POSITION_X, WINDOW_POSITION_Y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	std::cout << "Parametry vykreslovaciho okna jsou:" << std::endl << "Sirka: " << WINDOW_WIDTH << std::endl << "Vyska: " << WINDOW_HEIGHT << std::endl;
	std::cout << "Hodnoty museji mit hodnotu vetsi nez 0!" << std::endl << "Maji datovy typ double." << std::endl;

	do {
		std::cout << "Zadejte souradnici x0 prvniho bodu" << std::endl;
		std::cin >> x0;
	} while (!x0);
	do {
		std::cout << "Zadejte souradnici y0 prvniho bodu" << std::endl;
		std::cin >> y0;
	} while (!y0);
	do {
		std::cout << "Zadejte souradnici x1 druheho bodu" << std::endl;
		std::cin >> x1;
	} while (!x1);
	do {
		std::cout << "Zadejte souradnici y1 druheho bodu" << std::endl;
		std::cin >> y1;
	} while (!y1);

	std::cout << "Vykresluji primku na zaklade bodu A[" << x0 << ";" << y0 << "] a B[" << x1 << ";" << y1 << "]." << std::endl;
	std::cout << std::endl;
	drawLine(x0,y0,x1,y1, renderer);

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