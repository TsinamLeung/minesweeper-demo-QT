/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widget_stage.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEasy;
    QAction *actionMiddle;
    QAction *actionHard;
    QAction *actionCustom;
    QAction *actionQuit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *timer;
    QPushButton *pushButton;
    QLCDNumber *counter;
    WidgetStage *stage;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QMenu *menuLevel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(514, 546);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(514, 546));
        MainWindow->setAnimated(true);
        actionEasy = new QAction(MainWindow);
        actionEasy->setObjectName(QString::fromUtf8("actionEasy"));
        actionMiddle = new QAction(MainWindow);
        actionMiddle->setObjectName(QString::fromUtf8("actionMiddle"));
        actionHard = new QAction(MainWindow);
        actionHard->setObjectName(QString::fromUtf8("actionHard"));
        actionCustom = new QAction(MainWindow);
        actionCustom->setObjectName(QString::fromUtf8("actionCustom"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 10, 3, 10);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 5);
        timer = new QLCDNumber(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(timer->sizePolicy().hasHeightForWidth());
        timer->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("Lucida Sans"));
        timer->setFont(font);

        horizontalLayout->addWidget(timer);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setFont(font);
        pushButton->setCheckable(false);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        counter = new QLCDNumber(centralwidget);
        counter->setObjectName(QString::fromUtf8("counter"));
        sizePolicy2.setHeightForWidth(counter->sizePolicy().hasHeightForWidth());
        counter->setSizePolicy(sizePolicy2);
        counter->setFont(font);

        horizontalLayout->addWidget(counter);


        verticalLayout->addLayout(horizontalLayout);

        stage = new WidgetStage(centralwidget);
        stage->setObjectName(QString::fromUtf8("stage"));
        sizePolicy2.setHeightForWidth(stage->sizePolicy().hasHeightForWidth());
        stage->setSizePolicy(sizePolicy2);
        stage->setMinimumSize(QSize(0, 450));
        stage->setMouseTracking(true);
        stage->setTabletTracking(false);
        stage->setFrameShape(QFrame::Box);
        stage->setFrameShadow(QFrame::Plain);
        stage->setLineWidth(2);

        verticalLayout->addWidget(stage);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 514, 21));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuLevel = new QMenu(menuOptions);
        menuLevel->setObjectName(QString::fromUtf8("menuLevel"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(menuLevel->menuAction());
        menuOptions->addAction(actionQuit);
        menuLevel->addSeparator();
        menuLevel->addAction(actionEasy);
        menuLevel->addSeparator();
        menuLevel->addAction(actionMiddle);
        menuLevel->addAction(actionHard);
        menuLevel->addAction(actionCustom);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionEasy, SIGNAL(triggered()), stage, SLOT(SetDifficult()));
        QObject::connect(actionMiddle, SIGNAL(triggered()), stage, SLOT(SetDifficult()));
        QObject::connect(actionHard, SIGNAL(triggered()), stage, SLOT(SetDifficult()));

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HelloSweeper", nullptr));
        actionEasy->setText(QApplication::translate("MainWindow", "Easy", nullptr));
        actionMiddle->setText(QApplication::translate("MainWindow", "Middle", nullptr));
        actionHard->setText(QApplication::translate("MainWindow", "Hard", nullptr));
        actionCustom->setText(QApplication::translate("MainWindow", "Custom", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Reset and Status Displaying", nullptr));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
        menuLevel->setTitle(QApplication::translate("MainWindow", "Level", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
