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
	Texture tekstura;
	unsigned int IloscKlatek;
	bool Zajente;
public:
	friend class Mapa;
	friend class JakaTekstura;
	TeksturaTileSet(bool Zajente,std::filesystem::path Sciezka, unsigned int &Rozmiar);
	Rectangle ZwrocWymiary( unsigned int &Rozmiar,unsigned int IndexKlatki);
	unsigned int ZwrocIloscKlatek();

};

void StworzTileSet(std::filesystem::path Sciezka, std::string NazwaFolderu, unsigned int LiczbaTileSetow, unsigned int RozmiarKlatki);

class jakaTekstura
{
public:
	unsigned int indexTekstury;
	unsigned int Klatka;
	jakaTekstura(unsigned int indexTekstury, unsigned int Klatka);
	jakaTekstura operator=(const jakaTekstura& tekstura);
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
	void UstawTypPola(const PozycjaNaMapie& poz, TypPola typ);

	//Odpowiada za Tekstury

	void ZaladujTekstury(std::filesystem::path Folder);
	void UstawTileSet(const PozycjaNaMapie& poz, unsigned int IndexTekstury);
	void RenderujTileSet(PozycjaNaMapie poz);

	void NarysujZablokownaPozycje(PozycjaNaMapie poz);

public:
	friend class Obiekt;
	friend class Pocisk;
	friend class Agent;
	friend class SystemNamierzania;
	friend class Gra;
	friend class Damage;
	friend class DamageKolo;
	friend class DamageProstokat;
	friend class SystemObrazen;
	friend class GraczISter;
	

	friend void WypiszInformacje(Agent& agent, Mapa& mapa);

	Mapa(std::filesystem::path TileSety="", unsigned int RozmiarKlatki = 100);
	void StworzMape(unsigned int szerokosc, unsigned int wysokosc,const std::vector<PozycjaNaMapie> &PozycjeZajente={});

	Vector2 Wysrodkuj(PozycjaNaMapie poz);

	Vector2 SrodekPola(PozycjaNaMapie pozycja);
	PozycjaNaMapie Kordynat(Vector2 wektor);

	//Dotyczy pozycji czasowych

	

	void ustawPozycjeWchodzaca(PozycjaNaMapie pozycja,unsigned int wchodzacy,const unsigned int &IndexObiektu);
	void ustawPozycjeWychodzaca(PozycjaNaMapie pozycja, unsigned int wychodzacy,const unsigned int &IndexObiektu);

	bool CzyPozycjaZajenta(PozycjaNaMapie poz);

	bool czyPozycjaZajentaWCzasie(PozycjaNaMapie poz,unsigned int const Tick);

	bool CzyPozyjaZajentaWNieskonczonosc(PozycjaNaMapie poz);
	bool CzyPozyjaZajentaWNieskonczonosc(PozycjaNaMapie poz,unsigned int indexObiektu);

	void UsunPozycjeWCzasie(const unsigned int Tick);

	void UsunPozycjeCzasoweDlaObiektu(unsigned int IndexObiektu);

	/// 
	

	TypPola ZwrocTypPola(const PozycjaNaMapie &poz);
	void Wizualizacja(CzasLogiki& czaslogiki);
};

#endif // !MAPA_H


