#ifndef SOJUSZE_H
#define SOJUSZE_H




enum class Druzyny : unsigned char
{
	NEUTRALNA = 0b00000000,
	PRZECZIWNA = 0b11111111,
	DRUZYNA1 = 0b00000001,
	DRUZYNA2 = 0b00000010,
	DRUZYNA3 = 0b00000100,
	DRUZYNA4 = 0b00001000,
	DRUZYNA5 = 0b00010000,
	DRUZYNA6 = 0b00100000,
	DRUZYNA7 = 0b01000000,
	DRUZYNA8 = 0b10000000,
};
inline constexpr Druzyny operator|(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator&(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) & static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator^(Druzyny a, Druzyny b) {
	return static_cast<Druzyny>(static_cast<unsigned char>(a) ^ static_cast<unsigned char>(b));
}
inline constexpr Druzyny operator~(Druzyny a) {
	return static_cast<Druzyny>(~static_cast<unsigned char>(a));
}
inline constexpr bool operator!(Druzyny a) {
	return static_cast<unsigned char>(a) == 0;
}




class Sojusze
{
	Druzyny sojusz;
	Druzyny wlasciciel;

public:
	Sojusze(Druzyny wlasciciel = Druzyny::NEUTRALNA, Druzyny Sojusz = Druzyny::NEUTRALNA);
	Sojusze(Druzyny wlasciciel);
	void UstawWlasciciel(Druzyny wlasciciel);
	void UstawSojusz(Druzyny sojusz);
	void UsunSojusz(Druzyny sojusz);
	Druzyny zwrocSojusz();
	Druzyny zwrocWlasciciel();
	//checks if two objects have the same team
	bool SprawdzSojusz(const Sojusze sojusz1);
	Sojusze operator=(const Sojusze sojusz1);
};


#endif // !SOJUSZE_H