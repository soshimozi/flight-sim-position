#pragma once
#include "stdafx.h"

#include <hiberlite.h>
#include <string>

class CAirport
{
	friend class hiberlite::access;

	template<class Archive>
	void hibernate(Archive& ar) {
		ar & HIBERLITE_NVP(airport_id);
		ar & HIBERLITE_NVP(name);
		ar & HIBERLITE_NVP(city);
		ar & HIBERLITE_NVP(country);
		ar & HIBERLITE_NVP(iata_faa);
		ar & HIBERLITE_NVP(iaco);
		ar & HIBERLITE_NVP(longitude);
		ar & HIBERLITE_NVP(latitude);
		ar & HIBERLITE_NVP(altitude);
		ar & HIBERLITE_NVP(zone);
		ar & HIBERLITE_NVP(dst);
	}
public:
	int airport_id;
	std::string name;
	std::string city;
	std::string country;
	std::string iata_faa;
	std::string iaco;
	float latitude;
	float longitude;
	float altitude;
	float zone;
	std::string dst;
};

