#pragma once

#include <nlohmann/json.hpp>

struct Line
{
	Line()
	{
	}
	Line(int x1,
		int y1,
		int x2,
		int y2)
		: x1(x1)
		, y1(y1)
		, x2(x2)
		, y2(y2)
	{
	}

	Line(nlohmann::json const& json)
	{
		x1 = json["x1"];
		y1 = json["y1"];
		x2 = json["x2"];
		y2 = json["y2"];
	}
	int x1{ 0 };
	int y1{ 0 };
	int x2{ 0 };
	int y2{ 0 };
};

