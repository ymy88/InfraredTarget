#pragma once
#include <PSDFCore/PSDFCore.h>
#include <osg/Vec2s>
#include <Recordable.h>

const int INFRARED_VIEW_WIDTH = 512;
const int INFRARED_VIEW_HEIGHT = 512;

struct MakeImageReal : public Camera::DrawCallback
{
	unsigned	frame;
	char		path[200];
	bool		isEnd;
	bool		shouldSaveImage;

	MakeImageReal() : frame(0) {};

	virtual void operator () (osg::RenderInfo& renderInfo) const;
};

class RECORDER_DECL InfraredCamera : public CameraBase, public Recordable
{
	friend struct MakeImageReal;

public:
	InfraredCamera(void);
	~InfraredCamera(void);

	//
	// from CameraBase
	//
	virtual void	adjustCamera(int viewWidth, int viewHeight ) {}
	virtual void	resize(int viewWidth, int viewHeight) {}
	virtual void	reset() {}

	//
	// from Recordable
	//
	virtual void getReady(const Situation& situation, unsigned int& begFrame, unsigned int& endFrame);
	virtual void gotoFrame(unsigned int frame);
	virtual void end();

	Node*	getLayer() { Geode* g = new Geode; g->addDrawable(_geom); return g; }

private:
	Image*				_image;
	Texture2D*			_tex;
	vector<Vec2s>		_blindSpots;
	bool				_shouldSaveImage;

	MakeImageReal*		_makeImageRealCallback;
	unsigned int		_delayFrame;

	Geometry*			_geom;
	Texture2D*			_texture;

	Program*			_program;
	Shader*				_vertObj;
	Shader*				_fragObj;
};
