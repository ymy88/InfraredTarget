#pragma once

#include <decl.h>
#include <GlobalConfig.h>

class RECORDER_DECL Recordable
{
public:
	virtual void getReady(const Situation& situation, unsigned int& begFrame, unsigned int& endFrame) = 0; // return max frame
	virtual void gotoFrame(unsigned int frame) = 0;
	virtual void end() {};
};
