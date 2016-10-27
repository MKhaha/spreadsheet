#ifndef INFOMATIONMANAGEROFSERIALNUMBER_H
#define INFOMATIONMANAGEROFSERIALNUMBER_H

#include <QObject>

class QSqlDatabase;
class QList;

class InfomationManagerOfserialNumber : public QObject
{
    Q_OBJECT
public:
    explicit InfomationManagerOfserialNumber(QObject *parent = 0);

signals:

public slots:

private:
    QSqlDatabase *pDataBase;
    QString *databaseName;
    QString *tableName;

    int getColumnCount();
    void getInfomationOfSerialNumber(const QString &str, QList<QString> &list);
};

#endif // INFOMATIONMANAGEROFSERIALNUMBER_H
