

#include <nlohmann/json.hpp>

struct Hole
{
	Hole(int x, int y, int diameter)
		: x(x)
		, y(y)
		, diameter(diameter)
	{
	}

	Hole(nlohmann::json const& json)
	{
		x = json["x"];
		y = json["y"];
		diameter = json["diameter"];
	}
	int x{ 0 };
	int y{ 0 };
	int diameter{ 0 };
};

