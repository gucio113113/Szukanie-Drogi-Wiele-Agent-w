#pragma once
#include <raylib.h>
#include "CzasLogiki.h"
#include "PozycjeNaMapie.h"
#include <vector>
#include "Zasob.h"
#include <DyrektywyDebugowania.h>

#ifndef SYSTEMOBRAZEN
#define SYSTEMOBRAZEN


class Obiekt;
class Mapa;
class Damage
{
protected:
	Vector2 Pozycja;
	unsigned int CzasTrwania;
	unsigned int Tick;
	unsigned int KiedyZadaje;
	unsigned int IleZadaje;

public:
	//Kiedy Zadaje musi byc mniejszy od czasu trwania
	Damage(Vector2 Pozycja={0,0}, unsigned int CzasTrwania=0, unsigned int KiedyZadaje=0, unsigned int IleZadaje=0);
	virtual ~Damage();
	void NaliczTick(CzasLogiki &czasLogiki);
	virtual bool Sprawdz(Obiekt *& obiekt, Mapa& mapa, TablicaAnimacji &tablicanimacji);
	virtual PozycjaNaMapie DolnyZasieg(const unsigned int rozmiarKlatek);
	virtual PozycjaNaMapie GornyZasieg(const unsigned int rozmiarKlatek);
	friend class SystemObrazen;
	friend class Pocisk;

	virtual Damage *ZwrocKopie(Vector2 Pozycja);
	

};
class DamageKolo : public Damage
{
	
	float Promien;
public:
	DamageKolo(Vector2 Pozycja, float Promien, unsigned int CzasTrwania, unsigned int KiedyZadaje, unsigned int IleZadaje);
	virtual bool Sprawdz(Obiekt*& obiekt, Mapa &mapa, TablicaAnimacji& tablicanimacji) override;
	PozycjaNaMapie DolnyZasieg(const unsigned int rozmiarKlatek) override;
	PozycjaNaMapie GornyZasieg(const unsigned int rozmiarKlatek) override;
	friend class SystemObrazen;
	Damage* ZwrocKopie(Vector2 Pozycja) override;
};
class DamageProstokat : public Damage
{
	
	Vector2 Rozmiar;
public:
	DamageProstokat(Vector2 Pozycja, Vector2 Rozmiar, unsigned int CzasTrwania, unsigned int KiedyZadaje, unsigned int IleZadaje);
	virtual bool Sprawdz(Obiekt*& obiekt, Mapa& mapa, TablicaAnimacji& tablicanimacji) override;
	PozycjaNaMapie DolnyZasieg(const unsigned int rozmiarKlatek) override;
	PozycjaNaMapie GornyZasieg(const unsigned int rozmiarKlatek) override;
	friend class SystemObrazen;
	Damage* ZwrocKopie(Vector2 Pozycja) override;
};
class SystemObrazen
{
	unsigned int RozmiarKlatek;
	unsigned int RozmiarSystemu;
	std::vector<std::vector<unsigned int>> IndexyObiektow;
	std::vector<Damage*> Obrazenia;

public:

	std::vector<unsigned int> PodOstrzalem;

	friend class Pocisk;
	SystemObrazen(unsigned int RozmiarKlatek=100, unsigned int RozmiarSystemu=10);
	void ZmapujObiekty(std::vector<Obiekt*>& Obiekty);
	void LogikaSystemu(std::vector<Obiekt*> &Obiekty,CzasLogiki &Czaslogiki,Mapa &mapa, TablicaAnimacji& tablicanimacji);
	void UstawParametry(unsigned int RozmiarSystemu,Mapa &mapa);
#ifdef SYSTEM_OBRAZEN_DEBUG
	void Debug();
#endif // SYSTEM_OBRAZEN
};

#endif // !SYSTEMOBRAZEN
