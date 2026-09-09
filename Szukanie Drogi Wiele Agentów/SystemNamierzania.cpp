#include "SystemNamierzania.h"


void SystemNamierzania::CzyMozeNamierzyc(Obiekt*& obiekt1, Obiekt*& obiekt2, float& Zasieg, std::vector<unsigned int>& Celowe, Mapa& mapa)
{
	if (obiekt2 != nullptr)
	{
		const unsigned int IndexObiektu= obiekt2->ZwrocIndexObiektu();
		Vector2 pozycja1 = obiekt1->ZwrocPozycje();
		Vector2 pozycja2 = obiekt2->ZwrocPozycje();
		auto TenObiekt = std::find(Celowe.begin(), Celowe.end(), IndexObiektu);



		if (obiekt1 != nullptr && obiekt1!=obiekt2 && TenObiekt==Celowe.end() && obiekt1->ZwrocSojusz().SprawdzSojusz(obiekt2->ZwrocSojusz())==false && Zasieg * static_cast<float>(mapa.RozmiarKlatki) >= ZwrocDlugosc({pozycja2.x - pozycja1.x,pozycja2.y - pozycja1.y}))
		{
			Celowe.emplace_back(IndexObiektu);
		#ifdef SYSTEMNAMIERZANIA_DEBUG
			std::cout << "Dodany :" << obiekt2->IndexObiektu << "\n";
		#endif
		}
	}
}
SystemNamierzania::SystemNamierzania(unsigned int RozmiarMapy, unsigned int RozmiarSystemu)
{
	UstawRozmiarSystemu(RozmiarSystemu);
	DostosujDoRozmiaru(RozmiarMapy);
	this->TypSystemu = Typy::SYSTEM_NAMIERZANIA;
	
}
void SystemNamierzania::LogikaSystemuNamierzania(std::vector<Obiekt*>& Obiekty)
{
	for (Obiekt*& obiekt : Obiekty)
	{
		if (obiekt != nullptr)
			ZmapujObiekt(obiekt->ZwrocIndexObiektu(), obiekt->ZwrocCzyZaktualizowacSystemy(), obiekt->ZwrocPozycje(), obiekt->ZwrocPoprzedniaPozycje(), obiekt->ZwrocTypy());
	}
}


void SystemNamierzania::ZwrocSpelniajaceZasieg(unsigned int indexObiektu, float Zasieg, std::vector<unsigned int>& ListaObiektow, std::vector<Obiekt*>& Obiekty, Mapa& mapa)
{
#ifdef SYSTEMNAMIERZANIA_DEBUG
	std::cout << "Wywolujesz Sie Systemie namierzania ? \n";
#endif // !SYSTEMNAMIERZANIA_DEBUG
	Obiekt* obiekt = ZwrocObiekt(indexObiektu,Obiekty);
	if (obiekt != nullptr && SystemZainicjowany==true )
	{
		PozycjaNaMapie pozStartowa;
		PozycjaNaMapie pozKoncowa;
		const Vector2 pozycja = obiekt->ZwrocPozycje();
		const float RozmiarKlatekMapy = mapa.ZwrocRozmiarKlatki();
		

		pozStartowa.x = (pozycja.x - (Zasieg * RozmiarKlatekMapy)) / RozmiarKlatek;
		pozStartowa.y = (pozycja.y - (Zasieg * RozmiarKlatekMapy)) / RozmiarKlatek;
		pozKoncowa.x = (pozycja.x + (Zasieg * RozmiarKlatekMapy)) / RozmiarKlatek;
		pozKoncowa.y = (pozycja.y + (Zasieg * RozmiarKlatekMapy)) / RozmiarKlatek;

		if (pozStartowa.x < 0) pozStartowa.x = 0;
		if (pozStartowa.y < 0) pozStartowa.y = 0;
		if (pozKoncowa.x >= RozmiarSystemu) pozKoncowa.x = RozmiarKlatek - 1;
		if (pozKoncowa.y >= RozmiarSystemu) pozKoncowa.y = RozmiarKlatek - 1;

		for (unsigned int x = pozStartowa.x; x <= pozKoncowa.x; x++)
		{
			for (unsigned int y = pozStartowa.y; y <= pozKoncowa.y; y++)
			{
					for (unsigned int& index : ZmapowaneObiekty[ZwrocIndexKlatki(x,y)])
					{
						Obiekt* obiekt2 = ZwrocObiekt(index, Obiekty);
						#ifdef SYSTEMNAMIERZANIA_DEBUG
						std::cout << "Halo \n \n \n";
						#endif
						CzyMozeNamierzyc(obiekt, obiekt2, Zasieg, ListaObiektow, mapa);
					}
					//if (System[x + (y * rozmiarSystemu)].empty() == true) std::cout << "Iterator systemowy pusty :" << x+ (y * rozmiarSystemu) << "\n";
				
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

