#pragma once
#include "stdafx.h"

#include <hiberlite.h>
#include <string>

class CPilot
{
	friend class hiberlite::access;

	template<class Archive>
	void hibernate(Archive & ar)
	{
		ar & HIBERLITE_NVP(id);
		ar & HIBERLITE_NVP(name);
		ar & HIBERLITE_NVP(date_created);
		ar & HIBERLITE_NVP(hours);
		ar & HIBERLITE_NVP(company_id);
	}
public:
	int id;
	std::string name;
	INT64 date_created;
	float hours;
	int company_id;
};

