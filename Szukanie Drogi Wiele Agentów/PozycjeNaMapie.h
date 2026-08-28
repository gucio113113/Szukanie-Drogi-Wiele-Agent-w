#pragma once

#ifndef POZYCJENAMAPIE_H
#define POZYCJENAMAPIE_H

#include <raylib.h>
#include <limits>





struct PozycjaNaMapie
{
	int x;
	int y;
	PozycjaNaMapie(int x = 0, int y = 0);
	bool operator==(const PozycjaNaMapie& poz);
	bool operator!=(const PozycjaNaMapie& poz);
	PozycjaNaMapie operator = (const PozycjaNaMapie& poz);
	void operator += (const PozycjaNaMapie& poz);
	void operator -= (const PozycjaNaMapie& poz);
	PozycjaNaMapie operator=(const Vector2 wektor);
};
struct PozycjaWCzasie
{
	PozycjaNaMapie poz;
	unsigned int wejscie;
	unsigned int wyjscie;
	unsigned int IndexObiektu;

	PozycjaWCzasie(PozycjaNaMapie poz = { 0,0 }, unsigned int wejscie = std::numeric_limits<unsigned int>::infinity(), unsigned int wyjscie = std::numeric_limits<unsigned int>::infinity(),unsigned int IndexObiektu=std::numeric_limits<unsigned int>::infinity() );

	bool wTymCzasie(const unsigned int& Tick);

	bool operator==(const PozycjaWCzasie& poz);
	PozycjaWCzasie operator = (const PozycjaWCzasie& poz);
};

#endif // !POZYCJENAMAPIE_H
