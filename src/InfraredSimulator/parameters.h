#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "ui_parameters.h"
#include <QtCore/QObject>
#include <QtGui/QDialog>

#include "TableModel.h"
#include "ListModel.h"

class parameters : public QDialog
{
	Q_OBJECT

public:
	parameters(QWidget *parent = 0);
	~parameters();

	void preShow();

public slots:
	void onSelectPreset(const QModelIndex& index);
	void onBrowse();
	void onBeginSim();
	
	void onAddNewRow();
	void onDelRow();
	
	void onComboBoxChanged(int index);
	void onEditChanged();
	
	void onSaveFile(bool);
	
private:
	void fillFormForCurrSituation();
	
private:
	Ui::parameters ui;
	
};

#endif // PARAMETERS_H
