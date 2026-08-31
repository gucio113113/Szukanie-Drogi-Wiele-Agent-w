#include "Obiekt.h"

Sojusze::Sojusze(Druzyny wlasciciel, Druzyny sojusz)
{
	this->wlasciciel = wlasciciel;
	this->sojusz = sojusz;
}
Sojusze::Sojusze(Druzyny wlasciciel)
{
	this->wlasciciel = wlasciciel;
	this->sojusz = wlasciciel;
}
void Sojusze::UstawWlasciciel(Druzyny wlasciciel)
{
	this->sojusz = this->sojusz & ~this->wlasciciel;
	this->wlasciciel = wlasciciel;
	this->sojusz = this->sojusz | sojusz;
}
void Sojusze::UstawSojusz(Druzyny sojusz)
{
	this->sojusz = this->sojusz | sojusz;
}
void Sojusze::UsunSojusz(Druzyny sojusz)
{
	this->sojusz = this->sojusz ^ sojusz;
}
Druzyny Sojusze::zwrocSojusz()
{
	return sojusz;
}
Druzyny Sojusze::zwrocWlasciciel()
{
	return wlasciciel;
}
//checks if two objects have the same team
bool Sojusze::SprawdzSojusz(const Sojusze sojusz1)
{
#ifdef SYSTEMNAMIERZANIA_DEBUG

	bool so = (!!(sojusz & sojusz1.sojusz));
	if (so == true) std::cout << "Sa sojusz \n";
	else "Nie ma sojusz \n";
	return so;
#else // SYSTEMNAMIERZANIA_DEBUG
	return (!!(sojusz & sojusz1.sojusz));
#endif
}
Sojusze Sojusze::operator=(const Sojusze sojusz1)
{
	this->sojusz = sojusz1.sojusz;
	this->wlasciciel = sojusz1.wlasciciel;
	return *this;
}



void Obiekt::UstawIndexObiektu(std::vector<Obiekt*>& Obiekty)
{
	unsigned int indexNastepny = Obiekty.size();
	auto szukanie = [&](const Obiekt* obiekt)->bool
		{
			return obiekt->IndexObiektu==indexNastepny;
		};
	auto iteratorszukania = std::find_if(Obiekty.begin(), Obiekty.end(), szukanie);
	while (iteratorszukania!=Obiekty.end() )
	{
		indexNastepny++;
		auto iteratorszukania = std::find_if(Obiekty.begin(), Obiekty.end(), szukanie);
	}
	if(iteratorszukania==Obiekty.end())
	this->IndexObiektu = indexNastepny;
}
Obiekt::Obiekt(Vector2 pozycja , unsigned int Zdrowie,  Sojusze sojusz , Typy typ )
{
	this->pozycja = pozycja;
	this->Zdrowie = Zdrowie;
	this->sojusze = sojusz;
	this->typ = typ;
	

	
	player.kierunek = KierunkiSwiata::POLUDNIE;
	player.Klatka = 0;
	player.ObecnyTick = 0;
	player.typAnimacji = TypyAnimacji::STANIE;
	this->IndexObiektu = 0;
}
Obiekt::Obiekt(std::string NazwaAnimacji, Vector2 pozycja, unsigned int Zdrowie, Sojusze sojusz, Typy typ, std::vector<Obiekt*>& Obiekty, TablicaAnimacji& tablica)
{
	this->pozycja = pozycja;
	this->Zdrowie = Zdrowie;
	this->sojusze = sojusz;
	this->typ = typ;

	player.typAnimacji = TypyAnimacji::STANIE;
	player.ZnajdzZasob(NazwaAnimacji, tablica);
	player.kierunek = KierunkiSwiata::POLUDNIE;
	player.Klatka = 0;
	player.ObecnyTick = 0;
	
	UstawIndexObiektu(Obiekty);
}

 void Obiekt::Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica,  std::vector<Obiekt*>& Obiekty)
{
	 std::cout << "Akcja Obiekt \n";

}
  void Obiekt::Render(Mapa& mapa,CzasLogiki& czasLogiki, TablicaAnimacji& tablica)
 {
	  player.Rysuj(czasLogiki, pozycja,mapa.RozmiarKlatki, tablica);
 }
  // This command allow us for own terms of deleting the object from the engine and it saves all deleted object from the current state to the table
  void Obiekt::SprawdzCzyUsunObiekt(std::vector<unsigned int>& IndexyUsuwanych)
  {
	  if (!!(typ & Typy::SYSTEM_USUWANIA))
	  {
		  if (CzyZyje == false)
		  {
			  auto szukajObiektu = std::find(IndexyUsuwanych.begin(), IndexyUsuwanych.end(), IndexObiektu);
			  if (szukajObiektu == IndexyUsuwanych.end()) IndexyUsuwanych.emplace_back(IndexObiektu);
		  }
	  }
  }

  unsigned int Obiekt::DostanIdnex()
  {
	  return IndexObiektu;
  }
  bool Obiekt::operator== (Obiekt*& obiekt)
  {
	  return this->IndexObiektu == obiekt->IndexObiektu;
	 
  }
  bool Obiekt::operator!=(Obiekt*& obiekt)
  {
	  return this->IndexObiektu != obiekt->IndexObiektu;
  }
  Obiekt* ZwrocObiekt(unsigned indexObiektu, std::vector<Obiekt*>& Obiekty)
  {
	  auto szukanie = std::find_if(Obiekty.begin(), Obiekty.end(), [&](const Obiekt* ob) { return ob->IndexObiektu == indexObiektu; });
	  if (szukanie == Obiekty.end()) return nullptr;
	  return *szukanie;
  }

  Ruch::Ruch(Vector2 PunktA, Vector2 PunktB)
  {
	  this->PunktA = PunktA;
	  this->PunktB = PunktB;
	  this->procent = 1;

  }
  float Ruch::CzasTrwaniaRuchu(const float& predkosc)
  {
	  if (predkosc != 0)
	  {
		  return Dlugosc({ PunktB.x - PunktA.x,PunktB.y - PunktA.y }) / predkosc;
	  }
	  else return std::numeric_limits<float>::infinity();
  }
  float Ruch::PozostalyCzas(const float& predkosc)
  {
	  if (predkosc != 0)
	  {
		  return  (Dlugosc({ PunktB.x - PunktA.x,PunktB.y - PunktA.y }) / predkosc) * procent;
	  }
	  else return std::numeric_limits<float>::infinity();
  }
  void Ruch::ZdefiniujRuch(Vector2 PunktA, Vector2 PunktB, Vector2& Pozycja)
  {

	  this->PunktA = PunktA;
	  this->PunktB = PunktB;
	  Pozycja = PunktA;
	  procent = 0;
  }

  void Ruch::ZmienPozycje(Vector2& Pozycja)
  {
	  Pozycja.x = Interpolacja(PunktA.x, PunktB.x, procent);
	  Pozycja.y = Interpolacja(PunktA.y, PunktB.y, procent);
  }
  void Ruch::Porusz(float Predkosc, Vector2& Pozycja)
  {
	  if (Dotarlo() == true)
	  {
		  Pozycja = PunktB;
		  //	std::cout << "Dociera \n";
	  }
	  else
	  {
		  //	std::cout << "Predkosc :" << Predkosc << "\n";
		  if (Dlugosc({ PunktB.x - PunktA.x,PunktB.y - PunktA.y }) != 0)
		  {
			  procent = procent + ((Predkosc) / Dlugosc({ PunktB.x - PunktA.x,PunktB.y - PunktA.y }));
			  ZmienPozycje(Pozycja);
		  }
	  }


  }
  bool Ruch::Dotarlo()
  {
	  if (procent >= 1) return true;
	  else return false;
  }
  KierunkiSwiata RuchPoOkregu::ZwrocKierunek()
  {

  }


  void RuchPoOkregu::Ustaw(float kat, float Predkosc, Vector2& Pozycja, Vector2 Cel, float Promien)
  {
	  Vector2 Odleglosc = { Cel.x - Pozycja.x,Cel.y - Pozycja.y };

	  this->Cel = Cel;
	  this->Promien = Promien;
	  this->kat = kat;
	  
	  Vector2 Kierunkowy = { cosf(kat / 180 * LICZBA_PI), sinf(kat / 180 * LICZBA_PI) };
	  float Iloczyn = IloczynWektorowy(Kierunkowy, Normalizacja(Odleglosc));
	 

	  if (static_cast<int>(Iloczyn) == 0)
	  {
		  stanruchu = NATRAJEKTORI;
	  }
	  else
	  {
		  stanruchu = PRZEDOBROTEM;
		  this->Predkosc = { Kierunkowy.x * Predkosc,Kierunkowy.y * Predkosc };
	  }
  }
  void RuchPoOkregu::Ruch(Vector2& Pozycja, KierunkiSwiata& kierunekSwiata, CzasLogiki& czasLogiki)
  {
	  if (stanruchu!=NATRAJEKTORI && Promien != 0)
	  {
		  float dosrodkowe = powf(Dlugosc(Predkosc), 2) / Promien;
		  

		  

		  Vector2 Odleglosc = { Cel.x - Pozycja.x,Cel.y - Pozycja.y };
		  Vector2 Kierunkowy = { cosf(kat * 180/LICZBA_PI),sinf(kat * 180 /LICZBA_PI)};
		  
		  float Iloczyn = IloczynWektorowy(Kierunkowy, Normalizacja(Odleglosc));
		  

		  if (Iloczyn == 0)
		  {
			  stanruchu = StanRuchu::NATRAJEKTORI;
			  kat= (atan2f(Odleglosc.y, Odleglosc.x) * 180 / LICZBA_PI);
		  }
		  else if (Iloczyn > 0)
		  {
			  float katowe = sqrtf(dosrodkowe / Promien) + (kat / 180 * LICZBA_PI);
			  float nastepnyKat = (katowe) * 180 / LICZBA_PI;

			  Vector2 NastepnaKierunkowa = { cosf(katowe),sinf(katowe) };
			  float NastepnyIloczyn = IloczynWektorowy(NastepnaKierunkowa, Normalizacja(Odleglosc));

			  this->kat = nastepnyKat;
			  Predkosc.x = Predkosc.x + ( Kierunkowy.y * dosrodkowe);
			  Predkosc.y = Predkosc.y + (-Kierunkowy.x * dosrodkowe);

			  Pozycja.x += (Predkosc.x * czasLogiki.DeltaTimeTick()) + Pozycja.x;
			  Pozycja.y += (Predkosc.y * czasLogiki.DeltaTimeTick()) + Pozycja.y;

			  if (NastepnyIloczyn <= 0)
			  {
				  stanruchu = StanRuchu::NATRAJEKTORI;
				  this->kat = (atan2f(Odleglosc.y, Odleglosc.x) * 180 / LICZBA_PI);
			  }

		  }
		  else
		  {
			  float katowe = sqrtf(dosrodkowe / Promien) - (kat / 180 * LICZBA_PI);
			  float nastepnyKat = (katowe) * 180 / LICZBA_PI;

			  Vector2 NastepnaKierunkowa = { cosf(katowe),sinf(katowe) };
			  float NastepnyIloczyn = IloczynWektorowy(NastepnaKierunkowa, Normalizacja(Odleglosc));

			  this->kat = nastepnyKat;
			  Predkosc.x = Predkosc.x + (-Kierunkowy.y * dosrodkowe);
			  Predkosc.y = Predkosc.y + (Kierunkowy.x * dosrodkowe);

			  Pozycja.x += (Predkosc.x * czasLogiki.DeltaTimeTick()) + Pozycja.x;
			  Pozycja.y += (Predkosc.y * czasLogiki.DeltaTimeTick()) + Pozycja.y;
			  if (NastepnyIloczyn >= 0)
			  {
				  stanruchu = StanRuchu::NATRAJEKTORI;
				  this->kat = (atan2f(Odleglosc.y, Odleglosc.x) * 180 / LICZBA_PI);
			  }
		  }
	  }
  }
  StanRuchu RuchPoOkregu::ZwrocStanRuchu()
  {
	  return stanruchu;
  }
  void MapowanieObiektow(std::vector<Obiekt*>& Obiekty, std::vector<std::vector<unsigned int>> &KlatkiSystemu, unsigned int RozmiarKlatek, unsigned int RozmiarSystemu, Typy typ )
  {
	  for (std::vector<unsigned int>& indexy : KlatkiSystemu)
	  {
		  indexy.clear();
	  }
	  for (unsigned int index = 0; index < Obiekty.size(); index++)
	  {
		  if (Obiekty[index] != nullptr && !!(Obiekty[index]->typ & typ))
		  {
			  Obiekt*& obiekt = Obiekty[index];
			  PozycjaNaMapie poz;
			  poz.x = obiekt->pozycja.x / RozmiarKlatek;
			  poz.y = obiekt->pozycja.y / RozmiarKlatek;

			  if (poz.x >= 0 && poz.y>=0 && poz.x<RozmiarSystemu && poz.y < RozmiarSystemu)
			  {
				  KlatkiSystemu[poz.x + (poz.y * RozmiarSystemu)].emplace_back(obiekt->IndexObiektu);
			  }

		  }
	  }
  }
