#pragma once

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <raylib.h>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include "Kolory.h"
#include <iostream>
#include <string>
#include "CzasLogiki.h"
#include "PozycjeNaMapie.h"
#include <filesystem>
#include <fstream>
#include <Wczytywacz/WczytywaczOI.h>




enum TypPola
{
	ZAMKNIENTE,
	OTWARTE,
	NIEISTNIEJIE,
};


class TeksturaTileSet
{
	
	unsigned int IloscKlatek;
	bool CzyZajente;
public:
	Texture tekstura;
	TeksturaTileSet(bool CzyZajente,std::filesystem::path Sciezka, unsigned int &Rozmiar);

	void UstawCzyZajente(bool CzyZajente);

	Rectangle ZwrocWymiary( unsigned int &Rozmiar,unsigned int IndexKlatki);
	unsigned int ZwrocIloscKlatek();
	bool ZwrocCzyZajente();

};

void StworzTileSet(std::filesystem::path Sciezka, std::string NazwaFolderu, unsigned int LiczbaTileSetow, unsigned int RozmiarKlatki);

class jakaTekstura
{
	unsigned int IndexTekstury;
	unsigned int Klatka;
public:
	jakaTekstura(unsigned int IndexTekstury, unsigned int Klatka);
	jakaTekstura operator=(const jakaTekstura& tekstura);

	void UstawIndexTekstury(unsigned int IndexTekstury,std::vector<TeksturaTileSet> &TeksturyTileSet);
	void UstawKlatke(unsigned int Klatka, std::vector<TeksturaTileSet>& TeksturyTileSet);

	unsigned int ZwrocIndexTekstury();
	unsigned int ZwrocKlatke();

};


class Mapa
{
	unsigned int szerokosc;
	unsigned int wysokosc;
	unsigned int RozmiarKlatki;


	std::vector<TeksturaTileSet> tekstury;
	std::vector<jakaTekstura> Jakie;

	std::vector<TypPola> Pola;
	std::vector<PozycjaWCzasie> PozycjeCzasowe;

	bool WMapie(const PozycjaNaMapie& poz);

	//Odpowiada za Tekstury

	void ZaladujTekstury(std::filesystem::path Folder);
	void UstawTileSet(const PozycjaNaMapie& poz, unsigned int IndexTekstury);
	void RenderujTileSet(PozycjaNaMapie poz);

	void NarysujZablokownaPozycje(PozycjaNaMapie poz);

public:


	Mapa(std::filesystem::path TileSety="", unsigned int RozmiarKlatki = 100);
	void StworzMape(unsigned int szerokosc, unsigned int wysokosc,const std::vector<PozycjaNaMapie> &PozycjeZajente={});

	Vector2 Wysrodkuj(PozycjaNaMapie poz);

	Vector2 SrodekPola(PozycjaNaMapie pozycja);
	PozycjaNaMapie Kordynat(Vector2 wektor);

	//Dotyczy pozycji czasowych

	

	void UstawPozycjeWchodzaca(PozycjaNaMapie pozycja,unsigned int wchodzacy,const unsigned int &IndexObiektu);
	void UstawPozycjeWychodzaca(PozycjaNaMapie pozycja, unsigned int wychodzacy,const unsigned int &IndexObiektu);
	void UstawTypPola(const PozycjaNaMapie poz, TypPola typ);

	bool CzyPozycjaZajenta(PozycjaNaMapie poz);
	bool CzyPozycjaZajentaWCzasie(PozycjaNaMapie poz,unsigned int const Tick);

	bool CzyPozycjaZajentaWCzasieDlaObiektu(PozycjaNaMapie poz,unsigned int const Tick,const unsigned int IndexObiektu);
	
	bool CzyPozyjaZajentaWNieskonczonosc(PozycjaNaMapie poz);
	bool CzyPozyjaZajentaWNieskonczonoscDlaObiektu(PozycjaNaMapie poz,unsigned int indexObiektu);

	void UsunPozycjeWCzasie(const unsigned int Tick);

	void UsunPozycjeCzasoweDlaObiektu(unsigned int IndexObiektu);

	/// 

	unsigned int ZwrocSzerokosc();
	unsigned int ZwrocWysokosc();
	unsigned int ZwrocRozmiarKlatki();
	
	void UstawSzerokosc(unsigned int szerokosc);
	void UstawWysokosc(unsigned int wysokosc);
	void UstawRozmiarKlatki(unsigned int RozmiarKlatki);


	TypPola ZwrocTypPola(const PozycjaNaMapie &poz);

	void Wizualizacja(CzasLogiki& czaslogiki);
};

#endif // !MAPA_H


