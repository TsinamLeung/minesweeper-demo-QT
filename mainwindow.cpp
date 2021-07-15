#include "mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	// can also initialize the other custom widget here
	connect(ui->stage, SIGNAL(resizeWindow(int,int)), this, SLOT(setWindowSize(int,int)));
	connect(ui->stage, SIGNAL(changeState(QString)), this, SLOT(setState(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::difficultDialog()
{
	bool success;
	int row, col, num_mine;


	DifficultDialog::GetCustomDiffcult(this, row, col, num_mine, &success);
	if (success)
	{
		emit setMap(row, col, num_mine);
	}
}

DifficultDialog::DifficultDialog(QWidget *parent /* = nullptr */) : QDialog(parent)
{
	QFormLayout* layout = new QFormLayout(this);

	QLabel* row_label = new QLabel(QString("Please input row:"),this);
	QLineEdit* row_edit = new QLineEdit(this);

	QLabel* col_label = new QLabel(QString("Please input col:"), this);
	QLineEdit* col_edit = new QLineEdit(this);
	
	QLabel* mine_label = new QLabel(QString("Please input numbers of mine:"), this);
	QLineEdit* mine_edit = new QLineEdit(this);

	layout->addRow(row_label, row_edit);
	layout->addRow(col_label, col_edit);
	layout->addRow(mine_label, mine_edit);

	fields << row_edit;
	fields << col_edit;
	fields << mine_edit;

	QDialogButtonBox* buttonBox = new QDialogButtonBox
	(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, this);
	layout->addWidget(buttonBox);

	bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
		this, &DifficultDialog::accept);
	Q_ASSERT(conn);
	conn = connect(buttonBox, &QDialogButtonBox::rejected,
		this, &DifficultDialog::reject);
	Q_ASSERT(conn);

	this->setLayout(layout);
}

void DifficultDialog::GetCustomDiffcult(QWidget * parent, int & row, int & col, int & num_mine, bool * ok)
{
	DifficultDialog* dialog = new DifficultDialog(parent);
	
	const int ret = dialog->exec();
	if (ok)
	{
		*ok = !!ret;
	}
	if (ret)
	{
		row = dialog->fields.takeFirst()->text().toInt();
		col = dialog->fields.takeFirst()->text().toInt();
		num_mine = dialog->fields.takeFirst()->text().toInt();
	}

	dialog->deleteLater();
}
