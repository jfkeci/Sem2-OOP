#pragma once

#include<string>
#include<iostream>

using namespace std;

class Pitanje
{
public:
	Pitanje(int idp, string sp);
	~Pitanje();
	int p_iIDpitanja;
	string p_sPitanje;
};

