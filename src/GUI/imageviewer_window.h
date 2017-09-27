#pragma once

#include <QWidget>
#include "ui_imageviewer_window.h"

class imageviewer_window : public QWidget
{
	Q_OBJECT

public:
	imageviewer_window(QWidget *parent = Q_NULLPTR);
	~imageviewer_window();

private:
	Ui::imageviewer_window ui;
};
