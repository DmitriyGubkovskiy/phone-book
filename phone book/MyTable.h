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
#include <QMenu>
#include <QMenuBar>
#include <iostream>
#include <fstream>
#include <string>

class MyTable: public QWidget
{
	Q_OBJECT
private:
	std::vector<std::vector<QTableWidgetItem*>> newItemvect;
	std::vector<QTableWidgetItem*> tmd;
	std::vector<std::vector<QString>>* data;

	QPushButton* changebut;
	QPushButton* openbut;
	QPushButton* delbut;
	QPushButton* sortbut;
	QPushButton* searchbut;
	QTableWidget* tab;
	QLabel* lab;
	QLineEdit* line;
	QMenu* fileMenu;
	QMenuBar* mnubar;
	QAction* saveaction;
	QAction* openaction;

	void settab();
	void cleardata();
public:
	MyTable(std::vector<std::vector<QString>>* data);
	~MyTable();
private slots:
	void deleteitem();
	void changeitem();
	void sortitems();
	void searchitem();
	void openfile();
	void savefile();
signals:
	void change(int id);
};

