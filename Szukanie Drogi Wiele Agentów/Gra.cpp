#include "Gra.h"



void Gra::Inicjacja()
{
	InitWindow(rozmiarekranu.x, rozmiarekranu.y, NazwaGry.c_str());
	tablica.WczytajZestawyAnimacji("./Zasoby/Tekstury/Animacje");
	graczSter.InicjujKamere(mapa);
	Obiekty.reserve(500);
	parametrypociskow.Inicjuj();


	Agent* agent1 = new Agent(mapa.SrodekPola({ 3,3 }), "Ludzik", FIOLETOWY, 2.5, 100,  Sojusze(Druzyny::DRUZYNA1,Druzyny::DRUZYNA1), Obiekty, tablica);
	Obiekty.emplace_back(agent1);
	Agent* agent2 = new Agent(mapa.SrodekPola({ 9,9 }), "Ludzik", FIOLETOWY, 2.5, 100, Sojusze(Druzyny::DRUZYNA2, Druzyny::DRUZYNA2), Obiekty, tablica);
	Obiekty.emplace_back(agent2);
	Agent* agent3 = new Agent(mapa.SrodekPola({ 15,3 }), "Ludzik", FIOLETOWY, 2.5, 100, Sojusze(Druzyny::DRUZYNA3, Druzyny::DRUZYNA3), Obiekty, tablica);
	Obiekty.emplace_back(agent3);
	Agent* agent4 = new Agent(mapa.SrodekPola({ 15,19 }), "Ludzik", FIOLETOWY, 2.5, 100, Sojusze(Druzyny::DRUZYNA4, Druzyny::DRUZYNA4), Obiekty, tablica);
	Obiekty.emplace_back(agent4);

	
	
	
	

	systemobrazen.UstawParametry(10, mapa);
	systemnamierzania.UstawParametry(10, mapa);

	
	
}
void Gra::Sterowanie()
{
	graczSter.ZmienianiePozycjiZMyszka(0.2f, mapa);
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
	{
		for (Obiekt*& obiekt : Obiekty)
		{
			if (Agent* agent = dynamic_cast<Agent*>(obiekt))
			{
				agent->UstawGlownyCel(mapa.Wysrodkuj({ GetMouseX(),GetMouseY() }),mapa,czas);
			}
		}
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) == true)
	{
		PozycjaNaMapie poz = mapa.Kordynat({ static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) });

		
		if (mapa.ZwrocTypPola(poz) == TypPola::OTWARTE) mapa.UstawTypPola(poz, TypPola::ZAMKNIENTE);
		else if (mapa.ZwrocTypPola(poz) == TypPola::ZAMKNIENTE) mapa.UstawTypPola(poz, TypPola::OTWARTE);


		


	}



}
void Gra::Logika()
{
	if (czas.CzasTrwania() == true)
	{
		systemnamierzania.UstawSystem(Obiekty);
		systemobrazen.ZmapujObiekty(Obiekty);

		systemobrazen.LogikaSystemu(Obiekty,czas, mapa, tablica);

#ifdef GRA_DEBUG
		std::cout << "Ilosc Obiektow :" << Obiekty.size() << "\n";
#endif // GRA_DEBUG
		mapa.UsunPozycjeWCzasie(czas.ZwrocTick());
		if (Obiekty.empty() == false)
		{
			for (Obiekt*& obiekt : Obiekty)
			{
				if(obiekt!=nullptr)
				obiekt->Akcja(mapa, czas, systemobrazen, systemnamierzania, parametrypociskow, tablica, Obiekty);
			}
		}
		UsuwanieObiektow();
	}
}
//This function is for handling deleting objects
void Gra::UsuwanieObiektow()
{
	std::vector<unsigned int> Indexy;
	Indexy.reserve(80);
	for (Obiekt*& obiekt : Obiekty)
	{
		obiekt->SprawdzCzyUsunObiekt(Indexy);
	}
	for (unsigned int& index : Indexy)
	{
		auto szukanie = std::find_if(Obiekty.begin(), Obiekty.end(), [&](const Obiekt* ob) { return ob->IndexObiektu == index; });
		if (szukanie != Obiekty.end())
		{
#ifdef GRA_DEBUG
			std::cout << "Usuniento Obiekt o Indeksie :" << index << "\n";
#endif // GRA_DEBUG


			Obiekty.erase(szukanie);

		}
	}
}
void Gra::Render()
{
	ClearBackground(WHITE);
	BeginDrawing();

	BeginMode2D(graczSter.kamera);

	mapa.Wizualizacja(czas);

	#ifdef SYSTEMNAMIERZANIA_DEBUG
	systemnamierzania.Debug();
	#endif
	#ifdef SYSTEM_OBRAZEN_DEBUG
	systemobrazen.Debug();
	#endif
	for (Obiekt*& obiekt : Obiekty)
	{
		obiekt->Render(mapa, czas, tablica);
	}
	DrawCircle(graczSter.kamera.target.x, graczSter.kamera.target.y, 3, PINK);
	EndMode2D();

	EndDrawing();
}
Gra::Gra( std::string NazwaGry, PozycjaNaMapie rozmiarEkranu, unsigned int TickRate, unsigned int RozmiarKlatki)
{
	this->NazwaGry = NazwaGry;
	this->rozmiarekranu = rozmiarEkranu;
	czas.TickRate = TickRate;
	mapa.RozmiarKlatki = RozmiarKlatki;
	mapa.StworzMape(20, 20, {});
	Inicjacja();
}
void Gra::Pentla()
{
	

	while (WindowShouldClose()==false )
	{
		Sterowanie();
		Logika();
		Render();
	}
}