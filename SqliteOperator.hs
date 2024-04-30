#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>


class SqliteOperator 
{

private:

	int i = 0;

public:
	SqliteOperator();
	~SqliteOperator();
	void CreatDb();
	bool OpenDb();
	void CloseDb();
	void CreateTable();
	void QueryAllData();

	//void InsertData();
	//void InsertData(char* instrumentid, char* orderref, char direction, double limitprice);

};



#endif 
#pragma once