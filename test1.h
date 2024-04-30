#pragma once

#include <QWidget>
#include "ui_test1.h"

class test1 : public QWidget
{
	Q_OBJECT

public:
	test1(QWidget *parent = Q_NULLPTR);
	~test1();

private:
	Ui::test1 ui;
};
