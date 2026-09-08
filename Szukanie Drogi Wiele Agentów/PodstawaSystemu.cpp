#include "PodstawaSystemu.h"

void PodstawaSystemu::UstawRozmiarSystemu(unsigned int RozmiarSystemu)
{
	if (SystemZainicjowany == false)
	{
		this->RozmiarSystemu = RozmiarSystemu;
	}
	else std::cout << "System juz Zainicjowano nie mozna ustawic RozmiarSystemu \n";
}
void PodstawaSystemu::UstawRozmiarKlatek(unsigned int RozmiarKlatek)
{
	if (SystemZainicjowany == false)
	{
		this->RozmiarKlatek = RozmiarKlatek;
	}
	else std::cout << "System juz Zainicjowano nie mozna ustawic RozmiarKlatek \n";
}
void PodstawaSystemu::DostosujDoRozmiaru(unsigned int RozmiarMapy)
{
	if (SystemZainicjowany == false)
	{
		this->RozmiarKlatek = RozmiarMapy / RozmiarSystemu;
	}
	else std::cout << "System juz Zainicjowano nie mozna DostosowacDoRozmiaruMapy \n";
}
unsigned int PodstawaSystemu::ZwrocRozmiarSystemu()
{
	return RozmiarSystemu;
	}
unsigned int PodstawaSystemu::ZwrocRozmiarKlatek()
{
	return RozmiarKlatek;
}
std::vector<unsigned int> PodstawaSystemu::ZwrocObiektyWKlatce(unsigned int x, unsigned int y)
{
	if (ZwrocCzyMozeZmapowac(x, y) == true)
	{
		return ZmapowaneObiekty[ZwrocIndexKlatki(x, y)];
	}
	else return {};
}
bool PodstawaSystemu::ZwrocCzySystemZainijowany()
{
	return SystemZainicjowany;
}

 void PodstawaSystemu::GenerujSystem()
{
	 if (RozmiarKlatek != 0)
	 {
		 this->ZmapowaneObiekty.resize(RozmiarSystemu * RozmiarSystemu, {});
		 SystemZainicjowany = true;
	 }
	 else SystemZainicjowany = false;
}
void PodstawaSystemu::ZmapujObiekt(const unsigned int IndexObiektu, const bool CzyZaktualizowac, const Vector2 Pozycja,const Vector2 PoprzedniaPozycja,const Typy TypObiektu)
{
	if (!!(TypObiektu & TypSystemu) && CzyZaktualizowac == true && RozmiarKlatek!=0)
	{
		int x0 = Pozycja.x/RozmiarKlatek;
		int y0 = Pozycja.y/RozmiarKlatek;
		int x1 = PoprzedniaPozycja.x / RozmiarKlatek;
		int y1 = PoprzedniaPozycja.y / RozmiarKlatek;
		if (ZwrocCzyMozeZmapowac(x0, y0) == true && ZwrocCzyMozeZmapowac(x1,y1)==true )
		{
			std::vector<unsigned int> Pierwsza= ZmapowaneObiekty[ZwrocIndexKlatki(x0, y0)];
			std::vector<unsigned int> Druga=ZmapowaneObiekty[ZwrocIndexKlatki(x1,y1)];
			auto SzukajObiektuWPierwszym = std::find(Pierwsza.begin(), Pierwsza.end(), IndexObiektu);
			auto SzukajObiektuWDrugim = std::find(Druga.begin(), Druga.end(), IndexObiektu);

			if (SzukajObiektuWPierwszym == Pierwsza.end()) Pierwsza.emplace_back(IndexObiektu);
			if (SzukajObiektuWDrugim != Druga.end())
			{
				*SzukajObiektuWDrugim = Druga.back();
				Druga.pop_back();
			}
		}

	}
}