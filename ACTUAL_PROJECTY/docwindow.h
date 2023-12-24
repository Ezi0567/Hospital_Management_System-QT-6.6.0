#ifndef DOCWINDOW_H
#define DOCWINDOW_H

#include <QDialog>

namespace Ui {
class docwindow;
}

class docwindow : public QDialog
{
    Q_OBJECT

public:
    explicit docwindow(QWidget *parent = nullptr);
    ~docwindow();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::docwindow *ui;
    void chbox();

};

#endif // DOCWINDOW_H
