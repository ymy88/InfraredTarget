#include "StdAfx.h"

#include <GlobalConfig.h>
#include <Recorder.h>

#include "BaseEnv.h"
#include "Earth.h"
#include "Stars.h"

bool BaseEnv::initPlugin()
{
	Node* earthNode = loadEarth();
	Node* starsNode = loadStars();
	
	for (unsigned i = 0; i < getParentViewerCount(); ++i)
	{
		OsgViewerBase* parentViewer = getParentViewer(i);
		parentViewer->getMainCamera()->setCameraMinDistance(EARTH_R + 10);
		parentViewer->getMainCamera()->setCameraMaxDistance(EARTH_R * 10);
		parentViewer->getLayerManager()->addToNewLayer(earthNode, "Earth");
		parentViewer->getLayerManager()->addToNewLayer(starsNode, "Stars");
	}
	
	InfraredCamera* camera = Recorder::inst()->getInfraredCamera();
	camera->addChild(starsNode);
	
	return true;
}

Node* BaseEnv::loadEarth()
{
	Earth earth;
	Node* earthNode = earth.createEarth();
	return earthNode;
}

Node* BaseEnv::loadStars()
{
	Stars stars;
	return stars.createStars();
}
