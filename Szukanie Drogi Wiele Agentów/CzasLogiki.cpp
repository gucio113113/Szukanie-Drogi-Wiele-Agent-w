#include "CzasLogiki.h"

CzasLogiki::CzasLogiki(unsigned int TickRate)
{
	this->Tick = 0;
	this->TickRate = TickRate;
	staryczas = std::chrono::steady_clock::now();
	DeltaTime = 0;
	StanLogiki = false;
}
bool CzasLogiki::CzasTrwania()
{
	auto teraz = std::chrono::steady_clock::now();
	auto roznicza = teraz - staryczas;

	if (roznicza >= std::chrono::milliseconds(1000 / TickRate))
	{
		DeltaTime = std::chrono::duration<float>(roznicza).count();
		if (Tick == std::numeric_limits<unsigned int>::max()) Tick = 0;
		else Tick++;
		staryczas += std::chrono::milliseconds(1000 / TickRate);
		StanLogiki = true;
		return true;
	}
	else
	{
		StanLogiki = false;
		return false;
	}
}
bool CzasLogiki::StanCzasu()
{
	return StanLogiki;
}
float CzasLogiki::DeltaTimeTick()
{
	return DeltaTime;

}
float CzasLogiki::ZwroctickRate()
{

	return static_cast<float>(TickRate);

}
unsigned int CzasLogiki::ZwrocTick()
{
	return Tick;
}