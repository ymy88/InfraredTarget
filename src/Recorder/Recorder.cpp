#include "StdAfx.h"
#include <Recorder.h>
#include <GlobalConfig.h>
#include <PSDFViewQt/PSDFViewQt.h>
#include <osg/ShaderAttribute>
#include <osg/Uniform>

Recorder* Recorder::inst()
{
	static Recorder instance;
	return &instance;
}

Recorder::Recorder()
{
	_isPlaying = true;
	_frameInc = 1;
	_keyObj = NULL;
}

Recorder::~Recorder(void)
{
}

void Recorder::addRecordable( Recordable* obj, bool isKey )
{
	for (unsigned int i = 0; i < _objList.size(); ++i)
	{
		if (_objList[i] == obj)
		{
			return;
		}
	}

	_objList.push_back(obj);

	if (isKey)
	{
		_keyObj = obj;
	}
}

void Recorder::getReady()
{
	_begFrame = 0;
	_endFrame = 0;
	_currFrame = 0;
	_frameInc = 1;
	_isPlaying = false;

	unsigned f1, f2;
	Situation& s = *DataManager::getCurrSituation();
	for (unsigned int i = 0; i < _objList.size(); ++i)
	{
		_objList[i]->getReady(s, f1, f2);

		if (_keyObj == NULL)
		{
			_begFrame = _begFrame > f1 ? _begFrame : f1;
			_endFrame = _endFrame > f2 ? _endFrame : f2;
		}
		else if (_keyObj == _objList[i])
		{
			_begFrame = f1;
			_endFrame = f2;
		}
	}

	_currFrame = _begFrame;
	allObjGotoCurrentFrame();

	int rate = (int)(DataManager::getCurrSituation()->infrared.updateRate);
	setGlobalTimer(1000 / rate);
}

void Recorder::play()
{
	_isPlaying = true;

	_currFrame += _frameInc;
	allObjGotoCurrentFrame();

	if (_currFrame >= _endFrame)
	{
		allObjEnd();
	}
}

void Recorder::stop()
{
	_isPlaying = false;
}

void Recorder::gotoAndPlay( unsigned int frame )
{
	if (frame > _endFrame) { return; }

	_isPlaying = true;
	_currFrame = frame;
	allObjGotoCurrentFrame();
	if (_currFrame >= _endFrame)
	{
		allObjEnd();
	}
}

void Recorder::gotoAndStop( unsigned int frame )
{
	if (frame > _endFrame) { return; }

	_isPlaying = false;
	_currFrame = frame;
	allObjGotoCurrentFrame();
	if (_currFrame >= _endFrame)
	{
		allObjEnd();
	}
}

int Recorder::speedUp()
{
	if (_frameInc < 4)
	{
		_frameInc += 1;
	}
	else
	{
		_frameInc = 1;
	}
	return _frameInc;
}

int Recorder::rewind()
{
	if (_frameInc > 0)
	{
		_frameInc = -1;
	}
	else if (_frameInc > -4)
	{
		_frameInc -= 1;
	}
	else
	{
		_frameInc = 1;
	}
	return _frameInc;
}

void Recorder::handleSystemEvent( unsigned eventType, int param1, int param2 )
{
	if (eventType != FRAME_BEGIN) { return; }

	if (!_isPlaying) { return; }

	if ((int)_currFrame + _frameInc < 0) { return; }
	if (_currFrame >= _endFrame)
	{
		return;
	}

	play();
}

void Recorder::setMainView( OsgViewerBase* mainView )
{
	EventCenter::inst()->registerHandler(this, SCENE_GROUP, mainView->getStationId());
}

void Recorder::setInfraredView( OsgViewerBase* infraredView )
{
	_infraredCamera = new InfraredCamera;

	_texture = new Texture2D;
	
	int size = 512;
	_geom = osg::createTexturedQuadGeometry(Vec3d(-size/2, -size/2, 0), Vec3d(size, 0, 0), Vec3d(0, size, 0));
	_geom->getOrCreateStateSet()->setMode(GL_BLEND, StateAttribute::ON);
	_geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, _texture);
	Geode* geode = new Geode;
	geode->addDrawable(_geom);
	
	_program = new Program;
	_vertObj = new Shader(Shader::VERTEX);
	_fragObj = new Shader(Shader::FRAGMENT);
	_program->addShader(_vertObj);
	_program->addShader(_fragObj);
	geode->getOrCreateStateSet()->setAttributeAndModes(_program, StateAttribute::ON);
	geode->getOrCreateStateSet()->addUniform(new Uniform(Uniform::UNSIGNED_INT_SAMPLER_2D, "tex", 0));
	
	
	bool res;
	res = _vertObj->loadShaderSourceFromFile("./resources/camera.vert");
	res = _fragObj->loadShaderSourceFromFile("./resources/camera.frag");


	infraredView->getLayerManager()->addToNewLayer(_infraredCamera, "InfraredCamera");
	infraredView->getScreenManager()->addScreenItem(geode, SCREEN_CENTER_CENTER, 0, 0);
}

void Recorder::setInfraredTexture(Image* image)
{
	_texture->setImage(image);
}

InfraredCamera* Recorder::getInfraredCamera()
{
	return _infraredCamera;
}

void Recorder::resetFrameInc()
{
	_frameInc = 1;
}

void Recorder::allObjGotoCurrentFrame()
{
	for (unsigned int i = 0; i < _objList.size(); ++i)
	{
		_objList[i]->gotoFrame(_currFrame);
	}
}

void Recorder::allObjEnd()
{
	for (unsigned int i = 0; i < _objList.size(); ++i)
	{
		_objList[i]->end();
	}
}
