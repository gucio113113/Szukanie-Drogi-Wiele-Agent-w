// --------------------------------------------

#include "Agent.h"

KlatkaRuchu::KlatkaRuchu(PozycjaNaMapie poz, unsigned int Rodzic, int kosztG, int kosztH,unsigned int Tick)
{
	this->pozycja = poz;
	this->Rodzic = Rodzic;
	this->kosztG = kosztG;
	this->kosztH = kosztH;
	this->Tick = Tick;
}
bool KlatkaRuchu::operator==(const KlatkaRuchu& klatka)
{
	if (pozycja == klatka.pozycja) return true;
	else return false;
}
bool KlatkaRuchu::operator>(const KlatkaRuchu& klatka)
{
	if (kosztG + kosztH > klatka.kosztG + klatka.kosztH) return true;
	else if (kosztG + kosztH == klatka.kosztG + klatka.kosztH)
	{
		if (kosztG > klatka.kosztG) return true;
		else return false;
	}
	else return false;

}
KlatkaRuchu KlatkaRuchu::operator=(const KlatkaRuchu& klatka)
{
	this->kosztG = klatka.kosztG;
	this->kosztH = klatka.kosztH;
	this->pozycja = klatka.pozycja;
	this->Rodzic = klatka.Rodzic;
	this->Tick = klatka.Tick;
	return *this;
}
void KlatkaRuchu::WypiszKlatkeRuchu()
{
	std::cout << "Koszt G: " << kosztG << "\n Koszt H: " << kosztH << "\n Pozycja: " << pozycja.x << ".x " << pozycja.y << ".y \n Rodzic :" << Rodzic << "\n";
}

// --------------------------------
void Szukanaklatka(PozycjaNaMapie pozycja, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, KlatkaRuchu& klatkaruchu)
{
	KlatkaRuchu klatka{ pozycja,0,0};
	auto iteratorOtwarty = std::find(Otwarte.begin(), Otwarte.end(), klatka);
	auto iteratorZamknienty = std::find(Zamkniente.begin(), Zamkniente.end(), klatka);
	if (iteratorOtwarty != Otwarte.end())
	{
		klatkaruchu.kosztG = iteratorOtwarty._Ptr->kosztG;
		klatkaruchu.kosztH = iteratorOtwarty._Ptr->kosztH;
		klatkaruchu.pozycja = iteratorOtwarty._Ptr->pozycja;
		klatkaruchu.Rodzic = iteratorOtwarty._Ptr->Rodzic;
		klatkaruchu.Tick = iteratorOtwarty._Ptr->Tick;
	}
	else if (iteratorZamknienty != Zamkniente.end())
	{
		klatkaruchu.kosztG = iteratorZamknienty._Ptr->kosztG;
		klatkaruchu.kosztH = iteratorZamknienty._Ptr->kosztH;
		klatkaruchu.pozycja = iteratorZamknienty._Ptr->pozycja;
		klatkaruchu.Rodzic = iteratorZamknienty._Ptr->Rodzic;
		klatkaruchu.Tick = iteratorZamknienty._Ptr->Tick;
	}

}
//------------------------------------------
  // sluzy do wskaznania pozycji najbliszej celu

KlatkaCelu::KlatkaCelu(PozycjaNaMapie poz, unsigned int KosztH)
{
	this->poz = poz;
	this->KosztH = KosztH;

}



bool KlatkaCelu::operator > (const KlatkaCelu& klatka)
{
	if (KosztH > klatka.KosztH) return true;
	else return false;

}

bool KlatkaCelu::operator == (const KlatkaCelu& klatka)
{
	if (poz == klatka.poz) return true;
	else return false;

}

KlatkaCelu KlatkaCelu::operator=(const KlatkaCelu& klatka)
{
	this->poz = klatka.poz;
	this->KosztH = klatka.KosztH;
	return *this;
}








//------------------------------------------------------------------------
KlatkaRuchu Agent::ZwrocMinimalne(std::vector<KlatkaRuchu>& Otwarte)
{
	KlatkaRuchu minimalna = Otwarte[0];
	for (KlatkaRuchu& klatka : Otwarte)
	{
		if (minimalna > klatka)
		{
			minimalna = klatka;
		}
	}
	return minimalna;
}

KlatkaCelu Agent::ZwrocMinimalne(std::vector<KlatkaCelu>& Klatki)
{
	if (Klatki.empty() == false)
	{
		KlatkaCelu minimalna = Klatki[0];
		for (KlatkaCelu& klatka : Klatki)
		{
			if (minimalna > klatka)
			{
				minimalna = klatka;
			}
		}
		return minimalna;
	}

}
void Agent::SzukanieDrogi(PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, Mapa& mapa, CzasLogiki& czaslogiki)
{
	KlatkaRuchu obecna;

	mapa.UsunPozycjeCzasoweDlaObiektu(IndexObiektu);
	mapa.ustawPozycjeWchodzaca(mapa.Kordynat(pozycja), czaslogiki.ZwrocTick(),IndexObiektu);
	mapa.ustawPozycjeWychodzaca(mapa.Kordynat(pozycja), std::numeric_limits<unsigned int>::infinity(),IndexObiektu);

	Szukanaklatka(docelu, Otwarte, Zamkniente, obecna);
	droga.push(obecna.pozycja);

	int iteracji = 0;

	while (obecna.pozycja != Poczatek)
	{
		iteracji++;
		if (obecna.pozycja == Poczatek)
		{
			std::cout << "Serio naprawde \n";
			break;
		}
		else
		{

			droga.push(obecna.pozycja);



		#ifdef AGENT_DEBUG
			UstawKolor(obecna.pozycja, PURPLE, KoloroweKwadraty);
		#endif // AGENT_DEBUG
			Szukanaklatka(RodzicPozycja(obecna.Rodzic, mapa.szerokosc), Otwarte, Zamkniente, obecna);
		}
		//std::cout << "Kurwa mac \n";
	}
#ifdef AGENT_DEBUG
	std::cout << "Rozmiar Drogi :" << droga._Get_container().size() << "Rozmiar Klatek :" << Otwarte.size() + Zamkniente.size() << "\n Liczba iteracji:" << iteracji << "\n";
#endif // AGENT_DEBUG 
	if (droga.empty() == true)
	{
#ifdef AGENT_DEBUG
		std::cout << "Nie ma drogi \n";
#endif // AGENT_DEBUG
		CelGlobalny.x = std::numeric_limits<float>::infinity();
		CelGlobalny.y = std::numeric_limits<float>::infinity();
	}
	unsigned int Rozmiar = droga.size();
	std::stack<PozycjaNaMapie> stos;

	while (droga.empty() == false)
	{
		stos.push(droga.front());
		droga.pop();
	}

	while (stos.empty() == false)
	{
		droga.push(stos.top());
		stos.pop();
	}
#ifdef AGENT_DEBUG
	std::cout << "Odwrocenie kolejki";
#endif // AGENT_DEBUG
}
void Agent::ZajmowaniePozycjiCzasowych(PozycjaNaMapie &Poczatek,CzasLogiki &czaslogiki,Mapa &mapa)
{
	PozycjaNaMapie poprzednia = { 0,0 };
	PozycjaNaMapie Nastpstwa = { 0,0 };
	PozycjaNaMapie obecnaPoz = Poczatek;

	float obencytick = czaslogiki.ZwrocTick();
	float PredkoscKlatkowa = static_cast<float>(mapa.RozmiarKlatki) * Predkosc;


	mapa.ustawPozycjeWychodzaca(Poczatek, czaslogiki.ZwrocTick() + TickRuchu(mapa.SrodekPola(Poczatek), mapa.SrodekPola(droga.front()), PredkoscKlatkowa, czaslogiki.ZwroctickRate()),IndexObiektu);

	for (unsigned int index = 0; index < droga._Get_container().size(); index++)
	{
		obecnaPoz = droga._Get_container().at(index);
		if (index >= 1)
		{
			poprzednia = droga._Get_container().at(index - 1);
			float poprzedniTick = TickRuchu(mapa.SrodekPola(obecnaPoz), mapa.SrodekPola(poprzednia), PredkoscKlatkowa, czaslogiki.ZwroctickRate());
		#ifdef AGENT_DEBUG
			std::cout << "Poprzedni Tick :" << obencytick - poprzedniTick << " Pozycje :" << obecnaPoz.x << ".x " << obecnaPoz.y << ".y \n";
		#endif // AGENT_DEBUG
			mapa.ustawPozycjeWchodzaca(obecnaPoz, static_cast<unsigned int>(obencytick - poprzedniTick),IndexObiektu);
		}
		else
		{
			mapa.ustawPozycjeWchodzaca(obecnaPoz, obencytick,IndexObiektu);
		}
		if (index < droga._Get_container().size() - 1)
		{
			Nastpstwa = droga._Get_container().at(index + 1);
			float nastepnyTick = TickRuchu(mapa.SrodekPola(obecnaPoz), mapa.SrodekPola(Nastpstwa), PredkoscKlatkowa, czaslogiki.ZwroctickRate());
			mapa.ustawPozycjeWychodzaca(obecnaPoz, static_cast<unsigned int>(obencytick + nastepnyTick),IndexObiektu);
		#ifdef AGENT_DEBUG
			std::cout << "nastepny Tick :" << nastepnyTick + obencytick << " Pozycje :" << obecnaPoz.x << ".x " << obecnaPoz.y << ".y \n";
		#endif // AGENT_DEBUG
			obencytick = obencytick + TickRuchu(mapa.SrodekPola(obecnaPoz), mapa.SrodekPola(Nastpstwa), PredkoscKlatkowa, czaslogiki.ZwroctickRate(), 1);
		#ifdef AGENT_DEBUG
			//std::cout << "Obecny Tick:" << obencytick << "\n";
		#endif // AGENT_DEBUG
		}
		else
		{
			mapa.ustawPozycjeWychodzaca(obecnaPoz, std::numeric_limits<unsigned int>::infinity(),IndexObiektu);
		}
	}




}











void Agent::Roszerz(Mapa& mapa, std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& docelu, bool& SzukajDrogi, CzasLogiki& czasLogiki)
{

	KlatkaRuchu minimalna = ZwrocMinimalne(Otwarte);
#ifdef AGENT_DEBUG
	NowyKwadrat(minimalna.pozycja, NIEBIESKI, minimalna.Rodzic, minimalna.kosztG, minimalna.kosztH, KoloroweKwadraty);
#endif // AGENT_DEBUG
	Zamkniente.emplace_back(minimalna);
	auto iterator = std::find(Otwarte.begin(), Otwarte.end(), minimalna);

	Otwarte.erase(iterator);
	

	for (int ix = -1; ix <= 1; ix++)
	{
		for (int iy = -1; iy <= 1; iy++)
		{
			if (ix != 0 || iy != 0)
			{

				KlatkaRuchu nowaKlatka;
				nowaKlatka.pozycja.x = ix + minimalna.pozycja.x;
				nowaKlatka.pozycja.y = iy + minimalna.pozycja.y;
				nowaKlatka.Rodzic = minimalna.pozycja.x + (minimalna.pozycja.y * mapa.szerokosc);
				nowaKlatka.kosztH = minimalna.kosztH + Koszt(minimalna.pozycja, nowaKlatka.pozycja);
				nowaKlatka.kosztG = Koszt(nowaKlatka.pozycja, docelu);
				nowaKlatka.Tick = minimalna.Tick + TickRuchu(mapa.SrodekPola(minimalna.pozycja), mapa.SrodekPola(nowaKlatka.pozycja), Predkosc * static_cast<float>(mapa.RozmiarKlatki), czasLogiki.ZwroctickRate(), 1);

				if (nowaKlatka.pozycja == docelu)
				{
				#ifdef AGENT_DEBUG
					std::cout << "Znaleziona \n";
				#endif // AGENT_DEBUG
					SzukajDrogi = true;
				#ifdef AGENT_DEBUG
					std::cout << "Znaleziona \n";
					NowyKwadrat(nowaKlatka.pozycja, ZIELONY, nowaKlatka.Rodzic, nowaKlatka.kosztG, nowaKlatka.kosztH, KoloroweKwadraty);
				#endif // AGENT_DEBUG
					Otwarte.emplace_back(nowaKlatka);
					//ustawRodzic({ nowaKlatka.pozycja }, nowaKlatka.Rodzic);
					break;
				}


				auto IteratorOtwarty = std::find(Otwarte.begin(), Otwarte.end(), nowaKlatka);
				auto IteratorZamknienty = std::find(Zamkniente.begin(), Zamkniente.end(), nowaKlatka);

				

				if (IteratorOtwarty == Otwarte.end() && IteratorZamknienty == Zamkniente.end() && mapa.czyPozycjaZajentaWCzasie(nowaKlatka.pozycja, nowaKlatka.Tick) == false)
				{
					if (mapa.ZwrocTypPola(nowaKlatka.pozycja) == TypPola::OTWARTE)
					{

						//nowaKlatka.WypiszKlatkeRuchu();
						Otwarte.emplace_back(nowaKlatka);
					#ifdef AGENT_DEBUG
						NowyKwadrat(nowaKlatka.pozycja, ZIELONY, nowaKlatka.Rodzic, nowaKlatka.kosztG, nowaKlatka.kosztH, KoloroweKwadraty);
					#endif // AGENT_DEBUG

					}
				}
				else if (IteratorOtwarty != Otwarte.end())
				{
					if (*IteratorOtwarty._Ptr > nowaKlatka)
					{
						//nowaKlatka.WypiszKlatkeRuchu();
						//IteratorOtwarty._Ptr->WypiszKlatkeRuchu();
						IteratorOtwarty._Ptr->kosztG = nowaKlatka.kosztG;
						IteratorOtwarty._Ptr->kosztH = nowaKlatka.kosztH;
						IteratorOtwarty._Ptr->Rodzic = nowaKlatka.Rodzic;
						IteratorOtwarty._Ptr->Tick = nowaKlatka.Tick;
					}
				}
			}
		}
	}
}
void Agent::NajbliszyCel(bool& Znaleziono, Vector2 Poczatek, Vector2& ZwracanyCel, Mapa& mapa, CzasLogiki& czaslogiki)
{
	PozycjaNaMapie pozPoczatkowa = mapa.Kordynat(Poczatek);
	//PozycjaNaMapie pozCelGlowny = mapa.Kordynat(CelGlobalny);

	PozycjaNaMapie pozycjaplayera = mapa.Kordynat(pozycja);

	Znaleziono = false;


	std::vector<KlatkaCelu> Zamkniente;
	std::vector<KlatkaCelu> Otwarte;
	std::vector<KlatkaCelu> Celowe;

	auto ZOtwartychdoZamknietych = [&](KlatkaCelu klatka)
		{
			auto WOtwartych = std::find(Otwarte.begin(), Otwarte.end(), klatka);
			if (WOtwartych != Otwarte.end())
				Otwarte.erase(WOtwartych);
			Zamkniente.emplace_back(klatka);
		};
	auto jesliW = [](std::vector<KlatkaCelu>& Klatki, KlatkaCelu nowaKlatka)
		{
			auto iterator = std::find(Klatki.begin(), Klatki.end(), nowaKlatka);
			if (iterator != Klatki.end())
				iterator._Ptr->KosztH = nowaKlatka.KosztH;
			else Klatki.emplace_back(nowaKlatka);
		};
	auto JesliJest = [](std::vector<KlatkaCelu>& klatki, const KlatkaCelu& klatka)->bool
		{
			auto iterator = std::find(klatki.begin(), klatki.end(), klatka);

			if (iterator == klatki.end()) return false;
			else return true;
		};
	if (mapa.ZwrocTypPola(pozPoczatkowa) == TypPola::OTWARTE && mapa.CzyPozyjaZajentaWNieskonczonosc(pozPoczatkowa)==false )
	{
		ZwracanyCel = mapa.SrodekPola(pozPoczatkowa);
		Znaleziono = true;
	}
	else if (mapa.ZwrocTypPola(pozPoczatkowa) == TypPola::ZAMKNIENTE || mapa.CzyPozyjaZajentaWNieskonczonosc(pozPoczatkowa) == true)
	{
		Otwarte.emplace_back(pozPoczatkowa, Koszt(pozPoczatkowa,pozycjaplayera ));

		
		while (Otwarte.empty() == false)
		{
			
			pozPoczatkowa = ZwrocMinimalne(Otwarte).poz;
			ZOtwartychdoZamknietych(ZwrocMinimalne(Otwarte));
			for (int ix = -1; ix <= 1; ix++)
			{
				for (int iy = -1; iy <= 1; iy++)
				{
					if (ix != 0 || iy != 0 )
					{
						KlatkaCelu nowaklatka = { {pozPoczatkowa.x + ix,pozPoczatkowa.y + iy},0 };
						if (mapa.CzyPozyjaZajentaWNieskonczonosc(nowaklatka.poz) == true || mapa.ZwrocTypPola(nowaklatka.poz) == TypPola::ZAMKNIENTE)
						{
							nowaklatka.KosztH = Koszt(nowaklatka.poz, pozycjaplayera);

							if (JesliJest(Zamkniente, nowaklatka) == false)
							{
								jesliW(Otwarte, nowaklatka);
								
							}
						}
						else
						{
							Znaleziono = true;
							Celowe.emplace_back(nowaklatka);
							
						}
					}
				}
			}
			

			if (Znaleziono == true) break;
			else
			{
				KlatkaCelu minimalna = ZwrocMinimalne(Otwarte);
				pozPoczatkowa = minimalna.poz;
			#ifdef AGENT_DEBUG
				std::cout << "Co mi ty zwrociles" << minimalna.poz.x << ".x " << minimalna.poz.y << ".y \n";
			#endif // AGENT_DEBUG
			}
		}
		if (Znaleziono == true)
		{
			ZwracanyCel = mapa.SrodekPola(ZwrocMinimalne(Celowe).poz);
		#ifdef AGENT_DEBUG
			std::cout << "Cel najbliszy :" << ZwracanyCel.x << ".x " << ZwracanyCel.y << ".y \n";
		#endif // AGENT_DEBUG
		}
	}
}
bool Agent::Rezerwacja(std::vector<KlatkaRuchu>& Otwarte, std::vector<KlatkaRuchu>& Zamkniente, PozycjaNaMapie& Poczatek, PozycjaNaMapie& docelu, Mapa& mapa, CzasLogiki& Czaslogiki)
{
#ifdef AGENT_DEBUG
	KoloroweKwadraty.clear();
#endif // AGENT_DEBUG
	while (droga.empty() == false)
	{
		droga.pop();
	}
	


	if (mapa.ZwrocTypPola(docelu) != TypPola::OTWARTE || mapa.ZwrocTypPola(Poczatek) != TypPola::OTWARTE || Poczatek == docelu)
	{
		return false;
	}
	else
	{
		Zamkniente = {};
		Otwarte = { {Poczatek,std::numeric_limits<unsigned int>::infinity(),Koszt(Poczatek,docelu),0,Czaslogiki.ZwrocTick()}};



		return true;
	}
}

//metody ruchu

Agent::Agent(Vector2 Pozycja, std::string NazwaTekstury, Color kolor, float Predkosc, unsigned int Zdrowie, Sojusze sojusz)
{
	this->pozycja = Pozycja;
	this->kolor = kolor;
	this->player.animacja = nullptr;
	this->player.zestawAnimacji = nullptr;
	this->Predkosc = Predkosc;
	this->Zdrowie = Zdrowie;
	this->sojusze = sojusz;
	this->typ = Typy::SYSTEM_OBRAZEN | Typy::SYSTEM_NAMIERZANIA | Typy::SYSTEM_USUWANIA;


	CelLokalny.x = std::numeric_limits<float>::infinity();
	CelLokalny.y = std::numeric_limits<float>::infinity();

	CelGlobalny.x = std::numeric_limits<int>::infinity();
	CelGlobalny.y = std::numeric_limits<int>::infinity();
}
Agent::Agent(Vector2 Pozycja, std::string NazwaTekstury, Color kolor, float Predkosc, unsigned int Zdrowie, Sojusze sojusz, std::vector<Obiekt*> Obiekty, TablicaAnimacji& tablica)
{
	this->pozycja = Pozycja;
	this->kolor = kolor;

	this->player.typAnimacji = TypyAnimacji::STANIE;

	this->player.ZnajdzZasob(NazwaTekstury, tablica);
	this->Predkosc = Predkosc;
	this->Zdrowie = Zdrowie;
	this->sojusze = sojusz;
	this->typ = Typy::SYSTEM_OBRAZEN | Typy::SYSTEM_NAMIERZANIA | Typy::SYSTEM_USUWANIA;

	CelLokalny.x = std::numeric_limits<float>::infinity();
	CelLokalny.y = std::numeric_limits<float>::infinity();

	CelGlobalny.x = std::numeric_limits<int>::infinity();
	CelGlobalny.y = std::numeric_limits<int>::infinity();

	this->IndexObiektu = Obiekty.size();

}

void Agent::AlgorytmDrogi(Mapa& mapa, CzasLogiki& czaslogiki)
{
	std::vector<KlatkaRuchu> Otwarte = {};
	std::vector<KlatkaRuchu> Zamkniente = {};

	PozycjaNaMapie docelu = mapa.Kordynat(CelLokalny);
	PozycjaNaMapie Poczatek = mapa.Kordynat(pozycja);
#ifdef AGENT_DEBUG
	std::cout << "Do Celu :" << docelu.x << ".x " << docelu.y << ".y \n Poczatek: " << Poczatek.x << ".x " << Poczatek.y << ".y \n";
	std::cout << " Do Tick :" << czaslogiki.ZwrocTick() << "\n";
#endif // AGENT_DEBUG
	bool SzukajDrogi = false;
	if (Rezerwacja(Otwarte, Zamkniente, Poczatek, docelu, mapa,czaslogiki) == true)
	{
		//unsigned int licznik = 0;
		mapa.UsunPozycjeCzasoweDlaObiektu(IndexObiektu);

		while (Otwarte.empty() == false)
		{
			if (SzukajDrogi == true) break;
			Roszerz(mapa, Otwarte, Zamkniente, docelu, SzukajDrogi, czaslogiki);
		}
		
		if (SzukajDrogi == false)
		{
			if (mapa.Kordynat(CelGlobalny) == mapa.Kordynat(CelLokalny))
			{
				CelGlobalny = { std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity() };
			}
				CelLokalny = mapa.SrodekPola(ZwrocMinimalne(Zamkniente).pozycja);
				docelu = mapa.Kordynat(CelLokalny);
				SzukajDrogi = true;

		}
		if (SzukajDrogi == true)
		{
			SzukanieDrogi(Poczatek, docelu, Otwarte, Zamkniente, mapa, czaslogiki);
			ZajmowaniePozycjiCzasowych(Poczatek, czaslogiki, mapa);
		}
			


	}
}
void Agent::ZnajdzCelLokalny(Mapa& mapa, CzasLogiki& czaslogiki)
{
	Vector2 Odleglosc;
	Odleglosc.x = CelGlobalny.x - pozycja.x;
	Odleglosc.y = CelGlobalny.y - pozycja.y;
	if (Dlugosc(Odleglosc) != 0)
	{
		Vector2 Kierunek;



		if (Dlugosc(Odleglosc) <= 10 * static_cast<float>(mapa.RozmiarKlatki))
		{
			bool szukany;
			NajbliszyCel(szukany, CelGlobalny, CelLokalny, mapa, czaslogiki);
			if (szukany == false)
			{
				CelGlobalny.x = std::numeric_limits<float>::infinity();
				CelGlobalny.y = std::numeric_limits<float>::infinity();
			}
			//else mapa.ustawPozycjeWychodzaca(mapa.Kordynat(CelLokalny), std::numeric_limits<unsigned int>::infinity(),IndexObiektu);


		}
		else
		{
			Vector2 WyszukanieCelu;

			WyszukanieCelu.x = Interpolacja(pozycja.x, CelGlobalny.x, static_cast<float>(mapa.RozmiarKlatki) * 10 / Dlugosc(Odleglosc));
			WyszukanieCelu.y = Interpolacja(pozycja.y, CelGlobalny.y, static_cast<float>(mapa.RozmiarKlatki) * 10 / Dlugosc(Odleglosc));


			bool znalezionoCelLokalny;
			NajbliszyCel(znalezionoCelLokalny, WyszukanieCelu, CelLokalny, mapa, czaslogiki);
			if (znalezionoCelLokalny == false)
			{
				CelGlobalny.x = std::numeric_limits<float>::infinity();
				CelGlobalny.y = std::numeric_limits<float>::infinity();
			}
			//else mapa.ustawPozycjeWychodzaca(mapa.Kordynat(CelLokalny), std::numeric_limits<unsigned int>::infinity(),IndexObiektu);
		}
	}
	else
	{
		CelGlobalny.x = std::numeric_limits<float>::infinity();
		CelGlobalny.y = std::numeric_limits<float>::infinity();

	}
}
void Agent::UstawGlownyCel(Vector2 GlownyCel, Mapa& mapa, CzasLogiki& czaslogiki)
{
	bool znaleziono;
	NajbliszyCel(znaleziono, GlownyCel, this->CelGlobalny, mapa, czaslogiki);
	if (znaleziono == false)
	{
		this->CelGlobalny.x = std::numeric_limits<float>::infinity();
		this->CelGlobalny.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		//mapa.ustawPozycjeWychodzaca(mapa.Kordynat(CelGlobalny), std::numeric_limits<unsigned int>::infinity(), IndexObiektu);
		ZnajdzCelLokalny(mapa, czaslogiki);
		AlgorytmDrogi(mapa, czaslogiki);
	}
}


#ifdef AGENT_DEBUG
void Agent::WizuDrogi(Mapa& mapa)
{
	//std::cout<<"Pozycje Czasowe :" << mapa.PozycjeCzasowe.size() << "\n";
	int rozmiar = static_cast<int>(mapa.RozmiarKlatki);
	for (KolorowyKwadrat& kwadrat : KoloroweKwadraty)
	{


		NarysujKwadrat(kwadrat, rozmiar);
	}
	//DrawRectangle(pozycja.x - (rozmiar / 4), pozycja.y - (rozmiar / 4), rozmiar / 2, rozmiar / 2, MAGENTA);
	DrawLine(pozycja.x, pozycja.y, CelLokalny.x, CelLokalny.y, GREEN);
	DrawLine(pozycja.x, pozycja.y, CelGlobalny.x, CelGlobalny.y, YELLOW);
}
#endif // AGENT_DEBUG






void Agent::WykonujDroge(Mapa& mapa, CzasLogiki& czaslogiki)
{







	if (droga.empty() == false)
	{
		if (player.animacja != nullptr && player.animacja->typ != TypyAnimacji::CHODZENIE) player.ZnajdzTypAnimacji(TypyAnimacji::CHODZENIE);
		if (ruch.Dotarlo() == true)
		{
			ruch.ZdefiniujRuch(pozycja, mapa.SrodekPola(droga.front()), pozycja);
			if(mapa.Kordynat(pozycja)!=droga.front())
			player.kierunek = ZwrocKierunek(mapa.Kordynat(pozycja), droga.front());
			//	std::cout << "Wykonalem \n";
			droga.pop();


		}
		else
		{
			ruch.Porusz(Predkosc * static_cast<float>(mapa.RozmiarKlatki) * czaslogiki.DeltaTimeTick(), pozycja);
		}
	}
	else
	{
		if (CelGlobalny.x != std::numeric_limits<float>::infinity() && CelGlobalny.y != std::numeric_limits<float>::infinity())
		{

			if (mapa.Kordynat(CelGlobalny) == mapa.Kordynat(pozycja))
			{
				CelGlobalny.x = std::numeric_limits<float>::infinity();
				CelGlobalny.y = std::numeric_limits<float>::infinity();
				player.ZnajdzTypAnimacji(TypyAnimacji::STANIE);

			}
			else
			{
				std::cout << "Hej dzije sie cos \n";
				if (mapa.CzyPozyjaZajentaWNieskonczonosc(mapa.Kordynat(CelGlobalny),IndexObiektu)==false && mapa.CzyPozyjaZajentaWNieskonczonosc(mapa.Kordynat(CelGlobalny))==true)
				{
					bool szukanie;
					NajbliszyCel(szukanie, CelGlobalny, CelGlobalny, mapa, czaslogiki);
					if (szukanie == true) CelLokalny = CelGlobalny;
				}
				//mapa.UsunPozycjeCzasoweDlaObiektu(IndexObiektu);
				ZnajdzCelLokalny(mapa, czaslogiki);
				AlgorytmDrogi(mapa, czaslogiki);
				player.ZnajdzTypAnimacji(TypyAnimacji::CHODZENIE);
			}
		}
		


		ruch.procent = 1;
	}
}
 void Agent::Akcja(Mapa& mapa, CzasLogiki& czasLogiki, SystemObrazen& system, SystemNamierzania& systemnamierzania, ParametryPociskow& parametry, TablicaAnimacji& tablica, std::vector<Obiekt*>& Obiekty)
{
	 bron.Strzelanie(IndexObiektu,czasLogiki, systemnamierzania, Obiekty, mapa, parametry, tablica);

	 WykonujDroge(mapa, czasLogiki);
}
 void Agent::Render(Mapa& mapa,CzasLogiki& czasLogiki, TablicaAnimacji& tablica)
 {
//	 std::cout << "Index Obiektu :" << IndexObiektu << "\n";
#ifdef AGENT_DEBUG
	 WizuDrogi(mapa);
#endif // AGENT_DEBUG
	 player.Rysuj(czasLogiki, pozycja,mapa.RozmiarKlatki, tablica);
 }
