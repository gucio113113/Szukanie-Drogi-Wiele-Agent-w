#include "Sojusze.h"
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

