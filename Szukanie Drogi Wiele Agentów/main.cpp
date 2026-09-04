#include <raylib.h>
#include "Agent.h"
#include "Mapa.h"
#include <iostream>
#include <string>
#include "CzasLogiki.h"
#include <vector>
#include "Zasob.h"
#include "Gra.h"

//Mapa mapa(40);
//Agent agent(Vector2{50,50},ZOLTY,3);

std::vector<Agent> Agenci;




float CzasGlobalny;
float timestamp;

CzasLogiki czaslogiki(60);

void inicjacjaMapy()
{
	//mapa.StworzMape(,25, 25, { {2,3},{2,4},{5,2},{9,0},{6,9},{2,9},{1,0},{1,1},{0,1} });
}
 void WypiszInformacje(Agent &agent,Mapa &mapa)
{
	 for (const PozycjaNaMapie& pozycje : agent.droga._Get_container())
	 {
		 DrawText(std::to_string(pozycje.x + pozycje.y * mapa.szerokosc).c_str(), pozycje.x * mapa.RozmiarKlatki + mapa.RozmiarKlatki / 2, pozycje.y * mapa.RozmiarKlatki + mapa.RozmiarKlatki / 2, 10, BLACK);
	}
}
 /*
void ZnajdzDroge()
{
	
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
	{
		
		agent.UstawGlownyCel(mapa.Wysrodkuj({GetMouseX(),GetMouseY()}) , mapa,czaslogiki);
	
		std::cout << "What the hell \n";
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) == true)
	{
		agent.pozycja = mapa.Wysrodkuj({GetMouseX(),GetMouseY()});
	}
	
}
 */

int main()
{
	Gra gra("Gierka", { 1000,1000 }, 20,50);
	
	gra.Pentla();


//	ZestawAnimacji zestaw("../x64/Release/TestAnimacji");
	//StworzZestawAnimacji("../x64/Release/","Nowa", { 32,32 }, 8);
	//StworzTileSet(".", "TileSet", 10, 16);
	//StworzTabliceAnimacji(".", "Animacje", { "Ludzik" }, { 8,16 }, 4);






	return 0;
}