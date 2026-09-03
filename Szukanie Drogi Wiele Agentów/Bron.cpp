#include "Bron.h"

std::ostream& operator<<(std::ostream& os, const TypPocisku& typ)
{
	switch (typ)
	{
	case TypPocisku::RAKIETA:
		os << "TypPocisku::RAKIETA";
		break;
	case TypPocisku::RAKIETA_NAPROWADZAJACA:
		os << "TypPocisku::RAKIETA_NAPROWADZAJACA";
		break;
	case TypPocisku::POCISK:
		os << "TypPocisku::POCISK:";
		break;
	case TypPocisku::BOMBA:
		os << "TypPocisku::BOMBA";
		break;
	case TypPocisku::NABOJ:
		os << "TypPocisku::NABOJ";
		break;
	default:
		os << "NIEZNANY ";
		break;
	}
	return os;
}



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

#ifdef ZASOBY_DEBUG
void ParametrPocisk::WyswietlParametry()
{
	std::cout << "Zdrowie: " << this->Zdrowie << "\n"
		<< "NazwaTekstury: " << this->NazwaTekstury << "\n"
		<< "StatycznyCel: " << this->StatycznyCel << "\n"
		<< "Predkosc: " << this->Predkosc << "\n"
		<< "Promien: " << this->Promien << "\n"
		<< "TickZycia: " << this->TickZycia << "\n";
}
#endif
ParametryPociskow::ParametryPociskow()
{
	
}
void ParametryPociskow::Inicjuj()
{
	ParametrPocisk parametr(100,"Pocisk",4,true,1,200,new DamageKolo({0,0},30,40,1,5));
#ifdef ZASOBY_DEBUG
	parametr.WyswietlParametry();
#endif
	auto para= Parametry.try_emplace(TypPocisku::POCISK, parametr);
#ifdef ZASOBY_DEBUG
	if (para.second == false)
		std::cout << "Nie wpisano parametru :" << TypPocisku::POCISK << "\n";
	else std::cout << "Wpisano parametr :" << TypPocisku::POCISK << "\n";
#endif // ZASOBY_DEBUG
}

ParametrPocisk* ParametryPociskow::ZwrocParametr(TypPocisku typPocisku)
{
	auto iterator = Parametry.find(typPocisku);
	if (iterator == Parametry.end()) return nullptr;
	else return &iterator->second;

}
Pocisk::Pocisk(Vector2 Pozycja , Vector2 Cel , ParametrPocisk* parametr )
{
	this->pozycja = Pozycja;
	this->parametr = parametr;
	ruch.ZdefiniujRuch(Pozycja, Cel, Pozycja);
	this->IndexObiektu = std::numeric_limits<unsigned int>::infinity();
	this->Tick = 0;
	this->typ = Typy::SYSTEM_USUWANIA;
}

Pocisk::Pocisk(Vector2 Pozycja, TypPocisku typ, Vector2 Cel, ParametryPociskow& parametry, std::vector<Obiekt*>& Obiekty, TablicaAnimacji& tablica)
{
	
	parametr= parametry.ZwrocParametr(typ);
	if (parametr != nullptr)
	{
	#ifdef STRZELANIE_DEBUG
		std::cout << "Znaleziono Parametr :" << typ << "\n";
	#endif // STRZELANIE_DEBUG
		player.ZnajdzZasob(parametr->NazwaTekstury, tablica);
	}
		#ifdef STRZELANIE_DEBUG
	else
	{
		std::cout << "Parametr zostal nie znaleziony dla Pocisku o indeksie :"<<IndexObiektu<<"\n";
	}
	#endif // STRZELANIE_DEBUG

	this->pozycja = Pozycja;
	this->ruch.ZdefiniujRuch(this->pozycja, Cel, Pozycja);
	this->Tick = 0;
	this->IndexObiektu = Obiekty.size();
	this->typ = Typy::SYSTEM_USUWANIA;
}
 Pocisk::~Pocisk()
 {
	 
 }

 void Pocisk::Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty)
 {
	 std::cout << "Akcja \n";
	 if (czasLogiki.StanCzasu() == true)
	 {
		 NaLiczZycie(czasLogiki);
		 
		 if (ruch.Dotarlo() == true)
		 {

			 this->CzyZyje = false;
			 if (parametr != nullptr)
			 {
				 Damage* damage = parametr->damage->ZwrocKopie(pozycja);
				 system.Obrazenia.emplace_back(damage);
			 }

		 }
		 else
		 {
			 if (this->parametr != nullptr)
			 {
				 ruch.Porusz(parametr->Predkosc, pozycja);
			 }
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
	 this->Szybkostrzelnosc = szybkostrzelnosc;
	 this->Zasieg = Zasieg;
	 this->TickStrzalu = 0;
	 this->typ = typ;

 }
 void Bron::Strzelanie(const unsigned int& Index,CzasLogiki& czasLogiki, std::vector<unsigned int>& Indexy, std::vector<Obiekt*>& Obiekty,Mapa &mapa, ParametryPociskow& parametrypociskow, TablicaAnimacji& tablica)
 {

	 if (czasLogiki.StanCzasu() == true)
	 {
		 if (TickStrzalu >= Szybkostrzelnosc)
		 {
		#ifdef STRZELANIE_DEBUG
			 std::cout << "Strzal \n";
		#endif // STRZELANIE_DEBUG
			 
			


			 if (Indexy.empty() == false)
			 {
			#ifdef STRZELANIE_DEBUG
				 std::cout << "Liczba Indeksow :" << Indexy.size() << "\n";
			#endif // STRZELANIE_DEBUG
				 Obiekt* obiekt = ZwrocObiekt(Index, Obiekty);
				 Obiekt* obiekt2 = ZwrocObiekt(Indexy.at(0), Obiekty);

				 if (obiekt != nullptr && obiekt2 != nullptr)
				 {
					 Pocisk* pocisk = new Pocisk(obiekt->pozycja, typ, obiekt2->pozycja, parametrypociskow, Obiekty, tablica);
					 TickStrzalu = 0;
					 if (pocisk->parametr == nullptr)
					 {
						 
								#ifdef STRZELANIE_DEBUG
									std::cout << "Nie stworzylismy pociska o indeksie: "<<pocisk->IndexObiektu<<"\n";
								#endif // STRZELANIE_DEBUG
									delete pocisk;
					 }
					 else
					 {
					#ifdef STRZELANIE_DEBUG
						 std::cout << "Dodalismy Pocisk o indeksie :" << pocisk->IndexObiektu << "\n";
					#endif // STRZELANIE_DEBUG

						 Obiekty.emplace_back(pocisk);

#ifdef STRZELANIE_DEBUG
						 std::cout << "Tick: " << TickStrzalu << "\n";
#endif // STRZELANIE_DEBUG
						 
					 }
					
				 }
			 }
		#ifdef STRZELANIE_DEBUG
			 else std::cout << "Nie znaleziono nic \n";
			// if (Indexy.empty() == true) std::cout << "Indexy Puste \n";
		#endif // STRZELANIE_DEBUG
			 Indexy.clear();
		 }
		 else
		 {
			 TickStrzalu++;
		#ifdef STRZELANIE_DEBUG
			 std::cout << "Tick: "<<TickStrzalu<<"\n";
		#endif // STRZELANIE_DEBUG
		 }
		 
	 }

	 
	// Obiekty.emplace_back(new Pocisk(Pozycja,typ,))


 }

 