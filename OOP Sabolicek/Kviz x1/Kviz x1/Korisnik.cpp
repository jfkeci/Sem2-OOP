#include "pch.h"
#include "Korisnik.h"


Korisnik::Korisnik(int kid, string kia, string ksi, string ksp, int kigr, string kski, string kskl)
{
	k_iIdKorisnika = kid;
	k_iAutorizacija = kia;
	k_sIme = ksi;
	k_sPrezime = ksp;
	k_iGodina_rodenja = kigr;
	k_sKorisnickoIme = kski;
	k_sKorisnickaLozinka = kskl;
}

Korisnik::~Korisnik()
{
}
