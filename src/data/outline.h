#pragma once

#include "line.h"
#include <nlohmann/json.hpp>

struct Outline
{
	Outline()
	{
	}
	Outline(nlohmann::json const& json)
	{
		//auto holesJson = json["holes"];
		for (auto const& holeJson : json)
		{
			lines.push_back(Line(holeJson));
		}
	}
	std::vector<Line> lines;
};
