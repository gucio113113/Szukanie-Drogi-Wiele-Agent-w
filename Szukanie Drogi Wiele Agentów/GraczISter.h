#pragma once
#include <raylib.h>
#include <vector>
#include "Obiekt.h"


class GraczISter
{
	unsigned int Druzyna;
	std::vector<unsigned int> IndexyObiektow;
	float maksmyalnyzoom;
	Camera2D kamera;

public:
	//Zaznacza Jednostki

	//Zaznacza Jednostki w Kwadracie
	friend class Gra;

	GraczISter(unsigned int Druzyna=1);
	void InicjujKamere(Mapa &mapa);
	void ZmienianiePozycjiZMyszka(float czulosc,Mapa &mapa);
	void Zaznacz(Vector2 PozA,Vector2 PozB,Mapa &mapa, std::vector<Obiekt*> Obiekty);
	void KliknijNaPole(PozycjaNaMapie poz, std::vector<Obiekt*> Obiekty);

	//Polecenia
	
	void Rozprosz(std::vector<Obiekt*> Obiekty);
	void Zatakuj(Vector2 Cel,std::vector<Obiekt*> Obiekty);
	void RuszSie(Vector2 Cel,std::vector<Obiekt*> Obiekty);







};

