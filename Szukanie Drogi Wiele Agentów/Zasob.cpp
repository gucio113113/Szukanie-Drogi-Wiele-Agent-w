#include "Zasob.h"

std::string ZwrocNazweKierunku(KierunkiSwiata kierunki)
{
	switch (kierunki)
	{
	case KierunkiSwiata::POLUDNIE: return "POLUDNIE";
	case KierunkiSwiata::POLUDNIE_ZACHOD:  return "POLUDNIE_ZACHOD";
	case KierunkiSwiata::ZACHOD:  return "ZACHOD";
	case KierunkiSwiata::POLNOC_ZACHOD: return "POLNOC_ZACHOD";
	case KierunkiSwiata::POLNOC: return "POLNOC";
	case KierunkiSwiata::POLNOC_WSCHOD: return "POLNOC_WSCHOD";
	case KierunkiSwiata::WSCHOD: return "WSCHOD";
	case KierunkiSwiata::POLUDNIE_WSCHOD: return "POLUDNIEWCHOD";
	case KierunkiSwiata::ZADEN: return "ZADEN";
	}
}
KierunkiSwiata ZwrocKierunekZNazwy(std::string NazwaKierunku)
{
	if (NazwaKierunku == "POLUDNIE") return KierunkiSwiata::POLUDNIE;
	else if (NazwaKierunku == "POLUDNIE_ZACHOD") return KierunkiSwiata::POLUDNIE_ZACHOD;
	else if (NazwaKierunku == "ZACHOD") return KierunkiSwiata::ZACHOD;
	else if (NazwaKierunku == "POLNOC_ZACHOD") return KierunkiSwiata::POLNOC_ZACHOD;
	else if (NazwaKierunku == "POLNOC") return KierunkiSwiata::POLNOC;
	else if (NazwaKierunku == "POLNOC_WSCHOD")return KierunkiSwiata::POLNOC_WSCHOD;
	else if (NazwaKierunku == "WSCHOD") return KierunkiSwiata::WSCHOD;
	else if (NazwaKierunku == "POLUDNIEWCHOD")return KierunkiSwiata::POLUDNIE_WSCHOD;
	else return KierunkiSwiata::ZADEN;
}





TypyAnimacji ZwrocTypAnimacji(std::string NazwaAnimacji)
{
	if (NazwaAnimacji == "STRZELANIE" || NazwaAnimacji=="STRZELANIE.png") return TypyAnimacji::STRZELANIE;
	 if (NazwaAnimacji == "CHODZENIE" || NazwaAnimacji=="CHODZENIE.png") return TypyAnimacji::CHODZENIE;
	 else return TypyAnimacji::STANIE;
}
std::string ZwrocNazweAnimacji(TypyAnimacji typanimacji)
{
	switch (typanimacji)
	{
	case STRZELANIE: return "STRZELANIE";
		break;
	case CHODZENIE: return "CHODZENIE";
		break;
	default: return "STANIE";
		break;
	}
}
//Zwraca akierunek swiata na pdostawie rozniczy dwoch pozycji
KierunkiSwiata ZwrocKierunek(PozycjaNaMapie A, PozycjaNaMapie B)
{
	PozycjaNaMapie poz = { B.x - A.x,B.y- A.y };
	KierunkiSwiata kierunek=KierunkiSwiata::ZADEN;
	if (poz.x > 0) kierunek = kierunek | KierunkiSwiata::WSCHOD;
	else if (poz.x < 0) kierunek = kierunek | KierunkiSwiata::ZACHOD;
	if (poz.y > 0) kierunek = kierunek | KierunkiSwiata::POLUDNIE;
	else if (poz.y < 0) kierunek = kierunek | KierunkiSwiata::POLNOC;

	return kierunek;
}




Animacja::Animacja(unsigned int CoKtoryTick,   std::string AdresTekstury, TypyAnimacji typ, Vector2& Rozmiar)
{
	this->CoKtoryTick = CoKtoryTick;
	this->typ = typ;
	this->tekstura = LoadTexture(AdresTekstury.c_str());
	this->LiczbaKlatek = static_cast<unsigned int>(this->tekstura.width / Rozmiar.x);
	if (IsTextureValid(tekstura) == false)
	{
#ifdef ZASOBY_DEBUG
		std::cout << "Animacja nie zostala wczytana: " << AdresTekstury << "\n";
#endif
	}
#ifdef ZASOBY_DEBUG
	else std::cout << "Animacja zostala wczytana \n";
#endif
}
Rectangle Animacja::ZwrocKlatke(KierunkiSwiata kierunki, Vector2& Rozmiar, const unsigned int Klatka)
{
	Rectangle prostokat;

	prostokat.x = Klatka * Rozmiar.x;
	prostokat.y = ZwrocIndexKlatki(kierunki) * Rozmiar.y;
	prostokat.width = Rozmiar.x;
	prostokat.height = Rozmiar.y;

	return prostokat;
}
bool Animacja::operator ==(const Animacja& animacja)
{
	if (animacja.typ == typ) return true;
	else return false;




}
unsigned int Animacja::Zwroctick()
{
	return CoKtoryTick;
}
void ZestawAnimacji::WczytajKtoryTyp(TypyAnimacji typAnimacji, blmp::Obiekt& obiekt)
{
	auto znajdz = std::find_if(animacje.begin(), animacje.end(), [&](const Animacja& anima) { return typAnimacji == anima.typ; });
	if (znajdz != animacje.end())
	{
		blmp::WczytajWartoscWlasciwosci(obiekt, ZwrocNazweAnimacji(typAnimacji), znajdz->CoKtoryTick);
#ifdef ZASOBY_DEBUG
		std::cout << "Wczytano Animacje :" << ZwrocNazweAnimacji(typAnimacji) << "\n";
#endif
	}
#ifdef ZASOBY_DEBUG
	else std::cout << "Nie wczytano animacji o Typie :" << ZwrocNazweAnimacji(typAnimacji) << "\n";
#endif
}



ZestawAnimacji::ZestawAnimacji(std::filesystem::path Folder)
{
	

	std::filesystem::path SciezkaInfo = std::filesystem::path{ Folder.string() + "/info.obi" };
#ifdef ZASOBY_DEBUG
	if (std::filesystem::exists(SciezkaInfo) == false) std::cout << "Nie znaleziono Zestawu Animacji :" << SciezkaInfo.string() << "\n";
	if (std::filesystem::exists(Folder) == false) std::cout << "Nie znaleziono Folderu Zestawu Animaacji :" << Folder.string() << "\n";
#endif
	if (std::filesystem::exists(Folder) == true && std::filesystem::exists(SciezkaInfo)==true && std::filesystem::is_directory(Folder) == true)
	{
#ifdef ZASOBY_DEBUG
		std::cout << "Zawartosc Foldera :" << Folder.string() << "\n";

		for (const auto& iterator : std::filesystem::directory_iterator(Folder))
		{
			if (std::filesystem::equivalent(iterator.path(), SciezkaInfo) == false)
			{
				
				std::cout << iterator.path()<<"\n";
					
			}
		}
#endif

		for (const auto &iterator : std::filesystem::directory_iterator(Folder))
		{
			if (std::filesystem::equivalent(iterator.path(),SciezkaInfo)==false )
			{
				 TypyAnimacji typ= ZwrocTypAnimacji(iterator.path().filename().string());
			#ifdef ZASOBY_DEBUG
				 std::cout << "Jaki typ :" << iterator.path().filename().string() << "\n";
			#endif
				 animacje.emplace_back(0, iterator.path().string(), typ,Rozmiar);
			}
		}

			//std::filesystem::equivalent()


		std::ifstream Plik(SciezkaInfo);
		if (Plik.is_open() == true && Plik.good()==true)
		{
			blmp::Obiekt obiekt{ "",{} };
			blmp::WczytajObiekt(obiekt, Plik);
			this->NazwaAnimacji = obiekt.Nazwa;

			
			blmp::WczytajWartoscWlasciwosci(obiekt, "ROZMIARX",Rozmiar.x);
			blmp::WczytajWartoscWlasciwosci(obiekt, "ROZMIARY", Rozmiar.y);

			WczytajKtoryTyp(TypyAnimacji::STANIE, obiekt);
			WczytajKtoryTyp(TypyAnimacji::CHODZENIE, obiekt);
			WczytajKtoryTyp(TypyAnimacji::STRZELANIE, obiekt);

	#ifdef ZASOBY_DEBUG
			std::cout << "Wczytano Plik Informacyjny :" << SciezkaInfo.string();
	#endif
			Plik.close();
		}
	#ifdef ZASOBY_DEBUG
		else std::cout << "Nie wczytano Pliku informacyjnego dla zestatu animacji :" << SciezkaInfo.string() << "\n";
	#endif
	}
	else
	{
	#ifdef ZASOBY_DEBUG
		std::cout << "Zestaw Animacji o Folderze :" << Folder.string() << " Nie zostal znaleziony \n";
	#endif
	}
}
void ZestawAnimacji::DodajAnimacje(unsigned int CoKtoryTick, std::string AdresTekstury, TypyAnimacji typ)
{
	animacje.emplace_back(CoKtoryTick,AdresTekstury,typ,Rozmiar);
}
Rectangle ZestawAnimacji::ZwrocAnimacje(TypyAnimacji typAnimacji,KierunkiSwiata kierunki, const unsigned int Klatka)
{
	auto iterator = std::find_if(animacje.begin(), animacje.end(), [&](const Animacja& animacja) {return typAnimacji == animacja.typ; });
	if (iterator != animacje.end())
	{
		return iterator->ZwrocKlatke(kierunki, Rozmiar, Klatka);
	}
	else return { 0,0,Rozmiar.x,Rozmiar.y };
}
void StworzZestawAnimacji(std::filesystem::path Folder,std::string NazwaAnimacji, Vector2 Rozmiar, unsigned int LiczbaKlatek)
{
	
	if (std::filesystem::exists(Folder) == true && std::filesystem::is_directory(Folder))
	{
		std::filesystem::path Animka = Folder.string() + "/" + NazwaAnimacji;
		if (std::filesystem::exists(Animka) == false)
		{


			std::filesystem::create_directory(Animka);
			Image zdjecie = GenImageColor(LiczbaKlatek * Rozmiar.x, 8 * Rozmiar.y, { 0,0,0,255 });
			if (ExportImage(zdjecie, std::string(Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STANIE)+ ".png").c_str()) == true)
			{
#ifdef ZASOBY_DEBUG
				std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STANIE) << ".png\n";
#endif
			}
#ifdef ZASOBY_DEBUG
			else std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STANIE) << ".png\n";
#endif
			if (ExportImage(zdjecie, std::string(Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::CHODZENIE) +".png").c_str()) == true)
			{
#ifdef ZASOBY_DEBUG
				std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::CHODZENIE) << ".png\n";
#endif
			}
#ifdef ZASOBY_DEBUG
			else std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::CHODZENIE) << ".png\n";
#endif
			if (ExportImage(zdjecie, std::string(Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STRZELANIE) + ".png").c_str()) == true)
			{
#ifdef ZASOBY_DEBUG
				std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STRZELANIE) <<".png" << "\n";
#endif
			}
#ifdef ZASOBY_DEBUG
			else std::cout << "Stworzono zdjecia " << Animka.string() + "/" + ZwrocNazweAnimacji(TypyAnimacji::STRZELANIE) << ".png \n";
#endif
			std::ofstream Plik(Animka.string() + "/info.obi");
			if (Plik.is_open() == true && Plik.good() == true)
			{
				blmp::Obiekt obiekt(NazwaAnimacji, {
					{"ROZMIARX",blmp::Dane(Rozmiar.x)},
					{"ROZMIARY",blmp::Dane(Rozmiar.y)},
					{ZwrocNazweAnimacji(TypyAnimacji::STANIE),blmp::Dane(0u)},
					{ZwrocNazweAnimacji(TypyAnimacji::CHODZENIE),blmp::Dane(0u)},
					{ZwrocNazweAnimacji(TypyAnimacji::STRZELANIE),blmp::Dane(0u)}
					});
				blmp::ZapiszObiekt(obiekt, Plik);
				Plik.close();
			}
		}
#ifdef 	ZASOBY_DEBUG
		else std::cout << "Animacja Juz istnieje wiec nie stworzono Folderu z animacja :" << Animka.string() << "\n";
#endif // 	ZASOBY_DEBUG
	}
#ifdef 	ZASOBY_DEBUG
	else std::cout << "Folder o nazwie :" << Folder.string() << " nie zostal zanleziony \n";
#endif






}


TablicaAnimacji::TablicaAnimacji(std::filesystem::path Sciezka)
{
	WczytajZestawyAnimacji(Sciezka);
}
void TablicaAnimacji::WczytajZestawyAnimacji(std::filesystem::path Sciezka)
{
	if (std::filesystem::exists(Sciezka) == true && std::filesystem::is_directory(Sciezka) == true)
	{
		for (const auto& iterator : std::filesystem::directory_iterator(Sciezka))
		{
			Zestawy.emplace_back(iterator.path());



		}
#ifdef 	ZASOBY_DEBUG
		std::cout << "Zaladowano Pomyslnie TabliceAnimacji \n";
#endif

	}
#ifdef 	ZASOBY_DEBUG
	else std::cout << "Nie znaleziono Sciezki dla Tablicy Animacji :" << Sciezka.string() << "\n";
#endif
}
ZestawAnimacji* TablicaAnimacji::ZwrocZestawAnimajcji(std::string NazwaAnimacji)
{
	auto iterator = std::find_if(Zestawy.begin(), Zestawy.end(), [&](const ZestawAnimacji& zestaw) { return NazwaAnimacji == zestaw.NazwaAnimacji; });
	if (iterator != Zestawy.end())
	{
		return iterator._Ptr;
	}
	else return nullptr;
}

PlayerAnimacji::PlayerAnimacji(std::string NazwaAnimacji)
{
	ObecnyTick = 0;
	this->Klatka = 0;
	this->typAnimacji = TypyAnimacji::STANIE;
	this->kierunek = KierunkiSwiata::POLUDNIE;
	zestawAnimacji = nullptr;
	animacja = nullptr;
}
void PlayerAnimacji::ZnajdzZasob(std::string NazwaAnimacji, TablicaAnimacji& tablicaAnimacji)
{
	zestawAnimacji = tablicaAnimacji.ZwrocZestawAnimajcji(NazwaAnimacji);
#ifdef 	ZASOBY_DEBUG
	if (zestawAnimacji == nullptr) std::cout << "Nie znaleziono Zestawu Animacji \n";
#endif
	ZnajdzTypAnimacji(typAnimacji);
}
void PlayerAnimacji::ZnajdzTypAnimacji(TypyAnimacji typAnimacji)
{
	if (zestawAnimacji != nullptr)
	{
		
		auto iterator = std::find_if(zestawAnimacji->animacje.begin(), zestawAnimacji->animacje.end(), [&](const Animacja& animacja) { return animacja.typ == typAnimacji; });
#ifdef 	ZASOBY_DEBUG
		std::cout << "Ile jest animacji :" << zestawAnimacji->animacje.size() << "\n";
#endif
		if (iterator != zestawAnimacji->animacje.end())
		{
			this->typAnimacji = typAnimacji;
			animacja = iterator._Ptr;
#ifdef 	ZASOBY_DEBUG
			std::cout << "Znaleziono Typ Animacji \n";
#endif
		}
#ifdef 	ZASOBY_DEBUG
		else std::cout << "Nie znaleziono typu animacji \n";
#endif
	}
#ifdef 	ZASOBY_DEBUG
	else std::cout << "Zestaw Animacji nie zostal znaleziony \n";
#endif
}






void PlayerAnimacji::Rysuj(CzasLogiki &czasLogiki, Vector2 Pozycja,const unsigned int rozmiarKlatki, TablicaAnimacji& tablicaAnimacji)
{
	if (animacja != nullptr && zestawAnimacji!=nullptr )
	{
		
		float Dzielnik = (zestawAnimacji->Rozmiar.x > zestawAnimacji->Rozmiar.y) ? zestawAnimacji->Rozmiar.x : zestawAnimacji->Rozmiar.y;
		
		if (ObecnyTick == 60)
		{
			ObecnyTick = 0;
			Klatka++;
			if (animacja->LiczbaKlatek == Klatka)
			{
				Klatka = 0;
			}
		}
		else ObecnyTick++;
		
	//	std::cout << "Rozmiar :" << zestawAnimacji->Rozmiar.x << ".x " << zestawAnimacji->Rozmiar.y << "\n";

	//	std::cout << ZwrocNazweAnimacji(animacja->typ) << "\n";
		Rectangle kwadrat = { Pozycja.x,Pozycja.y ,static_cast<int>(zestawAnimacji->Rozmiar.x/Dzielnik * static_cast<float>(rozmiarKlatki)) , static_cast<int>((zestawAnimacji->Rozmiar.y/Dzielnik) * static_cast<float>(rozmiarKlatki) )};
		Rectangle kwadrattekstury = animacja->ZwrocKlatke(kierunek, zestawAnimacji->Rozmiar, Klatka);
		DrawTexturePro(animacja->tekstura, kwadrattekstury, kwadrat, { kwadrat.width / 2,kwadrat.height / 2 }, 0, { 255,255,255,255 });
	}
	else DrawRectangle(static_cast<int>(Pozycja.x) - static_cast<int>(rozmiarKlatki/2), static_cast<int>(Pozycja.y)-static_cast<int>(rozmiarKlatki/2), static_cast<int>(rozmiarKlatki), static_cast<int>(rozmiarKlatki), MAGENTA);
}
void PlayerAnimacji::UstawTypAnimacji(TypyAnimacji typ)
{
	this->typAnimacji = typAnimacji;
	}
void PlayerAnimacji::UstawKierunek(KierunkiSwiata kierunek)
{
	this->kierunek = kierunek;
}
void StworzTabliceAnimacji(std::filesystem::path Folder, std::string NazwaFolderu, std::vector<std::string> NazwyAnimacji, Vector2 Rozmiar, unsigned int liczbaKlatek)
{
	if (std::filesystem::exists(Folder) == true && std::filesystem::is_directory(Folder) == true)
	{
		std::filesystem::path FolderZAnimacjami = Folder.string() + "/" + NazwaFolderu;
		if (std::filesystem::exists(FolderZAnimacjami) == false)
		{
			std::filesystem::create_directory(FolderZAnimacjami);

			if (std::filesystem::exists(FolderZAnimacjami) == true && std::filesystem::is_directory(FolderZAnimacjami) == true)
			{
				
				for (std::string& nazwaAnimacji : NazwyAnimacji)
				{
#ifdef 	ZASOBY_DEBUG
					std::cout << "Stworzono Zestaw Animacji :" << nazwaAnimacji << "\n";
#endif
					StworzZestawAnimacji(FolderZAnimacjami, nazwaAnimacji, Rozmiar, liczbaKlatek);
				}
#ifdef 	ZASOBY_DEBUG
				std::cout << "Zapisano Pomyslnie Tablice Animacji  w folderze:"<< FolderZAnimacjami.string()<<"\n";
#endif
			}
		}
#ifdef 	ZASOBY_DEBUG
		else std::cout << "Folder o nazwie :" << Folder.string() + "/" + NazwaFolderu << " Juz istniejie";
#endif
	}
#ifdef 	ZASOBY_DEBUG
	else std::cout << "Nie zdolano uwtowrzyc folderu dla tablic animacji nie znaleziono Sciezki do Folderu :" << NazwaFolderu << "\n";
#endif
}

