#include "SystemNamierzania.h"

bool SystemNamierzania::PozycjaWSystemie(PozycjaNaMapie& poz)
{
	if (poz.x >= 0 && poz.y >= 0 && poz.x < rozmiarSystemu && poz.y < rozmiarSystemu)
	{
		return true;
	}
	else return false;
}
void SystemNamierzania::CzyMozeNamierzyc(Obiekt*& obiekt1, Obiekt*& obiekt2, float& Zasieg, std::vector<unsigned int>& Celowe, Mapa& mapa)
{
	if (obiekt2 != nullptr)
	{
		auto TenObiekt = std::find(Celowe.begin(), Celowe.end(), obiekt2->IndexObiektu);

		if (obiekt1 != nullptr && TenObiekt==Celowe.end() && obiekt1->sojusze.SprawdzSojusz(obiekt2->sojusze)==false && Zasieg * static_cast<float>(mapa.RozmiarKlatki) >= Dlugosc({obiekt2->pozycja.x - obiekt1->pozycja.x,obiekt2->pozycja.y - obiekt1->pozycja.y}))
		{
			Celowe.emplace_back(obiekt2->IndexObiektu);
		#ifdef SYSTEMNAMIERZANIA_DEBUG
			std::cout << "Dodany :" << obiekt2->IndexObiektu << "\n";
		#endif
		}
	}
}
SystemNamierzania::SystemNamierzania(unsigned int rozmiarKlatki, unsigned int rozmiarSystemu)
{
	this->rozmiarKlatki = rozmiarKlatki;
	this->rozmiarSystemu = rozmiarSystemu;
	System.resize(rozmiarSystemu * rozmiarSystemu,{});
}
void SystemNamierzania::UstawParametry(unsigned int rozmiarSystemu,Mapa& mapa)
{
	this->rozmiarSystemu = rozmiarSystemu;
	System.clear();
	System.resize(rozmiarSystemu * rozmiarSystemu, {});
	 rozmiarKlatki= mapa.szerokosc* mapa.RozmiarKlatki/rozmiarSystemu;
}
void SystemNamierzania::UstawSystem(std::vector<Obiekt*>& Obiekty)
{
	MapowanieObiektow(Obiekty, System, rozmiarKlatki, rozmiarSystemu,Typy::SYSTEM_NAMIERZANIA);

}
void SystemNamierzania::ZwrocSpelniajaceZasieg(unsigned int indexObiektu, float Zasieg, std::vector<unsigned int>& ListaObiektow, std::vector<Obiekt*>& Obiekty, Mapa& mapa)
{
#ifdef SYSTEMNAMIERZANIA_DEBUG
	std::cout << "Wywolujesz Sie Systemie namierzania ? \n";
#endif // !SYSTEMNAMIERZANIA_DEBUG
	Obiekt* obiekt = ZwrocObiekt(indexObiektu,Obiekty);
	if (obiekt != nullptr)
	{
		PozycjaNaMapie pozStartowa;
		PozycjaNaMapie pozKoncowa;

		pozStartowa.x = (obiekt->pozycja.x - static_cast<float>(Zasieg * mapa.RozmiarKlatki)) / rozmiarKlatki;
		pozStartowa.y = (obiekt->pozycja.y - static_cast<float>(Zasieg * mapa.RozmiarKlatki)) / rozmiarKlatki;
		pozKoncowa.x = (obiekt->pozycja.x + static_cast<float>(Zasieg * mapa.RozmiarKlatki)) / rozmiarKlatki;
		pozKoncowa.y = (obiekt->pozycja.y + static_cast<float>(Zasieg * mapa.RozmiarKlatki)) / rozmiarKlatki;

		if (pozStartowa.x < 0) pozStartowa.x = 0;
		if (pozStartowa.y < 0) pozStartowa.y = 0;
		if (pozKoncowa.x >= rozmiarSystemu) pozKoncowa.x = rozmiarSystemu - 1;
		if (pozKoncowa.y >= rozmiarSystemu) pozKoncowa.y = rozmiarSystemu - 1;

		for (unsigned int x = pozStartowa.x; x <= pozKoncowa.x; x++)
		{
			for (unsigned int y = pozStartowa.y; y <= pozKoncowa.y; y++)
			{




				if (System.empty() == false)
				{
					for (unsigned int& index : System[x + (y * rozmiarSystemu)])
					{
						Obiekt* obiekt2 = ZwrocObiekt(index, Obiekty);
						#ifdef SYSTEMNAMIERZANIA_DEBUG
						std::cout << "Halo \n \n \n";
						#endif
						CzyMozeNamierzyc(obiekt, obiekt2, Zasieg, ListaObiektow, mapa);
					}
					//if (System[x + (y * rozmiarSystemu)].empty() == true) std::cout << "Iterator systemowy pusty :" << x+ (y * rozmiarSystemu) << "\n";
				}
				#ifdef SYSTEMNAMIERZANIA_DEBUG
				else std::cout << "System jest pusty \n";
				#endif

			}
		}
	}
	#ifdef SYSTEMNAMIERZANIA_DEBUG
	else std::cout << "Obiektu o indexie nie znaleziono :" << indexObiektu << "\n";
	#endif
}
#ifdef SYSTEMNAMIERZANIA_DEBUG
void SystemNamierzania::Debug()
{
	NarysujSiatke(System, rozmiarSystemu, rozmiarKlatki, FIOLETOWY,ZOLTY);
}
#endif

