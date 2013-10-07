#pragma once

#include <PSDFCore/PSDFCore.h>
#include <decl.h>
#include <Recordable.h>
#include <InfraredCamera.h>

#include <osg/Program>
#include <osg/Shader>

const unsigned int MAX_END_FRAME = 60000;

class RECORDER_DECL Recorder : public EventHandler
{
public:
	static Recorder* inst();

private:
	Recorder();
	~Recorder(void);

public:
	void			setMainView(OsgViewerBase* mainView);
	void			setInfraredView(OsgViewerBase* infraredView);

	InfraredCamera*	getInfraredCamera();

	void			addRecordable(Recordable* obj, bool isKey = false);

	void			setInfraredTexture(Image* image);

	void			getReady();
	void			play();
	void			stop();
	void			gotoAndPlay(unsigned int frame);
	void			gotoAndStop(unsigned int frame);
	int				speedUp();
	int				rewind();
	void			resetFrameInc();

	int				getFrameIncrease() const { return _frameInc; }
	unsigned int	getMaxFrame() const { return _endFrame; }

	void			handleSystemEvent( unsigned eventType, int param1, int param2 );

private:
	void			allObjGotoCurrentFrame();
	void			allObjEnd();

private:
	unsigned int		_begFrame;
	unsigned int		_endFrame;
	unsigned int		_currFrame;

	bool				_isPlaying;
	int					_frameInc;

	InfraredCamera*		_infraredCamera;
	Geometry*			_geom;
	Texture2D*			_texture;

	vector<Recordable*> _objList;
	Recordable*			_keyObj;
	
	Program*			_program;
	Shader*				_vertObj;
	Shader*				_fragObj;
};


#ifdef _WIN32
#  ifndef RECORDER_EXPORTS
#    ifdef _DEBUG
#      pragma comment(lib, "Recorderd.lib")
#    else
#      pragma comment(lib, "Recorder.lib")
#    endif
#  endif
#endif