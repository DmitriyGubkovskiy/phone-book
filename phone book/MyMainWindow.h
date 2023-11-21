#pragma once
#include <QtDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QLabel> 
#include <QLineEdit> 
#include <QErrorMessage> 
#include <QRegExp> 
#include <QDateEdit> 
#include <vector> 
#include <QTableWidget>
#include "MyTable.h"

class MyMainWindow: public QMainWindow
{
	Q_OBJECT

private:

	QPushButton* save;
	QPushButton* open_database;
	QDateEdit* birthdate;

	std::vector<QLabel*> vec_label;
	std::vector<QLineEdit*> vec_lineedit;

	std::vector<std::vector<QString>> data;

	MyTable* table;
	int delind = 0;
	bool check();
	void normalize();
public:
	MyMainWindow();
	std::vector<std::vector<QString>>* getdata();
private slots:
	void save_date();
	void open_data_file();
	void change_data(int id);


};

