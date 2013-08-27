#pragma once

#include <PSDFCore/PSDFCore.h>
#include <Recorder.h>

class EnemyMissile :
	public Recordable, public EventHandler
{
public:
	EnemyMissile(OsgViewerBase* mainView);
	~EnemyMissile(void);

	const Matrixd&	getMissileMatrixInFrame(unsigned int frame);
	unsigned int	getHitTargetFrame() { return _maxFrame; }
	void			setBeenHitFrame(unsigned int frame);
	void			outputInfo(ofstream& fout, unsigned int frame);

	virtual void	getReady(const Situation& situation, unsigned int& begFrame, unsigned int& endFrame);
	virtual void	gotoFrame(unsigned int frame);
	virtual void	handleSystemEvent(unsigned int eventType, int param1, int param2);

private:
	//void			createTransformsForBaits(unsigned int count);
	void			createTransformForBaits();
	void			createTransformForMissile();

private:
	OsgViewerBase*				_mainView;

	vector<Matrixd>				_track;
	MatrixTransform*			_transformForMissile;
	MatrixTransform*			_transformForInfrared;
	MatrixTransform*			_transformForHumanEye;
	MatrixTransform*			_transformForBaits;
	//vector<MatrixTransform*>	_transformsForBaits;
	vector<Vec3d>				_speedForBaits;
	Geode*						_trackGeode;
	Material*					_missileMaterial;
	Material*					_baitsMaterial;
	Label*						_label;

	unsigned int				_maxFrame;
	unsigned int				_hitFrame;
	
	/* 更新明暗所需参数 */
	double gray;
	double gray0;
	int grayState;
	double grayDelta;
	float grayX;
};
