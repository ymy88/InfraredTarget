#pragma once

#include <PSDFCore/PSDFCore.h>

const double GM = 3.98866e14;  // 万有引力常量 * 地球质量

Geometry*	createMissileTrackGeometry(const vector<Matrixd>& track, const Vec4d& trackColor);
void		initCameraForTrackCalc(CameraBase* camera, float lon, float lat, float alt, double thetaEarth, double thetaNorth); 