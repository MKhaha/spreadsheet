#include "setdatabaseandtabledialog.h"
#include "ui_setdatabaseandtabledialog.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QTime>

SetDatabaseAndTableDialog::SetDatabaseAndTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDatabaseAndTableDialog)
{
    ui->setupUi(this);

    // initialize parameter
    database = QSqlDatabase::addDatabase("QMYSQL");

    connect(ui->testConnectionPushButton, SIGNAL(clicked(bool)), this, SLOT(testConnetctionWithSql()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createConnectionWithSql()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    setWhatsThis(QString("input parameter(hostname/IP username password), test whether you can or not connect with mysql"));
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

void SetDatabaseAndTableDialog::setParameterOfConnection()
{
    // set parameter of connection
    database.setHostName(hostNameOrIpAddress);
    database.setPort(port.toInt());
    database.setDatabaseName(databaseName);
    database.setUserName(username);
    database.setPassword(password);
}

void SetDatabaseAndTableDialog::testConnetctionWithSql(void)
{
    createConnectionWithSql();
    if(database.isOpen())
    {
        database.close();
    }

    return;
}

void SetDatabaseAndTableDialog::createConnectionWithSql()
{
    getParameterOfConnectionFromLineText();
    setParameterOfConnection();
    /* test connection of connection,
    ** and prompt user information of connection
    */
    if(!database.open())
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

int SetDatabaseAndTableDialog::getColumnCount()
{
    QSqlQuery sqlQuery;
    int count;
    QString selectSql = QString("select count(*) from information_schema.`COLUMNS` "
                                "where TABLE_SCHEMA='%1' and "
                                "TABLE_NAME='%2'").
                                arg(databaseName).arg(tableName);
    sqlQuery.exec(selectSql);

    if(!sqlQuery.isActive())
    {
        QMessageBox::warning(this, tr("Database Error"), sqlQuery.lastError().text());
        return 0;
    }
    else
    {
        qDebug() << "test1";
        sqlQuery.next();
        count = sqlQuery.value(0).toInt();
        return count;
    }
}

void SetDatabaseAndTableDialog::getInfomationOfSerialNumber(const QString &str, QList<QString> &list)
{
    int i = 0;
    int columnCount;
    QDate date;
    QTime time;
    QString currentDateAndTime;

    QSqlQuery sqlQuery;
    QString selectSql;

    list << str;

    date = QDate::currentDate();
    time = QTime::currentTime();
    currentDateAndTime =
            QString("%1 %2").arg(date.toString("dd-MM-yyyy")).arg(time.toString("hh:mm:ss.zzz"));
    list << currentDateAndTime;

    columnCount = 0;
    columnCount = getColumnCount();
    if(0 == columnCount)
    {
        list << "no infomation";
        goto evnOut;
    }

    selectSql = QString("select * from %1.%2 where ID=%3").arg(databaseName).arg(tableName).arg(str);
    sqlQuery.exec(selectSql);

    if(!sqlQuery.isActive())
    {
        QMessageBox::warning(this, tr("Database Error"), sqlQuery.lastError().text());
        list << "no infomation";
        goto evnOut;
    }
    else
    {
        // 只取第一行信息
        sqlQuery.first();
        qDebug() << "test2";

        while(i < columnCount)
        {
            list << sqlQuery.value(i).toString();
            i++;
        }
        goto evnOut;

    }

evnOut:
    emit inserInfomationToSpreadSheet(list);
    return;
}

SetDatabaseAndTableDialog::~SetDatabaseAndTableDialog()
{
    delete ui;
}
