#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <Wczytywacz/WczytywaczOI.h>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "CzasLogiki.h"
#include "PozycjeNaMapie.h"


enum KierunkiSwiata
{
 POLUDNIE =0,
 POLUDNIE_ZACHOD,
 ZACHOD,
 POLNOC_ZACHOD,
 POLNOC,
 POLNOC_WSCHOD,
 WSCHOD,
 POLUDNIEWCHOD,
 ZADEN
};
enum TypyAnimacji
{
	STANIE=0,
	CHODZENIE,
	STRZELANIE
};




std::string ZwrocNazweKierunku(KierunkiSwiata kierunki);
KierunkiSwiata ZwrocKierunekZNazwy(std::string NazwaKierunku);
TypyAnimacji ZwrocTypAnimacji(std::string NazwaAnimacji);
std::string ZwrocNazweAnimacji(TypyAnimacji typanimacji);

KierunkiSwiata ZwrocKierunek(PozycjaNaMapie A,PozycjaNaMapie B);


struct Animacja
{
	
	
	
	//Co ktory tick ma sie zmienic
	TypyAnimacji typ;
	unsigned int CoKtoryTick;
	unsigned int LiczbaKlatek;
	Texture tekstura;

	

	Animacja(unsigned int CoKtoryTick,std::string AdresTekstury,TypyAnimacji typ,Vector2 &Rozmiar);
	Rectangle ZwrocKlatke(KierunkiSwiata kierunki,Vector2 &Rozmiar,const unsigned int Klatka);
	

	bool operator ==(const Animacja& animacja);

	unsigned int Zwroctick();
};
class ZestawAnimacji
{
	std::string NazwaAnimacji;
	std::vector<Animacja> animacje;
	Vector2 Rozmiar;
	void WczytajKtoryTyp(TypyAnimacji typAnimacji, blmp::Obiekt& obiekt);
	public:
		friend class PlayerAnimacji;
		friend class TablicaAnimacji;
		friend class Damage;
		friend class DamageKolo;
		friend class DamageProstokat;
		ZestawAnimacji(std::filesystem::path Folder);
	void DodajAnimacje(unsigned int CoKtoryTick, std::string AdresTekstury, TypyAnimacji typ);
	Rectangle ZwrocAnimacje(TypyAnimacji typAnimacji, KierunkiSwiata kierunki,const unsigned int Klatka);
};

void StworzZestawAnimacji(std::filesystem::path Folder,std::string NazwaAnimacji,Vector2 Rozmiar,unsigned int LiczbaKlatek);

class TablicaAnimacji
{
	std::vector<ZestawAnimacji> Zestawy;
public:
	TablicaAnimacji(std::filesystem::path Sciezka="");
	void WczytajZestawyAnimacji(std::filesystem::path Sciezka);
	ZestawAnimacji* ZwrocZestawAnimajcji(std::string NazwaAnimacji);
	friend class PlayerAnimacji;
	friend class Damage;
	friend class DamageKolo;
	friend class DamageProstokat;
};
class PlayerAnimacji
{
	unsigned int ObecnyTick;
	unsigned int Klatka;
	TypyAnimacji typAnimacji;
	KierunkiSwiata kierunek;

	ZestawAnimacji* zestawAnimacji;
	Animacja* animacja;

public:

	friend class Obiekt;
	friend class Agent;
	friend class Pocisk;
	friend class Damage;
	friend class DamageKolo;
	friend class DamageProstokat;

	PlayerAnimacji(std::string NazwaAnimacji="");

	void ZnajdzZasob(std::string NazwaAnimacji,TablicaAnimacji &tablicaAnimacji);
	void ZnajdzTypAnimacji(TypyAnimacji typAnimacji);
	void Rysuj(CzasLogiki &czasLogiki,Vector2 &Pozycja, const unsigned int& rozmiarKlatki,TablicaAnimacji &tablicaAnimacji);
	void UstawTypAnimacji(TypyAnimacji typ);
	void UstawKierunek(KierunkiSwiata kierunek);

};

void StworzTabliceAnimacji(std::filesystem::path Folder,std::string NazwaFolderu ,std::vector<std::string> NazwyAnimacji, Vector2 Rozmiar, unsigned int liczbaKlatek);


