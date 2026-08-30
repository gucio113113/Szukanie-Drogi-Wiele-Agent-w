#pragma once

#include <raylib.h>
#include "Agent.h"
#include "Mapa.h"
//#include "rayguiimplementacja.h"
#include "CzasLogiki.h"
#include <filesystem>
#include "Obiekt.h"
#include "SystemNamierzania.h"
#include "Zasob.h"
#include "GraczISter.h"
#include <DyrektywyDebugowania.h>

class Gra
{
	std::vector<Obiekt*> Obiekty;
	Mapa mapa;
	CzasLogiki czas;
	TablicaAnimacji tablica;

	std::string NazwaGry;
	PozycjaNaMapie rozmiarekranu;

	SystemNamierzania systemnamierzania;
	SystemObrazen systemobrazen;

	GraczISter graczSter;
	ParametryPociskow parametrypociskow;

	
	void Inicjacja();
	void Sterowanie();
	void Logika();
	//This function is for handling deleting objects
	void UsuwanieObiektow();
	void Render();
	
public:


	Gra(std::string NazwaGry,PozycjaNaMapie rozmiarEkranu,unsigned int TickRate,unsigned int RozmiarKlatki);
	void Pentla();
	




};

