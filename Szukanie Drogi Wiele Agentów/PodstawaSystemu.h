#pragma once


#ifndef PODSTAWASYSTEMU_H
#define PODSTAWASYSTEMU_H

#include <vector>
#include <algorithm>
#include <raylib.h>


enum class Typy : unsigned char
{
	ZADEN = 0b00000000,
	SYSTEM_OBRAZEN = 0b00000001,  //typ druzyny polega na tym ze nie jest traktowana przez system namierzania jako cel do namierzania
	SYSTEM_NAMIERZANIA = 0b00000010,
	SYSTEM_USUWANIA = 0b00000100,
	SYSTEM_ZAJMOWANIA = 0b00001000
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
inline constexpr bool operator==(Typy a, Typy b)
{
	return static_cast<unsigned char>(a) == static_cast<unsigned char>(b);
}



class PodstawaSystemu
{
protected:
	bool SystemZainicjowany;
	std::vector<std::vector<unsigned int>> ZmapowaneObiekty;
	unsigned int RozmiarSystemu;
	unsigned int RozmiarKlatek;
	Typy TypSystemu=Typy::ZADEN;
	

public:

	void UstawRozmiarSystemu(unsigned int RozmiarSystemu);
	void UstawRozmiarKlatek(unsigned int RozmiarKlatek);

	unsigned int ZwrocRozmiarSystemu();
	unsigned int ZwrocRozmiarKlatek();

	std::vector<unsigned int> ZwrocObiektyWKlatce(unsigned int x,unsigned int y);

	inline unsigned int ZwrocIndexKlatki(unsigned int x,unsigned int y)
	{
		return x + (y * RozmiarSystemu);
	}
	bool ZwrocCzyMozeZmapowac(unsigned int x, unsigned int y)
	{
		return (SystemZainicjowany == true && x < RozmiarSystemu && y < RozmiarSystemu);
	}
	bool ZwrocCzySystemZainijowany();
	virtual void GenerujSystem();
	

	void ZmapujObiekt(const unsigned int IndexObiektu,const bool CzyZaktualizowac,const Vector2 Pozycja,const Vector2 PoprzedniaPozycja,const Typy TypObiektu);


};


#endif // !

