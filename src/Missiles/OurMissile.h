#pragma once

#include <PSDFCore/PSDFCore.h>
#include <Recordable.h>
#include "EnemyMissile.h"


class OurMissile :
	public Recordable, public EventHandler
{
public:
	OurMissile(OsgViewerBase* mainView, EnemyMissile* enemyMissile);
	~OurMissile(void);

	const Matrixd&	getMissileMatrixInFrame(unsigned int frame);
	const Vec2&		getDisturb(unsigned int frame);
	void			outputInfo(ofstream& fout, unsigned frame);
	virtual void	getReady( const Situation& situation, unsigned int& begFrame, unsigned int& endFrame);
	virtual void	gotoFrame( unsigned int frame );
	virtual void	handleSystemEvent(unsigned int eventType, int param1, int param2);

private:
	void			createTransformForMissile();
	Node*			createSight();
	unsigned		flyByTrack(const Situation& situation, CameraBase* camera, unsigned frame);
	unsigned		aimAtTarget(const Situation& situation, CameraBase* camera, unsigned frame);

private:
	OsgViewerBase*		_mainView;
	vector<Matrixd>		_track;
	vector<Vec2>		_disturb;
	MatrixTransform*	_transformForMissile;
	MatrixTransform*	_transformForHumanEye;
	MatrixTransform*	_atTransform;
	vector<Matrixd>		_posture;
	Geode*				_trackGeode;
	Label*				_label;

	unsigned int		_maxFrame;
	unsigned int		_delayFrame;
	unsigned int		_aimStartFrame;

	EnemyMissile*		_enemyMissile;

	double				_disturbAngleX;
	double				_disturbAngleY;
};
