#pragma once

#ifndef SYSTEM_ZAJMOWANIA

#include <DyrektywyDebugowania.h>
#include "Obiekt.h"
#include <vector>
#include <unordered_map>
#include <array>
#include <raylib.h>
#include "Funkcje.h"


class SystemZajmowaniaSojuszy
{
	bool StanInicjacji;

	unsigned int RozmiarSystemu;
	unsigned int RozmiarKlatek;

	std::vector<std::array<Vector2,4>> TablicaPunktyTerenu;
	std::vector<Druzyny> TablicaDruzynyZajmujaceTeren;
	std::vector<std::vector<unsigned int>> TablicaZmapowaneTereny;
	std::vector<std::unordered_map<Druzyny,std::vector<unsigned int>>> TablicaIloscObiektowDanejDruzyny;
	std::vector<unsigned int> TablicaPrzychody;
	std::vector<unsigned int> TablicaZajmowanieTick;
	std::vector<unsigned int> TablicaZajmowanieCzasZajmowania;
#ifdef SYSTEM_ZAJMOWANIA
	std::vector<KolorowyKwadrat> Kolorowe;
#endif // !SYSTEM_ZAJMOWANIA

	//Funkcje Inline

	inline unsigned int ZwrocIndex(unsigned int x, unsigned int y)
	{ 
		return x + (y * RozmiarSystemu); 
	};
	inline bool CzyMozeOdczytac(unsigned int x, unsigned int y) 
	{
#ifdef SYSTEM_ZAJMOWANIA
		if (StanInicjacji == false)
		{
			std::cout << "Systemu Zajmowania Nie Zainicjowanao \n";
		}
#endif // !SYSTEM_ZAJMOWANIA

		return (x < RozmiarSystemu && y < RozmiarSystemu && StanInicjacji == true);
	};


	void RozpocznijZajmowanie(unsigned int x,unsigned int y);
	

public:

	void UstawRozmiarSystemu(unsigned int RozmiarSystemu);
	void UstawRozmiarKlatek(unsigned int RozmiarKlatek);
	void UstawDruzyne(unsigned int x,unsigned int y, Druzyny druzyna);
	void UstawPrzychod(unsigned int x, unsigned int y, unsigned int Przychod);
	void UstawCzasZajmowania(unsigned int x, unsigned int y, unsigned int CzasZajmowania);
	void UstawTick(unsigned int x, unsigned int y, unsigned int Tick);

	unsigned int ZwrocRozmiarSystemu();
	unsigned int ZwrocRozmiarKlatek();
	Druzyny ZwrocDruzyne(unsigned int x,unsigned int y);
	unsigned int ZwrocPrzychod(unsigned int x,unsigned int y);
	unsigned int ZwrocCzasZajmowania(unsigned int x, unsigned int y);
	unsigned int ZwrocTick(unsigned int x, unsigned int y);

	//Zwraca Zbiotry

	unsigned int ZwrocIloscObiektowDruzyny(Druzyny druzyna, unsigned int x, unsigned int y);
	const std::vector<unsigned int> * ZwrocTabliceObiektow(Druzyny druzyna,unsigned int x,unsigned int y);

	void GenerujSystem(CzasLogiki& czasLogik);
	void ZmapujObiekty(std::vector<Obiekt*> &Obiekty);
	void Logika(std::vector<Obiekt*> &Obiekty,CzasLogiki &Czas);
	
	
	
	


};


#endif // !SYSTEM_ZAJMOWANIA

