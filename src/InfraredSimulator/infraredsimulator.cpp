#include "StdAfx.h"
#include "infraredsimulator.h"

#include <GlobalConfig.h>
#include <Recorder.h>
#include <sstream>

InfraredSimulator::InfraredSimulator(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.infraredView->setViewType(INFRARED_VIEW);
    bGo  =false;
	bBack=false;
	para = new parameters;

	connect(ui.parameter       ,SIGNAL(clicked()),this,SLOT(showParameter()));
	connect(ui.back            ,SIGNAL(clicked()),this,SLOT(back()         ));
	connect(ui.go              ,SIGNAL(clicked()),this,SLOT(go()           ));
	connect(ui.speed           ,SIGNAL(clicked()),this,SLOT(speed()        ));

	Vec3d pos(1, 0, 0);
	Vec4d amb(0.3, 0.3, 0.3, 1);
	Vec4d dif(1.5, 1.5, 1.5, 1);
	Vec4d sep(0.1, 0.1, 0.1, 1);
	ui.infraredView->setSunLightPosition(pos);
	ui.mainView->setSunLightPosition(pos);
	ui.infraredView->setSunLightValue(amb, dif, sep);
	ui.mainView->setSunLightValue(amb, dif, sep);

	EventCenter::inst()->registerHandler(this, MISSILES_DATA_UPDATE, ui.mainView->getStationId());
}

InfraredSimulator::~InfraredSimulator()
{

}

void InfraredSimulator::showParameter()
{
	Recorder::inst()->stop();
	ui.go->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/do.png);"));
    bGo=false;

	para->preShow();
	if (para->exec() == QDialog::Accepted)
	{
		ui.go->setEnabled(true);
		ui.back->setEnabled(true);
		ui.speed->setEnabled(true);
	}
}

void InfraredSimulator::go()
{
	if (false==bGo)
	{
		Recorder::inst()->play();
		ui.go->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/stop.png);"));
	    bGo=true;
	}
	else if (true==bGo)
	{
		Recorder::inst()->stop();
		ui.go->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/do.png);"));
	    bGo=false;
	}

}

void InfraredSimulator::speed()
{
	Recorder::inst()->speedUp();
}

void InfraredSimulator::back()
{
	Recorder::inst()->rewind();
}

void InfraredSimulator::handleCustomEvent( unsigned int eventType, int param1, int param2 )
{
	if (eventType == MISSILES_DATA_UPDATE)
	{
		DataCenter::DataPtr<MissileData> ptr;
		DataCenter::inst()->getData(ptr, param1);

		QString str = QString::number((double)ptr->currTime, 'f', 3);
		ui.timeLabel->setText(str);

		str = QString::number((double)ptr->distance, 'f', 3);
		ui.distLabel->setText(str);
	}
}