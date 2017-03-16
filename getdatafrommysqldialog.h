#ifndef GETDATAFROMMYSQLDIALOG_H
#define GETDATAFROMMYSQLDIALOG_H

#include <QDialog>

namespace Ui {
class GetDataFromMysqlDialog;
}

class GetDataFromMysqlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetDataFromMysqlDialog(QWidget *parent = 0);
    ~GetDataFromMysqlDialog();

signals:
    void getFieldName();
    void searchDataFromMysql(const QString &fieldName, const QString &value);

public slots:
    void fieldNameList(const QList<QString> &list);

private slots:
    void getFieldNameSlots();
    void searchDataSlots();

private:
    Ui::GetDataFromMysqlDialog *ui;
};

#endif // GETDATAFROMMYSQLDIALOG_H
