/********************************************************************************
** Form generated from reading UI file 'infraredsimulator.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFRAREDSIMULATOR_H
#define UI_INFRAREDSIMULATOR_H

#include <PSDFViewQt/PSDFViewQt.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfraredSimulatorClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    ViewerQt3D *infraredView;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *back;
    QPushButton *go;
    QPushButton *speed;
    QSpacerItem *horizontalSpacer;
    QPushButton *parameter;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *timeLabel;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLabel *distLabel;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    ViewerQt3D *mainView;

    void setupUi(QMainWindow *InfraredSimulatorClass)
    {
        if (InfraredSimulatorClass->objectName().isEmpty())
            InfraredSimulatorClass->setObjectName(QString::fromUtf8("InfraredSimulatorClass"));
        InfraredSimulatorClass->resize(1381, 651);
        InfraredSimulatorClass->setMinimumSize(QSize(1024, 618));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/InfraredSimulator/resource/peace.png"), QSize(), QIcon::Normal, QIcon::Off);
        InfraredSimulatorClass->setWindowIcon(icon);
        centralWidget = new QWidget(InfraredSimulatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_5 = new QHBoxLayout(centralWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        infraredView = new ViewerQt3D(centralWidget);
        infraredView->setObjectName(QString::fromUtf8("infraredView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infraredView->sizePolicy().hasHeightForWidth());
        infraredView->setSizePolicy(sizePolicy);
        infraredView->setMinimumSize(QSize(512, 512));
        infraredView->setMaximumSize(QSize(512, 512));

        verticalLayout->addWidget(infraredView);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(512, 100));
        frame->setMaximumSize(QSize(512, 10000));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);
        frame->setMidLineWidth(1);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        back = new QPushButton(frame);
        back->setObjectName(QString::fromUtf8("back"));
        back->setEnabled(false);
        back->setMinimumSize(QSize(0, 20));
        back->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/back.png);"));

        horizontalLayout->addWidget(back);

        go = new QPushButton(frame);
        go->setObjectName(QString::fromUtf8("go"));
        go->setEnabled(false);
        go->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setKerning(false);
        go->setFont(font);
        go->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/do.png);"));

        horizontalLayout->addWidget(go);

        speed = new QPushButton(frame);
        speed->setObjectName(QString::fromUtf8("speed"));
        speed->setEnabled(false);
        speed->setMinimumSize(QSize(0, 20));
        speed->setStyleSheet(QString::fromUtf8("border-image: url(:/InfraredSimulator/resource/speed.png);"));

        horizontalLayout->addWidget(speed);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        parameter = new QPushButton(frame);
        parameter->setObjectName(QString::fromUtf8("parameter"));
        parameter->setMinimumSize(QSize(30, 30));
        parameter->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font1.setPointSize(12);
        parameter->setFont(font1);
        parameter->setFlat(false);

        horizontalLayout_2->addWidget(parameter);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout_3->addWidget(label);

        timeLabel = new QLabel(frame);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setFont(font1);

        horizontalLayout_3->addWidget(timeLabel);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_3->addWidget(label_2);

        distLabel = new QLabel(frame);
        distLabel->setObjectName(QString::fromUtf8("distLabel"));
        distLabel->setFont(font1);

        horizontalLayout_3->addWidget(distLabel);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout);

        mainView = new ViewerQt3D(centralWidget);
        mainView->setObjectName(QString::fromUtf8("mainView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(mainView->sizePolicy().hasHeightForWidth());
        mainView->setSizePolicy(sizePolicy1);
        mainView->setMinimumSize(QSize(618, 618));
        mainView->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(mainView);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        InfraredSimulatorClass->setCentralWidget(centralWidget);

        retranslateUi(InfraredSimulatorClass);

        QMetaObject::connectSlotsByName(InfraredSimulatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *InfraredSimulatorClass)
    {
        InfraredSimulatorClass->setWindowTitle(QApplication::translate("InfraredSimulatorClass", "InfraredSimulator", 0, QApplication::UnicodeUTF8));
        back->setText(QString());
        go->setText(QString());
        speed->setText(QString());
        parameter->setText(QString());
        label->setText(QApplication::translate("InfraredSimulatorClass", "\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("InfraredSimulatorClass", "00.00", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("InfraredSimulatorClass", "s", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InfraredSimulatorClass", "\350\267\235\347\246\273\357\274\232", 0, QApplication::UnicodeUTF8));
        distLabel->setText(QApplication::translate("InfraredSimulatorClass", "0.0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("InfraredSimulatorClass", "km", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InfraredSimulatorClass: public Ui_InfraredSimulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFRAREDSIMULATOR_H
