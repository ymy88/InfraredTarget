#pragma once

#include <osg/ShapeDrawable>

class MySphereDrawable : public ShapeDrawable
{
public:
	MySphereDrawable(Shape* shape) : ShapeDrawable(shape) {}
	~MySphereDrawable(void) {}

	virtual void drawImplementation(RenderInfo& renderInfo) const;
};