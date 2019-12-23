#include "stdafx.h"
#include <iostream>     
#include <thread>     
#include <windows.h>   
#include <string>
#include <cstring>
#include <conio.h>
#include "stdafx.h"
#include <time.h>

#define ramka 10
#define vysota 330
#define shirina 450

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

void risovalka(int *x_nach_i, int *y_nach_j, int color_risovalka_flag_1, int color_risovalka_flag_2, HDC hdc);
void problem(int pr, int kordinatu_y_problem, bool color_pr, HDC hdc);
void rang_fruit(int qx_nach_i, int qy_nach_j, bool color, HDC hdc);
void risovalka_ramka(HDC hdc);
int one_pot();
void music();

int main()
{

	thread first(one_pot);
	thread second(music);

	first.join();
	second.join();

	return 0;
}

int one_pot() {
	HWND windowld = GetConsoleWindow();
	HDC hdc = GetDC(windowld);
	srand(time(0));

	int speed = 3;
	int speedpr = 2;
	int pr = ((ramka + 1) + rand() % ((shirina - 20) - (ramka + 1) + 1));
	int kordinatu_y_problem = ramka + 1;

	int color_risovalka_flag_1 = 222;
	int color_risovalka_flag_2 = 255;
	int x_nach_i = shirina / 2 + 5;
	int y_nach_j = vysota / 2 + 5;
	int key;
	bool color = false;
	int qx_nach_i = ((ramka + 1) + rand() % ((shirina - 20) - (ramka + 1) + 1));
	int qy_nach_j = ((ramka + 1) + rand() % ((vysota - 20) - (ramka + 1) + 1));
	int score = 0;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "                      SCORE - " << score << "       " << "\r";
	risovalka(&x_nach_i, &y_nach_j, color_risovalka_flag_1, color_risovalka_flag_2, hdc);
	rang_fruit(qx_nach_i, qy_nach_j, true, hdc);
	problem(pr, kordinatu_y_problem, true, hdc);
	risovalka_ramka(hdc);

	while (1) {
		if (kbhit()) {
			key = getch();
			while (!kbhit()) {
				risovalka(&x_nach_i, &y_nach_j, 0, 0, hdc);

				switch (key) {
				case 119:  y_nach_j -= speed; break;
				case 115: y_nach_j += speed; break;
				case 97:  x_nach_i -= speed; break;
				case 100: x_nach_i += speed; break;
				}

				if (x_nach_i + 20 >= shirina) {
					x_nach_i = ramka + 1;
				}
				if (y_nach_j + 20 >= vysota) {
					y_nach_j = ramka + 1;
				}
				if (x_nach_i <= ramka) {
					x_nach_i = shirina - 20 - 1;
				}
				if (y_nach_j <= ramka) {
					y_nach_j = vysota - 20 - 1;
				}

				for (int i = x_nach_i; i <= x_nach_i + 20; i++) {
					for (int j = y_nach_j; j <= y_nach_j + 20; j++) {
						if ((i == qx_nach_i && j == qy_nach_j) || (i == qx_nach_i + 20 && j == qy_nach_j + 20) || (j == qy_nach_j + 20 && i == qx_nach_i) || (j == qy_nach_j  && i == qx_nach_i + 20)) {
							rang_fruit(qx_nach_i, qy_nach_j, false, hdc);
							qx_nach_i = ((ramka + 1) + rand() % ((shirina - 20) - (ramka + 1)));
							qy_nach_j = ((ramka + 1) + rand() % ((vysota - 20) - (ramka + 1)));
							score++;
							cout << "                      SCORE - " << score << "       " << "\r";
							break;
						}
						if ((i == pr && j == kordinatu_y_problem) || (j == kordinatu_y_problem + 10 && i == pr) || (j == kordinatu_y_problem && i == pr + 10) || (j == kordinatu_y_problem + 10 && i == pr + 10)) {
							system("cls");
							HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(console, FOREGROUND_GREEN);
							cout << endl << endl << endl << endl << endl << endl << "                   GAME OVER" << endl;
							cout << "                   SCORE - " << score << endl;
							return 0;
						}
					}
				}
				risovalka(&x_nach_i, &y_nach_j, color_risovalka_flag_1, color_risovalka_flag_2, hdc);
				rang_fruit(qx_nach_i, qy_nach_j, true, hdc);
				problem(pr, kordinatu_y_problem, false, hdc);

				if (kordinatu_y_problem > vysota) {
					kordinatu_y_problem = ramka;
					pr = ((ramka + 1) + rand() % ((shirina - 20) - (ramka + 1) + 1));
				}
				kordinatu_y_problem += speedpr;
				problem(pr, kordinatu_y_problem, true, hdc);
			}
		}
	}
	return 0;
}

void problem(int pr, int kordinatu_y_problem, bool color_pr, HDC hdc) {
	int color_problem = 0;
	if (color_pr) {
		color_problem = 255;
	}
	for (int i = pr; i <= pr + 10; i++) {
		for (int j = kordinatu_y_problem; j <= kordinatu_y_problem + 10 && j < vysota; j++) {
			SetPixel(hdc, i, j, RGB(color_problem, color_problem, color_problem));
		}
	}
}

void risovalka(int *x_nach_i, int *y_nach_j, int color_risovalka_flag_1, int color_risovalka_flag_2, HDC hdc) {
	for (int i = *x_nach_i; i <= *x_nach_i + 20; i++) {
		for (int j = *y_nach_j; j <= *y_nach_j + 20; j++) {
			if (j <= *y_nach_j + 10) {
				SetPixel(hdc, i, j, RGB(0, 0, color_risovalka_flag_1));
			}
			else if (i > *x_nach_i) {
				SetPixel(hdc, i, j, RGB(color_risovalka_flag_2, color_risovalka_flag_2, 0));
			}
		}
	}
}

void rang_fruit(int qx_nach_i, int qy_nach_j, bool color, HDC hdc) {
	int ik = 0, jk = 0, lk = 0;
	for (int i = qx_nach_i; i <= qx_nach_i + 20; i++) {
		for (int j = qy_nach_j; j <= qy_nach_j + 20; j++) {
			if (color) {
				ik = i*j, jk = i*i, lk = j*j;
			}
			SetPixel(hdc, i, j, RGB(ik, jk, lk));
		}
	}
}

void music() {
	while (1) {
		PlaySound(L"Beggin.wav", NULL, SND_ASYNC | SND_FILENAME);
		Sleep(280000);//длительност песни
	}
}

void risovalka_ramka(HDC hdc) {
	for (int i = 0; i < shirina + ramka; i++) {
		for (int j = 0; j < vysota + ramka; j++) {
			if (i <= ramka || j <= ramka || i >= shirina || j >= vysota) {
				SetPixel(hdc, i, j, RGB(230, 170, 123));
			}
		}
	}
}//179 строr






