#pragma once

#include "device.h"
#include "outline.h"

#include <nlohmann/json.hpp>

#include <vector>

struct Enclosure
{
	Enclosure(int x, int y, int width, int height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{
	}
	Enclosure(nlohmann::json const& json)
	{
		x = json["x"];
		y = json["y"];
		width = json["width"];
		height = json["height"];

		if (json.contains("devices")) 
		{
			auto devicesJson = json["devices"];
			for (auto const& deviceJson : devicesJson)
			{
				devices.push_back(Device(deviceJson));
			}
		}
		if (json.contains("holes"))
		{
			auto holesJson = json["holes"];
			for (auto const& holeJson : holesJson)
			{
				holes.push_back(Hole(holeJson));
			}
		}
		if (json.contains("outline"))
		{
			outline = Outline(json["outline"]);
		}
	}
	int x;
	int y;
	int width;
	int height;

	std::vector<Device> devices;
	std::vector<Hole> holes;
	Outline outline;
};
