#pragma once
#include "Pitanje.h"
#include<vector>
class Odgovor :
	public Pitanje
{
public:
public:
	Odgovor(int idp, string sp, int oipid, int oit, string ovso);
	~Odgovor();
	int o_iOdgovorID;
	int o_iTocnost;
	string o_sOdgovor;
};

