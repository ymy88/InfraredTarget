/********************************************************************************
** Form generated from reading UI file 'parameters.ui'
**
** Created: Fri Oct 11 21:13:03 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERS_H
#define UI_PARAMETERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parameters
{
public:
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabStart;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QComboBox *cboEnemyLoc;
    QLabel *label_12;
    QComboBox *cboEnemyMissile;
    QLabel *label_22;
    QLabel *label_13;
    QLabel *label_16;
    QLineEdit *editEnemyThetaEarth;
    QLineEdit *editEnemyThetaNorth;
    QLabel *label_17;
    QLineEdit *editEnemyAlt;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_14;
    QComboBox *cboOurLoc;
    QLabel *label;
    QLineEdit *editOurAlt;
    QLabel *label_23;
    QComboBox *cboOurMissile;
    QLabel *label_19;
    QLineEdit *editOurThetaEarth;
    QLabel *label_18;
    QLineEdit *editOurThetaNorth;
    QLabel *label_21;
    QLineEdit *editOurDelay;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *btnSave;
    QPushButton *browse;
    QLabel *showPath;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *editInitDist;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget_5;
    QGridLayout *gridLayout_3;
    QLabel *label_47;
    QLineEdit *editCameraAngle;
    QLabel *label_46;
    QLineEdit *editResolution;
    QLabel *label_51;
    QLineEdit *editBlindRate;
    QLabel *label_52;
    QLineEdit *editUpdateRate;
    QPushButton *begin;
    QListView *listPreset;
    QToolButton *btnAddPreset;
    QToolButton *btnDelPreset;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *tabMissile;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnAddEnemy;
    QToolButton *btnDelEnemy;
    QSpacerItem *horizontalSpacer;
    QTableView *tableEnemy;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *btnAddOur;
    QToolButton *btnDelOur;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tableOur;
    QWidget *tabAddr;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_24;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *btnAddLoc;
    QToolButton *btnDelLoc;
    QSpacerItem *horizontalSpacer_5;
    QTableView *tableLoc;

    void setupUi(QWidget *parameters)
    {
        if (parameters->objectName().isEmpty())
            parameters->setObjectName(QString::fromUtf8("parameters"));
        parameters->resize(847, 490);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parameters->sizePolicy().hasHeightForWidth());
        parameters->setSizePolicy(sizePolicy);
        parameters->setMinimumSize(QSize(847, 490));
        parameters->setMaximumSize(QSize(847, 490));
        parameters->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/InfraredSimulator/resource/peace2.png"), QSize(), QIcon::Normal, QIcon::Off);
        parameters->setWindowIcon(icon);
        horizontalLayout_3 = new QHBoxLayout(parameters);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tabWidget = new QTabWidget(parameters);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabStart = new QWidget();
        tabStart->setObjectName(QString::fromUtf8("tabStart"));
        groupBox_2 = new QGroupBox(tabStart);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 30, 200, 261));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(12);
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QString::fromUtf8("border-top-color: rgb(255, 177, 167);"));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 15, 181, 188));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(20);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cboEnemyLoc = new QComboBox(layoutWidget);
        cboEnemyLoc->setObjectName(QString::fromUtf8("cboEnemyLoc"));
        cboEnemyLoc->setEnabled(true);
        cboEnemyLoc->setMaximumSize(QSize(126, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(10);
        cboEnemyLoc->setFont(font1);
        cboEnemyLoc->setFocusPolicy(Qt::ClickFocus);
        cboEnemyLoc->setEditable(false);

        gridLayout->addWidget(cboEnemyLoc, 0, 1, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        gridLayout->addWidget(label_12, 1, 0, 1, 1);

        cboEnemyMissile = new QComboBox(layoutWidget);
        cboEnemyMissile->setObjectName(QString::fromUtf8("cboEnemyMissile"));
        cboEnemyMissile->setMaximumSize(QSize(16777215, 16777215));
        cboEnemyMissile->setFont(font1);
        cboEnemyMissile->setFocusPolicy(Qt::ClickFocus);
        cboEnemyMissile->setEditable(false);

        gridLayout->addWidget(cboEnemyMissile, 2, 1, 1, 1);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font);

        gridLayout->addWidget(label_22, 2, 0, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        gridLayout->addWidget(label_13, 0, 0, 1, 1);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);

        gridLayout->addWidget(label_16, 3, 0, 1, 1);

        editEnemyThetaEarth = new QLineEdit(layoutWidget);
        editEnemyThetaEarth->setObjectName(QString::fromUtf8("editEnemyThetaEarth"));
        editEnemyThetaEarth->setMinimumSize(QSize(120, 0));
        editEnemyThetaEarth->setMaximumSize(QSize(120, 16777215));
        editEnemyThetaEarth->setFont(font1);
        editEnemyThetaEarth->setFocusPolicy(Qt::ClickFocus);
        editEnemyThetaEarth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(editEnemyThetaEarth, 3, 1, 1, 1);

        editEnemyThetaNorth = new QLineEdit(layoutWidget);
        editEnemyThetaNorth->setObjectName(QString::fromUtf8("editEnemyThetaNorth"));
        editEnemyThetaNorth->setMinimumSize(QSize(120, 0));
        editEnemyThetaNorth->setMaximumSize(QSize(120, 16777215));
        editEnemyThetaNorth->setFont(font1);
        editEnemyThetaNorth->setFocusPolicy(Qt::ClickFocus);
        editEnemyThetaNorth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(editEnemyThetaNorth, 4, 1, 1, 1);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font);

        gridLayout->addWidget(label_17, 4, 0, 1, 1);

        editEnemyAlt = new QLineEdit(layoutWidget);
        editEnemyAlt->setObjectName(QString::fromUtf8("editEnemyAlt"));
        editEnemyAlt->setMinimumSize(QSize(120, 0));
        editEnemyAlt->setMaximumSize(QSize(120, 16777215));
        editEnemyAlt->setFont(font1);
        editEnemyAlt->setFocusPolicy(Qt::ClickFocus);
        editEnemyAlt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(editEnemyAlt, 1, 1, 1, 1);

        groupBox = new QGroupBox(tabStart);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(200, 30, 200, 261));
        groupBox->setFont(font);
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 15, 181, 222));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setVerticalSpacing(20);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        cboOurLoc = new QComboBox(layoutWidget_2);
        cboOurLoc->setObjectName(QString::fromUtf8("cboOurLoc"));
        cboOurLoc->setFont(font1);
        cboOurLoc->setFocusPolicy(Qt::ClickFocus);
        cboOurLoc->setEditable(false);

        gridLayout_2->addWidget(cboOurLoc, 0, 1, 1, 1);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        editOurAlt = new QLineEdit(layoutWidget_2);
        editOurAlt->setObjectName(QString::fromUtf8("editOurAlt"));
        editOurAlt->setMinimumSize(QSize(120, 0));
        editOurAlt->setMaximumSize(QSize(120, 16777215));
        editOurAlt->setFont(font1);
        editOurAlt->setFocusPolicy(Qt::ClickFocus);
        editOurAlt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(editOurAlt, 1, 1, 1, 1);

        label_23 = new QLabel(layoutWidget_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font);

        gridLayout_2->addWidget(label_23, 2, 0, 1, 1);

        cboOurMissile = new QComboBox(layoutWidget_2);
        cboOurMissile->setObjectName(QString::fromUtf8("cboOurMissile"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cboOurMissile->sizePolicy().hasHeightForWidth());
        cboOurMissile->setSizePolicy(sizePolicy1);
        cboOurMissile->setMaximumSize(QSize(126, 16777215));
        cboOurMissile->setFont(font1);
        cboOurMissile->setFocusPolicy(Qt::ClickFocus);
        cboOurMissile->setEditable(false);
        cboOurMissile->setModelColumn(0);

        gridLayout_2->addWidget(cboOurMissile, 2, 1, 1, 1);

        label_19 = new QLabel(layoutWidget_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 3, 0, 1, 1);

        editOurThetaEarth = new QLineEdit(layoutWidget_2);
        editOurThetaEarth->setObjectName(QString::fromUtf8("editOurThetaEarth"));
        editOurThetaEarth->setMinimumSize(QSize(120, 0));
        editOurThetaEarth->setMaximumSize(QSize(120, 16777215));
        editOurThetaEarth->setFont(font1);
        editOurThetaEarth->setFocusPolicy(Qt::ClickFocus);
        editOurThetaEarth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(editOurThetaEarth, 3, 1, 1, 1);

        label_18 = new QLabel(layoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 4, 0, 1, 1);

        editOurThetaNorth = new QLineEdit(layoutWidget_2);
        editOurThetaNorth->setObjectName(QString::fromUtf8("editOurThetaNorth"));
        editOurThetaNorth->setMinimumSize(QSize(120, 0));
        editOurThetaNorth->setMaximumSize(QSize(120, 16777215));
        editOurThetaNorth->setFont(font1);
        editOurThetaNorth->setFocusPolicy(Qt::ClickFocus);
        editOurThetaNorth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(editOurThetaNorth, 4, 1, 1, 1);

        label_21 = new QLabel(layoutWidget_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 5, 0, 1, 1);

        editOurDelay = new QLineEdit(layoutWidget_2);
        editOurDelay->setObjectName(QString::fromUtf8("editOurDelay"));
        editOurDelay->setMinimumSize(QSize(120, 0));
        editOurDelay->setMaximumSize(QSize(120, 16777215));
        editOurDelay->setFont(font1);
        editOurDelay->setFocusPolicy(Qt::ClickFocus);
        editOurDelay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(editOurDelay, 5, 1, 1, 1);

        groupBox_3 = new QGroupBox(tabStart);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 300, 630, 111));
        QFont font2;
        font2.setPointSize(12);
        groupBox_3->setFont(font2);
        layoutWidget_3 = new QWidget(groupBox_3);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 611, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnSave = new QCheckBox(layoutWidget_3);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        btnSave->setFont(font3);
        btnSave->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(btnSave);

        browse = new QPushButton(layoutWidget_3);
        browse->setObjectName(QString::fromUtf8("browse"));
        browse->setEnabled(false);
        browse->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(browse);

        showPath = new QLabel(layoutWidget_3);
        showPath->setObjectName(QString::fromUtf8("showPath"));
        showPath->setMinimumSize(QSize(0, 0));
        showPath->setFont(font3);

        horizontalLayout->addWidget(showPath);

        layoutWidget_4 = new QWidget(groupBox_3);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 70, 452, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font3);

        horizontalLayout_2->addWidget(label_2);

        editInitDist = new QLineEdit(layoutWidget_4);
        editInitDist->setObjectName(QString::fromUtf8("editInitDist"));
        editInitDist->setMinimumSize(QSize(120, 0));
        editInitDist->setMaximumSize(QSize(120, 16777215));
        editInitDist->setFont(font1);
        editInitDist->setFocusPolicy(Qt::ClickFocus);
        editInitDist->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(editInitDist);

        groupBox_4 = new QGroupBox(tabStart);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(400, 30, 230, 261));
        groupBox_4->setFont(font);
        layoutWidget_5 = new QWidget(groupBox_4);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 15, 212, 151));
        gridLayout_3 = new QGridLayout(layoutWidget_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(10);
        gridLayout_3->setVerticalSpacing(20);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_47 = new QLabel(layoutWidget_5);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_3->addWidget(label_47, 0, 0, 1, 1);

        editCameraAngle = new QLineEdit(layoutWidget_5);
        editCameraAngle->setObjectName(QString::fromUtf8("editCameraAngle"));
        editCameraAngle->setMinimumSize(QSize(120, 0));
        editCameraAngle->setMaximumSize(QSize(120, 16777215));
        editCameraAngle->setFont(font1);
        editCameraAngle->setFocusPolicy(Qt::ClickFocus);
        editCameraAngle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(editCameraAngle, 0, 1, 1, 1);

        label_46 = new QLabel(layoutWidget_5);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_3->addWidget(label_46, 1, 0, 1, 1);

        editResolution = new QLineEdit(layoutWidget_5);
        editResolution->setObjectName(QString::fromUtf8("editResolution"));
        editResolution->setEnabled(false);
        editResolution->setMinimumSize(QSize(120, 0));
        editResolution->setMaximumSize(QSize(120, 16777215));
        editResolution->setFont(font1);
        editResolution->setFocusPolicy(Qt::ClickFocus);
        editResolution->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(editResolution, 1, 1, 1, 1);

        label_51 = new QLabel(layoutWidget_5);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_3->addWidget(label_51, 2, 0, 1, 1);

        editBlindRate = new QLineEdit(layoutWidget_5);
        editBlindRate->setObjectName(QString::fromUtf8("editBlindRate"));
        editBlindRate->setMinimumSize(QSize(120, 0));
        editBlindRate->setMaximumSize(QSize(120, 16777215));
        editBlindRate->setFont(font1);
        editBlindRate->setFocusPolicy(Qt::ClickFocus);
        editBlindRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(editBlindRate, 2, 1, 1, 1);

        label_52 = new QLabel(layoutWidget_5);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_3->addWidget(label_52, 3, 0, 1, 1);

        editUpdateRate = new QLineEdit(layoutWidget_5);
        editUpdateRate->setObjectName(QString::fromUtf8("editUpdateRate"));
        editUpdateRate->setMinimumSize(QSize(120, 0));
        editUpdateRate->setMaximumSize(QSize(120, 16777215));
        editUpdateRate->setFont(font1);
        editUpdateRate->setFocusPolicy(Qt::ClickFocus);
        editUpdateRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(editUpdateRate, 3, 1, 1, 1);

        begin = new QPushButton(tabStart);
        begin->setObjectName(QString::fromUtf8("begin"));
        begin->setGeometry(QRect(260, 420, 101, 31));
        begin->setFont(font2);
        begin->setAutoDefault(true);
        begin->setDefault(true);
        begin->setFlat(false);
        listPreset = new QListView(tabStart);
        listPreset->setObjectName(QString::fromUtf8("listPreset"));
        listPreset->setGeometry(QRect(630, 0, 212, 438));
        listPreset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        listPreset->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listPreset->setProperty("showDropIndicator", QVariant(false));
        listPreset->setDefaultDropAction(Qt::IgnoreAction);
        listPreset->setAlternatingRowColors(true);
        listPreset->setSelectionMode(QAbstractItemView::SingleSelection);
        listPreset->setSelectionBehavior(QAbstractItemView::SelectRows);
        listPreset->setIconSize(QSize(26, 26));
        listPreset->setLayoutMode(QListView::SinglePass);
        listPreset->setSpacing(5);
        listPreset->setGridSize(QSize(0, 38));
        listPreset->setViewMode(QListView::ListMode);
        listPreset->setWordWrap(false);
        btnAddPreset = new QToolButton(tabStart);
        btnAddPreset->setObjectName(QString::fromUtf8("btnAddPreset"));
        btnAddPreset->setGeometry(QRect(630, 438, 106, 23));
        QFont font4;
        font4.setPointSize(14);
        btnAddPreset->setFont(font4);
        btnDelPreset = new QToolButton(tabStart);
        btnDelPreset->setObjectName(QString::fromUtf8("btnDelPreset"));
        btnDelPreset->setGeometry(QRect(736, 438, 106, 23));
        btnDelPreset->setFont(font4);
        label_3 = new QLabel(tabStart);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 12, 201, 16));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 203, 190);"));
        label_4 = new QLabel(tabStart);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(200, 12, 201, 16));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 255);"));
        label_5 = new QLabel(tabStart);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(400, 12, 231, 16));
        label_5->setStyleSheet(QString::fromUtf8(""));
        tabWidget->addTab(tabStart, QString());
        tabMissile = new QWidget();
        tabMissile->setObjectName(QString::fromUtf8("tabMissile"));
        horizontalLayout_7 = new QHBoxLayout(tabMissile);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_15 = new QLabel(tabMissile);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);

        horizontalLayout_4->addWidget(label_15);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        btnAddEnemy = new QToolButton(tabMissile);
        btnAddEnemy->setObjectName(QString::fromUtf8("btnAddEnemy"));
        btnAddEnemy->setMinimumSize(QSize(22, 22));
        btnAddEnemy->setMaximumSize(QSize(22, 22));
        btnAddEnemy->setFont(font4);

        horizontalLayout_4->addWidget(btnAddEnemy);

        btnDelEnemy = new QToolButton(tabMissile);
        btnDelEnemy->setObjectName(QString::fromUtf8("btnDelEnemy"));
        btnDelEnemy->setMinimumSize(QSize(22, 22));
        btnDelEnemy->setMaximumSize(QSize(22, 22));
        btnDelEnemy->setFont(font4);
        btnDelEnemy->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnDelEnemy->setAutoRaise(false);

        horizontalLayout_4->addWidget(btnDelEnemy);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tableEnemy = new QTableView(tabMissile);
        tableEnemy->setObjectName(QString::fromUtf8("tableEnemy"));
        tableEnemy->setFocusPolicy(Qt::ClickFocus);
        tableEnemy->setContextMenuPolicy(Qt::DefaultContextMenu);
        tableEnemy->setDefaultDropAction(Qt::IgnoreAction);
        tableEnemy->setAlternatingRowColors(true);
        tableEnemy->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableEnemy->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableEnemy->setTextElideMode(Qt::ElideNone);
        tableEnemy->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableEnemy->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableEnemy->setShowGrid(false);
        tableEnemy->setWordWrap(false);
        tableEnemy->setCornerButtonEnabled(false);
        tableEnemy->horizontalHeader()->setDefaultSectionSize(90);
        tableEnemy->horizontalHeader()->setHighlightSections(false);
        tableEnemy->horizontalHeader()->setStretchLastSection(true);
        tableEnemy->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableEnemy);


        horizontalLayout_7->addLayout(verticalLayout_2);

        horizontalSpacer_7 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_20 = new QLabel(tabMissile);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font);

        horizontalLayout_5->addWidget(label_20);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnAddOur = new QToolButton(tabMissile);
        btnAddOur->setObjectName(QString::fromUtf8("btnAddOur"));
        btnAddOur->setMinimumSize(QSize(22, 22));
        btnAddOur->setMaximumSize(QSize(22, 22));
        btnAddOur->setFont(font4);

        horizontalLayout_5->addWidget(btnAddOur);

        btnDelOur = new QToolButton(tabMissile);
        btnDelOur->setObjectName(QString::fromUtf8("btnDelOur"));
        btnDelOur->setMinimumSize(QSize(22, 22));
        btnDelOur->setMaximumSize(QSize(22, 22));
        btnDelOur->setFont(font4);

        horizontalLayout_5->addWidget(btnDelOur);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_5);

        tableOur = new QTableView(tabMissile);
        tableOur->setObjectName(QString::fromUtf8("tableOur"));
        tableOur->setFocusPolicy(Qt::ClickFocus);
        tableOur->setAlternatingRowColors(true);
        tableOur->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableOur->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableOur->setTextElideMode(Qt::ElideNone);
        tableOur->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableOur->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableOur->setShowGrid(false);
        tableOur->horizontalHeader()->setDefaultSectionSize(85);
        tableOur->horizontalHeader()->setHighlightSections(false);
        tableOur->horizontalHeader()->setStretchLastSection(true);
        tableOur->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(tableOur);


        horizontalLayout_7->addLayout(verticalLayout_5);

        tabWidget->addTab(tabMissile, QString());
        tabAddr = new QWidget();
        tabAddr->setObjectName(QString::fromUtf8("tabAddr"));
        verticalLayout_4 = new QVBoxLayout(tabAddr);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_24 = new QLabel(tabAddr);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font);

        horizontalLayout_6->addWidget(label_24);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        btnAddLoc = new QToolButton(tabAddr);
        btnAddLoc->setObjectName(QString::fromUtf8("btnAddLoc"));
        btnAddLoc->setMinimumSize(QSize(22, 22));
        btnAddLoc->setMaximumSize(QSize(22, 22));
        btnAddLoc->setFont(font4);

        horizontalLayout_6->addWidget(btnAddLoc);

        btnDelLoc = new QToolButton(tabAddr);
        btnDelLoc->setObjectName(QString::fromUtf8("btnDelLoc"));
        btnDelLoc->setMinimumSize(QSize(22, 22));
        btnDelLoc->setMaximumSize(QSize(22, 22));
        btnDelLoc->setFont(font4);

        horizontalLayout_6->addWidget(btnDelLoc);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_6);

        tableLoc = new QTableView(tabAddr);
        tableLoc->setObjectName(QString::fromUtf8("tableLoc"));
        tableLoc->setAlternatingRowColors(true);
        tableLoc->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableLoc->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableLoc->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableLoc->setShowGrid(false);
        tableLoc->setWordWrap(false);
        tableLoc->setCornerButtonEnabled(false);
        tableLoc->horizontalHeader()->setHighlightSections(false);
        tableLoc->horizontalHeader()->setStretchLastSection(true);
        tableLoc->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(tableLoc);

        tabWidget->addTab(tabAddr, QString());

        horizontalLayout_3->addWidget(tabWidget);


        retranslateUi(parameters);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(parameters);
    } // setupUi

    void retranslateUi(QWidget *parameters)
    {
        parameters->setWindowTitle(QApplication::translate("parameters", "\344\273\277\347\234\237\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        label_12->setText(QApplication::translate("parameters", "\351\253\230\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("parameters", "\345\257\274\345\274\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("parameters", "\345\234\260\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("parameters", "\344\273\260\350\247\222\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editEnemyThetaEarth->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\345\210\232\350\277\233\345\205\245\344\270\255\346\256\265\351\243\236\350\241\214\346\227\266\347\233\270\345\257\271\345\234\260\345\271\263\351\235\242\347\232\204\344\273\260\350\247\222</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editEnemyThetaEarth->setPlaceholderText(QApplication::translate("parameters", "\345\272\246", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editEnemyThetaNorth->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\345\210\232\350\277\233\344\270\255\346\256\265\351\243\236\350\241\214\346\227\266\344\270\216\346\255\243\345\214\227\347\232\204\345\201\217\350\247\222</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editEnemyThetaNorth->setPlaceholderText(QApplication::translate("parameters", "\345\272\246", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("parameters", "\345\201\217\350\247\222\357\274\232", 0, QApplication::UnicodeUTF8));
        editEnemyAlt->setPlaceholderText(QApplication::translate("parameters", "\345\215\203\347\261\263", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label_14->setText(QApplication::translate("parameters", "\345\234\260\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("parameters", "\351\253\230\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        editOurAlt->setPlaceholderText(QApplication::translate("parameters", "\345\215\203\347\261\263", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("parameters", "\345\257\274\345\274\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("parameters", "\344\273\260\350\247\222\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editOurThetaEarth->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\345\210\232\350\277\233\345\205\245\344\270\255\346\256\265\351\243\236\350\241\214\346\227\266\347\233\270\345\257\271\345\234\260\345\271\263\351\235\242\347\232\204\344\273\260\350\247\222</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editOurThetaEarth->setPlaceholderText(QApplication::translate("parameters", "\345\272\246", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("parameters", "\345\201\217\350\247\222\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editOurThetaNorth->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\345\210\232\350\277\233\344\270\255\346\256\265\351\243\236\350\241\214\346\227\266\344\270\216\346\255\243\345\214\227\347\232\204\345\201\217\350\247\222</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editOurThetaNorth->setPlaceholderText(QApplication::translate("parameters", "\345\272\246", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("parameters", "\345\273\266\350\277\237\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editOurDelay->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\346\225\214\346\226\271\345\257\274\345\274\271\350\277\233\345\205\245\344\270\255\346\256\265\351\243\236\350\241\214\345\220\216\345\273\266\350\277\237\345\244\232\344\271\205\346\210\221\346\224\276\345\257\274\345\274\271\346\211\215\350\277\233\345\205\245\344\270\255\346\256\265\351\243\236\350\241\214</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editOurDelay->setPlaceholderText(QApplication::translate("parameters", "\347\247\222", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("parameters", "\345\205\266\345\256\203", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("parameters", "\344\277\235\345\255\230\344\273\277\347\234\237\345\233\276\345\203\217", 0, QApplication::UnicodeUTF8));
        browse->setText(QApplication::translate("parameters", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        showPath->setText(QString());
        label_2->setText(QApplication::translate("parameters", "\345\275\223\344\270\244\346\236\232\345\257\274\345\274\271\346\216\245\350\277\221\345\210\260\345\244\232\345\260\221\350\267\235\347\246\273\345\220\216\345\274\200\345\247\213\347\272\242\345\244\226\345\210\266\345\257\274\357\274\237", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editInitDist->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\350\276\223\345\205\2450\345\210\231\344\273\216\345\244\264\345\274\200\345\247\213\344\273\277\347\234\237</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editInitDist->setPlaceholderText(QApplication::translate("parameters", "\345\215\203\347\261\263", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        label_47->setText(QApplication::translate("parameters", "\350\247\206\345\234\272\350\247\222\357\274\232", 0, QApplication::UnicodeUTF8));
        editCameraAngle->setPlaceholderText(QApplication::translate("parameters", "\345\272\246", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("parameters", "\345\210\206\350\276\250\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editResolution->setToolTip(QApplication::translate("parameters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">\350\247\206\345\217\243\345\247\213\347\273\210\344\270\272\346\255\243\346\226\271\345\275\242\357\274\214\345\217\252\351\234\200\350\276\223\345\205\245\344\270\200\346\235\241\350\276\271\344\270\212\347\232\204\345\203\217\347\264\240\346\225\260</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editResolution->setPlaceholderText(QApplication::translate("parameters", "\345\203\217\347\264\240", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("parameters", "\347\233\262\345\205\203\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        editBlindRate->setPlaceholderText(QApplication::translate("parameters", "%", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("parameters", "\346\210\220\345\203\217\351\200\237\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        editUpdateRate->setPlaceholderText(QApplication::translate("parameters", "\346\210\220\345\203\217\346\225\260/\347\247\222", 0, QApplication::UnicodeUTF8));
        begin->setText(QApplication::translate("parameters", "\345\274\200\345\247\213\344\273\277\347\234\237", 0, QApplication::UnicodeUTF8));
        btnAddPreset->setText(QApplication::translate("parameters", "+", 0, QApplication::UnicodeUTF8));
        btnDelPreset->setText(QApplication::translate("parameters", "-", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("parameters", "\345\274\271\351\201\223\345\257\274\345\274\271", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("parameters", "\346\213\246\346\210\252\345\274\271", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("parameters", "\347\272\242\345\244\226\346\216\242\346\265\213\345\231\250", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabStart), QApplication::translate("parameters", "\345\274\200\345\247\213\344\273\277\347\234\237", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("parameters", "\345\274\271\351\201\223\345\257\274\345\274\271\357\274\232", 0, QApplication::UnicodeUTF8));
        btnAddEnemy->setText(QApplication::translate("parameters", "+", 0, QApplication::UnicodeUTF8));
        btnDelEnemy->setText(QApplication::translate("parameters", "-", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("parameters", "\346\213\246\346\210\252\345\257\274\345\274\271\357\274\232", 0, QApplication::UnicodeUTF8));
        btnAddOur->setText(QApplication::translate("parameters", "+", 0, QApplication::UnicodeUTF8));
        btnDelOur->setText(QApplication::translate("parameters", "-", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMissile), QApplication::translate("parameters", "\345\257\274\345\274\271\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("parameters", "\345\234\260\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        btnAddLoc->setText(QApplication::translate("parameters", "+", 0, QApplication::UnicodeUTF8));
        btnDelLoc->setText(QApplication::translate("parameters", "-", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabAddr), QApplication::translate("parameters", "\345\234\260\347\202\271\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class parameters: public Ui_parameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERS_H
