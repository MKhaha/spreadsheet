#ifndef GENERATEQRCODEDIALOG_H
#define GENERATEQRCODEDIALOG_H

#include <QDialog>

namespace Ui {
class GenerateQRcodeDialog;
}

class GenerateQRcodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateQRcodeDialog(QWidget *parent = 0);
    ~GenerateQRcodeDialog();

public slots:
    void textFromSpreedSheet(QString &text);

signals:
    void getTextCurrentPosition(QString &text);

private slots:
    void getTextCurrentPositionPrivateSlots();
    void generateQRcode();
    void getImageSavePath();

private:
    QString textCurrentPostion;
    QString imageSavePath;
    int imageMargin;
    int imageSize;
    Ui::GenerateQRcodeDialog *ui;
};

#endif // GENERATEQRCODEDIALOG_H
