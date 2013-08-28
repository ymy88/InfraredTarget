#pragma once

#include <PSDFCore/PSDFCore.h>
#include <Recordable.h>
#include "EnemyMissile.h"
#include "OurMissile.h"

class Missiles : public LayerPlugin, public Recordable
{
public:
	Missiles(void);
	~Missiles(void);

	bool			initPlugin();

	virtual void	getReady(const Situation& situation, unsigned int& begFrame, unsigned int& endFrame);
	virtual void	gotoFrame(unsigned int frame);
	virtual void	end();

private:
	EnemyMissile*	_enemyMissile;
	OurMissile*		_ourMissile;

	float			_timeForFrame;
	ofstream		_fout;
	bool			_shouldSaveFile;
};

EXPORT_PLUGIN_FUNCTION
{
	return new Missiles;
};