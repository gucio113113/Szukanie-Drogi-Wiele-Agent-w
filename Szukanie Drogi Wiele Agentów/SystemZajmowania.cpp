#include "SystemZajmowania.h"

void SystemZajmowaniaSojuszy::RozpocznijZajmowanie(unsigned int x, unsigned int y)
{
	

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
		if (CzyMozeOdczytac(x, y))
		{
			TablicaDruzynyZajmujaceTeren[ZwrocIndex(x,y)] = druzyna;
		}
	}
	void SystemZajmowaniaSojuszy::UstawPrzychod(unsigned int x, unsigned int y, unsigned int Przychod)
	{
		if (CzyMozeOdczytac(x, y))
		{
			 TablicaPrzychody[ZwrocIndex(x, y)] = Przychod;
		}

		}
	void SystemZajmowaniaSojuszy::UstawCzasZajmowania(unsigned int x, unsigned int y, unsigned int CzasZajmowania)
	{
		if (CzyMozeOdczytac(x, y))
		{
			TablicaZajmowanieCzasZajmowania[ZwrocIndex(x, y)] = CzasZajmowania;
		}

	}
	void SystemZajmowaniaSojuszy::UstawTick(unsigned int x, unsigned int y, unsigned int Tick)
	{
		if (CzyMozeOdczytac(x, y))
		{
			TablicaZajmowanieTick[ZwrocIndex(x, y)] = Tick;
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
		if (CzyMozeOdczytac(x, y))
		{
			return TablicaDruzynyZajmujaceTeren[ZwrocIndex(x, y)];
		}
		else return Druzyny::NEUTRALNA;

	}
	unsigned int SystemZajmowaniaSojuszy::ZwrocPrzychod(unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			return TablicaPrzychody[ZwrocIndex(x, y)];
		}
		else return 1;

		}
	unsigned int SystemZajmowaniaSojuszy::ZwrocCzasZajmowania(unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			return TablicaZajmowanieCzasZajmowania[ZwrocIndex(x, y)];
		}
		return 1;

		}
	unsigned int SystemZajmowaniaSojuszy::ZwrocTick(unsigned int x, unsigned int y)
	{

		if (CzyMozeOdczytac(x, y))
		{
			return TablicaZajmowanieTick[ZwrocIndex(x, y)];
		}
		return 1;
	}

	//Zwraca Zbiotry

	unsigned int SystemZajmowaniaSojuszy::ZwrocIloscObiektowDruzyny(std::vector<Obiekt*>& Obiekty, Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			return TablicaIloscObiektowDanejDruzyny[ZwrocIndex(x, y)].at(druzyna).size();
		}
		else return	1;
	}
	std::vector<unsigned int> SystemZajmowaniaSojuszy::ZwrocTabliceObiektow(std::vector<Obiekt*>& Obiekty, Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			std::vector<unsigned int> IndexySpelniajace;
			for()

		}
		return {};
	}
	void SystemZajmowaniaSojuszy::GenerujSystem(const unsigned int TickRate)
	{
		StanInicjacji = true;
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
		this->TablicaIndexyObiektow.resize(RozmiarSystemu * RozmiarSystemu,{});
		


		
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
				TablicaPunktyTerenu[ZwrocIndex(x, y)][0] = LosowePunkciki[ZwrocIndexDlaPunktow(x,y)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][1] = LosowePunkciki[ZwrocIndexDlaPunktow(x + 1, y)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][2] = LosowePunkciki[ZwrocIndexDlaPunktow(x + 1, y + 1)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][3] = LosowePunkciki[ZwrocIndexDlaPunktow(x, y + 1)];

				PozycjaNaMapie pozA = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y)].y / RozmiarKlatek) };
				PozycjaNaMapie pozB = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y)].y / RozmiarKlatek) };
				PozycjaNaMapie pozC = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y + 1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x + 1,y + 1)].y / RozmiarKlatek) };
				PozycjaNaMapie pozD = { static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y + 1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndexDlaPunktow(x,y+1)].y/RozmiarKlatek) };
				PozycjaNaMapie pozE = { static_cast<int>(x * RozmiarKlatek+ (RozmiarKlatek/2)),static_cast<int>(y * RozmiarKlatek + (RozmiarKlatek/2))};


				unsigned int index = ZwrocIndex(x, y);

				if (pozA.x < RozmiarSystemu && pozA.y < RozmiarSystemu)
				{
					auto iteratorA = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].end(), index);
					if (iteratorA == TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].emplace_back(index);
				}
				if (pozB.x < RozmiarSystemu && pozB.y < RozmiarSystemu)
				{
					auto iteratorB = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].end(), index);
					if (iteratorB == TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].emplace_back(index);

				}
				if (pozC.x < RozmiarSystemu && pozC.y < RozmiarSystemu)
				{
					auto iteratorC = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].end(), index);
					if (iteratorC == TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].emplace_back(index);

				}
				if (pozD.x < RozmiarSystemu && pozD.y < RozmiarSystemu)
				{
					auto iteratorD = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].end(), index);
					if (iteratorD == TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].emplace_back(index);
				}
				if (pozE.x < RozmiarSystemu && pozE.y < RozmiarSystemu)
				{
					auto iteratorE = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozE.x, pozE.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozE.x, pozE.y)].end(), index);
					if (iteratorE == TablicaZmapowaneTereny[ZwrocIndex(pozE.x, pozE.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozE.x, pozE.y)].emplace_back(index);
				}
			


			

			}

		}
	}
	void SystemZajmowaniaSojuszy::ZmapujObiekty(std::vector<Obiekt*>& Obiekty)
	{
		for (Obiekt*& obiekt : Obiekty)
		{
			if (!!(obiekt->ZwrocTypy() & Typy::SYSTEM_ZAJMOWANIA))
			{
				Vector2 Pozycja = obiekt->ZwrocPozycje();
				PozycjaNaMapie poz = { static_cast<int>(Pozycja.x / RozmiarKlatek),static_cast<int>(Pozycja.y / RozmiarKlatek) };
				Druzyny wlasciciel = obiekt->ZwrocSojusz().zwrocWlasciciel();
				if (CzyMozeOdczytac(poz.x, poz.y) == true)
				{
					for (unsigned int& NumerSiatki : TablicaZmapowaneTereny[ZwrocIndex(poz.x, poz.y)])
					{
						std::array<Vector2, 4>& CzworoBok = TablicaPunktyTerenu[NumerSiatki];
						if (CheckCollisionPointPoly(Pozycja, CzworoBok.data(), 4) == true)
						{
							std::vector<unsigned int>& tab = TablicaIloscObiektowDanejDruzyny[ZwrocIndex(poz.x, poz.y)].at(wlasciciel);
							auto szukanie = std::find(tab.begin(), tab.end(), obiekt->ZwrocIndexObiektu());
							if (szukanie == tab.end())
								tab.emplace_back(obiekt->ZwrocIndexObiektu());
#ifdef SYSTEM_ZAJMOWANIA_DEBUG
							std::cout << "Kolizja Wykonana dla Obiektu o Indeksie :" << obiekt->ZwrocIndexObiektu() << "\n";
#endif // SYSTEM_ZAJMOWANIA_DEBUG


						}
					}
				}


			}

		}
	}
	void SystemZajmowaniaSojuszy::OdMapujObiekty()
	{
		
		



	}
	SystemZajmowaniaSojuszy::SystemZajmowaniaSojuszy(unsigned int RozmiarSystemu, unsigned int RozmiarKlatek)
	{
		this->RozmiarSystemu = RozmiarSystemu;
		this->RozmiarKlatek = RozmiarKlatek;
		this->GenerujSystem(60);

	}
	void SystemZajmowaniaSojuszy::Logika(std::vector<Obiekt*>& Obiekty, CzasLogiki& Czas)
	{
		if (Czas.ZwrocTick() % Czas.ZwrocTick() == 0)
		{
			OdMapujObiekty();
			ZmapujObiekty(Obiekty);
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

				switch (pokazwartoscidebug)
				{
				case SystemZajmowaniaSojuszy::PokazWartosciDebug::PRZYCHOD_DEBUG:
				{
					std::string napis = std::to_string(TablicaPrzychody[ZwrocIndex(x, y)]);
					NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);
					break;
				}
				case SystemZajmowaniaSojuszy::PokazWartosciDebug::ZAJMOWANIA_TICK_DEBUG:
				{
					std::string napis = std::to_string(TablicaZajmowanieTick[ZwrocIndex(x, y)]);
					NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);

					break;
				}
				case SystemZajmowaniaSojuszy::PokazWartosciDebug::ZAJMOWANIA_CZASZAJMOWANIA_DEBUG:
				{
					std::string napis = std::to_string(TablicaZajmowanieCzasZajmowania[ZwrocIndex(x, y)]);
					NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);

					break;
				}
				case SystemZajmowaniaSojuszy::PokazWartosciDebug::ZMAPOWANY_TEREN_DEBUG:
				{
					std::string napis = std::to_string(TablicaZmapowaneTereny[ZwrocIndex(x, y)].size());
					NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);

					break;
				}
				case SystemZajmowaniaSojuszy::PokazWartosciDebug::ILOSCOBIEKTOW_DANEJ_DRUZYNY_DEBUG:
				{
					std::string napis = std::to_string(TablicaIloscObiektowDanejDruzyny[ZwrocIndex(x,y)].at(Druzyny::DRUZYNA1).size());
					NarysujTekst(napis, RozmiarKlatek / 10, (x * RozmiarKlatek) + RozmiarKlatek / 2, (y * RozmiarKlatek) + RozmiarKlatek / 2, BLACK);

					break;

				}

				default:
					break;
				}
			}
		}
		


	}
#endif // SYSTEM_ZAJMOWANIA_DEBUG
