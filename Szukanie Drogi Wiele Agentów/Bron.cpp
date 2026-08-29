#include "Bron.h"
ParametrPocisk::ParametrPocisk(unsigned int Zdrowie, std::string NazwaTekstury, float Predkosc, bool StatycznyCel, float Promien,unsigned int TickZycia,  Damage* damage)
{
	this->Zdrowie = Zdrowie;
	this->NazwaTekstury = NazwaTekstury;
	this->StatycznyCel = StatycznyCel;
	this->Predkosc = Predkosc;
	this->Promien = Promien;
	this->TickZycia = TickZycia;
	this->damage = damage;
}
ParametryPociskow::ParametryPociskow()
{
	ParametrPocisk parametr{ 100,"Pocisk",4,true,1,200,new DamageKolo({0,0},5,2,1,5) };
	Parametry.try_emplace(TypPocisku::POCISK, parametr);
}

ParametrPocisk* ParametryPociskow::ZwrocParametr(TypPocisku typPocisku)
{
	auto iterator = Parametry.find(typPocisku);
	if (iterator == Parametry.end()) return nullptr;
	else iterator._Ptr;

}
Pocisk::Pocisk(Vector2 Pozycja , Vector2 Cel , ParametrPocisk* parametr )
{
	this->pozycja = Pozycja;
	this->parametr = parametr;
	ruch.ZdefiniujRuch(Pozycja, Cel, Pozycja);
	this->IndexObiektu = std::numeric_limits<unsigned int>::infinity();
	this->Tick = 0;
}

Pocisk::Pocisk(Vector2 Pozycja, TypPocisku typ, Vector2 Cel, ParametryPociskow& parametry, std::vector<Obiekt*>& Obiekty, TablicaAnimacji& tablica)
{
	parametr= parametry.ZwrocParametr(typ);
	if (parametr != nullptr)
	{
		std::cout << "Parametr o typie pocisku nie zostal znaleziony :" << typ << "\n";
		player.ZnajdzZasob(parametr->NazwaTekstury, tablica);
		
	}
	this->Tick = 0;
	this->IndexObiektu = Obiekty.size();

}
 Pocisk::~Pocisk()
 {
	 
 }

 void Pocisk::Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty)
 {
	 if (czasLogiki.StanCzasu() == true)
	 {
		 NaLiczZycie(czasLogiki);

		 if (ruch.Dotarlo() == true) Zdrowie = 0;
		 else
		 {
			 if (this->parametr != nullptr)
			 {
				 ruch.Porusz(parametr->Predkosc, pozycja);
			 }
		 }
		 if (parametr != nullptr && Zdrowie == 0)
		 {
			 system.Obrazenia.emplace_back(parametr->damage->ZwrocKopie(pozycja));

		 }
	 }

}
 void Pocisk::NaLiczZycie(CzasLogiki& czasLogiki)
 {
	 if (czasLogiki.StanCzasu())
	 {
		 
		 if (parametr!=nullptr && parametr->TickZycia != std::numeric_limits<unsigned int>::infinity())
		 {
			 if (parametr->TickZycia == Tick)
			 {
				 CzyZyje = false;
			 }
			 else Tick++;
		 }
	 }
 }
 void  PociskKierowany::UstawCel(float katRozpoczeczeczia,Obiekt*& obiekt)
 {
	 if (obiekt != nullptr)
	 {
		 this->obiekt = obiekt;
		 this->IndexObiektuCel = this->obiekt->DostanIdnex();

		 this->kat = katRozpoczeczeczia;

		 ruchPoOkregu.Ustaw(this->kat, parametr->Predkosc, pozycja, obiekt->pozycja, parametr->Promien);



	 }
	 









	 
 }




 Bron::Bron(unsigned int szybkostrzelnosc, float Zasieg, TypPocisku typ)
 {
	 this->Szybkostrzelnosc = Szybkostrzelnosc;
	 this->Zasieg = Zasieg;
	 this->TickStrzalu = 0;
	 this->typ = typ;

 }
 void Bron::Strzelanie(const unsigned int& Index,CzasLogiki& czasLogiki, SystemNamierzania& namierzania, std::vector<Obiekt*>& Obiekty,Mapa &mapa, ParametryPociskow& parametrypociskow, TablicaAnimacji& tablica)
 {

	 if (czasLogiki.StanCzasu() == true)
	 {
		 if (TickStrzalu == Szybkostrzelnosc)
		 {
			 std::cout << "Strzal \n";
			 std::vector<unsigned int> Indexy;
			 namierzania.ZwrocSpelniajaceZasieg(Index, Zasieg, Indexy, Obiekty, mapa);


			 if (Indexy.empty() == false)
			 {
				 std::cout << "Liczba Indeksow :" << Indexy.size() << "\n";
				 Obiekt* obiekt = ZwrocObiekt(Index, Obiekty);
				 Obiekt* obiekt2 = ZwrocObiekt(Indexy.at(0), Obiekty);

				 if (obiekt != nullptr && obiekt2 != nullptr)
				 {
					 Pocisk* pocisk = new Pocisk(obiekt->pozycja, typ, obiekt2->pozycja, parametrypociskow, Obiekty, tablica);
					 std::cout << "Dodalismy Pocisk \n";
					 Obiekty.emplace_back(pocisk);
					 TickStrzalu = 0;
				 }
			 }
			 else std::cout << "Nie znaleziono nic \n";
			 if (Indexy.empty() == true) std::cout << "Indexy Puste \n";
			 Indexy.clear();
		 }
		 else
		 {
			 TickStrzalu++;
			 std::cout << "Tick: "<<TickStrzalu<<"\n";
		 }
		 
	 }

	 
	// Obiekty.emplace_back(new Pocisk(Pozycja,typ,))


 }

 