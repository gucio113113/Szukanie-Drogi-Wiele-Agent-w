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
// Do decyzji 
enum class Bodziec : unsigned char
{
	WYKRYTO_PRZECZWNIKA = 0b00000001,
	PODOSTRZALEM = 0b00000010,
	ZAJMUJETEREN = 0b00000100
};
inline constexpr Bodziec operator|(Bodziec a, Bodziec b) {
	return static_cast<Bodziec>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}
inline constexpr Bodziec operator&(Bodziec a, Bodziec b) {
	return static_cast<Bodziec>(static_cast<unsigned char>(a) & static_cast<unsigned char>(b));
}
inline constexpr bool operator!(Bodziec a) {
	return static_cast<unsigned char>(a) == 0;
}
enum class Decyzje : unsigned char
{
	IDZ_POLNOC = 0,
	IDZ_POLNOC_WSCHOD = 1,
	IDZ_WSCHOD = 2,
	IDZ_POLUDNIE_WSCHOD = 3,
	IDZ_POLUDNIE = 4,
	IDZ_POLUDNIE_ZACHOD = 5,
	IDZ_ZACHOD = 6,
	IDZ_POLNOC_ZACHOD = 7,
	STOJ = 8,
	STRZELAJ = 9
};
inline constexpr Decyzje  ZwrocDecyzje(KierunkiSwiata kierunek)
{
	switch (kierunek)
	{
	case KierunkiSwiata::POLUDNIE: return Decyzje::IDZ_POLUDNIE;
		break;
	case KierunkiSwiata::ZACHOD: return Decyzje::IDZ_ZACHOD;
		break;
	case KierunkiSwiata::POLNOC: return Decyzje::IDZ_POLNOC;
		break;
	case KierunkiSwiata::WSCHOD: return Decyzje::IDZ_WSCHOD;
		break;
	case KierunkiSwiata::POLNOC_ZACHOD: return Decyzje::IDZ_POLNOC_ZACHOD;
		break;
	case KierunkiSwiata::POLNOC_WSCHOD: return Decyzje::IDZ_POLNOC_WSCHOD;
		break;
	case KierunkiSwiata::POLUDNIE_WSCHOD: return Decyzje::IDZ_POLUDNIE_WSCHOD;
		break;
	case KierunkiSwiata::POLUDNIE_ZACHOD: return Decyzje::IDZ_POLUDNIE_ZACHOD;
		break;
	case KierunkiSwiata::ZADEN: return Decyzje::STOJ;
		break;
	default:
		break;
	}
}
enum class Rozkazy : unsigned char
{
	IDZ = 0,
	ATAKUJACY_RUCH = 1,
	UNIKAJ = 2,
	ZNISZCZ=3,
	PILNUJ=4
};
struct DecyzjaWCzasie
{
	unsigned int Tick;
	unsigned int CzasTrwania;
	bool Spelniona;
	Decyzje decyzja;
	DecyzjaWCzasie();
};

// 2026 - 08 - 31
//Trzeba cale te funkcje dac d o agenta i nadpisac logike odpowiadajaca za poruszanie sie 













// ------------------------

class Agent : public Obiekt
{
protected:
	float Predkosc;
	

	//bool DotarloDoGlownego;

	Color kolor;

	Ruch ruch;

	
	//Do Strzelania

	Bron bron;

	//Do Rozkazow oraz decyzji
	Rozkazy rozkaz;
	DecyzjaWCzasie decyzjaWCzasie;
	Bodziec bodziec;

	//Odpowiada Za ruch jaki decyzje Agenta

	void WykryjBodzcze( SystemNamierzania& systemnamierzania, SystemObrazen& systemObrazen, Mapa& mapa, std::vector<Obiekt*>& Obiekty, std::vector<unsigned int>& Namierzane);
	void UstawRuch( CzasLogiki& czasLogiki, Mapa& mapa);
	void DecyzjeOChodzeniu(CzasLogiki& czaslogiki, Mapa& mapa, SystemNamierzania& SystemNamierzania, SystemObrazen& SystemObrazen, ParametryPociskow& parametry, std::vector<Obiekt*>& Obiekty, TablicaAnimacji& tablica);
public:
	void WydajRozkaz(Rozkazy rozkaz,Vector2 CelGlobalny,Mapa &mapa,CzasLogiki &czaslogiki);
protected:


	//


	

	

	//Pozycja Posrednia w czasie


	Vector2 CelLokalny;

	//Sluzy do szukanaioa pozycji w czasie
	Vector2 CelGlobalny;

	std::queue<PozycjaNaMapie> droga;
#ifdef AGENT_DEBUG
	std::vector<KolorowyKwadrat> KoloroweKwadraty;
#endif
	bool Rezerwacja(std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, Mapa& mapa,CzasLogiki &Czaslogiki);

	//Metody Szukania drogi

	KlatkaRuchu ZwrocMinimalne(std::vector<KlatkaRuchu>& Otwarte);

	KlatkaCelu ZwrocMinimalne(std::vector<KlatkaCelu>& Klatki);

	//Gdy juz jest roszeszone i droga znalezione ponisza funkcja tworzy droge

	virtual void SzukanieDrogi(PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, Mapa& mapa, CzasLogiki& czaslogiki);

	//Ponisza funkcja po znalezieniu juz drogi tworzy pozycje czasowe

	virtual void ZajmowaniePozycjiCzasowych(PozycjaNaMapie& Poczatek, CzasLogiki& czaslogiki, Mapa& mapa);

	//Ponisza funkcja ponownie wyszukuje cel w celu dotarcia do celu glownego
	bool ZnajdywaniePonowne(Mapa &mapa,CzasLogiki &czaslogiki);

	//Gdy Droga jest znaleziona ponisza funkcja bedzie szukac trasy z do Celu
	void WykonanieDrogiWlasciwe(Mapa &mapa,CzasLogiki &czaslogiki);


	//Wybiera Najmniejsza Klatke o najkmniejsse jlicx zbie krokow i robi tam eskpansje

	void Roszerz(Mapa& mapa, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& docelu, bool& SzukajDrogi, CzasLogiki& czasLogiki);

	// Wybiera Klatke otwarta o najniszejLiczbieKrokow

	void NajbliszyCel(bool& Znaleziono, Vector2 Poczatek, Vector2& ZwracanyCel, Mapa& mapa, CzasLogiki& czaslogiki);
	//metody ruchu

public:


	Agent(Vector2 Pozycja,std::string NazwaTekstury,  Color kolor, float Predkosc,unsigned int Zdrowie,Sojusze sojusz);
	Agent(Vector2 Pozycja, std::string NazwaTekstury, Color kolor, float Predkosc, unsigned int Zdrowie, Sojusze sojusz,std::vector<Obiekt*> Obiekty,TablicaAnimacji &tablica);

	friend void ZnajdzDroge();
	friend void WypiszInformacje(Agent& agent, Mapa& mapa);
	friend void DecyzjeOChodzeniu(Agent*& agent, Rozkazy& rozkaz, DecyzjaWCzasie& DecyzjaWCzasie, float& predkosc, CzasLogiki& czaslogiki, Bodziec& bodziec, Mapa& mapa, SystemNamierzania& SystemNamierzania, SystemObrazen& SystemObrazen);
	void AlgorytmDrogi(Mapa& mapa, CzasLogiki& czaslogiki);

	void ZnajdzCelLokalny(Mapa& mapa, CzasLogiki& czaslogiki);
	void UstawGlownyCel(Vector2 GlownyCel, Mapa& mapa, CzasLogiki& czaslogiki);




	//wizualizajca drogi Agenta
#ifdef  AGENT_DEBUG
	void WizuDrogi(Mapa& mapa);
#endif // AGENT_DEBUG
	virtual void WykonujDroge(Mapa& mapa, CzasLogiki& czaslogiki);

	
	

	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& systemobrazen, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica,std::vector<Obiekt*> &Obiekty) override;

	virtual void Render(Mapa& mapa,CzasLogiki& czasLogiki, TablicaAnimacji& tablica) override;
};


#endif // !AGENT_H