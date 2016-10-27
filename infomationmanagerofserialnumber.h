#ifndef INFOMATIONMANAGEROFSERIALNUMBER_H
#define INFOMATIONMANAGEROFSERIALNUMBER_H

#include <QObject>
#include <QSqlDatabase>

class InfomationManagerOfserialNumber : public QObject
{
    Q_OBJECT
public:
    explicit InfomationManagerOfserialNumber(QObject *parent = 0);
    ~InfomationManagerOfserialNumber();

signals:
    void inserInfomationToSpreadSheet(const QList<QString> &list);
    void okConnectionWithSql(bool okConnection);

public slots:
    void getInfomationOfSerialNumber(const QString &str);
    void testConnetction(QHash<QString, QString> &hash);
    void setParameterOfConnection(QHash<QString, QString> &hash);

private:
    QString hostName;
    QString port;
    QString databaseName;
    QString tableName;
    QString username;
    QString password;
    QList<QString> listString;
    QSqlDatabase database;

    int getColumnCount();
    void setParameterLocal(QHash<QString, QString> &hash);
};

#endif // INFOMATIONMANAGEROFSERIALNUMBER_H
