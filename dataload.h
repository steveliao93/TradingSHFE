#pragma once

#include <QDialog>
#include "ui_dataload.h"

class dataload : public QDialog
{
	Q_OBJECT

public:
	dataload(QWidget *parent = Q_NULLPTR);
	~dataload();

private:
	Ui::dataload ui;
};
