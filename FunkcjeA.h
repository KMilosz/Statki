#pragma once

void menu(char wybor);
void zasady();
void wyswietlPlansze(int tab[10][10], int tab2[10][10], bool X);
void zerowaniePlanszy(int tab[10][10]);
bool tworzenieStat(int tab[10][10], int y, int x, int kierun, int masztowiec);
void losowaMapa(int tab[10][10]);
void graDwuosobowa(int tab11[10][10], int tab12[10][10], int tab21[10][10], int tab22[10][10]);
bool strzelanie(int tab11[10][10], int tab12[10][10], int tab3[10][10],bool losowo);
bool zatop(int tab1[10][10], int tab2[10][10], int tab3[10][10], int y, int x, int masztowiec, bool pion);
bool sprawdzCzyZatop(int tab[10][10], int tab1[10][10], int tab3[10][10], int y, int x, int masztowiec);
bool czyWygral(int tab[10][10]);


