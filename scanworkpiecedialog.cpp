#include "scanworkpiecedialog.h"
#include "ui_scanworkpiecedialog.h"

static QString currentTotalNum = "current total num:";

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
    currentTotalValue = 0;

    ui->currentTotalValueLabel->setText(QString("%1%2").arg(currentTotalNum).arg(currentTotalValue));
    targetValue = 100;
    targetMinValue = 1;
    targetMaxValue = 1000000;
    QString targetValueLineEditPlaceHolderText = QString("%1 %2(%3-%4)").\
            arg(tr("defalut value")).arg(targetValue).arg(targetMinValue).arg(targetMaxValue);
    ui->targetValueLineEdit->setPlaceholderText(targetValueLineEditPlaceHolderText);
    ui->targetValueLineEdit->setValidator(new QIntValidator(targetMinValue, targetMaxValue));

    ui->progressBar->setValue(int(double(currentTotalValue) / targetValue * 100));

    connect(ui->starScanButton, SIGNAL(clicked()), this, SLOT(setLineEditEnable()));
    connect(ui->stopScanButton, SIGNAL(clicked()), this, SLOT(setLineEidtDisable()));

    connect(ui->currentSerialNumberslineEdit, SIGNAL(editingFinished()), this, SLOT(currentSerialNumberslineEdit_returnPressed()));
    connect(ui->targetValueLineEdit, SIGNAL(editingFinished()), this, SLOT(targetValueLineEdit_returnPressed()));
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

void ScanWorkPieceDialog::targetValueLineEdit_returnPressed()
{
    if(ui->targetValueLineEdit->hasAcceptableInput())
    {
        targetValue = ui->targetValueLineEdit->text().toInt();
        ui->progressBar->setValue(int((double(currentTotalValue) / targetValue) * 100));
    }
}

void ScanWorkPieceDialog::currentSerialNumberslineEdit_returnPressed()
{
    currentTotalValue += 1;
    ui->currentTotalValueLabel->setText(QString("%1%2").arg(currentTotalNum).arg(currentTotalValue));
    if(currentTotalValue <= targetValue)
    {
        ui->progressBar->setValue(int((double(currentTotalValue) / targetValue) * 100));
    }
    else
    {
        ui->progressBar->setValue(100);
    }

    emit newSerialNumbers(ui->currentSerialNumberslineEdit->text());
    ui->currentSerialNumberslineEdit->clear();
}

ScanWorkPieceDialog::~ScanWorkPieceDialog()
{
    delete ui;
}
