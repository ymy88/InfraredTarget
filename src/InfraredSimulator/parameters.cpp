#include "StdAfx.h"
#include "parameters.h"
#include "GlobalConfig.h"
#include "Recorder.h"

#include <QtCore/QString>


parameters::parameters(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	PresetListModel* presetModel = new PresetListModel;
	ui.listPreset->setModel(presetModel);
	
	EnemyMissileTableModel* enemyModel = new EnemyMissileTableModel;
	ui.tableEnemy->setModel(enemyModel);
	
	OurMissileTableModel* ourModel = new OurMissileTableModel;
	ui.tableOur->setModel(ourModel);

	LocationTableModel* locModel = new LocationTableModel;
	ui.tableLoc->setModel(locModel);
	
	LocationComboModel* locComboModel = new LocationComboModel;
	ui.cboOurLoc->setModel(locComboModel);
	ui.cboEnemyLoc->setModel(locComboModel);
	
	EnemyMissileComboModel* enemyComboModel = new EnemyMissileComboModel;
	ui.cboEnemyMissile->setModel(enemyComboModel);
	
	OurMissileComboModel* ourComboModel = new OurMissileComboModel;
	ui.cboOurMissile->setModel(ourComboModel);
	
	connect(ui.listPreset->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onSelectPreset(const QModelIndex&)));
	connect(ui.browse, SIGNAL(clicked()), this, SLOT(onBrowse()));
	connect(ui.begin, SIGNAL(clicked()), this, SLOT(onBeginSim()));
	
	connect(ui.cboEnemyLoc, SIGNAL(activated(int)), this, SLOT(onComboBoxChanged(int)));
	connect(ui.cboOurLoc, SIGNAL(activated(int)), this, SLOT(onComboBoxChanged(int)));
	connect(ui.cboEnemyMissile, SIGNAL(activated(int)), this, SLOT(onComboBoxChanged(int)));
	connect(ui.cboOurMissile, SIGNAL(activated(int)), this, SLOT(onComboBoxChanged(int)));
	connect(ui.editEnemyAlt, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editEnemyThetaEarth, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editEnemyThetaNorth, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editOurAlt, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editOurThetaEarth, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editOurThetaNorth, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editOurDelay, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editCameraAngle, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editBlindRate, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editResolution, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	connect(ui.editUpdateRate, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	
	connect(ui.btnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveFile(bool)));
	connect(ui.editInitDist, SIGNAL(editingFinished()), this, SLOT(onEditChanged()));
	
	connect(ui.btnAddPreset, SIGNAL(clicked()), this, SLOT(onAddNewRow()));
	connect(ui.btnDelPreset, SIGNAL(clicked()), this, SLOT(onDelRow()));
	connect(ui.btnAddEnemy, SIGNAL(clicked()), this, SLOT(onAddNewRow()));
	connect(ui.btnDelEnemy, SIGNAL(clicked()), this, SLOT(onDelRow()));
	connect(ui.btnAddOur, SIGNAL(clicked()), this, SLOT(onAddNewRow()));
	connect(ui.btnDelOur, SIGNAL(clicked()), this, SLOT(onDelRow()));
	
	connect(ui.btnAddLoc, SIGNAL(clicked()), this, SLOT(onAddNewRow()));
	connect(ui.btnDelLoc, SIGNAL(clicked()), this, SLOT(onDelRow()));
	
	setWindowFlags(Qt::WindowMinimizeButtonHint);
}

parameters::~parameters()
{

}

void parameters::preShow()
{
	fillFormForCurrSituation();
}

void parameters::onSelectPreset(const QModelIndex& index)
{
	DataManager::setCurrSituation(index.row());
	fillFormForCurrSituation();
}


void parameters::onBrowse()
{

	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly
                                                                | QFileDialog::DontResolveSymlinks);
	ui.showPath->setText(dir);

}
void parameters::onBeginSim()
{
	Situation* currSituation = DataManager::getCurrSituation();
	if (currSituation && currSituation->isValid())
	{
		DataManager::commitEditPreset(*currSituation);
		Recorder::inst()->getReady();
		accept();
	}
	else
	{
		QMessageBox::information(this, QString("Error"), QString("Wrong input!"));
	}
}

void parameters::onAddNewRow()
{
	QAbstractItemView* view;
	vector<QComboBox*> cboList;
	QToolButton* button = qobject_cast<QToolButton*>(sender());
	if (button == ui.btnAddPreset)
	{
		view = ui.listPreset;
	}
	else if (button == ui.btnAddEnemy)
	{
		view = ui.tableEnemy;
		cboList.push_back(ui.cboEnemyMissile);
	}
	else if (button == ui.btnAddOur)
	{
		view = ui.tableOur;
		cboList.push_back(ui.cboOurMissile);
	}
	else if (button == ui.btnAddLoc)
	{
		view = ui.tableLoc;
		cboList.push_back(ui.cboOurLoc);
		cboList.push_back(ui.cboEnemyLoc);
	}
	else
	{
		return;
	}
	view->model()->insertRow(0);
	
	for (unsigned i = 0; i < cboList.size(); ++i)
	{
		cboList[i]->model()->insertRow(0);
	}
}

void parameters::onDelRow()
{
	QAbstractItemView* view;
	vector<QComboBox*> cboList;
	QToolButton* button = qobject_cast<QToolButton*>(sender());
	if (button == ui.btnDelPreset)
	{
		view = ui.listPreset;
	}
	else if (button == ui.btnDelEnemy)
	{
		view = ui.tableEnemy;
		cboList.push_back(ui.cboEnemyMissile);
	}
	else if (button == ui.btnDelOur)
	{
		view = ui.tableOur;
		cboList.push_back(ui.cboOurMissile);
	}
	else if (button == ui.btnDelLoc)
	{
		view = ui.tableLoc;
		cboList.push_back(ui.cboEnemyLoc);
		cboList.push_back(ui.cboOurLoc);
	}
	else
	{
		return;
	}
	
	QItemSelectionModel* select = view->selectionModel();
	QModelIndexList list = select->selectedRows();
	if (list.size() > 0)
	{
		for (int i = (int)list.size()-1; i >= 0; --i)
		{
			view->model()->removeRow(list[i].row());
			for (unsigned j = 0; j < cboList.size(); ++j)
			{
				cboList[j]->model()->removeRow(list[i].row());
			}
		}
	}
	
}

void parameters::onComboBoxChanged(int index)
{
	Situation* situ = DataManager::getCurrSituation();
	if (situ == NULL) { return; }
	
	QComboBox* cbo = qobject_cast<QComboBox*>(sender());
	if (cbo == ui.cboEnemyLoc)
	{
		situ->enemy.loc = DataManager::getLocation(index);
	}
	else if (cbo == ui.cboEnemyMissile)
	{
		situ->enemy.missile = DataManager::getEnemyMissile(index);
	}
	else if (cbo == ui.cboOurLoc)
	{
		situ->our.loc = DataManager::getLocation(index);
	}
	else if (cbo == ui.cboOurMissile)
	{
		situ->our.missile = DataManager::getOurMissile(index);
	}
	else
	{
		return;
	}
	
	DataManager::commitEditPreset(*situ);
}

void parameters::onEditChanged()
{
	Situation* situ = DataManager::getCurrSituation();
	if (situ == NULL) { return; }
	
	QLineEdit* edit = qobject_cast<QLineEdit*>(sender());
	if (edit == ui.editEnemyAlt)
	{
		situ->enemy.alt = ui.editEnemyAlt->text().toFloat();
	}
	else if (edit == ui.editEnemyThetaEarth)
	{
		situ->enemy.thetaEarth = ui.editEnemyThetaEarth->text().toFloat();
	}
	else if (edit == ui.editEnemyThetaNorth)
	{
		situ->enemy.thetaNorth = ui.editEnemyThetaNorth->text().toFloat();
	}
	else if (edit == ui.editOurAlt)
	{
		situ->our.alt = ui.editOurAlt->text().toFloat();
	}
	else if (edit == ui.editOurThetaEarth)
	{
		situ->our.thetaEarth = ui.editOurThetaEarth->text().toFloat();
	}
	else if (edit == ui.editOurThetaNorth)
	{
		situ->our.thetaNorth = ui.editOurThetaNorth->text().toFloat();
	}
	else if (edit == ui.editOurDelay)
	{
		situ->our.delayTime = ui.editOurDelay->text().toFloat();
	}
	else if (edit == ui.editBlindRate)
	{
		situ->infrared.blindRate = ui.editBlindRate->text().toFloat();
	}
	else if (edit == ui.editCameraAngle)
	{
		situ->infrared.cameraAngle = ui.editCameraAngle->text().toFloat();
	}
	else if (edit == ui.editResolution)
	{
		situ->infrared.resolution = ui.editResolution->text().toShort();
	}
	else if (edit == ui.editUpdateRate)
	{
		situ->infrared.updateRate = (byte)ui.editUpdateRate->text().toInt();
	}
	else if (edit == ui.editInitDist)
	{
		situ->other.distForStartInfr = ui.editInitDist->text().toFloat();
	}
	else
	{
		return;
	}
	
	DataManager::commitEditPreset(*situ);
}


void parameters::onSaveFile(bool)
{
	Situation* situ = DataManager::getCurrSituation();
	if (situ == NULL) { return; }
	
	situ->other.saveToFile = (ui.btnSave->checkState() == Qt::Checked);
	DataManager::commitEditPreset(*situ);
}

void parameters::fillFormForCurrSituation()
{
	Situation* currSituation = DataManager::getCurrSituation();
	
	if (currSituation)
	{
		ui.cboOurLoc->setCurrentIndex(DataManager::findLocationIndex(currSituation->our.loc));
		ui.editOurAlt->setText(QString::number(currSituation->our.alt));
		ui.cboOurMissile->setCurrentIndex(DataManager::findOurMissileIndex(currSituation->our.missile));
		ui.editOurThetaEarth->setText(QString::number(currSituation->our.thetaEarth));
		ui.editOurThetaNorth->setText(QString::number(currSituation->our.thetaNorth));
		ui.editOurDelay->setText(QString::number(currSituation->our.delayTime));
		
		ui.cboEnemyLoc->setCurrentIndex(DataManager::findLocationIndex(currSituation->enemy.loc));
		ui.editEnemyAlt->setText(QString::number(currSituation->enemy.alt));
		ui.cboEnemyMissile->setCurrentIndex(DataManager::findEnemyMissileIndex(currSituation->enemy.missile));
		ui.editEnemyThetaEarth->setText(QString::number(currSituation->enemy.thetaEarth));
		ui.editEnemyThetaNorth->setText(QString::number(currSituation->enemy.thetaNorth));
		
		ui.editBlindRate->setText(QString::number(currSituation->infrared.blindRate));
		ui.editCameraAngle->setText(QString::number(currSituation->infrared.cameraAngle));
		ui.editResolution->setText(QString::number(currSituation->infrared.resolution));
		ui.editUpdateRate->setText(QString::number(currSituation->infrared.updateRate));
		
		Qt::CheckState state = currSituation->other.saveToFile ? Qt::Checked : Qt::Unchecked;
		ui.btnSave->setCheckState(state);
		ui.editInitDist->setText(QString::number(currSituation->other.distForStartInfr));
	}
	else
	{
		ui.cboOurLoc->setCurrentIndex(-1);
		ui.editOurAlt->clear();
		ui.cboOurMissile->setCurrentIndex(-1);
		ui.editOurThetaEarth->clear();
		ui.editOurThetaNorth->clear();
		ui.editOurDelay->clear();
		
		ui.cboEnemyLoc->setCurrentIndex(-1);
		ui.editEnemyAlt->clear();
		ui.cboEnemyMissile->setCurrentIndex(-1);
		ui.editEnemyThetaEarth->clear();
		ui.editEnemyThetaNorth->clear();
		
		ui.editBlindRate->clear();
		ui.editCameraAngle->clear();
		ui.editResolution->clear();
		ui.editUpdateRate->clear();
		
		ui.btnSave->setCheckState(Qt::Unchecked);
		ui.editInitDist->clear();
	}
}
