#include "infomationmanagerofserialnumber.h"
#include <QtSql/QSqlDatabase>
#include <QHash>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>
#include <QDate>
#include <QTime>
#include <QDebug>

InfomationManagerOfserialNumber::InfomationManagerOfserialNumber(QObject *parent) : QObject(parent)
{
    // initialize database
    database = QSqlDatabase::addDatabase("QMYSQL");
}

void InfomationManagerOfserialNumber::setParameterLocal(QHash<QString, QString> &hash)
{
    QString emptyString = NULL;

    if(emptyString != hash["hostnameOrIpAddress"])
    {
        hostName = hash["hostnameOrIpAddress"];
        database.setHostName(hostName);
    }
    if(emptyString != hash["port"])
    {
        port = hash["port"];
        database.setPort(port.toInt());
    }
    if(emptyString != hash["databaseName"])
    {
        databaseName = hash["databaseName"];
        database.setDatabaseName(databaseName);
    }
    if(emptyString != hash["tableName"])
    {
        tableName = hash["tableName"];
    }
    if(emptyString != hash["username"])
    {
        username = hash["username"];
        database.setUserName(username);
    }
    if(emptyString != hash["password"])
    {
        password = hash["password"];
        database.setPassword(password);
    }
}

void InfomationManagerOfserialNumber::testConnetction(QHash<QString, QString> &hash)
{
    setParameterLocal(hash);
    bool ok = database.open();
    emit okConnectionWithSql(ok);
    if(ok)
    {
        database.close();
    }
}

void InfomationManagerOfserialNumber::setParameterOfConnection(QHash<QString, QString> &hash)
{
    setParameterLocal(hash);
    bool ok = database.open();
    emit okConnectionWithSql(ok);
}

int InfomationManagerOfserialNumber::getColumnCount()
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
        return 0;
    }
    else
    {
        sqlQuery.next();
        count = sqlQuery.value(0).toInt();
        return count;
    }
}

//get columns name from current database.table;
void InfomationManagerOfserialNumber::getColumnsName()
{
    qDebug() << "record.fieldName(i)";

    if(true != listString.isEmpty())
    {
        listString.clear();
    }

    QString selectQuery = QString("SELECT * FROM %1.%2 LIMIT 1").arg(databaseName).arg(tableName);
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(selectQuery))
    {
        listString << sqlQuery.lastError().text();
        qDebug() << sqlQuery.lastError().text();
        emit columnsNameInfomation(listString);
        return;
    }

    QSqlRecord record = sqlQuery.record();
    int columnCount = record.count();
    int i = 0;
    while(i < columnCount)
    {
        listString << record.fieldName(i);
        qDebug() << record.fieldName(i);
        i++;
    }

    emit columnsNameInfomation(listString);
    return;
}

void InfomationManagerOfserialNumber::getDataFromMysql(const QString &fieldName, const QString &value)
{
    int columnCount = 0;
    int i = 0;
    QSqlRecord record;
    if(true != listString.isEmpty())
    {
        listString.clear();
    }

    qDebug() << fieldName;
    qDebug() << value;

    QString selectQuery = QString("SELECT * FROM %1.%2 WHERE %3 LIKE '%%4%'")
                                .arg(databaseName).arg(tableName).arg(fieldName).arg(value);
    qDebug() << selectQuery;
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(selectQuery))
    {
        listString << sqlQuery.lastError().text();
        goto multipleRecordInfomationout;
    }
    qDebug() << "test";
    record = sqlQuery.record();
    columnCount = record.count();
    i = 0;
    while(i < columnCount)
    {
        listString << record.fieldName(i);
        qDebug() << record.fieldName(i);
        i++;
    }

    qDebug() << sqlQuery.size();
    if(sqlQuery.size() == 0)
    {
        listString << "empty set";
        goto multipleRecordInfomationout;
    }
    while(sqlQuery.next())
    {
        i = 0;
        while(i < columnCount)
        {
            listString << sqlQuery.value(i).toString();
            qDebug() << sqlQuery.value(i).toString();
            i++;
        }
    }

multipleRecordInfomationout:
    emit multipleRecordInfomation(listString, columnCount);
    return;
}

void InfomationManagerOfserialNumber::getInfomationOfSerialNumber(const QString &str)
{
    int i = 0;
    int columnCount = 0;
    QDate date;
    QTime time;
    QString currentDateAndTime;

    QSqlQuery sqlQuery;
    QString selectSql;

    QString fieldName = "serialnumber";

    if(true != listString.isEmpty())
    {
        listString.clear();
    }

    // set serial number as first field
    listString << str;

    // set data as second fiel
    date = QDate::currentDate();
    time = QTime::currentTime();
    currentDateAndTime =
            QString("%1 %2").arg(date.toString("dd-MM-yyyy")).arg(time.toString("hh:mm:ss.zzz"));
    listString << currentDateAndTime;

    // get information of the serial number
    selectSql = QString("select * from %1.%2 where %3=%4")
            .arg(databaseName).arg(tableName).arg(fieldName).arg(str);
    qDebug() << selectSql;
    sqlQuery.exec(selectSql);

    if(!sqlQuery.isActive())
    {
        // set database error if database error when excute database select
        listString << sqlQuery.lastError().text();
        goto evnOut;
    }
    else
    {
        // only get first row
        sqlQuery.first();
        QSqlRecord record = sqlQuery.record();
        if(true == record.isEmpty())
        {
            // set no record if not found
            listString << "no infomation";
            goto evnOut;
        }
        columnCount = record.count();
        while(i < columnCount)
        {
            if(true == record.isNull(i))
            {
                listString << "NULL";
            }
            else
            {
                // get information of serial number exclude serialnumber
                if(str != record.value(i).toString())
                {
                    listString << record.value(i).toString();
                }
            }
            i++;
        }
        goto evnOut;

    }

evnOut:
    emit inserInfomationToSpreadSheet(listString);
    return;
}

InfomationManagerOfserialNumber::~InfomationManagerOfserialNumber()
{
    if(database.isOpen())
    {
        database.close();
    }
}

