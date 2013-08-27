#pragma once

#include <PSDFCore/PSDFCore.h>
#include <osg/Billboard>

class BaseEnv : public LayerPlugin
{
public:
	BaseEnv () : LayerPlugin() {};
	~BaseEnv () {};
	
	virtual bool	initPlugin();
	
private:
	Node*			loadEarth();
	Node*			loadStars();
};

EXPORT_PLUGIN_FUNCTION
{
	return new BaseEnv;
};
