#include "setdatabaseandtabledialog.h"
#include "ui_setdatabaseandtabledialog.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDate>
#include <QTime>
#include <QHash>

SetDatabaseAndTableDialog::SetDatabaseAndTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDatabaseAndTableDialog)
{
    ui->setupUi(this);

    connect(ui->testConnectionPushButton, SIGNAL(clicked(bool)), this, SLOT(testConnetction()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setParameter()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    setWhatsThis(QString("input parameter(hostname/IP username password), "
                         "test whether you can or not connect with mysql"));
}

void SetDatabaseAndTableDialog::getParameterOfConnectionFromLineText()
{
    // get parameter of connection
    hostNameOrIpAddress = ui->hostnameLineEdit->text();
    port = ui->portLineEdit->text();
    databaseName = ui->databaseNameLineEdit->text();
    tableName = ui->tableNameLineEdit->text();
    username = ui->userNameLineEdit->text();
    password = ui->passwordLineEdit->text();
    qDebug() << QString("hostname:%1, port:%2, databasename:%3, username:%4, password:%5").\
                arg(hostNameOrIpAddress).arg(port).arg(databaseName).arg(username).arg(password);
}
void SetDatabaseAndTableDialog::setHashMap(QString emptyString,
                                           QHash<QString, QString> &hash,
                                           QString key, QString value)
{
    if(emptyString != value)
    {
        hash[key] = value;
    }
}
void SetDatabaseAndTableDialog::setParameterOfConnection()
{
    QString emptyString = "";

    if(true != hashConnetcion.isEmpty())
    {
        hashConnetcion.clear();
    }

    if(emptyString != hostNameOrIpAddress)
    {
        hashConnetcion["hostnameOrIpAddress"] = hostNameOrIpAddress;
    }
    if(emptyString != port)
    {
        hashConnetcion["port"] = port;
    }
    if(emptyString != databaseName)
    {
        hashConnetcion["databaseName"] = databaseName;
    }
    if(emptyString != tableName)
    {
        hashConnetcion["tableName"] = tableName;
    }
    if(emptyString != username)
    {
        hashConnetcion["username"] = username;
    }
    if(emptyString != password)
    {
        hashConnetcion["password"] = password;
    }
}

void SetDatabaseAndTableDialog::getAndSetParameter(void)
{
    getParameterOfConnectionFromLineText();
    setParameterOfConnection();
}

void SetDatabaseAndTableDialog::testConnetction(void)
{
    getAndSetParameter();
    emit testConnetctionWithSqlSignal(hashConnetcion);

    return;
}

void SetDatabaseAndTableDialog::setParameter(void)
{
    getAndSetParameter();
    emit setDatabaseNameAndTableNameSignal(hashConnetcion);

    return;
}

void SetDatabaseAndTableDialog::okConnectionSlot(bool okConnection)
{
    if(!okConnection)
    {
        QMessageBox::warning(this, tr("Database Error"),
                             database.lastError().text());
    }
    else
    {
        QMessageBox::information(this, tr("connection with sql"),
                             tr("connection test with sql success"),
                             QMessageBox::Ok);
    }
    return;
}

SetDatabaseAndTableDialog::~SetDatabaseAndTableDialog()
{
    delete ui;
}
