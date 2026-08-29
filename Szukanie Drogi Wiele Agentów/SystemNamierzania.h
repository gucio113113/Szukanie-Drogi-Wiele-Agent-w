#pragma once
#include "Obiekt.h"
#include "PozycjeNaMapie.h"
#include <vector>
#include "Mapa.h"
#include "Funkcje.h"


class SystemNamierzania
{

	std::vector<std::vector<unsigned int>> System;
	unsigned int rozmiarKlatki;
	unsigned int rozmiarSystemu;

	bool PozycjaWSystemie(PozycjaNaMapie& poz);

	void CzyMozeNamierzyc(Obiekt*& obiekt1, Obiekt*& obiekt2, float& Zasieg, std::vector<unsigned int>& Celowe, Mapa& mapa);

public:
	SystemNamierzania(unsigned int rozmiarKlatki=100,unsigned int rozmiarSystemu=100);
	
	void UstawParametry(unsigned int rozmiarSystemu,Mapa &mapa);
	void UstawSystem(std::vector<Obiekt*> &Obiekty);
	void ZwrocSpelniajaceZasieg(unsigned int indexObiektu,float Zasieg,std::vector<unsigned int> &ListaObiektow,std::vector<Obiekt*> &Obiekty,Mapa &mapa);
	#ifdef SYSTEMNAMIERZANIA_DEBUG
	void Debug();
	#endif
};

