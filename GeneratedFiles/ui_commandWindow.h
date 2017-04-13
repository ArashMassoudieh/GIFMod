/********************************************************************************
** Form generated from reading UI file 'commandWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDWINDOW_H
#define UI_COMMANDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include "commandlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_commandWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *back;
    QPushButton *forward;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *save;
    QTextEdit *textEdit;
    commandLineEdit *lineEdit;

    void setupUi(QDialog *commandWindow)
    {
        if (commandWindow->objectName().isEmpty())
            commandWindow->setObjectName(QStringLiteral("commandWindow"));
        commandWindow->resize(617, 459);
        commandWindow->setWindowOpacity(1);
        commandWindow->setLayoutDirection(Qt::LeftToRight);
        commandWindow->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(commandWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        back = new QPushButton(commandWindow);
        back->setObjectName(QStringLiteral("back"));

        horizontalLayout->addWidget(back);

        forward = new QPushButton(commandWindow);
        forward->setObjectName(QStringLiteral("forward"));

        horizontalLayout->addWidget(forward);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        save = new QPushButton(commandWindow);
        save->setObjectName(QStringLiteral("save"));

        horizontalLayout->addWidget(save);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(commandWindow);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        lineEdit = new commandLineEdit(commandWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);


        retranslateUi(commandWindow);

        QMetaObject::connectSlotsByName(commandWindow);
    } // setupUi

    void retranslateUi(QDialog *commandWindow)
    {
        commandWindow->setWindowTitle(QApplication::translate("commandWindow", "Command interpreter", 0));
        back->setText(QApplication::translate("commandWindow", "<", 0));
        forward->setText(QApplication::translate("commandWindow", ">", 0));
        save->setText(QApplication::translate("commandWindow", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class commandWindow: public Ui_commandWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDWINDOW_H
