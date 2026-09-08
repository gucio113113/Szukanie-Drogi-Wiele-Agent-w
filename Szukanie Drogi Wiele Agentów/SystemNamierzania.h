#pragma once
#include "Obiekt.h"
#include "PozycjeNaMapie.h"
#include <vector>
#include "Mapa.h"
#include "Funkcje.h"
#include <DyrektywyDebugowania.h>
#include "PodstawaSystemu.h"


class SystemNamierzania : public PodstawaSystemu
{




	void CzyMozeNamierzyc(Obiekt*& obiekt1, Obiekt*& obiekt2, float& Zasieg, std::vector<unsigned int>& Celowe, Mapa& mapa);

public:
	SystemNamierzania(unsigned int RozmiarMapy=1000,unsigned int RozmiarSystemu=10);
	
	void LogikaSystemuNamierzania(std::vector<Obiekt*> &Obiekty);

	void ZwrocSpelniajaceZasieg(unsigned int indexObiektu,float Zasieg,std::vector<unsigned int> &ListaObiektow,std::vector<Obiekt*> &Obiekty,Mapa &mapa);
	#ifdef SYSTEMNAMIERZANIA_DEBUG
	void Debug();
	#endif
};

