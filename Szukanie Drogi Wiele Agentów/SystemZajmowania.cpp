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

	unsigned int SystemZajmowaniaSojuszy::ZwrocIloscObiektowDruzyny(Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			return TablicaIloscObiektowDanejDruzyny[ZwrocIndex(x, y)].at(druzyna).size();
		}
		else return	1;
	}
	const std::vector<unsigned int>* SystemZajmowaniaSojuszy::ZwrocTabliceObiektow(Druzyny druzyna, unsigned int x, unsigned int y)
	{
		if (CzyMozeOdczytac(x, y))
		{
			return &TablicaIloscObiektowDanejDruzyny[ZwrocIndex(x, y)].at(druzyna);
		}
		else return nullptr;
	}
	void SystemZajmowaniaSojuszy::GenerujSystem(CzasLogiki &czasLogiki)
	{
		StanInicjacji = true;
		std::default_random_engine generator;

		std::vector<Vector2> LosowePunkciki(((RozmiarSystemu) * (RozmiarSystemu)),{0,0});
		TablicaDruzynyZajmujaceTeren.resize(RozmiarSystemu * RozmiarSystemu, Druzyny::NEUTRALNA);
		this->TablicaPrzychody.resize(RozmiarSystemu * RozmiarSystemu,1);
		this->TablicaZajmowanieCzasZajmowania.resize(RozmiarSystemu * RozmiarSystemu, 30 * czasLogiki.ZwroctickRate());
		this->TablicaZajmowanieTick.resize(RozmiarSystemu * RozmiarSystemu, 0);
		this->TablicaZmapowaneTereny.resize(RozmiarSystemu * RozmiarSystemu, {});
		TablicaIloscObiektowDanejDruzyny.resize(RozmiarSystemu & RozmiarSystemu, {
			{Druzyny::DRUZYNA1,{}},
			{Druzyny::DRUZYNA2,{}},
			{Druzyny::DRUZYNA3,{}},
			{Druzyny::DRUZYNA4,{}},
			{Druzyny::DRUZYNA5,{}},
			{Druzyny::DRUZYNA6,{}},
		    {Druzyny::DRUZYNA7,{}},
			{Druzyny::DRUZYNA8,{}},
			});




		for (unsigned int x = 0; x < RozmiarSystemu+1  ; x++)
		{
			for (unsigned int y = 0; y < RozmiarSystemu+1; y++ )
			{
				std::uniform_int_distribution<int> dystrybucjaX(x * RozmiarKlatek, (x+1)* RozmiarKlatek );
				std::uniform_int_distribution<int> dystrybucjaY(y * RozmiarKlatek, (y + 1) * RozmiarKlatek);
				if (x == 0)
				{
					LosowePunkciki[ZwrocIndex(x, y)].x = 0;
				}
				else if (x == RozmiarSystemu)
				{
					LosowePunkciki[ZwrocIndex(x, y)].x = RozmiarKlatek * RozmiarSystemu;
				}
				else
				{
					LosowePunkciki[ZwrocIndex(x, y)].x = dystrybucjaX(generator);
				}
				if (y == 0)
				{
					LosowePunkciki[ZwrocIndex(x, y)].y = 0;
				}
				else if (y == RozmiarSystemu)
				{
					LosowePunkciki[ZwrocIndex(x, y)].y = RozmiarKlatek * RozmiarSystemu;
				}
				else
				{
					LosowePunkciki[ZwrocIndex(x, y)].y = dystrybucjaY(generator);
				}
			}
		}
		
		for (unsigned int x = 0; x < RozmiarSystemu; x++)
		{
			for (unsigned int y = 0; y < RozmiarSystemu; y++)
			{
				TablicaPunktyTerenu[ZwrocIndex(x, y)][0] = LosowePunkciki[ZwrocIndex(x, y)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][1] = LosowePunkciki[ZwrocIndex(x+1, y)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][2] = LosowePunkciki[ZwrocIndex(x+1, y+1)];
				TablicaPunktyTerenu[ZwrocIndex(x, y)][3] = LosowePunkciki[ZwrocIndex(x, y+1)];

				PozycjaNaMapie pozA = {static_cast<int>(LosowePunkciki[ZwrocIndex(x,y)].x/RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndex(x,y)].y)};
				PozycjaNaMapie pozB = { static_cast<int>(LosowePunkciki[ZwrocIndex(x+1,y)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndex(x+1,y)].y) };;
				PozycjaNaMapie pozC = { static_cast<int>(LosowePunkciki[ZwrocIndex(x+1,y+1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndex(x+1,y+1)].y) };;
				PozycjaNaMapie pozD = { static_cast<int>(LosowePunkciki[ZwrocIndex(x,y+1)].x / RozmiarKlatek),static_cast<int>(LosowePunkciki[ZwrocIndex(x,y+1)].y) };;
				
			auto iteratorA= std::find(TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].begin(),TablicaZmapowaneTereny[ZwrocIndex(pozA.x,pozA.y)].end(), ZwrocIndex(x, y));
			auto iteratorB = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].end(), ZwrocIndex(x, y));
			auto iteratorC = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].end(), ZwrocIndex(x, y));
			auto iteratorD = std::find(TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].begin(), TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].end(), ZwrocIndex(x, y));

			if (iteratorA == TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozA.x, pozA.y)].emplace_back(ZwrocIndex(x, y));
			if (iteratorB == TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozB.x, pozB.y)].emplace_back(ZwrocIndex(x, y));
			if (iteratorC == TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozC.x, pozC.y)].emplace_back(ZwrocIndex(x, y));
			if (iteratorD == TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].end()) TablicaZmapowaneTereny[ZwrocIndex(pozD.x, pozD.y)].emplace_back(ZwrocIndex(x, y));

			}

		}




	}
	void SystemZajmowaniaSojuszy::ZmapujObiekty(std::vector<Obiekt*>& Obiekty)
	{


	}
	void SystemZajmowaniaSojuszy::Logika(std::vector<Obiekt*>& Obiekty, CzasLogiki& Czas)
	{


		}