#include "pch.h"
#include "ProjectManagementSystem.h"


ProjectManagementSystem::ProjectManagementSystem()
{
}

void ProjectManagementSystem::DohvatiIzbornik() {
	cout << "|------------------------------------------|" << endl;
	cout << "|---------DOBRODOSLI U IZBORNIK------------|" << endl;
	cout << "|------------------------------------------|" << endl;
	cout << endl;
	cout << "1.--------------------PREGLED PITANJA------" << endl;
	cout << "2.--------------------DODAJ PITANJE--------" << endl;
	cout << "3.--------------------OBRISI PITANJE-------" << endl;
	cout << "4.--------------------PRIKAZ RANG LISTE----" << endl;
	cout << "5.--------------------ODJAVA---------------" << endl;
	cout << endl;

	cin.clear();

	int nOdabir;
	cin >> nOdabir;
	switch (nOdabir)
	{
	case 1:
		PregledajPitanja();
		break;
	case 2:
		DodajPitanje();
		break;
	case 3:
		IzbrisiPitanje();
		break;
	case 4:
		PrikaziRezultate();
		break;
	case 5:
		LoginSystem();
		break;
	default:
		cout << "Unijeli ste nepostojecu opciju" << endl;
		break;
	}
}

void ProjectManagementSystem::UcitajKorisnike() {

	vKorisnici.clear();

	oXmlDocument.LoadFile("korisnici.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pKorisnik = m_pDataset->FirstChildElement("korisnici");

	for (pChildKorisnik = m_pKorisnik->FirstChildElement("korisnik"); pChildKorisnik != NULL; pChildKorisnik = pChildKorisnik->NextSiblingElement()) {
		int id = stoi(pChildKorisnik->Attribute("id"));
		string autorizacija = pChildKorisnik->Attribute("autorizacija");
		string ime = pChildKorisnik->Attribute("ime");
		string prezime = pChildKorisnik->Attribute("prezime");
		int godinaRodenja = stoi(pChildKorisnik->Attribute("godinaRodenja"));
		string korisnickoIme = pChildKorisnik->Attribute("korisnickoIme");
		string korisnickaLozinka = pChildKorisnik->Attribute("korisnickaLozinka");

		vKorisnici.push_back(new Korisnik(id, autorizacija, ime, prezime, godinaRodenja, korisnickoIme, korisnickaLozinka));
	}
}

void ProjectManagementSystem::UcitajPitanja() {	

	vPitanja.clear();

	oXmlDocument.LoadFile("pitanja.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pPitanje = m_pDataset->FirstChildElement("pitanja");

	for (pChildPitanje = m_pPitanje->FirstChildElement("pitanje"); pChildPitanje != NULL; pChildPitanje = pChildPitanje->NextSiblingElement()) {
		int id = stoi(pChildPitanje->Attribute("idPitanja"));
		string pitanje = pChildPitanje->Attribute("pitanje");

		vPitanja.push_back(new Pitanje(id, pitanje));
	}
}
void ProjectManagementSystem::UcitajOdgovore() {

	vOdgovori.clear();

	oXmlDocument.LoadFile("pitanja.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pOdgovor = m_pDataset->FirstChildElement("odgovori");
	m_pPitanje = m_pDataset->FirstChildElement("pitanja");

	for (pChildPitanje = m_pPitanje->FirstChildElement("pitanje"); pChildPitanje != NULL; pChildPitanje = pChildPitanje->NextSiblingElement()) {
		int id = stoi(pChildPitanje->Attribute("idPitanja"));
		string pitanje = pChildPitanje->Attribute("pitanje");
		for (pChildOdgovor = m_pOdgovor->FirstChildElement("odgovor"); pChildOdgovor != NULL; pChildOdgovor = pChildOdgovor->NextSiblingElement()) {
			int idOdgovora = stoi(pChildOdgovor->Attribute("idOdgovora"));
			int tocnost = stoi(pChildOdgovor->Attribute("tocnost"));
			string odgovor = pChildOdgovor->Attribute("odgovor");
			if (id == idOdgovora) {
				vOdgovori.push_back(new Odgovor(id, pitanje, idOdgovora, tocnost, odgovor));
			}
		}
	}
}

void ProjectManagementSystem::UcitajRezultate() {

	vRezultati.clear();

	oXmlDocument.LoadFile("rezultati.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pRezultat = m_pDataset->FirstChildElement("rezultati");
	for (pChildRezultat = m_pRezultat->FirstChildElement("rezultat"); pChildRezultat != NULL; pChildRezultat = pChildRezultat->NextSiblingElement()) {
		int idIgraca = stoi(pChildRezultat->Attribute("idIgraca"));
		int bodovi = stoi(pChildRezultat->Attribute("bodovi"));
		int vrijeme = stoi(pChildRezultat->Attribute("vrijeme"));

		vRezultati.push_back(new Rezultat(idIgraca, bodovi, vrijeme));
	}
}

void ProjectManagementSystem::LoginSystem() {

	string username;
	string userpass;
	char ch;

	int index = 0;
	int provjera = 0;

	UcitajKorisnike();
	UcitajRezultate();

	cout << "\n\n--Unesite korisnicko ime--"<<endl;
	cout << "\n---->";
	cin >> username;
	cout << "Unesite korisnicku lozinku" << endl;
	cout << "\n---->";
	ch = _getch();
	while (ch != 13) {//character 13 is enter
		userpass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	for (int i = 0; i < vKorisnici.size(); i++) {
		
		if (vKorisnici[i]->k_sKorisnickoIme == username && vKorisnici[i]->k_sKorisnickaLozinka==userpass) {
			system("CLS");
			PrijavljeniKorisnikID = vKorisnici[i]->k_iIdKorisnika;
			cout << "\n\n-----USPJESNA PRIJAVA-----\n" << endl;
			cout << "Bok " << vKorisnici[i]->k_sIme << " " << vKorisnici[i]->k_sPrezime << endl;
			if (vKorisnici[i]->k_iAutorizacija == "admin") {
				cout << "\n-----Prijavljeni ste kao admin-----\n" << endl;
				DohvatiIzbornik();
			}
			else if (vKorisnici[i]->k_iAutorizacija == "igrac") {
				cout << "\n-----Prijavljeni ste kao igrac-----\n" << endl;
				for (int m = 0; m < vRezultati.size(); m++) {
					if (vKorisnici[i]->k_iIdKorisnika == vRezultati[m]->r_iIdIgraca) {
						index = m;
					}
				}
				if (vKorisnici[i]->k_iIdKorisnika == vRezultati[index]->r_iIdIgraca) {
					system("CLS");
					MaliIzbornik();
				}
				else if(vKorisnici[i]->k_iIdKorisnika != vRezultati[index]->r_iIdIgraca){
					PokreniKviz();
					break;
				}
			}		
			provjera = 1;
		}
	}
	if (provjera == 0) {
		system("CLS");
		cout << "\n\n------UNIJELI STE POGRESNE PODATKE------" << endl;
		cout << "-----------POKUSAJTE PONOVNO------------" << endl;
		LoginSystem();
	}
}
void ProjectManagementSystem::DodajPitanje() {

	system("CLS");

	cin.clear();// clear input buffer to restore cin to a usable state
	cin.ignore(INT_MAX, '\n');// ignore last input

	UcitajPitanja();

	oXmlDocument.LoadFile("pitanja.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	XMLElement *m_pDataPitanja = m_pDataset->FirstChildElement("pitanja");
	XMLElement *m_pDataOdgovori = m_pDataset->FirstChildElement("odgovori");

	XMLElement *pElementPitanje = oXmlDocument.NewElement("pitanje");
	XMLElement *pElementOdgovor = oXmlDocument.NewElement("odgovor");
	XMLElement *pElementOdgovor1 = oXmlDocument.NewElement("odgovor");
	XMLElement *pElementOdgovor2 = oXmlDocument.NewElement("odgovor");
	XMLElement *pElementOdgovor3 = oXmlDocument.NewElement("odgovor");
	
	int idp=1;

	string dppitanje="";
	string todgovor="";
	string nodgovor1="";
	string nodgovor2 = "";
	string nodgovor3 = "";
	string unos = "";

	cout << "\nOdabrali ste opciju dodaj pitanje\n" << endl;

	cout << "Upisite pitanje." << endl;
	cout << "----->";
	getline(cin, dppitanje);
	
	cout << "\n\nUpisite tocan odgovor od pitanja." << endl;
	cout << "Tocan odgovor----->";
	getline(cin, todgovor);

	cout << "\n\nUnesite tri netocna odgovora" << endl;
	cout << "----->";
	cin >> nodgovor1;
	cout << "\n----->";
	cin >> nodgovor2;
	cout << "\n----->";
	cin >> nodgovor3;

	/*for (int i = 0; i < vPitanja.size(); i++) {
		if (vPitanja[i]->p_iIDpitanja == vPitanja.size()) {
			idp = (vPitanja.size() + 1);
			goto dalje;
		}
	}*/

	for (int i = 0; i < vPitanja.size(); i++) {
		if (idp == vPitanja[i]->p_iIDpitanja) {
			idp++;
		}
		else {
			goto dalje;
		}
	}

dalje:

	krivo:
		cout << "\n\n\nDA LI STE UNJELI TOCNO PITANJE I ODGOVORE?" << endl;
		cout << "pritisnite D za DA ili N za NE" << endl;
		cout << "----->";
		cin >> unos;
		if (unos == "d") {

			pElementPitanje->SetAttribute("idPitanja", idp);
			pElementPitanje->SetAttribute("pitanje", dppitanje.c_str());

			pElementOdgovor->SetAttribute("idOdgovora", idp);
			pElementOdgovor->SetAttribute("tocnost", 1);
			pElementOdgovor->SetAttribute("odgovor", todgovor.c_str());

			pElementOdgovor1->SetAttribute("idOdgovora", idp);
			pElementOdgovor1->SetAttribute("tocnost", 0);
			pElementOdgovor1->SetAttribute("odgovor", nodgovor1.c_str());

			pElementOdgovor2->SetAttribute("idOdgovora", idp);
			pElementOdgovor2->SetAttribute("tocnost", 0);
			pElementOdgovor2->SetAttribute("odgovor", nodgovor2.c_str());

			pElementOdgovor3->SetAttribute("idOdgovora", idp);
			pElementOdgovor3->SetAttribute("tocnost", 0);
			pElementOdgovor3->SetAttribute("odgovor", nodgovor3.c_str());

			m_pDataOdgovori->InsertEndChild(pElementOdgovor);
			m_pDataOdgovori->InsertEndChild(pElementOdgovor1);
			m_pDataOdgovori->InsertEndChild(pElementOdgovor2);
			m_pDataOdgovori->InsertEndChild(pElementOdgovor3);

			m_pDataPitanja->InsertEndChild(pElementPitanje);

			oXmlDocument.SaveFile("pitanja.xml");
			system("CLS");
			cout << "\n\n----------PITANJE I ODGOVORI USPJESNO POHRANJENI U BAZU PODATAKA----------" << endl;
			cout << "\n-----------------------ODABERITE OPCIJU ZA NASTAVAK-----------------------" << endl;
			ExitIzbornik();
		}
		else if (unos == "n") {
			DodajPitanje();
		}
		else {
			goto krivo;
		}

	cout << "\n\n";

	ExitIzbornik();
}
void ProjectManagementSystem::IzbrisiPitanje() {

	system("CLS");

	m_pDataset = oXmlDocument.FirstChildElement("data");

	int rbIzbor;

	cout << "\nOdabrali ste opciju izbrisi pitanje." << endl;
	PregledajPitanja();
	cout << "\nNapomena- kod brisanja pitanja brisu se i odgovori koji idu uz to pitanje" << endl;
	cout << "\nUpisite redni broj pitanja koje zelite izbrisati" << endl;
	cout << "----->";
	cin >> rbIzbor;

	oXmlDocument.LoadFile("pitanja.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pPitanje = m_pDataset->FirstChildElement("pitanja");

	int counter = 1;
	int idodgovora = vPitanja[rbIzbor - 1]->p_iIDpitanja;

	for (pChildPitanje = m_pPitanje->FirstChildElement("pitanje"); pChildPitanje != NULL; 
		pChildPitanje = pChildPitanje->NextSiblingElement()) {
		if (counter == rbIzbor) {
			m_pPitanje->DeleteChild(pChildPitanje);

			break;
		}
		counter++;
	}

	m_pOdgovor = m_pDataset->FirstChildElement("odgovori");

	string ssid = to_string(idodgovora);

	for (int i = 0; i < 4; i++) {
		for (pChildOdgovor = m_pOdgovor->FirstChildElement("odgovor"); pChildOdgovor != NULL;
			pChildOdgovor = pChildOdgovor->NextSiblingElement()) {
			if (pChildOdgovor->Attribute("idOdgovora") == ssid) {
				m_pOdgovor->DeleteChild(pChildOdgovor);
				break;
			}
		}
	}
	oXmlDocument.SaveFile("pitanja.xml");
	cout << "\n\n---------------PITANJE JE USPJESNO UKLONJENO IZ BAZE PODATAKA---------------\n\n";

	cout << "\n\n";
	ExitIzbornik();
}


void ProjectManagementSystem::MaliIzbornik() {

	cin.clear();

	int izborx = 0;
	system("CLS");
	cout << "\n- Da li zelite :" << endl;
	cout << "--------> 1. -Igrati kviz" << endl;
	cout << "--------> 2. -Vidjeti rezultate" << endl;
	cout << "--------> 3. -Zatvoriti program" << endl;
	cout << "\nUnesite broj zeljene opcije koju zelite provesti:";
	cin >> izborx;

	if (izborx == 1) {
		PokreniKviz();
	}
	else if (izborx == 2) {
		PrikaziRezultate();
	}
	else if (izborx == 3) {

	}
	else {
		MaliIzbornik();
	}
}

void ProjectManagementSystem::ExitIzbornik() {

	cin.clear();

	int izbor;

	cout << "\n\nDa li zelite:" << endl;
	cout << "          1-----> Vratiti se na pocetni izbornik." << endl;
	cout << "          2-----> Zatvoriti program." << endl;
	cout << "\nUnesite broj zeljene opcije koji zelite provesti." << endl;
	cout << "----->";
	cin >> izbor;
	if (izbor == 1) {
		DohvatiIzbornik();
	}
	else if (izbor == 2) {
		system("pause");
	}
	else {
		cout << "\nUNIJELI STE POGRESAN BROJ OPCIJE, POKUSAJTE OPET" << endl;
		ExitIzbornik();
	}
}

void ProjectManagementSystem::PokreniKviz() {
	system("CLS");

	UcitajKorisnike();
	UcitajPitanja();
	UcitajOdgovore();

	cout << "\n---------------POCETAK KVIZA---------------" << endl;
	
	int bodovi = 0;
	int rbr = 1;
	int unosOdg;

	int j, temp;

	int vIndOdg[4] = { 0, 1, 2, 3 };
	vector<int> vIndPit;
	vector<string>v4Odgovora;
	int idOdgovora;

	for (int i = 0; i < vPitanja.size(); i++) {
		vIndPit.push_back(i);
	}

	chrono::steady_clock sc;   // create an object of `steady_clock` class
	auto start = sc.now();     // start timer
	
	srand(time(NULL));
	for (int i = 0; i < vPitanja.size(); i++) {
		j = rand() % (vPitanja.size() - 1);
		temp = vIndPit[i];
		vIndPit[i] = vIndPit[j];
		vIndPit[j] = temp;
	}

	for (int i = 0; i < 10; i++) {
		cout << "\n"<<rbr<<". Pitanje: "<<vPitanja[vIndPit[i]]->p_sPitanje << endl;

		for (int x = 0; x < 4; x++) {
			j = rand() % 3;
			temp = vIndOdg[x];
			vIndOdg[x] = vIndOdg[j];
			vIndOdg[j] = temp;
		}

		for (int x = 0; x < vOdgovori.size(); x++) {
			if (vOdgovori[x]->o_iOdgovorID == vPitanja[vIndPit[i]]->p_iIDpitanja) {
				v4Odgovora.push_back(vOdgovori[x]->o_sOdgovor);
				idOdgovora = vOdgovori[x]->o_iOdgovorID;
			}
		}
		for (int x = 0; x < 4; x++) {
			cout <<"					"<<(x+1)<<". ------->"<<v4Odgovora[vIndOdg[x]] << endl;
		}

		cout << "\n\nUnesite broj odgovora: " << endl;
		cout << "----->";
		cin >> unosOdg;

		int toc;

		for (int x = 0; x < vOdgovori.size(); x++) {
			if (idOdgovora == vOdgovori[x]->o_iOdgovorID && v4Odgovora[vIndOdg[unosOdg-1]] == vOdgovori[x]->o_sOdgovor) {
				//cout << "\nIdOdgovora:   ---->" << vOdgovori[x]->o_iOdgovorID << ", Tocnost odgovora: " << vOdgovori[x]->o_iTocnost << ", Odgovor: " << vOdgovori[x]->o_sOdgovor <<"\n\n"<< endl;
				if (vOdgovori[x]->o_iTocnost == 1) {
					bodovi += 1;
				}
			}
		}
		v4Odgovora.clear();
		rbr++;
	}

	auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
	//cout << "\n\nOperation took: " << time_span.count() << " seconds !!!";

	//cout << "\n\nBroj Bodova: " << bodovi << endl;

	oXmlDocument.LoadFile("rezultati.xml");
	m_pDataset = oXmlDocument.FirstChildElement("data");
	m_pRezultat = m_pDataset->FirstChildElement("rezultati");

	XMLElement *pElementRezultat = oXmlDocument.NewElement("rezultat");

	pElementRezultat->SetAttribute("idIgraca", PrijavljeniKorisnikID);
	pElementRezultat->SetAttribute("bodovi", bodovi);
	pElementRezultat->SetAttribute("vrijeme", (time_span.count()));

	m_pRezultat->InsertEndChild(pElementRezultat);

	oXmlDocument.SaveFile("rezultati.xml");

	cout << "\n\n\n---------------VASI REZULTATI I PODACI SU SPREMLJENI U BAZU PODATAKA---------------\n\n\n";

}
void ProjectManagementSystem::PrikaziRezultate() {

	cout << "\n\n";

	UcitajKorisnike();
	UcitajRezultate();

	int i, j, min, temp;
	for (i = 0; i < (vRezultati.size() - 1); i++) {
		min = i;
		for (j = i + 1; j < vRezultati.size(); j++)
			if (vRezultati[j]->r_iRangBodovi < vRezultati[min]->r_iRangBodovi) {
				min = j;
				temp = vRezultati[i]->r_iRangBodovi;
				vRezultati[i]->r_iRangBodovi = vRezultati[min]->r_iRangBodovi;
				vRezultati[min]->r_iRangBodovi = temp;
			}
	}
	int rbr = 1;
	string ime = "";
	string prezime = "";
	int bodovi;
	int vrijeme;

	cout << fixed;
	cout << setprecision(2);

	cout << left << setw(15) << "Redni Broj";
	cout << right << setw(15) << "Ime";
	cout << right << setw(15) << "Prezime";
	cout << right << setw(15) << "Bodovi";
	cout << right << setw(15) << "Vrijeme [s]";
	cout << "\n" << endl;

	for (int k = (vRezultati.size()-1); k >=0; k--) {
		for (int l = 0; l < vKorisnici.size(); l++) {
			if (vKorisnici[l]->k_iIdKorisnika == vRezultati[k]->r_iIdIgraca) {
				ime = vKorisnici[l]->k_sIme;
				prezime = vKorisnici[l]->k_sPrezime;
			}
		}

		bodovi = vRezultati[k]->r_iRangBodovi;
		vrijeme = vRezultati[k]->r_iVrijeme;

		cout << left << setw(15) <<	rbr;
		cout << right << setw(15) << ime;
		cout << right << setw(15) << prezime;
		cout << right << setw(15) << bodovi;
		cout << right << setw(15) << vrijeme;
		cout << "\n" << endl;
		
		rbr++;
	}

	system("pause");
}
void ProjectManagementSystem::PregledajPitanja() {

	vOdgovori.clear();
	vPitanja.clear();

	UcitajOdgovore();
	UcitajPitanja();
	
	int rbr = 1;
	cout << "\nPrikaz pitanja i odgovora:" << endl;
	for (int i = 0; i < vPitanja.size(); i++) {
		cout <<"\n"<<rbr++ << ". Pitanje----->" << vPitanja[i]->p_sPitanje << endl;
		for (int j = 0; j < vOdgovori.size(); j++) {
			if (vOdgovori[j]->o_iOdgovorID == vPitanja[i]->p_iIDpitanja) {
				if (vOdgovori[j]->o_iTocnost == 1) {
					cout <<"       Tocan odgovor: "<<vOdgovori[j]->o_sOdgovor << endl;
				}
				if (vOdgovori[j]->o_iTocnost == 0) {
					cout << "       Netocan odgovor: " << vOdgovori[j]->o_sOdgovor << endl;
				}
			}
		}
	}
	cout << "\n\n";
	ExitIzbornik();
}

ProjectManagementSystem::~ProjectManagementSystem()
{
}
