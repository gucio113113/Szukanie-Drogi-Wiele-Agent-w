#include "SystemObrazen.h"
#include "Obiekt.h"
#include "Mapa.h"


Damage::Damage(Vector2 Pozycja, unsigned int CzasTrwania, unsigned int KiedyZadaje, unsigned int IleZadaje)
{
	this->Pozycja = Pozycja;
	this->CzasTrwania = CzasTrwania;
	this->Tick = 0;
	this->KiedyZadaje = KiedyZadaje;
	this->IleZadaje = IleZadaje;
}
Damage::~Damage()
{
	std::cout << "Usuniento Damage \n";


 }
void Damage::NaliczTick(CzasLogiki& czasLogiki)
{
	if (czasLogiki.StanCzasu() == true)
	{
		if(Tick < CzasTrwania) Tick++;

	}
		
		
}
bool Damage::Sprawdz(Obiekt*& obiekt, Mapa& mapa, TablicaAnimacji& tablicanimacji)
{
	std::cout << "Sprawdza Damage \n";
	return false;
}
PozycjaNaMapie Damage::DolnyZasieg(const unsigned int rozmiarKlatek)
{
	return { static_cast<int>(Pozycja.x) / static_cast<int>(rozmiarKlatek),static_cast<int>(Pozycja.y) / static_cast<int>(rozmiarKlatek) };
}
PozycjaNaMapie Damage::GornyZasieg(const unsigned int rozmiarKlatek)
{
	return { static_cast<int>(Pozycja.x) / static_cast<int>(rozmiarKlatek),static_cast<int>(Pozycja.y) / static_cast<int>(rozmiarKlatek) };
}
DamageKolo::DamageKolo(Vector2 Pozycja, float Promien, unsigned int CzasTrwania, unsigned int KiedyZadaje, unsigned int IleZadaje)
{
	this->Pozycja = Pozycja;
	this->Promien = Promien;
	this->CzasTrwania = CzasTrwania;
	this->KiedyZadaje = KiedyZadaje;
	this->IleZadaje = IleZadaje;
	this->Tick = 0;
}

bool DamageKolo::Sprawdz(Obiekt*& obiekt, Mapa& mapa,TablicaAnimacji& tablicanimacji)
{
	//Rectangle kwadrat1={}
	if (obiekt != nullptr)
	{
		Rectangle kwadrat = { obiekt->pozycja.x - static_cast<float>(mapa.RozmiarKlatki / 2),obiekt->pozycja.y - static_cast<float>(mapa.RozmiarKlatki / 2),static_cast<float>(mapa.RozmiarKlatki),static_cast<float>(mapa.RozmiarKlatki) };

		if (CheckCollisionCircleRec(obiekt->pozycja, Promien, kwadrat) == true && Tick % KiedyZadaje == 0)
		{
			if (obiekt->Zdrowie - IleZadaje > 0) obiekt->Zdrowie -= IleZadaje;
			else obiekt->Zdrowie = 0;
			return true;
		}
	}
	return false;
}
PozycjaNaMapie DamageKolo::DolnyZasieg(const unsigned int rozmiarKlatek)
{

	PozycjaNaMapie poz=Damage::DolnyZasieg(rozmiarKlatek);
	poz.x = poz.x + (Promien / rozmiarKlatek);
	poz.y = poz.y + (Promien / rozmiarKlatek);

	return poz;


}
PozycjaNaMapie DamageKolo::GornyZasieg(const unsigned int rozmiarKlatek)
{
	PozycjaNaMapie poz = Damage::GornyZasieg(rozmiarKlatek);
	poz.x = poz.x - (Promien / rozmiarKlatek);
	poz.y = poz.y - (Promien / rozmiarKlatek);

	return poz;

}



DamageProstokat::DamageProstokat(Vector2 Pozycja, Vector2 Rozmiar, unsigned int CzasTrwania, unsigned int KiedyZadaje, unsigned int IleZadaje)
{
	this->Pozycja = Pozycja;
	this->Rozmiar = Rozmiar;
	this->CzasTrwania = CzasTrwania;
	this->KiedyZadaje = KiedyZadaje;
	this->IleZadaje = IleZadaje;
	this->Tick = 0;


}


 bool DamageProstokat::Sprawdz(Obiekt*& obiekt, Mapa& mapa, TablicaAnimacji& tablicanimacji)
{
	 if (obiekt != nullptr)
	 {
		 ZestawAnimacji*& Zestaw = obiekt->player.zestawAnimacji;

		 if (Zestaw != nullptr)
		 {

			 Rectangle kwadrat0 = { obiekt->pozycja.x - static_cast<float>(Zestaw->Rozmiar.x / 2),obiekt->pozycja.y - static_cast<float>(Zestaw->Rozmiar.y / 2),static_cast<float>(Zestaw->Rozmiar.x),static_cast<float>(Zestaw->Rozmiar.y) };
			 Rectangle kwadrat1 = { Pozycja.x - (Rozmiar.x / 2),Pozycja.y - (Rozmiar.y / 2),Rozmiar.x,Rozmiar.y };


			 if (CheckCollisionRecs(kwadrat0, kwadrat1) == true && Tick % KiedyZadaje == 0)
			 {
				 if (obiekt->Zdrowie - IleZadaje > 0) obiekt->Zdrowie -= IleZadaje;
				 else obiekt->Zdrowie = 0;
				 return true;
			 }

		 }

	 }
	 return false;


}
 PozycjaNaMapie DamageProstokat::DolnyZasieg(const unsigned int rozmiarKlatek)
 {
	 PozycjaNaMapie poz = Damage::DolnyZasieg(rozmiarKlatek);
	 poz.x = poz.x + (Rozmiar.x / rozmiarKlatek);
	 poz.y = poz.y + (Rozmiar.y / rozmiarKlatek);

	 return poz;



 }
 PozycjaNaMapie DamageProstokat::GornyZasieg(const unsigned int rozmiarKlatek)
 {
	 PozycjaNaMapie poz = Damage::GornyZasieg(rozmiarKlatek);
	 poz.x = poz.x - (Rozmiar.x / rozmiarKlatek);
	 poz.y = poz.y - (Rozmiar.y / rozmiarKlatek);

	 return poz;

 }
Damage* Damage::ZwrocKopie(Vector2 Pozycja)
 {
	return new Damage(Pozycja, this->CzasTrwania, this->KiedyZadaje, this->IleZadaje);
 }
Damage* DamageProstokat::ZwrocKopie(Vector2 Pozycja)
{
	return new DamageProstokat(Pozycja, Rozmiar, CzasTrwania, KiedyZadaje, IleZadaje);
}
Damage* DamageKolo::ZwrocKopie(Vector2 Pozycja)
{
	return new DamageKolo(Pozycja, Promien, CzasTrwania, KiedyZadaje, IleZadaje);
}


 SystemObrazen::SystemObrazen(unsigned int RozmiarKlatek, unsigned int RozmiarSystemu)
 {
	 this->RozmiarKlatek = RozmiarKlatek;
	 this->RozmiarSystemu = RozmiarSystemu;

	 this->IndexyObiektow.resize(RozmiarSystemu * RozmiarSystemu, {});
	 this->PodOstrzalem.reserve(30);
 }
 void SystemObrazen::ZmapujObiekty(std::vector<Obiekt*>& Obiekty)
 {
	 PodOstrzalem.clear();
	 MapowanieObiektow(Obiekty, IndexyObiektow, RozmiarKlatek, RozmiarSystemu,Typy::SYSTEM_OBRAZEN);
 }
 void SystemObrazen::LogikaSystemu(std::vector<Obiekt*>& Obiekty, CzasLogiki& Czaslogiki, Mapa& mapa,TablicaAnimacji & tablicanimacji)
 {
	 ZmapujObiekty(Obiekty);
	 for (Damage*& damage : Obrazenia)
	 {
		 if (damage != nullptr)
		 {
			 damage->NaliczTick(Czaslogiki);
			 PozycjaNaMapie dolnyRog = damage->DolnyZasieg(RozmiarKlatek);
			 PozycjaNaMapie gornyRog = damage->GornyZasieg(RozmiarKlatek);
			 if (gornyRog.x < 0) dolnyRog.x = 0;
			 if (gornyRog.y < 0) dolnyRog.y = 0;
			 if (dolnyRog.x >= RozmiarSystemu) dolnyRog.x = RozmiarSystemu - 1;
			 if (dolnyRog.y >= RozmiarSystemu) dolnyRog.y = RozmiarSystemu - 1;
			 for (unsigned int x = gornyRog.x; x <= dolnyRog.x; x++)
			 {
				 for (unsigned int y = gornyRog.y; y <= dolnyRog.y; y++)
				 {
					 for (unsigned int& indexobiektu : IndexyObiektow[x+(y * RozmiarSystemu)])
					 {
						 Obiekt * obiekt = ZwrocObiekt(indexobiektu,Obiekty);
						 if (obiekt != nullptr)
						 {
							 if (damage->Sprawdz(obiekt, mapa, tablicanimacji) == true)
							 {
								 PodOstrzalem.emplace_back(indexobiektu);
							 }
						 }
					#ifdef SYSTEM_OBRAZEN_DEBUG
						 else
						 {
							 std::cout << "Wskaznik Obiektu jest pusty dla Systemu namierzania  \n";
						 }

					#endif // SYSTEM_OBRAZEN_DEBUG

					 }
				 }
			 }
		 }
#ifdef SYSTEM_OBRAZEN_DEBUG
		 else
		 {
			 std::cout << "Wskaznik damage jest pusty \n";


		 }
#endif // SYSTEM_OBRAZEN_DEBUG

		 
	 }
	 auto szukacz = [&](const Damage* damage)->bool { return damage->Tick >= damage->CzasTrwania; };
	 auto iterator = std::find_if(Obrazenia.begin(), Obrazenia.end(), szukacz);
	 while (iterator!=Obrazenia.end() )
	 {
			 Obrazenia.erase(iterator);
			 iterator = std::find_if(Obrazenia.begin(), Obrazenia.end(), szukacz);
	 }

 }
 void SystemObrazen::UstawParametry(unsigned int RozmiarSystemu, Mapa& mapa)
 {
	 this->RozmiarSystemu = RozmiarSystemu;
	 this->RozmiarKlatek = mapa.szerokosc * mapa.RozmiarKlatki / RozmiarSystemu;
	 this->IndexyObiektow.resize(RozmiarSystemu * RozmiarSystemu, {});
 }
#ifdef SYSTEM_OBRAZEN_DEBUG
 void SystemObrazen::Debug()
 {
	 NarysujSiatke(IndexyObiektow, RozmiarSystemu, RozmiarKlatek, POMARANCZOWY, RED);
 }
#endif