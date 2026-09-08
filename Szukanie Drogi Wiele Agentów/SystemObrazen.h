#pragma once
#include <raylib.h>
#include "CzasLogiki.h"
#include "PozycjeNaMapie.h"
#include <vector>
#include "Zasob.h"
#include <DyrektywyDebugowania.h>
#include "PodstawaSystemu.h"

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
#ifdef SYSTEM_OBRAZEN_DEBUG
	virtual void NarysujDamage(unsigned int rozmiarKlatki);
#endif // AGENT_DEBUG

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

#ifdef SYSTEM_OBRAZEN_DEBUG
	 void NarysujDamage(unsigned int rozmiarKlatki) override;
#endif
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
#ifdef SYSTEM_OBRAZEN_DEBUG
	void NarysujDamage(unsigned int rozmiarKlatki) override;
#endif
};
class SystemObrazen : public PodstawaSystemu
{
	
	std::vector<Damage*> Obrazenia;
public:
	std::vector<unsigned int> PodOstrzalem;

	friend class Pocisk;
	SystemObrazen(unsigned int RozmiarKlatek=100, unsigned int RozmiarSystemu=10);

	void LogikaSystemuObrazen(std::vector<Obiekt*> &Obiekty,CzasLogiki &Czaslogiki,Mapa &mapa, TablicaAnimacji& tablicanimacji);
#ifdef SYSTEM_OBRAZEN_DEBUG
	void Debug(unsigned int Rozmiar);
#endif // SYSTEM_OBRAZEN


};

#endif // !SYSTEMOBRAZEN
