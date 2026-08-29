#pragma once

#ifndef OBIEKT_H
#define OBIEKT_H



#include <raylib.h>
#include <string>
#include "Zasob.h"
#include "Mapa.h"
#include "CzasLogiki.h"
#include "Funkcje.h"
#include "SystemObrazen.h"


#define LICZBA_PI 3.141592f

//Zdefiniowane Druzyny

 
// Pociskow druzyna nie dziala na nia system namierzania jaki system obrazen



enum class Druzyny : unsigned char
{
	NEUTRALNA= 0b00000000,
	PRZECZIWNA=0b11111111,
	DRUZYNA1 = 0b00000001,
	DRUZYNA2 = 0b00000010,
	DRUZYNA3 = 0b00000100,
	DRUZYNA4 = 0b00001000,
	DRUZYNA5 = 0b00010000,
	DRUZYNA6 = 0b00100000,
	DRUZYNA7 = 0b01000000,
	DRUZYNA8 = 0b10000000,
};
inline constexpr Druzyny operator|(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator&(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) & static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator^(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) ^ static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator~(Druzyny a) {
	return static_cast<Druzyny>(~static_cast<unsigned char>(a));
}
inline constexpr bool operator!(Druzyny a) {
	return static_cast<unsigned char>(a)==0;
}


enum class Typy : unsigned char
{
	ZADEN       = 0b00000000,
	SYSTEM_OBRAZEN      = 0b00000001,  //typ druzyny polega na tym ze nie jest traktowana przez system namierzania jako cel do namierzania
	SYSTEM_NAMIERZANIA = 0b00000010,
	
	
};
inline constexpr Typy operator|(Typy a, Typy b) {
	return static_cast<Typy>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}
inline constexpr Typy operator&(Typy a, Typy b) {
	return static_cast<Typy>(static_cast<unsigned char>(a) & static_cast<unsigned char>(b));
}
inline constexpr bool operator!(Typy a) {
	return static_cast<unsigned char>(a) == 0;
}

class Sojusze
{
	Druzyny sojusz;
	Druzyny wlasciciel;

public:
	Sojusze(Druzyny wlasciciel=Druzyny::NEUTRALNA, Druzyny Sojusz=Druzyny::NEUTRALNA);
	Sojusze(Druzyny wlasciciel);
	void UstawWlasciciel(Druzyny wlasciciel);
	void UstawSojusz(Druzyny sojusz);
	void UsunSojusz(Druzyny sojusz);
	Druzyny zwrocSojusz();
	Druzyny zwrocWlasciciel();
	//checks if two objects have the same team
	bool SprawdzSojusz(const Sojusze& sojusz1);
	Sojusze operator=(const Sojusze &sojusz1);
};









class SystemNamierzania;
class ParametryPociskow;
class TablicaAnimacji;
class Obiekt
{
protected:
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
	virtual void Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty);
	virtual void Render(Mapa& mapa,CzasLogiki &czasLogiki,TablicaAnimacji &tablica);

	unsigned int DostanIdnex();
	
	bool operator== (Obiekt*& obiekt);

	friend class Bron;
	friend class Damage;
	friend class DamageKolo;
	friend class DamageProstokat;
	friend class SystemObrazen;
	friend class SystemNamierzania;
	friend class Pocisk;
	friend class PociskKierowany;
	friend void MapowanieObiektow(std::vector<Obiekt*>& Obiekty, std::vector<std::vector<unsigned int>> &KlatkiSystemu, unsigned int RozmiarKlatek, unsigned int RozmiarSystemu, Typy typ);
	friend Obiekt* ZwrocObiekt(unsigned indexObiektu, std::vector<Obiekt*>& Obiekty);
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

