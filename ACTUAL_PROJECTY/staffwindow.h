#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QDialog>

namespace Ui {
class staffwindow;
}

class staffwindow : public QDialog
{
    Q_OBJECT

public:
    explicit staffwindow(QWidget *parent = nullptr);
    ~staffwindow();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_departmentcombo_currentIndexChanged(int index);

    void on_doctorcombo_currentIndexChanged(int index);

    void on_daycombo_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_4_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_patdocdep_currentIndexChanged(int index);

    void on_lineEdit_78_editingFinished();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();



    void on_pushButton_7_clicked();



    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::staffwindow *ui;
    int Isdisabled();
    void trtime(const QString &day, QString docname, QString department);
    void resetrad();


};

#endif // STAFFWINDOW_H
