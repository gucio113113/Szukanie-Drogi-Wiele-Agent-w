#include "PozycjeNaMapie.h"
PozycjaNaMapie::PozycjaNaMapie(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool PozycjaNaMapie::operator == (const PozycjaNaMapie& poz)
{
	if (x == poz.x && y == poz.y) return true;
	else return false;
}
bool PozycjaNaMapie::operator!=(const PozycjaNaMapie& poz)
{
	if (x != poz.x || y != poz.y) return true;
	else return false;
}


PozycjaNaMapie PozycjaNaMapie::operator = (const PozycjaNaMapie& poz)
{
	this->x = poz.x;
	this->y = poz.y;
	return *this;

}

void PozycjaNaMapie::operator += (const PozycjaNaMapie& poz)
{
	x += poz.x;
	y += poz.y;
}

void PozycjaNaMapie::operator -= (const PozycjaNaMapie& poz)
{
	x -= poz.x;
	y -= poz.y;
}
PozycjaNaMapie PozycjaNaMapie::operator=(const Vector2 wektor)
{
	this->x = static_cast<int>(wektor.x),
		this->y = static_cast<int>(wektor.y);
	return *this;
}

PozycjaWCzasie::PozycjaWCzasie(PozycjaNaMapie poz, unsigned int wejscie, unsigned int wyjscie, unsigned int IndexObiektu)
{
	this->poz = poz;
	this->wejscie = wejscie;
	this->wyjscie = wyjscie;
	this->IndexObiektu = IndexObiektu;
}
bool PozycjaWCzasie::wTymCzasie(const unsigned int& Tick)
{
	if (wyjscie == std::numeric_limits<unsigned int>::infinity()) return true;

	else if (Tick >= wejscie && Tick <= wyjscie)
	{
		return true;
	}
	else return false;
}


bool PozycjaWCzasie::operator == (const PozycjaWCzasie& poz)
{
	if (this->poz == poz.poz) return true;
	else return false;
}
PozycjaWCzasie PozycjaWCzasie::operator = (const PozycjaWCzasie& poz)
{
	this->poz = poz.poz;
	this->wejscie = poz.wejscie;
	this->wyjscie = poz.wyjscie;
	this->IndexObiektu = poz.IndexObiektu;

	return *this;
}
