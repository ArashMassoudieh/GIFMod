/********************************************************************************
** Form generated from reading UI file 'imageviewer_window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWER_WINDOW_H
#define UI_IMAGEVIEWER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageviewer_window
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *imageviewer_window)
    {
        if (imageviewer_window->objectName().isEmpty())
            imageviewer_window->setObjectName(QStringLiteral("imageviewer_window"));
        imageviewer_window->resize(852, 476);
        verticalLayout = new QVBoxLayout(imageviewer_window);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(imageviewer_window);

        QMetaObject::connectSlotsByName(imageviewer_window);
    } // setupUi

    void retranslateUi(QWidget *imageviewer_window)
    {
        imageviewer_window->setWindowTitle(QApplication::translate("imageviewer_window", "imageviewer_window", 0));
    } // retranslateUi

};

namespace Ui {
    class imageviewer_window: public Ui_imageviewer_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_WINDOW_H
