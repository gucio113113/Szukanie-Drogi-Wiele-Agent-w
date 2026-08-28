#pragma once
#ifndef CZASLOGIKI_H
#define CZASLOGIKI_H


#include <raylib.h>
#include <chrono>
class CzasLogiki
{
	unsigned int Tick;
	unsigned int TickRate;
	float DeltaTime;
	bool StanLogiki;
	std::chrono::steady_clock::time_point staryczas;

public:
	friend class Gra;
	CzasLogiki(unsigned int TickRate=24);
	bool CzasTrwania();
	//mowina nam czy logika moze sie wykonac
	bool StanCzasu();
	float DeltaTimeTick();
	float ZwroctickRate();
	unsigned int ZwrocTick();
	


};

#endif // !CZASLOGIKI_H