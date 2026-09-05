#pragma once

#ifndef OBIEKT_H
#define OBIEKT_H



#include <raylib.h>
#include <algorithm>
#include <string>
#include "Zasob.h"
#include "Mapa.h"
#include "CzasLogiki.h"
#include "Funkcje.h"
#include "SystemObrazen.h"
#include "Sojusze.h"
#include "PodstawaSystemu.h"



#define LICZBA_PI 3.141592f

//Zdefiniowane Druzyny

 
// Pociskow druzyna nie dziala na nia system namierzania jaki system obrazen












class SystemNamierzania;
class ParametryPociskow;
class TablicaAnimacji;
class Obiekt
{
protected:


	Vector2 pozycjapoprzednia;
	Vector2 pozycja;
	PlayerAnimacji player;
	unsigned int Zdrowie;
	Sojusze sojusze;
	Typy typ;
	unsigned int IndexObiektu;
	bool CzyZyje=true;
	void UstawIndexObiektu(std::vector<Obiekt*>& Obiekty);

public:
	virtual  ~Obiekt() = default;
	
	Obiekt( Vector2 pozycja = {}, unsigned int Zdrowie = 100,Sojusze sojusz={Druzyny::NEUTRALNA,Druzyny::NEUTRALNA},Typy typ=Typy::ZADEN);
	Obiekt(std::string NazwaAnimacji , Vector2 pozycja , unsigned int Zdrowie , Sojusze sojusz, Typy typ,std::vector<Obiekt*> &Obiekty,TablicaAnimacji &tablica );
	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& systemobrazen, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty);
	virtual void Render(Mapa& mapa,CzasLogiki &czasLogiki,TablicaAnimacji &tablica);

	// This command allow us for own terms of deleting the object from the engine and it saves all deleted object from the current state to the table
	virtual void SprawdzCzyUsunObiekt(std::vector<unsigned int> &IndexyUsuwanych);

	PlayerAnimacji * ZwrocPlayerAnimacji();
	Animacja* ZwrocAnimacje();
	ZestawAnimacji * ZwrocZestawAnimacji();

	virtual bool ZwrocCzySkonczyloSieRuszac();

	unsigned int ZwrocIndexObiektu();
	unsigned int ZwrocZdrowie();
	Sojusze ZwrocSojusz();
	Typy ZwrocTypy();
	bool ZwrocCzyZyje();
	Vector2 ZwrocPozycje();
	Vector2 ZwrocPoprzedniaPozycje();
	virtual bool ZwrocCzyZaktualizowacSystemy();

	void UstawZdrowie(unsigned int Zdrowie);
	void UstawSojusze(Druzyny wlasciciel,Druzyny sojusz);
	void UstawTypy(Typy typ);
	void UstawCzyZyje(bool CzyZyje);
	void UstawPozycje(Vector2 pozycja);
	void UstawPozycjePoprzednia(Vector2 pozycjapoprzednia);
	
	bool operator== (Obiekt*& obiekt);
	bool operator!=(Obiekt*& obiekt);

	//Do usuniencia

	friend class Bron;
	friend class Damage;
	friend class DamageKolo;
	friend class DamageProstokat;
	friend class SystemObrazen;
	friend class SystemNamierzania;
	friend class Pocisk;
	friend class PociskKierowany;
	friend class Gra;
	friend void MapowanieObiektow(std::vector<Obiekt*>& Obiekty, std::vector<std::vector<unsigned int>> &KlatkiSystemu, unsigned int RozmiarKlatek, unsigned int RozmiarSystemu, Typy typ);
	friend Obiekt* ZwrocObiekt(unsigned indexObiektu, std::vector<Obiekt*>& Obiekty);

	//Do usuniencia
};
// ---------------------------------------
Obiekt* ZwrocObiekt(unsigned indexObiektu, std::vector<Obiekt*>& Obiekty);


// ---------------------------
class Ruch
{
	Vector2 PunktA;
	Vector2 PunktB;
	float procent; // jako od 0 do 1


public:

	Ruch(Vector2 PunktA = { std::numeric_limits<float>::infinity() }, Vector2 PunktB = { std::numeric_limits<float>::infinity() });

	friend class Agent;
	friend class Pocisk;

	void ZdefiniujRuch(Vector2 PunktA, Vector2 PunktB, Vector2& Pozycja);

	float CzasTrwaniaRuchu(const float& predkosc);
	float PozostalyCzas(const float& predkosc);

	void ZmienPozycje(Vector2& Pozycja);
	void Porusz(float Predkosc, Vector2& Pozycja);



	bool Dotarlo();
};

//
enum  StanRuchu
{
	PRZEDOBROTEM,
	ZAOBROTEM,
	NATRAJEKTORI
	

};




//------------------------------------------
class RuchPoOkregu
{
	
	Vector2 Cel;
	float kat;
	StanRuchu stanruchu;
	float Promien;
	Vector2 Predkosc;

	KierunkiSwiata ZwrocKierunek();
public:

	RuchPoOkregu(Vector2 Cel={0,0}, float kat=0, float Promien=10, float Predkosc=2);
	void Ustaw(float kat, float Predkosc,Vector2 &Pozycja,Vector2 Cel,float Promien);
	void UstawCel(Vector2 Cel);
	
	void Ruch(Vector2 &Pozycja,KierunkiSwiata &kierunekSwiata,CzasLogiki &czasLogiki);
	StanRuchu ZwrocStanRuchu();

};
//

void MapowanieObiektow(std::vector<Obiekt*>& Obiekty, std::vector<std::vector<unsigned int>> &KlatkiSystemu, unsigned int RozmiarKlatek, unsigned int RozmiarSystemu,Typy typ);


#endif // !OBIEKT_H

