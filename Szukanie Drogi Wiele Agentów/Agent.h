#pragma once

// -----------------------------

#ifndef AGENT_H
#define AGENT_H


#include <raylib.h>
#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>
#include "PozycjeNaMapie.h"
#include "CzasLogiki.h"
#include "Funkcje.h"
#include "Mapa.h"
//#include "Obiekt.h"
#include "Bron.h"





struct KlatkaRuchu
{
	PozycjaNaMapie pozycja;
	unsigned int Rodzic;
	int kosztG;
	int kosztH;
	unsigned int Tick;
	KlatkaRuchu(PozycjaNaMapie poz = { 0,0 }, unsigned int Rodzic = std::numeric_limits<unsigned int>::infinity(), int kosztG = std::numeric_limits<int>::infinity(), int kosztH = std::numeric_limits<int>::infinity(),unsigned int Tick=std::numeric_limits<unsigned int>::infinity() );

	bool operator==(const KlatkaRuchu& klatka);
	bool operator>(const KlatkaRuchu& klatka);
	KlatkaRuchu operator=(const KlatkaRuchu& klatka);
	//bool operator(const KlatkaRuchu& klatka);
	void WypiszKlatkeRuchu();
};

void Szukanaklatka(PozycjaNaMapie pozycja, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, KlatkaRuchu& klatkaruchu);

// sluzy do wskaznania pozycji najbliszej celu
struct KlatkaCelu
{
	PozycjaNaMapie poz;
	unsigned int KosztH;
	KlatkaCelu(PozycjaNaMapie poz, unsigned int KosztH);

	bool operator>(const KlatkaCelu& koszt);

	bool operator==(const KlatkaCelu& koszt);

	KlatkaCelu operator=(const KlatkaCelu& koszt);



};




// ------------------------

class Agent : public Obiekt
{
	float Predkosc;
	

	//bool DotarloDoGlownego;

	Color kolor;

	Ruch ruch;

	
	//Do Strzelania

	Bron bron;



	

	//Pozycja Posrednia w czasie


	Vector2 CelLokalny;

	//Sluzy do szukanaioa pozycji w czasie
	Vector2 CelGlobalny;

	std::queue<PozycjaNaMapie> droga;

	std::vector<KolorowyKwadrat> KoloroweKwadraty;

	bool Rezerwacja(std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, Mapa& mapa,CzasLogiki &Czaslogiki);

	//Metody Szukania drogi

	KlatkaRuchu ZwrocMinimalne(std::vector<KlatkaRuchu>& Otwarte);

	KlatkaCelu ZwrocMinimalne(std::vector<KlatkaCelu>& Klatki);

	//Gdy juz jest roszeszone i droga znalezione ponisza funkcja tworzy droge

	virtual void SzukanieDrogi(PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, Mapa& mapa, CzasLogiki& czaslogiki);

	//Ponisza funkcja po znalezieniu juz drogi tworzy pozycje czasowe

	virtual void ZajmowaniePozycjiCzasowych(PozycjaNaMapie& Poczatek, CzasLogiki& czaslogiki, Mapa& mapa);


	//Wybiera Najmniejsza Klatke o najkmniejsse jlicx zbie krokow i robi tam eskpansje

	void Roszerz(Mapa& mapa, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& docelu, bool& SzukajDrogi, CzasLogiki& czasLogiki);

	// Wybiera Klatke otwarta o najniszejLiczbieKrokow

	void NajbliszyCel(bool& Znaleziono, Vector2 Poczatek, Vector2& ZwracanyCel, Mapa& mapa, CzasLogiki& czaslogiki);
	//metody ruchu

	void PoruszPierwszy(PozycjaNaMapie pozycjaA, PozycjaNaMapie pozycjaB, Mapa& mapa);
	void PoruszDrugi(PozycjaNaMapie pozycjaA, PozycjaNaMapie pozycjaB, Mapa& mapa);

public:


	Agent(Vector2 Pozycja,std::string NazwaTekstury,  Color kolor, float Predkosc,unsigned int Zdrowie,unsigned int Druzyna);
	Agent(Vector2 Pozycja, std::string NazwaTekstury, Color kolor, float Predkosc, unsigned int Zdrowie, unsigned int Druzyna,std::vector<Obiekt*> Obiekty,TablicaAnimacji &tablica);

	friend void ZnajdzDroge();
	friend void WypiszInformacje(Agent& agent, Mapa& mapa);

	void AlgorytmDrogi(Mapa& mapa, CzasLogiki& czaslogiki);

	void ZnajdzCelLokalny(Mapa& mapa, CzasLogiki& czaslogiki);

	void UstawGlownyCel(Vector2 GlownyCel, Mapa& mapa, CzasLogiki& czaslogiki);

	//wizualizajca drogi Agenta
	void WizuDrogi(Mapa& mapa);

	virtual void WykonujDroge(Mapa& mapa, CzasLogiki& czaslogiki);


	

	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica,std::vector<Obiekt*> &Obiekty) override;

	virtual void Render(Mapa& mapa,CzasLogiki& czasLogiki, TablicaAnimacji& tablica) override;
};


#endif // !AGENT_H