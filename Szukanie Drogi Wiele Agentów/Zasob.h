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
#include <DyrektywyDebugowania.h>


enum class KierunkiSwiata : unsigned char
{
 POLUDNIE        = 0b00000001,
 ZACHOD          = 0b00000010,
 POLNOC          = 0b00000100,
 WSCHOD          = 0b00001000,

 POLNOC_ZACHOD   = POLNOC | ZACHOD ,
 POLNOC_WSCHOD   = POLNOC | WSCHOD,
 POLUDNIE_WSCHOD = POLUDNIE | WSCHOD,
 POLUDNIE_ZACHOD = POLUDNIE | ZACHOD,
 ZADEN           =0b00000000
};
inline constexpr KierunkiSwiata operator | (KierunkiSwiata kierunki0,  KierunkiSwiata kierunki1)
{
	return static_cast<KierunkiSwiata>(static_cast<unsigned char>(kierunki0) | static_cast<unsigned char>(kierunki1));
}
inline constexpr KierunkiSwiata operator & (KierunkiSwiata kierunki0,  KierunkiSwiata kierunki1)
{
	return static_cast<KierunkiSwiata>(static_cast<unsigned char>(kierunki0) & static_cast<unsigned char>(kierunki1));
}

inline constexpr bool operator ==( KierunkiSwiata kierunki0,  KierunkiSwiata kierunki1)
{
	return static_cast<unsigned char>(kierunki0)==static_cast<unsigned char>(kierunki1);
}
inline constexpr unsigned char ZwrocIndexKlatki( KierunkiSwiata kierunki0)
{
	 if     ((kierunki0 == KierunkiSwiata::POLUDNIE_ZACHOD)) return 1;
	else if ((kierunki0 == KierunkiSwiata::POLNOC_ZACHOD)) return 3;
	else if ((kierunki0 == KierunkiSwiata::POLNOC_WSCHOD)) return 5;
	else if ((kierunki0 == KierunkiSwiata::POLUDNIE_WSCHOD)) return 7;
	else if ((kierunki0 == KierunkiSwiata::POLUDNIE)) return 0;
	else if ((kierunki0 == KierunkiSwiata::ZACHOD)) return 2;
	else if ((kierunki0 == KierunkiSwiata::POLNOC)) return 4;
	else if ((kierunki0 == KierunkiSwiata::WSCHOD)) return 6;
	else return 0;
}
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
	void Rysuj(CzasLogiki &czasLogiki,Vector2 Pozycja, const unsigned int rozmiarKlatki,TablicaAnimacji &tablicaAnimacji);
	void UstawTypAnimacji(TypyAnimacji typ);
	void UstawKierunek(KierunkiSwiata kierunek);

};

void StworzTabliceAnimacji(std::filesystem::path Folder,std::string NazwaFolderu ,std::vector<std::string> NazwyAnimacji, Vector2 Rozmiar, unsigned int liczbaKlatek);


