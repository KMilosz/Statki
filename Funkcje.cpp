#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>

using namespace std;

void menu(char wybor);
void wyswietlPlansze(int tab[10][10], int tab2[10][10], bool X);
void zerowaniePlanszy(int tab[10][10]);
bool tworzenieStat(int tab[10][10], int y, int x, int kierun, int masztowiec);
void losowaMapa(int tab[10][10]);
bool zatop(int tab1[10][10], int tab2[10][10], int tab3[10][10], int y, int x, int masztowiec, bool pion);
bool sprawdzCzyZatop(int tab[10][10], int tab1[10][10], int tab3[10][10], int y, int x, int masztowiec);
bool czyWygral(int tab[10][10]);
bool strzelanie(int tab1[10][10], int tab2[10][10], int tab3[10][10],bool losowo);
void graDwuosobowa(int tab11[10][10], int tab12[10][10], int tab21[10][10], int tab22[10][10]);
void graJednoosobowa(int tab11[10][10], int tab12[10][10], int tab21[10][10], int tab22[10][10]);

void gra(char drugi)
{
	system("cls");
	cout << "Wybierz opcje gry:" << endl << "1. Gra dwuosobowa." << endl << "2. Gra jednoosobowa." << endl << "3. Powrot" << endl;
	if (drugi != '1' && drugi != '2' && drugi != '3')
		cout << "Wprowadz poprawna liczbe: ";
	cin >> drugi;
	if (drugi == '1')
	{
		system("cls");
		int tab11[10][10]{};
		int tab12[10][10]{};
		int tab21[10][10]{};
		int tab22[10][10]{};
		graDwuosobowa(tab11, tab12, tab21, tab22);
	}
	else
		if (drugi == '2')
		{
			system("cls");
			int tab11[10][10]{};
			int tab12[10][10]{};
			int tab21[10][10]{};
			int tab22[10][10]{};
			graJednoosobowa(tab11, tab12, tab21, tab22);
		}
		else
			if (drugi == '3')
			{
				system("cls");
				menu('0');
			}
			else
			{
				gra(drugi);
			}
}

void zasady()
{
	system("cls");
	cout << "Zasady gry w statki:" << endl;
	cout << "Statki to jest gra turowa z udzialem dwoch graczy (moze byc komputer)" << endl;
	cout << "Rozgrywka toczy sie na dwoch planszach na kazdego gracza 10x10 (Pozioma A-J, Pionowa 1-10) (jedna odpowiada Twoja plansze, druga przeciwnika)." << endl;
	cout << "Kieruj sie zgodnie z wyswietlanymi komunikatami, a ukonczysz gre." << endl;
	cout << "Kazdy z graczy ma 9 statkow (1 4-masztowiec, 2 3-masztowce, 3 2-masztowce, 4 1-masztowce) i zajmuja tyle kratek ile maja masztow." << endl;
	cout << "Statki nie moga stac obok siebie." << endl;
	cout << "Jesli ktorys z graczy zestrzeli wszystkie statki przeciwnika- wygrywa." << endl;
	cout << "Milej zabawy!" << endl;
	system("pause");
	system("cls");
	menu('0');
}

void autor()
{
	system("cls");
	cout << "Autor: Milosz Krajczok" << endl;
	cout << "Gra jest w wersji konsolowej, wiec tury gracza sa rozdzielone specjalnym ekranem informujacym ktory gracz bedzie wykonywal ruch" << endl;
	cout << "Jesli gracz zrobi cos niedozwolonego powinnien pojawic sie na gorze ekranu ERROR: prosze sie do tego stosowac i poprawic blad" << endl;
	cout << "Gdyby program nie dzialal tak jak powinien prosze nie wpisywac calej frazy (np. A10 2) tylko (A *enter* A *enter* itd.) dopoki program sie nie naprawi" << endl;
	system("pause");
	system("cls");
	menu('0');
}

void menu(char wybor)
{
	cout << "SSS   TTT    A    TTT   K K   I" << endl;
	cout << "S      T    A A    T    K K   I" << endl;
	cout << "SSS    T    A A    T    KK    I" << endl;
	cout << "  S    T    AAA    T    K K   I" << endl;
	cout << "SSS    T    A A    T    K K   I " << endl;
	cout << "Witam w grze statki!" << endl << endl;
	cout << "1. Zacznij Gre." << endl;
	cout << "2. Zasady." << endl;
	cout << "3. Autor i dodatkowe informacje o grze." << endl;
	cout << "4. Wyjdz." << endl;
	if (wybor == '0' || wybor == '1' || wybor == '2' || wybor == '3' || wybor == '4')
		cout << "Wybierz odpowiednia opcje poprzez wpisanie odpowiedniej liczby: ";
	else
		cout << "Prosze podac poprawna liczbe: ";
	cin >> wybor;
	if (wybor == '1')
	{
		cout << "Wybrales opcje 1" << endl;
		gra(wybor);

	}
	else
		if (wybor == '2')
		{
			cout << "Wybrales opcje 2" << endl;
			zasady();
		}
		else
			if (wybor == '3')
			{
				cout << "Wybrales opcje 3" << endl;
				autor();
			}
			else
				if (wybor == '4')
				{
					system("cls");
					cout << "Dziekuje za gre!" << endl;
					exit(0);
				}
				else
				{
					system("cls");
					cout << "ERROR: Prosze wpisac poprawna liczbe!" << endl;
					menu(wybor);
				}

}

void graDwuosobowa(int tab11[10][10], int tab12[10][10], int tab21[10][10], int tab22[10][10])
{
	int ileSt = 0;
	int masztowiec = 4;
	bool gracz = false;
	char litera;
	int liczba = 0;
	char kierunek = 'x';
	char liczbac;
	char czynnosc = '0';
	bool gra = false;
	for (int i = 0; i < 2; i++)
	{
		while (ileSt != 10)
		{
			if (gra == true)
			{
				system("cls");
				break;
			}
			if ((ileSt == 1 && masztowiec != 3) || (ileSt == 3 && masztowiec != 2) || (ileSt == 6 && masztowiec != 1))
				masztowiec -= 1;
			if (gracz == false)
			{
				cout << "Gracz 1 ustawia statki na planszy:" << endl << "Ustaw statek o " << masztowiec << " masztach." << endl;
				wyswietlPlansze(tab11, tab12, false);
			}
			else
			{
				cout << "Gracz 2 ustawia statki na planszy:" << endl << "Ustaw statek o " << masztowiec << " masztach." << endl;
				wyswietlPlansze(tab21, tab22, false);
			}
			cout << "Wprowadz wspolrzedne poczatku statku oraz kierunek (1-gora, 2-prawo, 3-dol, 4-lewo) np.A10 1" << endl << "Jest tez opcja generowanie losowej mapy, nalezy wpisac 'L' lub 'l'" << endl;
			cout << "Trzecia opcja jest wyczyszczenie dotychczasowej tworzonej mapy (wpisz 'W' lub 'w')." << endl;
			cout << "Zawsze mozesz wrocic do menu wpisujac 'M' lub 'm'." << endl;
			cin >> litera;
			if (litera == 'M' || litera == 'm')
			{
				system("cls");
				menu('0');
				exit(0);
			}
			if (litera == 'W' || litera == 'w')
			{
				if (gracz == false)
				{
					zerowaniePlanszy(tab11);
				}
				else
					zerowaniePlanszy(tab21);
				ileSt = 0;
				masztowiec = 4;
				system("cls");
				continue;
			}
			while (true)
			{
				if (litera == 'l' || litera == 'L')
				{
					system("cls");
					if (gracz == false)
					{
						losowaMapa(tab11);
						wyswietlPlansze(tab11, tab12, false);
					}
					else
					{
						losowaMapa(tab21);
						wyswietlPlansze(tab21, tab22, false);
					}
					cout << "Co chcesz dalej zrobic?" << endl;
					cout << "1. Losuj ponownie." << endl << "2. Chce grac na takiej!" << endl << "3. Jednak stworze swoja plansze." << endl;
					cin >> czynnosc;
					if (czynnosc == '1')
					{
						system("cls");
						continue;
					}
					if (czynnosc == '2')
					{
						system("cls");
						gra = true;
						break;
					}
					if (czynnosc == '3')
					{
						system("cls");
						ileSt = 0;
						masztowiec = 4;
						break;;
					}
					system("cls");
					cout << "ERROR: Wprowadz prawidlowe dane." << endl;
					continue;
				}
				break;
			}
			if (czynnosc == '3' || czynnosc == '2')
			{
				if (gra == false)
				{
					if (gracz == false)
						zerowaniePlanszy(tab11);
					else
						zerowaniePlanszy(tab21);
				}
				system("cls");
				czynnosc = '0';
				continue;
			}
			cin >> liczbac;
			if (liczbac >= '1' && liczbac <= '9')
			{
				liczba = liczbac - 48;
				cin >> liczbac;
				if (liczbac == '0' && liczba == 1)
				{
					liczba = 10;
					cin >> kierunek;
				}
				else
					kierunek = liczbac;

			}
			if (((litera >= 65 && litera <= 74) || (litera >= 97 && litera <= 106)) && (liczba >= 1 && liczba <= 10) && (kierunek >= 49 && kierunek <= 52))
			{
				if (litera > 96)
					litera -= 32;
				system("cls");
				if (gracz == false)
				{
					if (tworzenieStat(tab11, liczba - 1, litera - 65, kierunek - 49, masztowiec))
					{
						cout << "Statek wprowadzono powyslnie!" << endl;
						ileSt += 1;
					}
					else
						cout << "ERROR: Blad wprowadzania statku" << endl;
					wyswietlPlansze(tab11, tab12, false);
					system("pause");
					system("cls");
				}
				else
				{
					if (tworzenieStat(tab21, liczba - 1, litera - 65, kierunek - 49, masztowiec))
					{
						cout << "Statek wprowadzono pomyslnie!" << endl;
						ileSt += 1;
					}
					else
						cout << "ERROR: Blad wprowadzania statku" << endl;
					wyswietlPlansze(tab21, tab22, false);
					system("pause");
					system("cls");
				}
			}
			else
			{
				system("cls");
				cout << "ERROR: Wrowadzono zle dane!" << endl;
				system("pause");
				liczba = 0;
				litera = 'x';
				liczbac = 'x';
				kierunek = 'x';
				system("cls");
				continue;
			}
		}
		gra = false;
		ileSt = 0;
		masztowiec = 4;
		gracz = true;
	}
	gracz = false;
	bool czy1 = false;
	while (czy1 == false)
	{
		if (gracz == false)
		{
			system("cls");
			cout << "Gracz 1 wykonuje ruch:" << endl;
			system("pause");
			system("cls");
			cout << "Gracz 1:	Twoja Mapa					Twoje strzaly" << endl;
			wyswietlPlansze(tab11, tab12, true);
			if (strzelanie(tab12, tab21, tab11,false))
			{
				cout << "Gracz 1 wygral!" << endl;
				system("pause");
				system("cls");
				menu('0');
				exit(0);
			}
			gracz = true;
		}
		else
		{
			system("cls");
			cout << "Gracz 2 wykonuje ruch:" << endl;
			system("pause");
			system("cls");
			cout << "Gracz 2:	Twoja Mapa					Twoje strzaly" << endl;
			wyswietlPlansze(tab21, tab22, true);
			if (strzelanie(tab22, tab11, tab21, false))
			{
				cout << "Gracz 2 wygral!" << endl;
				system("pause");
				system("cls");
				menu('0');
				exit(0);
			}
			gracz = false;
		}
	}
}

void graJednoosobowa(int tab11[10][10], int tab12[10][10], int tab21[10][10], int tab22[10][10])
{
	int ileSt = 0;
	int masztowiec = 4;
	bool gracz = false;
	char litera;
	int liczba = 0;
	char kierunek = 'x';
	char liczbac;
	char czynnosc = '0';
	bool gra = false;
	while (ileSt != 9)
	{
		if (gra == true)
		{
			system("cls");
			break;
		}
		if ((ileSt == 1 && masztowiec != 3) || (ileSt == 3 && masztowiec != 2) || (ileSt == 6 && masztowiec != 1))
			masztowiec -= 1;
		cout << "Ustawiasz statki na planszy:" << endl << "Ustaw statek o " << masztowiec << " masztach." << endl;
		wyswietlPlansze(tab11, tab12, false);
		cout << "Wprowadz wspolrzedne poczatku statku oraz kierunek (1-gora, 2-prawo, 3-dol, 4-lewo) np.A10 3" << endl << "Jest tez opcja generowanie losowej mapy, nalezy wpisac 'L' lub 'l'" << endl;
		cout << "Trzecia opcja jest wyczyszczenie dotychczasowej tworzonej mapy (wpisz 'W' lub 'w')." << endl;
		cout << "Zawsze mozesz wrocic do menu wpisujac 'M' lub 'm'." << endl;
		cin >> litera;
		if (litera == 'M' || litera == 'm')
		{
			system("cls");
			menu('0');
			exit(0);
		}
		if (litera == 'W' || litera == 'w')
		{
			zerowaniePlanszy(tab11);
			ileSt = 0;
			masztowiec = 4;
			system("cls");
			continue;
		}
		while (true)
		{
			if (litera == 'l' || litera == 'L')
			{
				system("cls");
				losowaMapa(tab11);
				wyswietlPlansze(tab11, tab12, false);
				cout << "Co chcesz dalej zrobic?" << endl;
				cout << "1. Losuj ponownie." << endl << "2. Chce grac na takiej!" << endl << "3. Jednak stworze swoja plansze." << endl;
				cin >> czynnosc;
				if (czynnosc == '1')
				{
					system("cls");
					continue;
				}
				if (czynnosc == '2')
				{
					system("cls");
					gra = true;
					break;
				}
				if (czynnosc == '3')
				{
					system("cls");
					ileSt = 0;
					masztowiec = 4;
					break;;
				}
				system("cls");
				cout << "ERROR: Wprowadz prawidlowe dane." << endl;
				continue;
			}
			break;
		}
		if (czynnosc == '3' || czynnosc == '2')
		{
			if (gra == false)
			{
				zerowaniePlanszy(tab11);
			}
			system("cls");
			czynnosc = '0';
			continue;
		}
		cin >> liczbac;
		if (liczbac >= '1' && liczbac <= '9')
		{
			liczba = liczbac - 48;
			cin >> liczbac;
			if (liczbac == '0' && liczba == 1)
			{
				liczba = 10;
				cin >> kierunek;
			}
			else
				kierunek = liczbac;
		}
		if (((litera >= 65 && litera <= 74) || (litera >= 97 && litera <= 106)) && (liczba >= 1 && liczba <= 10) && (kierunek >= 49 && kierunek <= 52))
		{
			if (litera > 96)
				litera -= 32;
			system("cls");
			if (tworzenieStat(tab11, liczba - 1, litera - 65, kierunek - 49, masztowiec))
			{
				cout << "Statek wprowadzono powyslnie!" << endl;
				ileSt += 1;
			}
			else
				cout << "ERROR: Blad wprowadzania statku" << endl;
			wyswietlPlansze(tab11, tab12, false);
			system("pause");
			system("cls");
		}
		else
		{
			liczba = 0;
			litera = 'x';
			liczbac = 'x';
			kierunek = 'x';
			system("cls");
			continue;
		}
	}
	losowaMapa(tab21);
	gra = false;
	ileSt = 0;
	masztowiec = 4;
	bool czy1 = false;
	while (czy1 == false)
	{
		if (gracz == false)
		{
			system("cls");
			cout << "Wykonujesz ruch:" << endl;
			system("pause");
			system("cls");
			cout << "Ty:	Twoja Mapa					Twoje strzaly" << endl;
			wyswietlPlansze(tab11, tab12, true);
			if (strzelanie(tab12, tab21, tab11,false))
			{
				cout << "Wygrales!" << endl;
				system("pause");
				system("cls");
				menu('0');
				exit(0);
			}
			gracz = true;
		}
		else
		{
			system("cls");
			cout << "BOT wykonuje ruch:" << endl;
			system("pause");
			system("cls");
			if (strzelanie(tab22, tab11, tab21,true))
			{
				cout << "BOT wygral!" << endl;
				system("pause");
				system("cls");
				menu('0');
				exit(0);
			}
			gracz = false;
		}
	}
}

bool strzelanie(int tab1[10][10], int tab2[10][10], int tab3[10][10], bool losowo)
{
	string tekst = "xxxxx";
	char literka = 'Q';
	char liczba = 'Q';
	if (losowo == false)
	{
		tekst = "xxx";
		literka = 'x';
		liczba = 'x';
		cout << "Wprowadz wspolrzedne w ktore chcesz strzelic np. A4" << endl << "Aby sie poddac i wrocic do menu wpisz 'M' lub 'm'" << endl;
		cin >> tekst;
	}
	else
	{
		mt19937 generator(time(nullptr));
		uniform_int_distribution<int> pole(0, 9);
		int x = pole(generator);
		int y = pole(generator);
		if (tab1[x][y] == 0)
		{
			if (tab2[x][y] == 0 || tab2[x][y] == 5)
			{
				tab1[x][y] = 2;
				tab2[x][y] = 10;
			}
			else
			{
				tab1[x][y] = 1;
				tab2[x][y] += 5;
				if (sprawdzCzyZatop(tab2, tab1, tab3, y, x, tab2[x][y] - 5))
					if (czyWygral(tab2))
						return true;
			}
			return false;
		}
		else
		{
			system("cls");
			cout << "ERROR: wprowadzono zle dane" << endl;
			wyswietlPlansze(tab1, tab3, losowo);
			strzelanie(tab1, tab2, tab3, losowo);
			return false;
		}
	}
	if (tekst[0] == 'm' || tekst[0] == 'M')
	{
		cout << "Poddales sie, wracasz do menu" << endl;
		system("pause");
		system("cls");
		menu('0');
		exit(0);
	}
	if ((tekst[0] >= 'a' && tekst[0] <= 'j') || (tekst[0] >= 'A' && tekst[0] <= 'J'))
	{
		literka = tekst[0];
		if (tekst[0] >= 'a')
			literka -= 32;
		if (tekst[1] >= '1' && tekst[1] <= '9')
		{
			liczba = tekst[1];
			if (tekst[1] == '1' && tekst[2] == '0')
			{
				liczba = '9' + 1;
			}
		}
		else
		{
			system("cls");
			cout << "ERROR: wprowadzono zle dane" << endl;
			wyswietlPlansze(tab3, tab1, true);
			system("pause");
			return strzelanie(tab1, tab2, tab3, losowo);
		}
	}
	else
	{
		system("cls");
		cout << "ERROR: Wprowadzono zle dane. Prosze sprobowac ponownie." << endl;
		wyswietlPlansze(tab3, tab1, true);
		strzelanie(tab1, tab2, tab3,false);
	}
	if (tab1[literka - 65][liczba - 49] == 0)
	{
		if (tab2[literka - 65][liczba - 49] == 0 || tab2[literka - 65][liczba - 49] == 5)
		{
			tab1[literka - 65][liczba - 49] = 2;
			tab2[literka - 65][liczba - 49] = 10;
		}
		else
		{
			tab1[literka - 65][liczba - 49] = 1;
			tab2[literka - 65][liczba - 49] += 5;
			if(sprawdzCzyZatop(tab2, tab1, tab3, liczba - 49, literka - 65, tab2[literka - 65][liczba - 49] - 5))
				if(czyWygral(tab2))
					return true;
		}
	}
	else
	{
		system("cls");
		cout << "ERROR: Te pole juz jest odkryte! Wybierz inne pole." << endl;
		wyswietlPlansze(tab3, tab1, true);
		strzelanie(tab1, tab2, tab3,false);
	}
	return false;
}

bool sprawdzCzyZatop(int tab[10][10], int tab1[10][10], int tab3[10][10], int y, int x, int masztowiec)
{
	bool pion = true;
	int ile = 0;
	if (masztowiec == 1)
	{
		zatop(tab, tab1, tab3, y, x, masztowiec, pion);
		return true;
	}
	for (int i = 0; i < 2 * masztowiec; i++)
	{
		for (int j = 0; j < masztowiec; j++)
		{
			if (i < masztowiec)
			{
				if (x - masztowiec +1 + i < 0 || x + i > 9)
					break;
				if (tab[x + i - j][y] == masztowiec + 5)
				{
					ile += 1;
				}
				else
				{
					ile = 0;
					break;
				}
				if (ile == masztowiec)
				{
					pion = false;
					zatop(tab, tab1, tab3, y, x + i - j, masztowiec, pion);
					return true;
				}
			}
			else
			{
				if (y + masztowiec - 1 - i + masztowiec > 9 && y - i + masztowiec < 0)
					break;
				if (tab[x][y - i + masztowiec + j] == masztowiec + 5)
				{
					ile += 1;
				}
				else
				{
					ile = 0;
					break;
				}
				if (ile == masztowiec)
				{
					pion = true;
					zatop(tab, tab1, tab3, y - i + masztowiec + j, x, masztowiec, pion);
					return true;
				}
			}
		}
	}

	return false;
}

bool zatop(int tab1[10][10], int tab2[10][10], int tab3[10][10], int y, int x, int masztowiec, bool pion)
{
	if (pion == true)
	{
		for (int i = 0; i < masztowiec + 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (x - 1 + j > 9 || x - 1 + j < 0 || y - masztowiec + i > 9 || y - masztowiec + i < 0)
					continue;
				if ((i >= 1) && (i <= masztowiec) && (j == 1))
				{
					tab2[x - 1 + j][y - masztowiec + i] = 1;
				}
				else
				{
					tab1[x - 1 + j][y - masztowiec + i] = 10;
					tab2[x - 1 + j][y - masztowiec + i] = 2;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < masztowiec + 2; j++)
			{
				if (x - 1 + j > 9 || x - 1 + j < 0 || y - 1 + i>9 || y - 1 + i < 0)
					continue;
				if (i == 1 && j >= 1 && j <= masztowiec)
				{
					tab2[x - 1 + j][y - 1 + i] = 1;
				}
				else
				{
					tab1[x - 1 + j][y - 1 + i] = 10;
					tab2[x - 1 + j][y - 1 + i] = 2;
				}
			}
		}
	}
	return true;
}

void wyswietlPlansze(int tab[10][10], int tab2[10][10], bool X)
{
	char literka = 'A';
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 && j == 0)
			{
				cout << "+	";
				continue;
			}
			if (i == 0)
			{
				cout << char(literka + j-1)<<"  ";
				continue;
			}
			if (j == 0)
			{
				cout << i << "	";
				continue;
			}
			if (tab[j-1][i-1] <= 9 && tab[j-1][i-1] >= 6)
			{
				cout << "X  ";
				continue;
			}
			if (tab[j-1][i-1] == 10)
			{
				cout << "/  ";
				continue;
			}
			if (tab[j-1][i-1] == 5)
			{
				cout << 0 << "  ";
			}
			else
				cout << tab[j-1][i-1] << "  ";
		}
		if (X == 1)
		{
			cout << "	|	";
			for (int j = 0; j < 11; j++)
			{
				if (i == 0 && j == 0)
				{
					cout << "+	";
					continue;
				}
				if (i == 0)
				{
					cout << char(literka + j-1)<<"  ";
					continue;
				}
				if (j == 0)
				{
					cout << i << "	";
					continue;
				}
				if (tab2[j-1][i-1] == 1)
				{
					cout << "X  ";
					continue;
				}
				if (tab2[j-1][i-1] == 2)
				{
					cout << "/  ";
				}
				else
					cout << tab2[j-1][i-1] << "  ";
			}
		}
		cout << endl << endl;
	}
}

bool tworzenieStat(int tab[10][10], int y, int x, int kierun, int masztowiec) //licza litera
{
	if (tab[x][y] == 0)
	{
		if (kierun == 0)
		{
			for (int i = 0; i < masztowiec; i++)
			{
				if (tab[x][y - i] != 0)
					return false;
			}
			if (y - masztowiec + 1 < 0)
				return false;
			for (int i = 0; i < 2 + masztowiec; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (x - 1 + j < 0 || x - 1 + j>9)
						continue;
					if (y - masztowiec + i < 0 || y - masztowiec + i>9)
						continue;
					if (i > 0 && i < masztowiec + 1 && j == 1)
					{
						tab[x - 1 + j][y - masztowiec + i] = masztowiec;
						continue;
					}
					tab[x - 1 + j][y - masztowiec + i] = 5;
				}
			}
			return true;
		}
		if (kierun == 1)
		{
			if (x + masztowiec - 1 > 9)
				return false;
			for (int i = 0; i < masztowiec; i++)
			{
				if (tab[x + i][y] != 0)
					return false;
			}
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 2 + masztowiec; j++)
				{
					if (x - 1 + j < 0 || x - 1 + j>9)
						continue;
					if (y - 1 + i < 0 || y - 1 + i>9)
						continue;
					if (i == 1 && j > 0 && j < masztowiec + 1)
					{
						tab[x - 1 + j][y - 1 + i] = masztowiec;
						continue;
					}
					tab[x - 1 + j][y - 1 + i] = 5;
				}
			}
			return true;
		}
		if (kierun == 2)
		{
			if (y + masztowiec - 1 > 9)
				return false;
			for (int i = 0; i < masztowiec; i++)
			{
				if (tab[x][y + i] != 0)
					return false;
			}
			for (int i = 0; i < 2 + masztowiec; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (x - 1 + j > 9 || x - 1 + j < 0)
						continue;
					if (y - 1 + i > 9 || y - 1 + i < 0)
						continue;
					if (j == 1 && i > 0 && i < masztowiec + 1)
					{
						tab[x - 1 + j][y - 1 + i] = masztowiec;
						continue;
					}
					tab[x - 1 + j][y - 1 + i] = 5;
				}
			}
			return true;
		}
		if (kierun == 3)
		{
			for (int i = 0; i < masztowiec; i++)
			{
				if (tab[x - masztowiec + 1][y] != 0)
					return false;
			}
			if (x - masztowiec + 1 < 0)
				return false;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 2 + masztowiec; j++)
				{
					if (x - masztowiec + j > 9 || x - masztowiec + j < 0)
						continue;
					if (y - 1 + i > 9 || y - 1 + i < 0)
						continue;
					if (i == 1 && j > 0 && j < masztowiec + 1)
					{
						tab[x - masztowiec + j][y - 1 + i] = masztowiec;
						continue;
					}
					tab[x - masztowiec + j][y - 1 + i] = 5;
				}
			}
			return true;
		}
	}
	else
		return false;
}



void losowaMapa(int tab[10][10])
{
	zerowaniePlanszy(tab);
	//tab = {};
	int masztowiec = 4;
	bool czy = false;
	int ktoryst = 1;
	int x = 0;
	int y = 0;
	int kier = 0;
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> pole(0, 9);
	uniform_int_distribution<int> kierunek(0, 3);
	while (true)
	{
		x = pole(generator);
		y = pole(generator);
		if (tab[x][y] == 0)
		{
			while (czy == false)
			{
				kier = kierunek(generator);
				czy = tworzenieStat(tab, y, x, kier, masztowiec);
				x = pole(generator);
				y = pole(generator);
			}
			czy = false;
			ktoryst += 1;
			if (ktoryst == 2 || ktoryst == 4 || ktoryst == 7)
				masztowiec -= 1;
			if (ktoryst == 11)
				break;
		}
		else
			continue;

	}

}

void zerowaniePlanszy(int tab[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tab[j][i] = 0;
		}
	}
}

bool czyWygral(int tab[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (tab[i][j] >= 1 && tab[i][j] <= 4)
			{
				return false;
			}
		}
	}
	return true;
}


//bool przesunStatek(int tab[10][10], int y, int x, int masztowiec, int kierunek)
//{
//	int ilePol = 0;
//	bool jest = false;
//	if (kierunek == 0 || kierunek == 2)
//	{
//		for (int i = 0; i < masztowiec;i++)
//		{
//			for (int j = 0;j < masztowiec;j++)
//			{
//				if (y + masztowiec - 1 - i > 9)
//				{
//					ilePol = 0;
//					jest = false;
//					break;
//				}
//				if (y - i < 0)
//				{
//					return false;
//				}
//				if (tab[x][y - i + j] == masztowiec)
//				{
//					ilePol += 1;
//				}
//				else
//				{
//					ilePol = 0;
//					break;
//				}
//				if (ilePol == masztowiec)
//				{
//					if (kierunek == 0 && y-i-1<10)
//					{
//						if (tab[x][y - i - 1] == 0)
//						{
//							for (int q = 0;q < masztowiec+3;q++)
//							{
//								for (int w = 0;w < 3 ; w++)
//								{
//									if (w == 1 && q > 0 && q < masztowiec + 1)
//									{
//										tab[x - 1 + w][y - i - 2 + q] = masztowiec;
//										continue;
//									}
//									if (y-1-2+q>=0 && x-1+w>=0 && x-1+w<=9)
//									{
//										if (tab[x - 1 + w][y - i - 2 + q] == 0)
//										{
//											tab[x - 1 + w][y - i - 2 + q] = 5;
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}