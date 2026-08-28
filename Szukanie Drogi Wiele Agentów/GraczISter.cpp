#include "GraczISter.h"


GraczISter::GraczISter(unsigned int Druzyna)
{
	this->Druzyna = Druzyna;
	this->IndexyObiektow = {};
	this->kamera.offset.x = GetScreenWidth() / 2;
	this->kamera.offset.y = GetScreenHeight() / 2;
	this->kamera.zoom = 1;
}
void GraczISter::InicjujKamere(Mapa& mapa)
{
	this->kamera.offset.x = GetScreenWidth() / 2;
	this->kamera.offset.y = GetScreenHeight() / 2;
	this->kamera.zoom = 1;
	this->kamera.target.x = GetScreenWidth() / 2;
	this->kamera.target.y = GetScreenHeight() / 2;
	maksmyalnyzoom = std::max(static_cast<float>(GetScreenWidth()/mapa.szerokosc * mapa.RozmiarKlatki), static_cast<float>(GetScreenWidth() /mapa.wysokosc * mapa.RozmiarKlatki) );
}

void GraczISter::ZmienianiePozycjiZMyszka(float czulosc,Mapa& mapa)
{
	
	this->IndexyObiektow = {};
	
	if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT))
	{
		this->kamera.target = GetScreenToWorld2D({ GetMousePosition().x - GetWorldToScreen2D(kamera.target,kamera).y,GetMousePosition().y - GetWorldToScreen2D(kamera.target,kamera).y}, kamera);
	}
	if (kamera.zoom != 0)
	{
		Vector2 RozmiarObszaru = { GetScreenWidth() / kamera.zoom,GetScreenHeight() / kamera.zoom };
		Vector2 RozmiarMapy = { mapa.szerokosc * mapa.RozmiarKlatki, mapa.wysokosc * mapa.RozmiarKlatki };

		//Vector2 Kwadrat = { RozmiarMapy.x - RozmiarObszaru.x,RozmiarMapy.y - RozmiarObszaru.y };

		Vector2 LewyRog = { RozmiarObszaru.x/2,RozmiarObszaru.y/2  };
		Vector2 PrawyRog = {(RozmiarMapy.x/2)-(RozmiarObszaru.x/2),(RozmiarMapy.y/2) - (RozmiarObszaru.y/2)};
		


		if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT) == true)
		{
			Vector2 Delta = GetMouseDelta();

			//this->kamera.target = Delta;
		             this->kamera.target.x= std::clamp(this->kamera.target.x +   (Delta.x / kamera.zoom),PrawyRog.x,LewyRog.x);
					 this->kamera.target.y = std::clamp(this->kamera.target.y + (Delta.y / kamera.zoom), PrawyRog.y, LewyRog.y);
					 
		};


		
		if (RozmiarObszaru.x >= RozmiarMapy.x) this->kamera.target.x = RozmiarMapy.x / 2;
		else
		{
			if (PrawyRog.x < this->kamera.target.x) this->kamera.target.x = PrawyRog.x;
			else if (LewyRog.x > this->kamera.target.x) this->kamera.target.x = LewyRog.x;
		}
		if (RozmiarObszaru.y >= RozmiarMapy.y) this->kamera.target.y = RozmiarMapy.y / 2;
		else
		{
			if (PrawyRog.y < this->kamera.target.y) this->kamera.target.y = PrawyRog.y;
			else if (LewyRog.y > this->kamera.target.y) this->kamera.target.y = LewyRog.y;
		}
	
	
	}





		float kolko = GetMouseWheelMove();
		if (kolko != 0)
		{
			kolko = kolko * czulosc;
			float nowyzoom = std::clamp(exp2f(logf(kamera.zoom) + kolko),maksmyalnyzoom,2.0f);
			kamera.zoom = nowyzoom;
			//Vector2 RozmairMapy = { mapa.szerokosc * mapa.RozmiarKlatki,mapa.wysokosc * mapa.RozmiarKlatki };

			//Vector2 WymiarObrazu = { GetScreenWidth() / nowyzoom,GetScreenHeight() / nowyzoom };
			//Vector2 PrawyRog = {WymiarObrazu.x/2,WymiarObrazu.y/2};
			//Vector2 LewyRog = {RozmairMapy.x-(WymiarObrazu.x/2),RozmairMapy.y - (WymiarObrazu.y/2)};

			//if (PrawyRog.x > kamera.target.x) kamera.target.x = PrawyRog.x;
			//if (PrawyRog.y > kamera.target.y) kamera.target.y = PrawyRog.y;
			//if (LewyRog.x < kamera.target.x) kamera.target.x = LewyRog.x;
			//if (LewyRog.y < kamera.target.y) kamera.target.y = LewyRog.y;
		//	kamera.target.x = std::clamp(kamera.target.x, PrawyRog.x, LewyRog.x);
		//	kamera.target.y = std::clamp(kamera.target.y, PrawyRog.y, LewyRog.y);





		}
	//	std::cout << "Kamera :" << this->kamera.target.x << ".x " << this->kamera.target.y << ".y \n";
	
}
void GraczISter::Zaznacz(Vector2 PozA, Vector2 PozB, Mapa& mapa, std::vector<Obiekt*> Obiekty)
{




	}
void GraczISter::KliknijNaPole(PozycjaNaMapie poz, std::vector<Obiekt*> Obiekty)
{




	}

void GraczISter::Rozprosz(std::vector<Obiekt*> Obiekty)
{




	}
void GraczISter::Zatakuj(Vector2 Cel, std::vector<Obiekt*> Obiekty)
{




	}
void GraczISter::RuszSie(Vector2 Cel, std::vector<Obiekt*> Obiekty)
{




	}