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
    void inserInfomationToSpreadSheet(const QList<QString> &list);

public slots:
    void getInfomationOfSerialNumber(const QString &str, QList<QString> &list);

private slots:
    void testConnetctionWithSql(void);
    void createConnectionWithSql(void);

private:
    Ui::SetDatabaseAndTableDialog *ui;
    QString hostNameOrIpAddress;
    QString port;
    QString databaseName;
    QString tableName;
    QString username;
    QString password;
    QSqlDatabase database;

    void getParameterOfConnectionFromLineText(void);
    void setParameterOfConnection(void);
    int getColumnCount(void);
};

#endif // SETDATABASEANDTABLEDIALOG_H
