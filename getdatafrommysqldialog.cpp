#include "getdatafrommysqldialog.h"
#include "ui_getdatafrommysqldialog.h"
#include <QMessageBox>

GetDataFromMysqlDialog::GetDataFromMysqlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetDataFromMysqlDialog)
{
    ui->setupUi(this);

    connect(ui->GetFieldNamePushButton, SIGNAL(clicked(bool)),
            this, SLOT(getFieldNameSlots()));
    connect(ui->SearchRecordPushButton, SIGNAL(clicked(bool)),
            this, SLOT(searchDataSlots()));
}

void GetDataFromMysqlDialog::fieldNameList(const QList<QString> &list)
{
    for (int i = 0; i < list.size(); ++i) {
        ui->FieldNameTextBrowser->insertPlainText(list.at(i) + ";\n");
    }
}

void GetDataFromMysqlDialog::getFieldNameSlots()
{
    emit getFieldName();
}

void GetDataFromMysqlDialog::searchDataSlots()
{
    if(ui->SearchStringLineEdit->text().isEmpty() || ui->FieldNameLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("GetDataFromMysql"),
                             tr("FieldName or SearchString is NULL"));
        return;
    }
    else
    {
        emit searchDataFromMysql(ui->FieldNameLineEdit->text(), ui->SearchStringLineEdit->text());
    }
}

GetDataFromMysqlDialog::~GetDataFromMysqlDialog()
{
    delete ui;
}
