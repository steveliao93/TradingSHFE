#pragma once

#include <QDialog>
#include "ui_test3.h"

class test3 : public QDialog
{
	Q_OBJECT

public:
	test3(QWidget *parent = Q_NULLPTR);
	~test3();

private:
	Ui::test3 ui;
};
