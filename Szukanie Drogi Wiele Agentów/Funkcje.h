#pragma once

#ifndef FUNKCJE_H
#define FUNKCJE_H




#include <raylib.h>
#include "PozycjeNaMapie.h"
#include <iostream>
#include <string>
#include "Kolory.h"
#include <algorithm>
#include <vector>

struct KolorowyKwadrat
{
	PozycjaNaMapie poz;
	Color kolor;
	std::string Napis;
	std::string Napis2;


	KolorowyKwadrat(PozycjaNaMapie poz = { 0,0 }, Color kolor = ZIELONY, std::string Napis = "", std::string Napis2 = "");
	bool operator==(const KolorowyKwadrat& kolorowy);
	bool operator==(const PozycjaNaMapie& poz);
};

//--------------------------------------------------



//Funkcje --------------

//zamyka w czas w okreslonych odstepach 

//Metody do kolorowych kwadratow

void UstawKoszt(PozycjaNaMapie poz, int kosztG, int kosztH, std::vector<KolorowyKwadrat>& tablica);

void UstawKolor(PozycjaNaMapie  poz, Color Kolor, std::vector<KolorowyKwadrat>& tablica);

void UstawRodzica(PozycjaNaMapie poz, unsigned int Rodzic, std::vector<KolorowyKwadrat>& tablica);

void NowyKwadrat(PozycjaNaMapie poz, Color kolor, unsigned int rodzic, int kosztG, int kosztH, std::vector<KolorowyKwadrat>& tablica);


float Interpolacja(float x0, float y0, float x1, float y1, float obecna);
float Interpolacja(float x0, float x1, float procent);

float TickRuchu(Vector2 pozA, Vector2 pozB, float Predkosc, const float tickrate, float procent = 0.5);

float Dlugosc(Vector2 wektor);

Vector2 Normalizacja(Vector2 wektor);

int WInterwale(float t);

int Manhatan(PozycjaNaMapie A, PozycjaNaMapie B);

int Koszt(const PozycjaNaMapie& A, const PozycjaNaMapie& B);

//konwersja rodzicza na wektor

PozycjaNaMapie RodzicPozycja(const unsigned int& Rodzic, const unsigned int& szerokosc);

unsigned int PozycjaRodzic(const PozycjaNaMapie& poz, const unsigned int& szerokosc);

void NarysujKwadrat(KolorowyKwadrat& kwadrat, const int& rozmiar);

//Zamienia z ujemnych na dodatnie od 0 do 180 zamienia na odpowiednio 180 do 360
float KonwersjaKatow(float Kat);
float OdwrocenieKonta(float Kat,bool WKtoraStrone);

float IloczynSkalarny(Vector2 A, Vector2 B);
float IloczynWektorowy(Vector2 A, Vector2 B);

//Sluzy donarysowanie siatki sluzy do przedstawienia ilosci elementow na danym polu

void NarysujSiatke(std::vector<std::vector<unsigned int>>& Klatki,  int RozmiarSystemu,  int RozmiarKlatki,Color ZObiektem,Color BezObiektu);


#endif // !FUNKCJE_H