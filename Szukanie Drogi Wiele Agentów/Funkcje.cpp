#include "Funkcje.h"

// -------------------------------------
KolorowyKwadrat::KolorowyKwadrat(PozycjaNaMapie poz, Color kolor, std::string Napis, std::string Napis2)
{
	this->poz = poz;
	this->kolor = kolor;
	this->Napis = Napis;
	this->Napis2 = Napis2;
}
bool KolorowyKwadrat::operator==(const KolorowyKwadrat& kolorowy)
{
	if (poz == kolorowy.poz) return true;
	else return false;
}
bool KolorowyKwadrat::operator==(const PozycjaNaMapie poz)
{
	if (this->poz == poz) return true;
	else return false;

}





// --------------------------------------------------------- 
//Funkcje

void UstawKoszt(PozycjaNaMapie poz, int kosztG, int kosztH, std::vector<KolorowyKwadrat>& tablica)
{
	auto iterator = std::find(tablica.begin(), tablica.end(), poz);
	if (iterator != tablica.end()) iterator->Napis = std::to_string(kosztH) + "H " + std::to_string(kosztG) + "G";
	else
	{
		KolorowyKwadrat kolorowy;
		kolorowy.kolor = WHITE;
		kolorowy.Napis = std::to_string(kosztH) + "H " + std::to_string(kosztG) + "G";
		kolorowy.Napis2 = "";
		tablica.emplace_back(kolorowy);
	}

}

void UstawKolor(PozycjaNaMapie  poz, Color Kolor, std::vector<KolorowyKwadrat>& tablica)
{
	auto iterator = std::find(tablica.begin(), tablica.end(), poz);
	if (iterator != tablica.end()) iterator->kolor = Kolor;
	else
	{
		KolorowyKwadrat kolorowy;
		kolorowy.kolor = Kolor;
		kolorowy.Napis = "";
		kolorowy.Napis2 = "";
		tablica.emplace_back(kolorowy);
	}
}
void UstawRodzica(PozycjaNaMapie poz, unsigned int Rodzic, std::vector<KolorowyKwadrat>& tablica)
{
	auto iterator = std::find(tablica.begin(), tablica.end(), poz);
	if (iterator != tablica.end()) iterator->Napis2 = std::to_string(Rodzic);
	else
	{
		KolorowyKwadrat kolorowy;
		kolorowy.kolor = WHITE;
		kolorowy.Napis = "";
		kolorowy.Napis2 = std::to_string(Rodzic);
		tablica.emplace_back(kolorowy);
	}


}
void NowyKwadrat(PozycjaNaMapie poz, Color kolor, unsigned int rodzic, int kosztG, int kosztH, std::vector<KolorowyKwadrat>& tablica)
{
	auto iterator = std::find(tablica.begin(), tablica.end(), poz);
	if (iterator != tablica.end())
	{
		iterator->kolor = kolor;
		iterator->Napis = std::to_string(kosztH) + "H " + std::to_string(kosztG) + "G";
		iterator->Napis2 = std::to_string(rodzic);
	}
	else tablica.emplace_back(poz, kolor, std::to_string(kosztH) + "H " + std::to_string(kosztG) + "G", std::to_string(rodzic));
}
float Interpolacja(float x0, float y0, float x1, float y1, float obecna)
{
	return  ((y0 + (y1 - y0)) * (x1 - obecna) / (x1 - x0));
}
float Interpolacja(float x0, float x1, float procent)
{
	return x0 + (x1 - x0) * procent;
}



float TickRuchu(Vector2 pozA, Vector2 pozB, float Predkosc, const float tickrate, float procent)
{
	return ((Dlugosc({ pozB.x - pozA.x,pozB.y - pozA.y }) * procent) / Predkosc) * tickrate;
}
float Dlugosc(Vector2 wektor)
{
	return sqrtf(wektor.x * wektor.x + wektor.y * wektor.y);
}
Vector2 Normalizacja(Vector2 wektor)
{
	float dl= Dlugosc(wektor);
	if (dl != 0)
		return { wektor.x / dl,wektor.y / dl };
	else return { std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity() };
}

int WInterwale(float t)
{
	if (static_cast<int>(t) < t) return static_cast<int>(t) + 1;
	else return  static_cast<int>(t);
}
int Manhatan(PozycjaNaMapie A, PozycjaNaMapie B)
{
	return (B.x - A.x) + (B.y - A.y);
}
int Koszt(const PozycjaNaMapie A, const PozycjaNaMapie B)
{
	if (abs(B.x - A.x) > abs(B.y - A.y)) return (abs(B.x - A.x) - abs(B.y - A.y)) * 10 + abs(B.y - A.y) * 14;
	else if (abs(B.x - A.x) < abs(B.y - A.y)) return (abs(B.y - A.y) - abs(B.x - A.x)) * 10 + abs(B.x - A.x) * 14;
	else return abs((B.x - A.x) * 14);
}

PozycjaNaMapie RodzicPozycja(const unsigned int Rodzic, const unsigned int szerokosc)
{
	return { static_cast<int>(Rodzic % szerokosc),static_cast<int>(Rodzic / szerokosc) };
}

unsigned int PozycjaRodzic(const PozycjaNaMapie poz, const unsigned int szerokosc)
{
	return  static_cast<unsigned int>(poz.x) + static_cast<unsigned int>(poz.y) * szerokosc;
}
void NarysujKwadrat(KolorowyKwadrat& kwadrat, const  int& rozmiar)
{

	DrawRectangle(static_cast<int>(kwadrat.poz.x * rozmiar), static_cast<int>(kwadrat.poz.y * rozmiar), static_cast<int>(rozmiar), static_cast<int>(rozmiar), kwadrat.kolor);
	int rozmiartekstu = MeasureText(kwadrat.Napis.c_str(), rozmiar / 5);
	int tekstrozmiar = MeasureText(kwadrat.Napis2.c_str(), rozmiar / 5);
	DrawText(kwadrat.Napis.c_str(), kwadrat.poz.x * rozmiar + ((rozmiar - rozmiartekstu) / 2), kwadrat.poz.y * rozmiar + (rozmiar / 2), rozmiar / 5, BLACK);
	DrawText(kwadrat.Napis2.c_str(), kwadrat.poz.x * rozmiar + ((rozmiar - tekstrozmiar) / 2), kwadrat.poz.y * rozmiar + (rozmiar / 2) + (rozmiar / 5) + (rozmiar / 10), rozmiar / 5, BLACK);
}
float KonwersjaKatow(float Kat)
{
		return static_cast<float>(static_cast<int>(Kat) % 360) + static_cast<float>(Kat -  static_cast<int>(Kat)) ;
}
float OdwrocenieKonta(float Kat, bool WKtoraStrone)
{
	if (WKtoraStrone == true)
	{
		if (Kat >= -180 && Kat <= 0) return 360 + Kat;
		else return Kat;
	}
	else
	{
		if (Kat <= 180 && Kat >= 0) return -360 + Kat;
		else return Kat;
	}
}

float IloczynSkalarny(Vector2 A, Vector2 B)
{
	return (A.x * B.x) + (A.y * B.y);
}
float IloczynWektorowy(Vector2 A, Vector2 B)
{
	return (A.x * B.y) - (B.x * A.y);
}
void NarysujSiatke(std::vector<std::vector<unsigned int>>& Klatki,  int RozmiarSystemu,  int RozmiarKlatki, Color ZObiektem, Color BezObiektu)
{
	
	for (int index = 0; index < Klatki.size(); index++)
	{
		if (Klatki[index].empty() == true)
			DrawRectangle((index % RozmiarSystemu) * RozmiarKlatki, (index / RozmiarSystemu) * RozmiarKlatki, RozmiarKlatki, RozmiarKlatki, BezObiektu);
		else
		{
			int rozmiarTekstu = std::to_string(Klatki[index].size()).size() * (RozmiarKlatki / 10);

			DrawRectangle((index % RozmiarSystemu) * RozmiarKlatki, (index / RozmiarSystemu) * RozmiarKlatki, RozmiarKlatki, RozmiarKlatki, ZObiektem);
			DrawText(std::to_string(Klatki[index].size()).c_str(), (index % RozmiarSystemu) * RozmiarKlatki + ((RozmiarKlatki - rozmiarTekstu) / 2), (index / RozmiarSystemu) * RozmiarKlatki + (RozmiarKlatki / 2), RozmiarKlatki / 10, BLACK);

		}




	}






}


//---------------------------------------------------------------