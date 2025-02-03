#pragma once

#include <QMainWindow>
#include "ui_test2.h"

class test2 : public QMainWindow
{
	Q_OBJECT

public:
	test2(QWidget *parent = Q_NULLPTR);
	~test2();

private:
	Ui::test2 ui;
};
