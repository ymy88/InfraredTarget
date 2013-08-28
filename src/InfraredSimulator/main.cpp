#include "StdAfx.h"
#include "infraredsimulator.h"

#include <QtCore/QTextCodec>
#include <QtGui/QApplication>

#include <Recorder.h>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
	
	
	QApplication a(argc, argv);

	if (!DataManager::loadData())
	{
		return -1;
	}

	InfraredSimulator w;
	w.show();

	Recorder::inst()->setMainView(w.getMainView());
	Recorder::inst()->setInfraredView(w.getInfraredView());

	setGlobalTimer(20);

	PluginManager::inst()->loadPlugins();

	allViewAdjustCamera();

	a.exec();

	return 1;
}
