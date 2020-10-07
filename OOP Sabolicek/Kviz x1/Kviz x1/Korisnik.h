#pragma once

#include<string>
#include<iostream>

using namespace std;

class Korisnik
{
public:
	Korisnik(int kid, string kia, string ksi, string ksp, int kigr, string kski, string kskl);
	~Korisnik();
	int k_iIdKorisnika;
	string k_iAutorizacija;
	string k_sIme;
	string k_sPrezime;
	int k_iGodina_rodenja;
	string k_sKorisnickoIme;
	string k_sKorisnickaLozinka;
	
};

