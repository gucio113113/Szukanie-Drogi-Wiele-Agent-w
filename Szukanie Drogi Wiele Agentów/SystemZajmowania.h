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

/*
struct ProcesZajmowania
{
	Druzyny druzyna;
	unsigned int Tick;
	unsigned int TickZajmowania;
	ProcesZajmowania();
};
*/


class SystemZajmowaniaSojuszy : public PodstawaSystemu
{

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
		ILOSCOBIEKTOW_DEBUG
	};
	PokazWartosciDebug pokazwartoscidebug=PokazWartosciDebug::ILOSCOBIEKTOW_DEBUG;


#endif // SYSTEM_ZAJMOWANIA_DEBUG

	void RozpocznijZajmowanie(unsigned int x,unsigned int y);
#ifdef SYSTEM_ZAJMOWANIA_DEBUG


	Vector2 ZwrocSrodekCzworokata(std::array<Vector2,4> &Tablica);

	void NarysujDebug(unsigned int x,unsigned int y);
#endif // SYSTEM_ZAJMOWANIA_DEBUG

	float ZwrocPoleCzworokata(std::array<Vector2, 4>& Tablica);

public:

	SystemZajmowaniaSojuszy(unsigned int RozmiarSystemu=5, unsigned int RozmiarKlatek=200);


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

	void ZmapujObiekt(const unsigned int IndexObiektu, const bool CzyZaktualizowac, const Vector2 Pozycja, const Vector2 PoprzedniaPozycja,const Typy TypObiektu) override;

	void Logika(std::vector<Obiekt*> &Obiekty,CzasLogiki &Czas);
	
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
	void Debug();
#endif // SYSTEM_ZAJMOWANIA_DEBUG

	
	
	
	


};


#endif // !SYSTEM_ZAJMOWANIA

