#include "pch.h"
#include "Odgovor.h"


Odgovor::Odgovor(int idp, string sp, int oipid, int oit, string ovso) : Pitanje(idp, sp)
{
	o_iOdgovorID = oipid;
	o_iTocnost = oit;
	o_sOdgovor = ovso;
}


Odgovor::~Odgovor()
{
}
