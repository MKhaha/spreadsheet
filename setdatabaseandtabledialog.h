#ifndef SETDATABASEANDTABLEDIALOG_H
#define SETDATABASEANDTABLEDIALOG_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class SetDatabaseAndTableDialog;
}

class SetDatabaseAndTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDatabaseAndTableDialog(QWidget *parent = 0);
    ~SetDatabaseAndTableDialog();

signals:
    void testConnetctionWithSqlSignal(QHash<QString, QString> &hash);
    void setDatabaseNameAndTableNameSignal(QHash<QString, QString> &hash);

public slots:
    void okConnectionSlot(bool okConnection);

private slots:
    void testConnetction(void);
    void setParameter(void);

private:
    Ui::SetDatabaseAndTableDialog *ui;
    QString hostNameOrIpAddress;
    QString port;
    QString databaseName;
    QString tableName;
    QString username;
    QString password;
    QSqlDatabase database;
    QHash<QString, QString> hashConnetcion;

    void setHashMap(QString emptyString,QHash<QString, QString> &hash,
                    QString key, QString value);
    void getAndSetParameter(void);
    void getParameterOfConnectionFromLineText(void);
    void setParameterOfConnection(void);
    int getColumnCount(void);
};

#endif // SETDATABASEANDTABLEDIALOG_H
