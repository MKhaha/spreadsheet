#include "scanworkpiecedialog.h"
#include "ui_scanworkpiecedialog.h"
#include <QDebug>
#include <QMessageBox>

ScanWorkPieceDialog::ScanWorkPieceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanWorkPieceDialog)
{
    ui->setupUi(this);

    ui->stopScanButton->setEnabled(false);
#if 0
    QRegExp regExp("[1-9][0-9]{12}");
    ui->currentSerialNumberslineEdit->setValidator(new QRegExpValidator(regExp, this));
#endif
    ui->currentSerialNumberslineEdit->setEnabled(false);

    connect(ui->starScanButton, SIGNAL(clicked()), this, SLOT(setLineEditEnable()));
    connect(ui->stopScanButton, SIGNAL(clicked()), this, SLOT(setLineEidtDisable()));

    connect(ui->currentSerialNumberslineEdit, SIGNAL(returnPressed()),
            this, SLOT(currentSerialNumberslineEdit_returnPressed()));
}

void ScanWorkPieceDialog::setLineEditEnable()
{
    ui->currentSerialNumberslineEdit->setEnabled(true);
    ui->starScanButton->setEnabled(false);
    ui->stopScanButton->setEnabled(true);
}

void ScanWorkPieceDialog::setLineEidtDisable()
{
    ui->currentSerialNumberslineEdit->setEnabled(false);
    ui->starScanButton->setEnabled(true);
    ui->stopScanButton->setEnabled(false);
}

void ScanWorkPieceDialog::currentSerialNumberslineEdit_returnPressed()
{
    if(!ui->columnNameLineEdit->hasAcceptableInput())
    {
        std::string strThisObjectName = this->objectName().toStdString();
        const char* chThisObjectName = strThisObjectName.c_str();
        QMessageBox::warning(this, tr(chThisObjectName),
                             tr("column name is NULL"));
        return;
    }
    emit newSerialNumbers(ui->columnNameLineEdit->text(), ui->currentSerialNumberslineEdit->text());
    ui->currentSerialNumberslineEdit->clear();
}

ScanWorkPieceDialog::~ScanWorkPieceDialog()
{
    delete ui;
}
