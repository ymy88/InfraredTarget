#pragma once

#include <PSDFCore/PSDFCore.h>

#include <osg/Program>
#include <osg/Shader>

const int HALO_INNER_RADIUS = EARTH_R;
const int HALO_OUTER_RADIUS = HALO_INNER_RADIUS + 200;

class Earth
{
public:
	Earth(void) {};
	~Earth(void) {};

	Node*	createEarth();

private:
	Node*	loadEarth();
	Node*	createHalo();

private:
	Program*	_haloProgram;
	Shader*		_haloVertObj;
	Shader*		_haloFragObj;
};