#pragma once

#ifndef SYSTEM_ZAJMOWANIA

#include <DyrektywyDebugowania.h>
#include "Obiekt.h"
#include <vector>
#include <unordered_map>
#include <array>
#include <raylib.h>
#include "Funkcje.h"
#include <generator>
#include "CzasLogiki.h"
#include "PodstawaSystemu.h"


class SystemZajmowaniaSojuszy : public PodstawaSystemu
{
	bool StanInicjacji;

	std::vector<std::array<Vector2,4>> TablicaPunktyTerenu;
	std::vector<Druzyny> TablicaDruzynyZajmujaceTeren;
	std::vector<std::vector<unsigned int>> TablicaZmapowaneTereny;
	std::vector<unsigned int> TablicaPrzychody;
	std::vector<unsigned int> TablicaZajmowanieTick;
	std::vector<unsigned int> TablicaZajmowanieCzasZajmowania;

#ifdef SYSTEM_ZAJMOWANIA_DEBUG
	std::vector<Vector2> LosowePunkciki;
	enum class PokazWartosciDebug : unsigned char
	{
		PRZYCHOD_DEBUG,
		ZAJMOWANIA_TICK_DEBUG,
		ZAJMOWANIA_CZASZAJMOWANIA_DEBUG,
		ZMAPOWANY_TEREN_DEBUG,
		ILOSCOBIEKTOW_DANEJ_DRUZYNY_DEBUG
	};
	PokazWartosciDebug pokazwartoscidebug=PokazWartosciDebug::ILOSCOBIEKTOW_DANEJ_DRUZYNY_DEBUG;


#endif // SYSTEM_ZAJMOWANIA_DEBUG

	void RozpocznijZajmowanie(unsigned int x,unsigned int y);
	
	void ZmapujObiekty(std::vector<Obiekt*>& Obiekty);
	void OdMapujObiekty();



public:

	SystemZajmowaniaSojuszy(unsigned int RozmiarSystemu=20, unsigned int RozmiarKlatek=50);


	//void DopasujDoRozmiarow(unsigned int RozmiarMapy);

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

	unsigned int ZwrocIloscObiektowDruzyny(std::vector<Obiekt*> &Obiekty,Druzyny druzyna, unsigned int x, unsigned int y);
	std::vector<unsigned int>  ZwrocTabliceObiektow(std::vector<Obiekt*> &Obiekty,Druzyny druzyna,unsigned int x,unsigned int y);

	void GenerujSystem(const unsigned int TickRate);

	void Logika(std::vector<Obiekt*> &Obiekty,CzasLogiki &Czas);
	
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
	void Debug();
#endif // SYSTEM_ZAJMOWANIA_DEBUG

	
	
	
	


};


#endif // !SYSTEM_ZAJMOWANIA

