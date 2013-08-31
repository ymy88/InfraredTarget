#pragma once

#include <PSDFCore/PSDFCore.h>

const int HALO_INNER_RADIUS = EARTH_R;
const int HALO_OUTER_RADIUS = HALO_INNER_RADIUS + 500;

class Earth
{
public:
	Earth(void) {};
	~Earth(void) {};

	Node*	createEarth();

private:
	Node*	loadEarth();
	Node*	createHalo();
};