#include "SystemZajmowania.h"

void SystemZajmowaniaSojuszy::RozpocznijZajmowanie(unsigned int x, unsigned int y)
{
	

}
#ifdef SYSTEM_ZAJMOWANIA_DEBUG



Vector2 SystemZajmowaniaSojuszy::ZwrocSrodekCzworokata(std::array<Vector2, 4>& Tablica)
{
	return { (Tablica[0].x + Tablica[1].x + Tablica[2].x + Tablica[3].x) / 4,(Tablica[0].y + Tablica[1].y + Tablica[2].y + Tablica[3].y) / 4 };
}
void SystemZajmowaniaSojuszy::NarysujDebug(unsigned int x, unsigned int y)
{
	if (pokazwartoscidebug == PokazWartosciDebug::ZMAPOWANY_TEREN_DEBUG)
	{
		std::string napis=std::to_string(TablicaZmapowaneTereny[ZwrocIndexKlatki(x,y)].size());
		NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);
	}
	else
	{
		Vector2 poz = ZwrocSrodekCzworokata(TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)]);

		std::string napis;
		
		

		switch (pokazwartoscidebug)
		{
		case PokazWartosciDebug::PRZYCHOD_DEBUG: napis = std::to_string(TablicaPrzychody[ZwrocIndexKlatki(x, y)]);
			break;
		case PokazWartosciDebug::ZAJMOWANIA_TICK_DEBUG: napis = std::to_string(TablicaZajmowanieTick[ZwrocIndexKlatki(x, y)]);
			break;
		case PokazWartosciDebug::ZAJMOWANIA_CZASZAJMOWANIA_DEBUG: napis = std::to_string(TablicaZajmowanieCzasZajmowania[ZwrocIndexKlatki(x, y)]);
			break;
		case PokazWartosciDebug::ILOSCOBIEKTOW_DEBUG: napis = std::to_string(ZmapowaneObiekty[ZwrocIndexKlatki(x, y)].size());
			break;
		}
		NarysujTekst(napis, RozmiarKlatek / 10, static_cast<int>(poz.x), static_cast<int>(poz.y), BLACK);
	}
}

#endif // SYSTEM_ZAJMOWANIA_DEBUG


float SystemZajmowaniaSojuszy::ZwrocPoleCzworokata(std::array<Vector2, 4>& Tablica)
{
	Vector2 a = {Tablica[2].x - Tablica[0].x,Tablica[2].y - Tablica[0].y};
	Vector2 b = {Tablica[3].x - Tablica[1].x, Tablica[3].y - Tablica[1].y};
	return  abs(ZwrocIloczynWektorowy(a, b) / 2);
}

	void SystemZajmowaniaSojuszy::UstawRozmiarSystemu(unsigned int RozmiarSystemu)
	{
		this->RozmiarSystemu = RozmiarSystemu;
	}
	void SystemZajmowaniaSojuszy::UstawRozmiarKlatek(unsigned int RozmiarKlatek)
	{
		this->RozmiarKlatek = RozmiarKlatek;
	}
	void SystemZajmowaniaSojuszy::UstawDruzyne(unsigned int x, unsigned int y, Druzyny druzyna)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			TablicaDruzynyZajmujaceTeren[ZwrocIndexKlatki(x, y)] = druzyna;
		}
	}
	void SystemZajmowaniaSojuszy::UstawPrzychod(unsigned int x, unsigned int y, unsigned int Przychod)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			TablicaPrzychody[ZwrocIndexKlatki(x, y)] = Przychod;
		}

	}
	void SystemZajmowaniaSojuszy::UstawCzasZajmowania(unsigned int x, unsigned int y, unsigned int CzasZajmowania)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			TablicaZajmowanieCzasZajmowania[ZwrocIndexKlatki(x, y)] = CzasZajmowania;
		}

	}
	void SystemZajmowaniaSojuszy::UstawTick(unsigned int x, unsigned int y, unsigned int Tick)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			TablicaZajmowanieTick[ZwrocIndexKlatki(x, y)] = Tick;
		}
	}

	unsigned int SystemZajmowaniaSojuszy::ZwrocRozmiarSystemu()
	{
		return RozmiarSystemu;
	}
	unsigned int SystemZajmowaniaSojuszy::ZwrocRozmiarKlatek()
	{
		return RozmiarKlatek;

	}
	Druzyny SystemZajmowaniaSojuszy::ZwrocDruzyne(unsigned int x, unsigned int y)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			return TablicaDruzynyZajmujaceTeren[ZwrocIndexKlatki(x, y)];
		}
		else return Druzyny::NEUTRALNA;

	}
	unsigned int SystemZajmowaniaSojuszy::ZwrocPrzychod(unsigned int x, unsigned int y)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			return TablicaPrzychody[ZwrocIndexKlatki(x, y)];
		}
		else return 1;

	}
	unsigned int SystemZajmowaniaSojuszy::ZwrocCzasZajmowania(unsigned int x, unsigned int y)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			return TablicaZajmowanieCzasZajmowania[ZwrocIndexKlatki(x, y)];
		}
		return 1;

	}
	unsigned int SystemZajmowaniaSojuszy::ZwrocTick(unsigned int x, unsigned int y)
	{

		if (ZwrocCzyMozeZmapowac(x, y))
		{
			return TablicaZajmowanieTick[ZwrocIndexKlatki(x, y)];
		}
		return 1;
	}

	//Zwraca Zbiotry

	unsigned int SystemZajmowaniaSojuszy::ZwrocIloscObiektowDruzyny(std::vector<Obiekt*>& Obiekty, Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			unsigned int Ilosc=0;
			for (unsigned int& Index : ZmapowaneObiekty[ZwrocIndexKlatki(x, y)])
			{
				Obiekt* obiekt = ZwrocObiekt(Index, Obiekty);
				if (obiekt!=nullptr)
				{
					Ilosc++;
				}
			}
			return Ilosc;
		}
		else return	0;
	}
	std::vector<unsigned int> SystemZajmowaniaSojuszy::ZwrocTabliceObiektow(std::vector<Obiekt*>& Obiekty, Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (ZwrocCzyMozeZmapowac(x, y))
		{
			std::vector<unsigned int> IndexyZmapowane;
			for (unsigned int& Index : ZmapowaneObiekty[ZwrocIndexKlatki(x, y)])
			{
				Obiekt* obiekt = ZwrocObiekt(Index, Obiekty);
				if (obiekt != nullptr && !!(obiekt->ZwrocSojusz().zwrocWlasciciel() & druzyna))
				{
					IndexyZmapowane.emplace_back(Index);
				}
			}
			return IndexyZmapowane;
		}
		return {};
	}
	void SystemZajmowaniaSojuszy::GenerujSystem(const unsigned int TickRate)
	{
		SystemZainicjowany = true;
		std::default_random_engine generator;

#ifndef SYSTEM_ZAJMOWANIA_DEBUG
		std::vector<Vector2> LosowePunkciki;
#endif // SYSTEM_ZAJMOWANIA_DEBUG


		LosowePunkciki.resize((RozmiarSystemu + 1) * (RozmiarSystemu + 1), { 0,0 });
		TablicaDruzynyZajmujaceTeren.resize(RozmiarSystemu * RozmiarSystemu, Druzyny::NEUTRALNA);
		this->TablicaPrzychody.resize(RozmiarSystemu * RozmiarSystemu,1);
		this->TablicaZajmowanieCzasZajmowania.resize(RozmiarSystemu * RozmiarSystemu, 30 * TickRate);
		this->TablicaZajmowanieTick.resize(RozmiarSystemu * RozmiarSystemu, 0);
		this->TablicaZmapowaneTereny.resize(RozmiarSystemu * RozmiarSystemu, {});
		this->TablicaPunktyTerenu.resize(RozmiarSystemu * RozmiarSystemu);
		this->ZmapowaneObiekty.resize(RozmiarSystemu* RozmiarSystemu);
		


		
		auto ZwrocIndexDlaPunktow = [&](unsigned int x, unsigned int y)->unsigned int
			{
				return x + (y * (RozmiarSystemu + 1));
			};




		for (unsigned int x = 0; x < RozmiarSystemu+1  ; x++)
		{
			for (unsigned int y = 0; y < RozmiarSystemu+1; y++ )
			{
				
				
				if (x == 0)
				{
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].x = 0;
				}
				else if (x == RozmiarSystemu)
				{
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].x = RozmiarKlatek * RozmiarSystemu;
				}
				//else if(x>0)
				//{
				//	std::uniform_int_distribution<int> dystrybucjaX(LosowePunkciki[ZwrocIndexDlaPunktow(x-1,y)].x, x * RozmiarKlatek + RozmiarKlatek);
				//	LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].x = dystrybucjaX(generator);
				//}
				else
				{
					std::uniform_int_distribution<int> dystrybucjaX(x * RozmiarKlatek, x * RozmiarKlatek + RozmiarKlatek);
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].x = dystrybucjaX(generator);
				}
				if (y == 0)
				{
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].y = 0;
				}
				else if (y == RozmiarSystemu)
				{
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].y = RozmiarKlatek * RozmiarSystemu;
				}
				//else if (x > 0)
				//{
				//	std::uniform_int_distribution<int>  dystrybucjaY(LosowePunkciki[ZwrocIndexDlaPunktow(x, y-1)].y, y * RozmiarKlatek + RozmiarKlatek);
				//	LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].y = dystrybucjaY(generator);
				//}
				else
				{
					std::uniform_int_distribution<int> dystrybucjaY(y * RozmiarKlatek + (RozmiarKlatek / 2), y * RozmiarKlatek + RozmiarKlatek);
					LosowePunkciki[ZwrocIndexDlaPunktow(x, y)].y = dystrybucjaY(generator);
				}
			}
		}
		
		for (unsigned int x = 0; x < RozmiarSystemu; x++)
		{
			for (unsigned int y = 0; y < RozmiarSystemu; y++)
			{
				TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)][0] = LosowePunkciki[ZwrocIndexDlaPunktow(x,y)];
				TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)][1] = LosowePunkciki[ZwrocIndexDlaPunktow(x + 1, y)];
				TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)][2] = LosowePunkciki[ZwrocIndexDlaPunktow(x + 1, y + 1)];
				TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)][3] = LosowePunkciki[ZwrocIndexDlaPunktow(x, y + 1)];

				PozycjaNaMapie pozA = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y)].y / RozmiarKlatek) };
				PozycjaNaMapie pozB = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y)].y / RozmiarKlatek) };
				PozycjaNaMapie pozC = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y + 1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y + 1)].y / RozmiarKlatek) };
				PozycjaNaMapie pozD = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y + 1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y+1)].y/RozmiarKlatek) };
				PozycjaNaMapie pozE = { static_cast<int>(x * RozmiarKlatek+ (RozmiarKlatek/2)),static_cast<int>(y * RozmiarKlatek + (RozmiarKlatek/2))};


				TablicaPrzychody[ZwrocIndexKlatki(x, y)] = ZwrocPoleCzworokata(TablicaPunktyTerenu[ZwrocIndexKlatki(x, y)])/RozmiarKlatek;


				unsigned int index = ZwrocIndexKlatki(x, y);

				if (pozA.x < RozmiarSystemu && pozA.y < RozmiarSystemu)
				{
					auto iteratorA = std::find(TablicaZmapowaneTereny[ZwrocIndexKlatki(pozA.x, pozA.y)].begin(), TablicaZmapowaneTereny[ZwrocIndexKlatki(pozA.x, pozA.y)].end(), index);
					if (iteratorA == TablicaZmapowaneTereny[ZwrocIndexKlatki(pozA.x, pozA.y)].end()) TablicaZmapowaneTereny[ZwrocIndexKlatki(pozA.x, pozA.y)].emplace_back(index);
				}
				if (pozB.x < RozmiarSystemu && pozB.y < RozmiarSystemu)
				{
					auto iteratorB = std::find(TablicaZmapowaneTereny[ZwrocIndexKlatki(pozB.x, pozB.y)].begin(), TablicaZmapowaneTereny[ZwrocIndexKlatki(pozB.x, pozB.y)].end(), index);
					if (iteratorB == TablicaZmapowaneTereny[ZwrocIndexKlatki(pozB.x, pozB.y)].end()) TablicaZmapowaneTereny[ZwrocIndexKlatki(pozB.x, pozB.y)].emplace_back(index);

				}
				if (pozC.x < RozmiarSystemu && pozC.y < RozmiarSystemu)
				{
					auto iteratorC = std::find(TablicaZmapowaneTereny[ZwrocIndexKlatki(pozC.x, pozC.y)].begin(), TablicaZmapowaneTereny[ZwrocIndexKlatki(pozC.x, pozC.y)].end(), index);
					if (iteratorC == TablicaZmapowaneTereny[ZwrocIndexKlatki(pozC.x, pozC.y)].end()) TablicaZmapowaneTereny[ZwrocIndexKlatki(pozC.x, pozC.y)].emplace_back(index);

				}
				if (pozD.x < RozmiarSystemu && pozD.y < RozmiarSystemu)
				{
					auto iteratorD = std::find(TablicaZmapowaneTereny[ZwrocIndexKlatki(pozD.x, pozD.y)].begin(), TablicaZmapowaneTereny[ZwrocIndexKlatki(pozD.x, pozD.y)].end(), index);
					if (iteratorD == TablicaZmapowaneTereny[ZwrocIndexKlatki(pozD.x, pozD.y)].end()) TablicaZmapowaneTereny[ZwrocIndexKlatki(pozD.x, pozD.y)].emplace_back(index);
				}
				if (pozE.x < RozmiarSystemu && pozE.y < RozmiarSystemu)
				{
					auto iteratorE = std::find(TablicaZmapowaneTereny[ZwrocIndexKlatki(pozE.x, pozE.y)].begin(), TablicaZmapowaneTereny[ZwrocIndexKlatki(pozE.x, pozE.y)].end(), index);
					if (iteratorE == TablicaZmapowaneTereny[ZwrocIndexKlatki(pozE.x, pozE.y)].end()) TablicaZmapowaneTereny[ZwrocIndexKlatki(pozE.x, pozE.y)].emplace_back(index);
				}
			}

		}
	}
	SystemZajmowaniaSojuszy::SystemZajmowaniaSojuszy(unsigned int RozmiarSystemu, unsigned int RozmiarKlatek)
	{
		this->RozmiarSystemu = RozmiarSystemu;
		this->RozmiarKlatek = RozmiarKlatek;
		this->TypSystemu = Typy::SYSTEM_ZAJMOWANIA;
		
	}
	void SystemZajmowaniaSojuszy::ZmapujObiekt (const unsigned int IndexObiektu, const bool CzyZaktualizowac, const Vector2 Pozycja, const Vector2 PoprzedniaPozycja,const Typy TypObiektu)
	{
		if (!!(this->TypSystemu & TypObiektu) && CzyZaktualizowac == true && this->RozmiarKlatek!=0)
		{
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
			std::cout << "To ty dzialasz ?\n";
#endif // SYSTEM_ZAJMOWANIA_DEBUG
			PozycjaNaMapie pozNaSiatce0 = { static_cast<int>(static_cast<int>(Pozycja.x) / RozmiarKlatek),static_cast<int>(static_cast<int>(Pozycja.y) / RozmiarKlatek) };
			PozycjaNaMapie pozNaSiatce1 = {static_cast<int>(static_cast<int>(PoprzedniaPozycja.x)/RozmiarKlatek),static_cast<int>(static_cast<int>(PoprzedniaPozycja.y)/RozmiarKlatek)};

#ifdef SYSTEM_ZAJMOWANIA_DEBUG
			std::cout << "Pozycja 0:" << pozNaSiatce0.x << ".x " << pozNaSiatce0.y << ".y \n";
			std::cout << "Pozycja 1:" << pozNaSiatce1.x << ".x " << pozNaSiatce1.y << ".y \n";
#endif // SYSTEM_ZAJMOWANIA_DEBUG

			
			if (ZwrocCzyMozeZmapowac(pozNaSiatce0.x, pozNaSiatce0.y) == true && ZwrocCzyMozeZmapowac(pozNaSiatce1.x, pozNaSiatce1.y)==true )
			{
				
				std::vector<unsigned int> &ZmapowaneObszary0 = TablicaZmapowaneTereny[ZwrocIndexKlatki(pozNaSiatce0.x, pozNaSiatce0.y)];
				std::vector<unsigned int> &ZmapowaneObszary1 = TablicaZmapowaneTereny[ZwrocIndexKlatki(pozNaSiatce1.x, pozNaSiatce1.y)];
				
				for (unsigned int IndexKlatki1 : ZmapowaneObszary1)
				{
					auto ZnajdzObiekt = std::find(ZmapowaneObiekty[IndexKlatki1].begin(), ZmapowaneObiekty[IndexKlatki1].end(), IndexObiektu);
					if (ZnajdzObiekt != ZmapowaneObiekty[IndexKlatki1].end())
					{
						*ZnajdzObiekt = ZmapowaneObiekty[IndexKlatki1].back();
						ZmapowaneObiekty[IndexKlatki1].pop_back();
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
						std::cout << "Wyrzuca Z IndexKlatki :"<< IndexKlatki1  <<" Obiekt :" << IndexObiektu << "\n";
#endif

					}
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
					else
					{
						std::cout << "Nie Wyrzuca Z IndexKlatki :" << IndexKlatki1 << " Obiekt :" << IndexObiektu << "\n";
					}
#endif
					
				}
				
				for (unsigned int IndexKlatki0 : ZmapowaneObszary0)
				{
					


					if ( CheckCollisionPointPoly(Pozycja, TablicaPunktyTerenu[IndexKlatki0].data(), TablicaPunktyTerenu[IndexKlatki0].size()) == true)
					{
						auto ZnajdzObiekt = std::find(ZmapowaneObiekty[IndexKlatki0].begin(), ZmapowaneObiekty[IndexKlatki0].end(), IndexObiektu);

#ifdef SYSTEM_ZAJMOWANIA_DEBUG

						if (ZnajdzObiekt == ZmapowaneObiekty[IndexKlatki0].end()) std::cout << "Nie znaleziono w indeksie klatki : " << IndexKlatki0 << " Obiektu : " << IndexObiektu << "\n";
						else std::cout << "Znaleziono w indeksie klatki : " << IndexKlatki0 << " Obiektu : " << IndexObiektu << "\n";
#endif
						if (ZnajdzObiekt == ZmapowaneObiekty[IndexKlatki0].end())
							ZmapowaneObiekty[IndexKlatki0].emplace_back(IndexObiektu);
						break;
					}
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
					else
					{
						std::cout << "Nie jest na polu o indeksie :" << IndexKlatki0<<"\n";
					}

#endif
					
				}
			}
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
			else
			{
				std::cout << "Nie moze zmapowac pozycji \n";
				std::cout<<"Czy moze zmapowac pozycje :"<< ZwrocCzyMozeZmapowac(pozNaSiatce0.x, pozNaSiatce0.y)<<"\n";
				std::cout << "Czy moze zmapowac pozycje poprzednia:" << ZwrocCzyMozeZmapowac(pozNaSiatce1.x, pozNaSiatce1.y)<<"\n";
				std::cout << "Czy zainicjowanao: "<<SystemZainicjowany<<"\n";
			}
#endif
		}
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
		else
		{
			if(RozmiarKlatek==0) std::cout << "Rozmair Sie nie zgadza \n";
			if (CzyZaktualizowac == false) std::cout << "Nie ma aktualizacji \n";
			std::cout << "Nie mapuje Wogole \n";


		}
#endif // SYSTEM_ZAJMOWANIA_DEBUG

	}
	void SystemZajmowaniaSojuszy::Logika(std::vector<Obiekt*>& Obiekty, CzasLogiki& Czas)
	{
		if (Czas.ZwrocTick() % static_cast<unsigned char>(Czas.ZwroctickRate()))
		{
			for (Obiekt*& obiekt : Obiekty)
			{
				this->ZmapujObiekt(obiekt->ZwrocIndexObiektu(), obiekt->ZwrocCzyZaktualizowacSystemy(), obiekt->ZwrocPozycje(), obiekt->ZwrocPoprzedniaPozycje(), obiekt->ZwrocTypy());
			}
		}
		
	}

#ifdef SYSTEM_ZAJMOWANIA_DEBUG
	void SystemZajmowaniaSojuszy::Debug()
	{
		std::default_random_engine generator;
		for (std::array<Vector2, 4> &czworokat : TablicaPunktyTerenu)
		{
			std::uniform_int_distribution<int> dystrybucja(0,0xFF);
			Color kolor;
			kolor.a = 70;
			kolor.r = dystrybucja(generator);
			kolor.g = dystrybucja(generator);
			kolor.b = dystrybucja(generator);
			DrawTriangle(czworokat.at(2),czworokat.at(1),czworokat.at(0),kolor);
			DrawTriangle(czworokat.at(0), czworokat.at(3), czworokat.at(2), kolor);
			//DrawTriangle(czworokat.at(2), czworokat.at(3), czworokat.at(0), kolor);
		}
		for (Vector2& punkciki : LosowePunkciki)
		{
			DrawCircle(static_cast<int>(punkciki.x), static_cast<int>(punkciki.y),5, PINK);
		}
		for (int x = 0; x <= RozmiarSystemu; x++)
		{
			for (int y = 0; y <= RozmiarSystemu; y++)
			{
				DrawCircle(x * static_cast<int>(RozmiarKlatek), static_cast<int>(RozmiarKlatek) * y, 5, GREEN);
				NarysujDebug(x, y);
				
			}
		}
		


	}
#endif // SYSTEM_ZAJMOWANIA_DEBUG
