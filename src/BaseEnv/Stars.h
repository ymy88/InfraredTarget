#pragma once

#include <PSDFCore/PSDFCore.h>

class Stars
{
public:
	Stars(void) {}
	~Stars(void) {}

	Node* createStars();

private:
	Geometry* createGeom();

private:
	Vec3dArray* g_vertices;
	Vec4dArray* g_colors;
	Vec3dArray* g_normals;
	DrawArrays* g_drawArrays;
};
