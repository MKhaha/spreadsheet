#include "infomationmanagerofserialnumber.h"
#include <QtSql/QSqlDatabase>

InfomationManagerOfserialNumber::InfomationManagerOfserialNumber(QObject *parent) : QObject(parent)
{
}

int InfomationManagerOfserialNumber::getColumnCount()
{
    QSqlQuery sqlQuery;
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
        sqlQuery.next();
        count = sqlQuery.value(0).toInt();
        return count;
    }
}

void InfomationManagerOfserialNumber::getInfomationOfSerialNumber(const QString &str, QList<QString> &list)
{
    QSqlQuery sqlQuery;
    int columnCount = 0;
    columnCount = getColumnCount();
    if(0 == columnCount)
    {
        list << "no infomation";
        return;
    }
    QString selectSql = QString("select * from %1.%2 where ID=%3").arg(databaseName).arg(tableName).arg(str);
    sqlQuery.exec(selectSql);

    if(!sqlQuery.isActive())
    {
        QMessageBox::warning(this, tr("Database Error"), sqlQuery.lastError().text());
        list << "no infomation";
        return;
    }
    else
    {
        // 只取第一行信息
        int i = 0;
        while(i < columnCount)
        {
            list << sqlQuery.value(i).toString();
            i++;
        }
        return;
    }
}
