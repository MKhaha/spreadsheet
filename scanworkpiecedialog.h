#ifndef SCANWORKPIECEDIALOG_H
#define SCANWORKPIECEDIALOG_H

#include <QDialog>

namespace Ui {
class ScanWorkPieceDialog;
}

class ScanWorkPieceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanWorkPieceDialog(QWidget *parent = 0);
    ~ScanWorkPieceDialog();

signals:
    void newSerialNumbers(const QString &columnName, const QString &serialNumber);

private slots:
    void setLineEditEnable();
    void setLineEidtDisable();
    void currentSerialNumberslineEdit_returnPressed();

private:
    Ui::ScanWorkPieceDialog *ui;
};

#endif // SCANWORKPIECEDIALOG_H
