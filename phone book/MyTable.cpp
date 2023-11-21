#include "MyTable.h"


void MyTable::settab()
{
	newItemvect.clear();
	tab->setRowCount(this->data->size());
	tab->setColumnCount(7);
	tab->setHorizontalHeaderLabels(QStringList(
		QList<QString>{"Name", "Surname", "Patronymic", "Address", "Email",
		"Phone number", "Birth date"}));
	tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
	for (auto it1 : *this->data)
	{
		for (auto it2 : it1)
		{
			QTableWidgetItem* item = new QTableWidgetItem(it2);
			tab->setCurrentItem(item, QItemSelectionModel::Rows);
			tmd.push_back(item);
		}
		newItemvect.push_back(tmd);
		tmd.clear();
	}

	for (int i = 0; i < this->data->size(); i++)
	{

		for (int j = 0; j < 7; j++)
		{
			tab->setItem(i, j, newItemvect[i][j]);
		}
	}
	this->update();
}

void MyTable::cleardata()
{
	for (int i = 0; i < data->size(); i++)
	{

		for (int j = 0; j < (data)[0].size(); j++)
		{
			delete newItemvect[i][j];
		}
	}
}

MyTable::MyTable(std::vector<std::vector<QString>>* data)
{
	this->resize(1400, 1200);
	this->data = data;


	tab = new QTableWidget(this);
	tab->setGeometry(QRect(0, 100, 1400, 1130));


	delbut = new QPushButton(this);
	delbut->setGeometry(QRect(180, 40, 170, 50));
	delbut->setText("Delete item");

	changebut = new QPushButton(this);
	changebut->setGeometry(QRect(350, 40, 170, 50));
	changebut->setText("Change item");
	
	sortbut = new QPushButton(this);
	sortbut->setGeometry(QRect(10, 40, 170, 50));
	sortbut->setText("Sort items");

	searchbut = new QPushButton(this);
	searchbut->setGeometry(QRect(1200, 40, 170, 50));
	searchbut->setText("Search items");

	line = new QLineEdit(this);
	line->setGeometry(QRect(750, 40, 450, 50));
	line->setPlaceholderText("Enter the item index");

	lab = new QLabel(this);
	lab->setGeometry(QRect(620, 40, 130, 50));
	lab->setText("Item index: ");

	openaction = new QAction("Open file", this);
	saveaction = new QAction("Save file", this);

	fileMenu = new QMenu("File", this);
	fileMenu->addAction(openaction);
	fileMenu->addAction(saveaction);

	mnubar = new QMenuBar(this);
	mnubar->addMenu(fileMenu);


	connect(openaction, SIGNAL(triggered(bool)), this,
		SLOT(openfile()));

	connect(saveaction, SIGNAL(triggered(bool)), this,
		SLOT(savefile()));


	connect(delbut, SIGNAL(clicked()), this,
		SLOT(deleteitem()));

	connect(changebut, SIGNAL(clicked()), this,
		SLOT(changeitem()));

	connect(sortbut, SIGNAL(clicked()), this,
		SLOT(sortitems()));

	connect(searchbut, SIGNAL(clicked()), this,
		SLOT(searchitem()));

	settab();
	this->show();
}

MyTable::~MyTable()
{
	cleardata();
}

void MyTable::deleteitem()
{
	if (tab->currentRow() < 0) 
	{
		(new QErrorMessage(this))->showMessage("Delete item error");
		return;
	}
	data[0].erase(data[0].begin() + tab->currentRow());
	settab();
	return;
}
void MyTable::changeitem()
{
	if (tab->currentRow() < 0)
	{
		(new QErrorMessage(this))->showMessage("Change item error");
		return;
	}
	
	auto tmp = tab->currentItem();
	int id = -1;
	bool fl = 0;
	for (int i = 0; i < newItemvect.size(); i++)
	{
		for (int j = 0; j < newItemvect[i].size(); j++)
		{
			if (newItemvect[i][j] == tmp)
			{	
				id = i;
				fl = 1;
				break;
			}
		}
		if (fl) break;
	}
	if (id != -1)
	{
		emit change(id);
	}
}

void MyTable::sortitems()
{
	qDebug() << tab->currentColumn();
	if (tab->currentColumn() < 0)
	{
		(new QErrorMessage(this))->showMessage("Sort error");
		return;
	}
	tab->sortItems(tab->currentColumn());
	this->update();
}

void MyTable::searchitem()
{
	auto mas = tab->findItems(line->text(), Qt::MatchExactly);
	for (auto it1 : newItemvect)
	{
		for (auto it2 : it1)
		{
			it2->setBackground(QBrush());
		}
	}
	qDebug() << mas.size();
	for (auto item: mas)
	{
		item->setBackground(QBrush(Qt::cyan));
	}
}

void MyTable::openfile()
{
	std::ifstream task_file;
	task_file.open("Bd.txt");
	std::string line;
	if (!(task_file.is_open()))
	{
		return ;
	}

	std::getline(task_file, line);
	int size = stoi(line);

	this->data->clear();
	cleardata();
	std::vector<QString> tmd;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			getline(task_file, line);
			tmd.push_back(QString::fromStdString(line));
		}
		data->push_back(tmd);
		tmd.clear();
	}
	settab();
	task_file.close();
}

void MyTable::savefile()
{
	if (data->size() == 0)
	{
		return ;
	}

	std::ofstream task_file;
	task_file.open("Bd.txt");
	task_file << this->data->size() << "\n";
	for (auto it1 : *this->data)
	{
		for (auto it2 : it1)
		{
			task_file << it2.toStdString() << "\n";
		}
	}
	task_file.close();
}
