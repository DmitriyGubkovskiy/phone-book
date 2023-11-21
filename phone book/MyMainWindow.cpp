#include "MyMainWindow.h"
#include <iostream>



MyMainWindow::MyMainWindow()
{
	this->resize(800, 700);
	this->setMinimumSize(QSize(800, 700));
	this->setMaximumSize(QSize(800, 700));

	save = new QPushButton(this);
	open_database = new QPushButton(this);

	save->setText("Save data");
	save->setGeometry(QRect(550, 600, 200, 50));

	open_database->setText("Open database");
	open_database->setGeometry(QRect(50, 600, 200, 50));

	connect(save, SIGNAL(clicked()), this,
		SLOT(save_date()));
	connect(open_database, SIGNAL(clicked()), this,
		SLOT(open_data_file()));

	birthdate = new QDateEdit(this);
	birthdate->setGeometry(QRect(200, 500, 500, 50));
	birthdate->setCalendarPopup(true);
	birthdate->setDate(QDate::currentDate());
	birthdate->setMaximumDate(QDate::currentDate());

	


	for (int i = 0; i < 7; i++)
	{
		QLabel* label = new QLabel(this);
		vec_label.push_back(label);
		vec_label[i]->setGeometry(QRect(20, 50+75*i, 200, 50));
		if (i != 6)
		{
			QLineEdit* line = new QLineEdit(this);
			vec_lineedit.push_back(line);
			vec_lineedit[i]->setGeometry(QRect(200, 50 + 75 * i, 500, 50));
		}
		switch (i)
		{
		case 0:
			vec_label[i]->setText("Name: ");
			vec_lineedit[i]->setPlaceholderText("Enter your name");
			break;
		case 1:
			vec_label[i]->setText("Surname: ");
			vec_lineedit[i]->setPlaceholderText("Enter your surname");
			break;
		case 2:
			vec_label[i]->setText("Patronymic: ");
			vec_lineedit[i]->setPlaceholderText("Enter your patronymic");
			break;
		case 3:
			vec_label[i]->setText("Address: ");
			vec_lineedit[i]->setPlaceholderText("Enter your address");
			break;
			break;
		case 4:
			vec_label[i]->setText("Email: ");
			vec_lineedit[i]->setPlaceholderText("Enter your email");
			break;
		case 5:
			vec_label[i]->setText("Phone number: ");
			vec_lineedit[i]->setPlaceholderText("Enter your phone number");
			vec_lineedit[i]->setInputMask("+7(999)-999-99-99");
			break;
		case 6:
			vec_label[i]->setText("Birth date: ");
		default:
			break;
		}
	}

}
std::vector<std::vector<QString>>* MyMainWindow::getdata()
{
	return &(this->data);
}

void MyMainWindow::save_date() 
{
	if (!check()) 
	{
		return;
	}
	std::vector<QString> v;
	for (int i = 0; i < vec_lineedit.size(); i++)
	{
		
		if (i == 4) 
		{
			auto s = vec_lineedit[i]->text();
			s.trimmed();
			s.replace(" @ ", "@");
			v.push_back(s);
		}
		else
		{
			v.push_back(vec_lineedit[i]->text().trimmed());
		}
	}
	if (delind != 0)
	{
		data.erase(data.begin() + delind);
	}
	delind = 0;
	v.push_back(birthdate->date().toString(Qt::ISODate));
	data.push_back(v);
	v.clear();
	normalize();
	
}

void MyMainWindow::open_data_file()
{
	table = new MyTable(&this->data);
	connect(table, SIGNAL(change(int)), this,
		SLOT(change_data(int)));
}

void MyMainWindow::change_data(int id)
{
	for (int i = 0; i < 6; i++)
	{
		vec_lineedit[i]->setText(data[id][i]);
	}
	
	QString year(data[id][vec_lineedit.size()]);
	QString month(data[id][vec_lineedit.size()]);
	QString day(data[id][vec_lineedit.size()]);
	day.remove(0, 8);
	month.remove(0, 5);
	month.remove(2, 3);
	year.remove(4,6);
	birthdate->setDate(QDate(
		year.toInt(),
		month.toInt(),
		day.toInt()));
	delind = id;
	this->update();
	delete table;
}


bool MyMainWindow::check()
{
	if ((!(vec_lineedit[0]->text()[0].isLetter()) && 
		vec_lineedit[0]->text()[0] != ' ') ||
		vec_lineedit[0]->text().size() == 0)
	{
		(new QErrorMessage(this))->showMessage("Name entry error");
		return false;
	}
	if ((!(vec_lineedit[1]->text()[0].isLetter()) &&
		vec_lineedit[1]->text()[0] != ' ') ||
		vec_lineedit[1]->text().size() == 0)
	{
		(new QErrorMessage(this))->showMessage("Surname entry error");
		return false;
	}
	if ((!(vec_lineedit[1]->text()[0].isLetter()) &&
		vec_lineedit[1]->text()[0] != ' ') ||
		vec_lineedit[1]->text().size() == 0)
	{
		(new QErrorMessage(this))->showMessage("Patronymic entry error");
		return false;
	}
	if (vec_lineedit[3]->text().size() == 0)
	{
		(new QErrorMessage(this))->showMessage("Address entry error");
		return false;
	}
	if (!(birthdate->date().isValid()) || birthdate->date().isNull())
	{
		(new QErrorMessage(this))->showMessage("Patronymic entry error");
		return false;
	}
	QRegExp rx("[a-zA-Z0-9 ]{1}\\@[a-zA-Z0-9 ]{1}");
	if (vec_lineedit[4]->text().contains(rx) <= 0 )
	{
		(new QErrorMessage(this))->showMessage("Email entry error");
		return false;
	}
	if (vec_lineedit[5]->text().size() != 17)
	{
		(new QErrorMessage(this))->showMessage("Phone number entry error");
		return false;
	}
	return true;
	
}

void MyMainWindow::normalize()
{
	/*for (int i = 0; i < data.size(); i++)
	{
		for (int z = 0; z < data[0].size(); z++)
		{
			qDebug() << data[i][z];
		}
	}*/


	for (auto it : vec_lineedit)
	{
		it->clear();
	}
	birthdate->setDate(QDate::currentDate());
}


