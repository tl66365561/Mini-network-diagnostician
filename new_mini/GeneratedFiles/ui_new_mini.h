/********************************************************************************
** Form generated from reading UI file 'new_mini.ui'
**
** Created: Wed Dec 11 18:22:11 2019
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_MINI_H
#define UI_NEW_MINI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_new_miniClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *new_miniClass)
    {
        if (new_miniClass->objectName().isEmpty())
            new_miniClass->setObjectName(QString::fromUtf8("new_miniClass"));
        new_miniClass->resize(600, 400);
        menuBar = new QMenuBar(new_miniClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        new_miniClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(new_miniClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        new_miniClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(new_miniClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        new_miniClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(new_miniClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        new_miniClass->setStatusBar(statusBar);

        retranslateUi(new_miniClass);

        QMetaObject::connectSlotsByName(new_miniClass);
    } // setupUi

    void retranslateUi(QMainWindow *new_miniClass)
    {
        new_miniClass->setWindowTitle(QApplication::translate("new_miniClass", "new_mini", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class new_miniClass: public Ui_new_miniClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_MINI_H
