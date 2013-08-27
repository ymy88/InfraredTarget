#ifndef INFRAREDSIMULATOR_H
#define INFRAREDSIMULATOR_H

#include <PSDFViewQt/PSDFViewQt.h>
#include <QtGui/QMainWindow>
#include <QtCore/QObject>
#include "ui_infraredsimulator.h"
#include "parameters.h"

class InfraredSimulator : public QMainWindow, public EventHandler
{
	Q_OBJECT

public:
	InfraredSimulator(QWidget *parent = 0, Qt::WFlags flags = 0);
	~InfraredSimulator();

	OsgViewerBase* getMainView() { return ui.mainView; }
	OsgViewerBase* getInfraredView() { return ui.infraredView; }

	virtual void handleCustomEvent(unsigned int eventType, int param1, int param2);

public slots:
	void showParameter();
	void back();
	void go();
	void speed();

private:
	Ui::InfraredSimulatorClass ui;

	parameters* para;
	bool bGo;
	bool bBack;
};

#endif // INFRAREDSIMULATOR_H
