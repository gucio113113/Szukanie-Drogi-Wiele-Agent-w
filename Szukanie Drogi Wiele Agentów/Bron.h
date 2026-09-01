#pragma once

#ifndef BRON_H
#define BRON_H



#include <raylib.h>
#include <unordered_map>
#include <string>
#include "Zasob.h"
#include <numeric>
#include "Obiekt.h"
#include <iostream>
#include "SystemNamierzania.h"
#include <DyrektywyDebugowania.h>

enum class TypPocisku : unsigned char
{
	RAKIETA=0,
	RAKIETA_NAPROWADZAJACA,
	POCISK,
	BOMBA,
	NABOJ
};
std::ostream& operator<<(std::ostream& os, const TypPocisku& typ);

class ParametrPocisk
{
public:
	unsigned int Zdrowie;
	std::string NazwaTekstury;
	float Predkosc;
	bool StatycznyCel;
	float Promien;
	unsigned int TickZycia;
	Damage* damage;
	ParametrPocisk(unsigned int Zdrowie,std::string NazwaTekstury,float Predkosc,bool StatycznyCel,float Promien,unsigned int TickZycia, Damage* damage);
#ifdef ZASOBY_DEBUG
	void WyswietlParametry();
#endif // ZASOBY_DEBUG
};
class Pocisk;
class ParametryPociskow
{
	std::unordered_map<TypPocisku, ParametrPocisk> Parametry;
public:
	ParametryPociskow();
	void Inicjuj();
	// Przed strzalem z broni bron nadaje wartsic Pociskowi
	ParametrPocisk * ZwrocParametr(TypPocisku typPocisku);
};





//Zdrowie jest zywotnoscia 
//Jesli Pocisk nie ma celu to on wybuchnie 
class Pocisk : public Obiekt
{

protected:
	ParametrPocisk* parametr;
	Ruch ruch;
	unsigned int Tick;
	float kat;

	void WyczyscCel();

public:
	//virtual ~Pocisk() = default;
	Pocisk(Vector2 Pozycja={0,0}, Vector2 Cel={0,0}, ParametrPocisk* parametr = nullptr);
	Pocisk(Vector2 Pozycja,TypPocisku typ , Vector2 Cel , ParametryPociskow& parametry,std::vector<Obiekt*> &Obiekty,TablicaAnimacji &tablica);
	virtual ~Pocisk();
	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty) override;
	void NaLiczZycie(CzasLogiki& czasLogiki);
	friend class Bron;
};

//----------------------------------------

class PociskKierowany : public Pocisk
{
protected:
	unsigned int IndexObiektuCel;
	RuchPoOkregu ruchPoOkregu;
	Obiekt* obiekt;
public:

	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty) override;
	void UstawCel(float katRozpoczeczeczia,Obiekt *& obiekt);
	void NaliczZycie(CzasLogiki &czasLogiki);
	void NamierzCel(std::vector<Obiekt*> &Obiekty);
	friend class Bron;
};

/*

class Rakieta : public Pocisk
{
	RuchPoOkregu ruchpookregu;
public:
	Rakieta(Vector2 Pozycja, Vector2* Cel, ParametrPocisk parametrPocisku);
	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system) override;
};
class Naboj : public Pocisk
{


};
*/
class Bron
{
	unsigned int Szybkostrzelnosc;
	float Zasieg;
	TypPocisku typ;
	unsigned int TickStrzalu;
public:
	Bron(unsigned int szybkostrzelnosc=20, float Zasieg=5, TypPocisku typ=TypPocisku::POCISK);
	void Strzelanie(const unsigned int &Index,CzasLogiki &czasLogiki,std::vector<unsigned int> &Indexy,std::vector<Obiekt*> &Obiekty, Mapa& mapa ,ParametryPociskow &parametrypociskow,TablicaAnimacji &tablica);
	friend class Agent;
};

#endif // !BRON_H