#include "Mapa.h"




TeksturaTileSet::TeksturaTileSet(bool Zajente,std::filesystem::path Sciezka, unsigned int &Rozmiar)
{
	if (std::filesystem::exists(Sciezka) == true)
	{
		this->Zajente = Zajente;
		tekstura = LoadTexture(Sciezka.string().c_str());
		IloscKlatek = static_cast<unsigned int>(tekstura.width / Rozmiar);
		if (IsTextureValid(tekstura) == true) std::cout << "Zaladowano Teksture :" << Sciezka.string() << "\n";
		else std::cout << "Nie Zaladowano Tekstury :" << Sciezka.string() << "\n";
	}
	else std::cout << "Nie zaladowano Tekstury :" << Sciezka.string() << "\n";
}
Rectangle TeksturaTileSet::ZwrocWymiary( unsigned int& Rozmiar, unsigned int IndexKlatki)
{
	return { static_cast<float>(IndexKlatki * Rozmiar),0,static_cast<float>(Rozmiar),static_cast<float>(Rozmiar) };
}
unsigned int TeksturaTileSet::ZwrocIloscKlatek()
{
	return IloscKlatek;
}

// -------------------------------------------------------

void StworzTileSet(std::filesystem::path Sciezka, std::string NazwaFolderu, unsigned int LiczbaTileSetow, unsigned int RozmiarKlatki)
{
	if (std::filesystem::exists(Sciezka) == true && std::filesystem::is_directory(Sciezka) == true)
	{
		std::filesystem::path NowyFolder = Sciezka.string() + "/" + NazwaFolderu;
		if (std::filesystem::exists(NowyFolder) == false) std::filesystem::create_directory(NowyFolder);
		if (std::filesystem::exists(NowyFolder) == true && std::filesystem::is_directory(NowyFolder) == true)
		{
			
			for (unsigned int index = 0; index < LiczbaTileSetow; index++)
			{
				Image zdjecie = GenImageColor(RozmiarKlatki, RozmiarKlatki, { 255,255,255,255 });
				if (ExportImage(zdjecie, std::string(NowyFolder.string() + "/TILESET" + std::to_string(index) + ".png").c_str()) == true)
				{
					std::cout << "Zapisano Zdjecia :" << NowyFolder.string() + "/TILESET" + std::to_string(index) + ".png" << "\n";
				}
				else  std::cout << "Nie Zapisano Zdjecia :" << NowyFolder.string() + "/TILESET" + std::to_string(index) + ".png" << "\n";
				
			}
			
			std::ofstream Plik(NowyFolder.string() + "/info.obi");
			if (Plik.is_open() == true && Plik.good() == true)
			{
				blmp::Obiekt TileSety{ "TILESETY",{} };
				for (unsigned int index = 0; index < LiczbaTileSetow; index++)
				{
					
					TileSety.Wlasciwosci.emplace_back("TILESET" + std::to_string(index), blmp::Dane(false));
				}
				std::cout << "Zaladowano Plik Informacjyny"<<"\n";
				blmp::ZapiszObiekt(TileSety, Plik);

				Plik.close();
			}
			else std::cout << "Nie stworzono Pliku informacji \n";
		}
	}
	else std::cout << "Sciezka nie istnieje: " << Sciezka.string() << "\n albo nie jest folderem TileSet Nie zostal Stworzony \n";


}



//------------------------------------------
jakaTekstura::jakaTekstura(unsigned int indexTekstury, unsigned int Klatka)
{
	this->indexTekstury = indexTekstury;
	this->Klatka = Klatka;
}
jakaTekstura jakaTekstura::operator=(const jakaTekstura& tekstura)
{
	this->indexTekstury = tekstura.indexTekstury;
	this->Klatka = tekstura.Klatka;
	return *this;
}







//------------------------------------------

Mapa::Mapa(std::filesystem::path TileSety, unsigned int RozmiarKlatki)
{
	ZaladujTekstury(TileSety);
	this->RozmiarKlatki = RozmiarKlatki;
	szerokosc = 0;
	wysokosc = 0;
	Pola = {};
	Jakie = {};
}

bool Mapa::WMapie(const PozycjaNaMapie& poz)
{
	if (0 <= poz.x && szerokosc > poz.x && 0 <= poz.y && wysokosc > poz.y) return true;
	else return false;
}
void Mapa::UstawTypPola(const PozycjaNaMapie& poz, TypPola typ)
{
	if (WMapie(poz) == true)
	{ 
		Pola[poz.x + (poz.y * szerokosc)] = typ;
	}
}

//Odpowiada za Tekstury

void Mapa::ZaladujTekstury(std::filesystem::path Folder)
{

	std::filesystem::path Info = Folder.string() + "/info.obi";

	if (std::filesystem::exists(Folder) == true && std::filesystem::exists(Info)==true && std::filesystem::is_directory(Folder) == true)
	{



		

		std::cout << "Zaladowano Folder :" << Folder.string() << "\n";
		for (const auto iterator : std::filesystem::directory_iterator(Folder))
		{
			std::cout<< iterator.path().filename() << "\n";
		}
		for (const auto iterator : std::filesystem::directory_iterator(Folder))
		{
			if (std::filesystem::equivalent(iterator.path(), Info) == false)
			{

				tekstury.emplace_back(false, iterator, RozmiarKlatki);
			}
		}
		std::ifstream PlikInfo(Info);
		if (PlikInfo.is_open()==true && PlikInfo.good()==true)
		{
			blmp::Obiekt obiekt{ "",{} };
			blmp::WczytajObiekt(obiekt, PlikInfo);
			for (unsigned int index=0;index <  tekstury.size();index++ )
			{
				blmp::WczytajWartoscWlasciwosci(obiekt, "TILESET" + std::to_string(index), tekstury[index].Zajente);
			}
			PlikInfo.close();
		}
	}
	else std::cout << "Nie Zaladowano Folder :" << Folder.string() << "\n";
}
void Mapa::UstawTileSet(const PozycjaNaMapie& poz, unsigned int IndexTekstury)
{
	if (WMapie(poz) == true && tekstury.empty()==false && tekstury.size()>IndexTekstury  )
	{
		Jakie[poz.y * RozmiarKlatki + poz.x].Klatka = 0;
		Jakie[poz.y * RozmiarKlatki + poz.x].indexTekstury = IndexTekstury;
		if (tekstury[IndexTekstury].Zajente == true)
		{
			Pola[poz.y * RozmiarKlatki + poz.x] = TypPola::ZAMKNIENTE;
		}
		else Pola[poz.y * RozmiarKlatki + poz.x] = TypPola::OTWARTE;
	}
}
void Mapa::RenderujTileSet(PozycjaNaMapie poz)
{
	unsigned int index = static_cast<unsigned int>(poz.x) + static_cast<unsigned int>(poz.y) * RozmiarKlatki;
	if (tekstury.empty()==false  && IsTextureValid(tekstury[Jakie[index].indexTekstury].tekstura) == true)
	{
		DrawTextureRec(tekstury[Jakie[index].indexTekstury].tekstura,
			tekstury[Jakie[index].indexTekstury].ZwrocWymiary(RozmiarKlatki, Jakie[index].Klatka),
			{ static_cast<float>(poz.x * RozmiarKlatki),static_cast<float>(poz.y * RozmiarKlatki) },
			{ 255,255,255,255 });
	}
	//else DrawRectangle(poz.x * RozmiarKlatki, poz.y * RozmiarKlatki, RozmiarKlatki, RozmiarKlatki, { 255,255,255,255 });
}
void Mapa::NarysujZablokownaPozycje(PozycjaNaMapie poz)
{
	
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), [&](const PozycjaWCzasie& wczasie) {return  poz.x == wczasie.poz.x && poz.y == wczasie.poz.y; });
	if (iterator != PozycjeCzasowe.end())
	{
		std::string Nazwa = std::to_string(iterator->wyjscie);
		if (iterator->wyjscie == std::numeric_limits<unsigned int>::infinity()) Nazwa = "n";
		int rozmiarTekstu=  (static_cast<int>(RozmiarKlatki) - Nazwa.size() * (static_cast<int>(RozmiarKlatki) / 10))/2;
		DrawText(Nazwa.c_str(), poz.x * static_cast<int>(RozmiarKlatki) + rozmiarTekstu, poz.y * static_cast<int>(RozmiarKlatki) + static_cast<int>(RozmiarKlatki / 2), static_cast<int>(RozmiarKlatki) / 10, BLACK);
		DrawRectangle(static_cast<int>(RozmiarKlatki) * poz.x, static_cast<int>(RozmiarKlatki) * poz.y, static_cast<int>(RozmiarKlatki), static_cast<int>(RozmiarKlatki), { 253,249,0,100 });
	}


}


void Mapa::StworzMape(unsigned int szerokosc, unsigned int wysokosc,const std::vector<PozycjaNaMapie> &PozycjeZajente )
{
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
	
	Pola.resize(szerokosc * wysokosc, OTWARTE);
	Jakie.resize(szerokosc *wysokosc, { 0,0 });

	for (const PozycjaNaMapie& poz : PozycjeZajente)
	{
		UstawTypPola(poz,TypPola::ZAMKNIENTE);
	}
}
Vector2 Mapa::Wysrodkuj(PozycjaNaMapie poz)
{
	Vector2 wektor;
	wektor.x = static_cast<float>(poz.x) + static_cast<float>(RozmiarKlatki / 2) - static_cast<float>(static_cast<unsigned int>(poz.x) % (RozmiarKlatki));
	wektor.y = static_cast<float>(poz.y) + static_cast<float>(RozmiarKlatki / 2) - static_cast<float>(static_cast<unsigned int>(poz.y) % (RozmiarKlatki));
	return wektor;
}

Vector2 Mapa::SrodekPola(PozycjaNaMapie pozycja)
{
	return { (static_cast<float>(pozycja.x)+0.5f) * static_cast<float>(RozmiarKlatki),(static_cast<float>(pozycja.y)+0.5f) * static_cast<float>(RozmiarKlatki)};
}
PozycjaNaMapie Mapa::Kordynat(Vector2 wektor)
{
	return { static_cast<int>(wektor.x) / static_cast<int>(RozmiarKlatki),static_cast<int>(wektor.y) / static_cast<int>(RozmiarKlatki) };
}
//Dotyczy pozycji czasowych

void Mapa::ustawPozycjeWchodzaca(PozycjaNaMapie pozycja, unsigned int wchodzacy,const unsigned int &IndexObiektu)
{
	
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), [&](const PozycjaWCzasie& czasie) {
		return (czasie.poz.x == pozycja.x && czasie.poz.y==pozycja.y && IndexObiektu==czasie.IndexObiektu);
		});
	if (iterator == PozycjeCzasowe.end())
	{
		PozycjeCzasowe.emplace_back(pozycja, wchodzacy, std::numeric_limits<unsigned int>::infinity(),IndexObiektu);
	}
	else iterator->wejscie = wchodzacy;
}
void Mapa::ustawPozycjeWychodzaca(PozycjaNaMapie pozycja, unsigned int wychodzacy,const unsigned int &IndexObiektu)
{
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), [&](const PozycjaWCzasie& czasie) {
		return (czasie.poz.x == pozycja.x && czasie.poz.y == pozycja.y && IndexObiektu==czasie.IndexObiektu);
		});
	if (iterator == PozycjeCzasowe.end())
	{
		PozycjeCzasowe.emplace_back(pozycja,0,wychodzacy,IndexObiektu);
	}
	else iterator->wyjscie = wychodzacy;
}
bool Mapa::CzyPozycjaZajenta(PozycjaNaMapie poz)
{
	PozycjaWCzasie wczasie = { poz };
	auto iterator = std::find(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), wczasie);
	if (iterator != PozycjeCzasowe.end()) return true;
	else return false;
}
bool Mapa::czyPozycjaZajentaWCzasie(PozycjaNaMapie poz, unsigned int const Tick)
{
	PozycjaWCzasie wczasie = { poz };
	auto iterator = std::find(PozycjeCzasowe.begin(), PozycjeCzasowe.end(),wczasie);
	if (PozycjeCzasowe.empty()==false && iterator != PozycjeCzasowe.end())
	{
		
		 if (iterator->wyjscie == std::numeric_limits<unsigned int>::infinity()) return true;
		else if (iterator->wTymCzasie(Tick) == true) return true;
		else return false;
	}
	else return false;
}
bool Mapa::CzyPozyjaZajentaWNieskonczonosc(PozycjaNaMapie poz)
{
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), [&](const PozycjaWCzasie& wCzasie) { return (wCzasie.poz.x == poz.x && wCzasie.poz.y == poz.y && wCzasie.wyjscie==std::numeric_limits<unsigned int>::infinity());     });
	if (iterator == PozycjeCzasowe.end()) return false;
	else return true;
}
bool Mapa::CzyPozyjaZajentaWNieskonczonosc(PozycjaNaMapie poz, unsigned int indexObiektu)
{
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), [&](const PozycjaWCzasie& wCzasie) { return (wCzasie.poz.x == poz.x && wCzasie.poz.y == poz.y && wCzasie.wyjscie == std::numeric_limits<unsigned int>::infinity() && indexObiektu==wCzasie.IndexObiektu);     });
	if (iterator == PozycjeCzasowe.end()) return false;
	else return true;

}


void Mapa::UsunPozycjeWCzasie(const unsigned int Tick)
{
	if (PozycjeCzasowe.empty() == false)
	{
		//std::cout << "Tick :" << Tick << "\n";
		for (auto iterator = PozycjeCzasowe.begin(); iterator != PozycjeCzasowe.end(); )
		{
 			
			if (iterator->wyjscie!=std::numeric_limits<unsigned int>::infinity() && Tick > iterator->wyjscie)
			{
			//	std::cout << "Usun Tick:" << Tick<<"\n";
			//	std::cout << iterator->wyjscie << " wyjscie "<< iterator->poz.x<<".x "<< iterator->poz.y<<".y \n";
				PozycjeCzasowe.erase(iterator);
			}
			else iterator++;

		}
	}
	//std::cout <<"Liczba pozycji czasowych :" << PozycjeCzasowe.size() << "\n";


}
void Mapa::UsunPozycjeCzasoweDlaObiektu(unsigned int IndexObiektu)
{
	auto funkcjaszukajaca = [&](const PozycjaWCzasie& pozycja)->bool {return IndexObiektu == pozycja.IndexObiektu;  };
	auto iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), funkcjaszukajaca);
	while (iterator!=PozycjeCzasowe.end())
	{
		PozycjeCzasowe.erase(iterator);
		iterator = std::find_if(PozycjeCzasowe.begin(), PozycjeCzasowe.end(), funkcjaszukajaca);
	}
}

/// 


TypPola Mapa::ZwrocTypPola(const PozycjaNaMapie& poz)
{
	if (WMapie(poz) == false) return TypPola::NIEISTNIEJIE;
	else return Pola[poz.x + (poz.y * szerokosc)];
	}

void Mapa::Wizualizacja(CzasLogiki &czaslogiki)
{
	if (Pola.empty() == true && Jakie.empty()==true )
	{

		DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), WHITE);
		DrawText("Tablica jest pusta", GetRenderWidth() / 2, GetScreenHeight() / 2, 30, BLACK);
		//return exit(-1);
	}
	else
	{
		
		for (int index = 0; index < Jakie.size(); index++)
		{
			RenderujTileSet({ index % static_cast<int>(szerokosc),index / static_cast<int>(szerokosc) });
			if (czaslogiki.StanCzasu() == true && tekstury.empty() == false)
			{
				Jakie[index].Klatka++;
				if (Jakie[index].Klatka == tekstury[Jakie[index].indexTekstury].IloscKlatek)
					Jakie[index].Klatka = 0;
			}
			
		}
		

		for (int index = 0; index < Pola.size(); index++)
		{
			
			if (CzyPozycjaZajenta({ index%static_cast<int>(szerokosc),index/static_cast<int>(szerokosc)})==true)
			{
				NarysujZablokownaPozycje({ index % static_cast<int>(szerokosc),index / static_cast<int>(szerokosc) });
			}
			else if (Pola[index] == OTWARTE)
				DrawRectangle((index % szerokosc) * RozmiarKlatki, (index / szerokosc) * RozmiarKlatki, RozmiarKlatki, RozmiarKlatki, WHITE);
			else DrawRectangle((index % szerokosc) * RozmiarKlatki, (index / szerokosc) * RozmiarKlatki, RozmiarKlatki, RozmiarKlatki, RED);
		}
		for (unsigned int liniey = 0; liniey < szerokosc; liniey++)
		{
			DrawLine(liniey * RozmiarKlatki, 0, liniey * RozmiarKlatki, RozmiarKlatki * wysokosc, BLACK);
		}
		for (unsigned int liniex = 0; liniex < wysokosc; liniex++)
		{
			DrawLine(0, liniex * RozmiarKlatki, RozmiarKlatki * szerokosc, liniex *RozmiarKlatki, BLACK);
		}
	
	}
}



	


	
	
	//else std::cout << "Droga Pusta \n";
	

	



