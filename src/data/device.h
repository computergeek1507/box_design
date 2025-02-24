#pragma once

#include "hole.h"
#include "outline.h"

#include <nlohmann/json.hpp>

#include <vector>

struct Device
{
	Device(int x, int y, int width, int height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{
	}

	Device(nlohmann::json const& json)
	{
		x = json["x"];
		y = json["y"];
		width = json["width"];
		height = json["height"];
		auto holesJson = json["holes"];
		for (auto const& holeJson : holesJson)
		{
			holes.push_back(Hole(holeJson));
		}
		outline = Outline(json["outline"]);
	}
	int x{ 0 };
	int y{ 0 };
	int width{ 0 };
	int height{ 0 };

	std::vector<Hole> holes;
	Outline outline;
};