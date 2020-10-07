#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <conio.h>
#include <iomanip>
#include <time.h>

#include "tinyxml2.h"

#include"Pitanje.h"
#include"Odgovor.h"
#include"Korisnik.h"
#include"Rezultat.h"

#include<chrono>

using namespace std;
using namespace tinyxml2;

class ProjectManagementSystem
{
public:
	vector<Korisnik*> vKorisnici;
	vector<Pitanje*> vPitanja;
	vector<Odgovor*> vOdgovori;
	vector<Rezultat*> vRezultati;

	XMLElement *pChildKorisnik;
	XMLElement *pChildPitanje;
	XMLElement *pChildOdgovor;
	XMLElement *pChildRezultat;
	XMLDocument oXmlDocument;
	XMLElement* m_pDataset;
	XMLElement* m_pKorisnik;
	XMLElement* m_pPitanje;
	XMLElement* m_pOdgovor;
	XMLElement* m_pRezultat;

	void DohvatiIzbornik();
	void UcitajKorisnike();
	void UcitajPitanja();
	void UcitajOdgovore();
	void UcitajRezultate();
	void LoginSystem();
	void PregledajPitanja();
	void PokreniKviz();
	void PrikaziRezultate();
	void MaliIzbornik();
	void DodajPitanje();
	void IzbrisiPitanje();
	void ExitIzbornik();

	int PrijavljeniKorisnikID;

	ProjectManagementSystem();

	~ProjectManagementSystem();
};