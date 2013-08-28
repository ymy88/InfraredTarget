#include "StdAfx.h"
#include "InfraredCamera.h"
#include <GlobalConfig.h>
#include <Recorder.h>

//const string IMAGEPATH = "./resources/Missiles/Image";
const string IMAGEPATH = "c:/Image";

void MakeImageReal::operator()( osg::RenderInfo& renderInfo ) const
{
	InfraredCamera* camera = dynamic_cast<InfraredCamera*>(renderInfo.getCurrentCamera());
	Image* image = camera->_image;
	for (unsigned int i = 0; i < camera->_blindSpots.size(); ++i)
	{
		Vec2s& blindSpot = camera->_blindSpots[i];
		(*(image->data(blindSpot.x(), blindSpot.y()))) = (unsigned char)255;
	}

	if (!isEnd && shouldSaveImage)
	{
		sprintf((char*)path, "%s/Image%05d.jpg", IMAGEPATH.c_str(), frame);
		osgDB::writeImageFile(*image, path);
	}
}


InfraredCamera::InfraredCamera(void) : CameraBase(NULL, false)
{
	setClearColor(Vec4(0, 0, 0, 1));
	setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setViewport( 0, 0, INFRARED_VIEW_WIDTH, INFRARED_VIEW_HEIGHT );
	setReferenceFrame( Camera::ABSOLUTE_RF );
	setRenderOrder( Camera::PRE_RENDER );
	setCullingMode(NO_CULLING);

	Recorder::inst()->addRecordable(this);

	srand((unsigned)time(NULL));

	_makeImageRealCallback = new MakeImageReal;

	_image = new Image;
	this->attach(Camera::COLOR_BUFFER, _image);

	this->setComputeNearFarMode(DO_NOT_COMPUTE_NEAR_FAR);
}

InfraredCamera::~InfraredCamera(void)
{
}

void InfraredCamera::getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame )
{
	int resolution = situation.infrared.resolution;
	double angle = situation.infrared.cameraAngle;
	float blindRate = situation.infrared.blindRate;
	_makeImageRealCallback->shouldSaveImage = situation.other.saveToFile;

	// handle texture

	_image->allocateImage(resolution, resolution, 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	_image->setInternalTextureFormat(GL_LUMINANCE);
	Recorder::inst()->setInfraredTexture(_image);

	// handle camera property

	_cameraController.adjustCamera(resolution, resolution, 1);
	this->setProjectionMatrixAsPerspective(DegreesToRadians(angle), 1.0, 0.1, 1e6);
	this->setPostDrawCallback(_makeImageRealCallback);


	// handle blind spots

	_blindSpots.clear();
	int totalCount = resolution * resolution;
	int blindCount = totalCount * blindRate / 100;
	for (int i = 0; i < blindCount; ++i)
	{
		int x = (int)(1.0 * rand() / RAND_MAX * (resolution-1));
		int y = (int)(1.0 * rand() / RAND_MAX * (resolution-1));
		_blindSpots.push_back(Vec2s(x, y));
	}


	begFrame = 0;
	endFrame = 1;

	// handle callback

	_makeImageRealCallback->isEnd = false;

	// handle image directory
	if (situation.other.saveToFile)
	{
		boost::filesystem::path imagePath(stringToWString(IMAGEPATH));
		if (exists(imagePath))
		{
			boost::filesystem::remove_all(imagePath);
		}
		boost::filesystem::create_directory(imagePath);
	}
}

void InfraredCamera::gotoFrame(unsigned int frame)
{
	_makeImageRealCallback->frame = frame;
	_makeImageRealCallback->isEnd = false;
}

void InfraredCamera::end()
{
	_makeImageRealCallback->isEnd = true;
}