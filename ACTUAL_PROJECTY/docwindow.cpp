#include "docwindow.h"
#include "ui_docwindow.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QDate>
#include<QMovie>
#include<globalvar.h>
#include<mainwindow.h>
#include<QUuid>
#include<QFile>
#include<QTime>
#include<QTimer>
bool conndb();



docwindow::docwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::docwindow)
{

    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    QMovie* gif = new QMovie("C:/Users/Hamza Athar/Documents/ACTUAL_PROJECTY/resources/sparkle.gif");
    ui->labelGif->setMovie(gif);
    gif->start();
    ui->labelGif->setScaledContents(true);

    QMovie* gif3 = new QMovie("C:/Users/Hamza Athar/Documents/ACTUAL_PROJECTY/resources/tree.gif");
    ui->labelGif_3->setMovie(gif3);
    gif3->start();
    ui->labelGif_3->setScaledContents(true);

    QMovie* gif4 = new QMovie("C:/Users/Hamza Athar/Documents/ACTUAL_PROJECTY/resources/tree.gif");
    ui->labelGif_4->setMovie(gif4);
    gif4->start();
    ui->labelGif_4->setScaledContents(true);
}

docwindow::~docwindow()
{
    delete ui;
}

void docwindow::on_tabWidget_tabBarClicked(int index)
{

    //Profile Information Display starts from here
    struct doc {
        QString name;
        QString department;
        QString gender;
        QDate dob;
        qint64 cnic;
        qint64 contact;
        QString address;
    };

    conndb();
    QString tempmail = loggedindocemail;
    doc de;

    if (conndb())
    {
        QSqlQuery ba;
        ba.prepare("SELECT name, department, gender, dob, cnic, contact, address FROM dcredentials WHERE email=:email");
        ba.bindValue(":email", tempmail);

        if (ba.exec() && ba.next()) {


            de.name = ba.value("name").toString();
            de.department = ba.value("department").toString();
            de.gender = ba.value("gender").toString();
            de.cnic = ba.value("cnic").toLongLong();
            de.dob = ba.value("dob").toDate();
            de.contact = ba.value("contact").toLongLong();
            de.address = ba.value("address").toString();

            QString resultText = "Name: " + de.name + "\n\n"
                                 + "Department: " + de.department + "\n\n"
                                 + "Gender: " + de.gender + "\n\n"
                                 + "CNIC: " + QString::number(de.cnic) + "\n\n"
                                 + "DOB: " + ( de.dob.toString("dd/MM/yyyy")) + "\n\n"
                                 + "Contact: " + QString::number(de.contact) + "\n\n";

            ui->textBrowser_7->setText(resultText);
            qDebug() << de.dob.toString("yyyy/MM/dd");
            qDebug() << de.cnic;

        } else {
            QMessageBox::information(this, "Contact Admin", "Query Failed");
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///
        //Salary for doctor calculation
            qint32 k=0;
            double hoursworked;
            double totalhours=0;
            QSqlQuery salary;
            salary.prepare("SELECT * FROM salary WHERE name=:loggedname");
            salary.bindValue(":loggedname",loggedindocname);
            if(salary.exec())
            {
                while(salary.next())
                {
                    hoursworked= salary.value("hoursworked").toDouble();
                    totalhours=totalhours+hoursworked;

                    k++;
                }
                QString text="No. Of Days Worked: "+ QString::number(k)+
                "\n\nTotal Hours Worked: "+ QString::number(totalhours);
                ui->textBrowser_salary->setText(text);

            }
            if (conndb()) {
                // Retrieve department from dcredentials table
                QString department;
                QSqlQuery deptQuery;
                deptQuery.prepare("SELECT department FROM dcredentials WHERE name=:loggedname");
                deptQuery.bindValue(":loggedname", loggedindocname);

                if (deptQuery.exec() && deptQuery.next()) {
                    department = deptQuery.value("department").toString();
                } else {
                    // Handle query execution error or no department found
                    qDebug() << "Error retrieving department for doctor: " << loggedindocname;
                    // You may want to set a default department or handle this case appropriately
                }

                // Use an if condition for each department to set deptPrice
                double deptPrice = 0.0;
                if (department == "Cardiology")
                    deptPrice = 15;
                else if (department == "Dermatology")
                    deptPrice = 12;
                else if (department == "Emergency Medicine")
                    deptPrice = 12;
                else if (department == "Endocrinology")
                    deptPrice = 13;
                else if (department == "Gastroenterology")
                    deptPrice = 14;
                else if (department == "General Surgery")
                    deptPrice = 13.5;
                else if (department == "Internal Medicine")
                    deptPrice = 15.5;
                else if (department == "Neurology")
                    deptPrice = 18;
                else if (department == "Obstetrics and Gynecology")
                    deptPrice = 19;
                else if (department == "Oncology")
                    deptPrice = 18.5;
                else if (department == "Ophthalmology")
                    deptPrice = 17.5;
                else if (department == "Orthopedics")
                    deptPrice = 15.5;
                else if (department == "Pediatrics")
                    deptPrice = 11;
                else if (department == "Psychiatry")
                    deptPrice = 17;
                else if (department == "Pulmonary Medicine")
                    deptPrice = 20;
                else if (department == "Rheumatology")
                    deptPrice = 16;
                else if (department == "Urology")
                    deptPrice = 16.5;

                double totalsalary= totalhours*deptPrice;
                QString salary= "Your Total Salary is: "+QString::number(totalsalary);
                ui->textBrowser_salary2->setText(salary);


            }


    } else if (!conndb()) {
        QMessageBox::information(this, "Error", "Database connection failed");
    }

    //LAB RESULTS
    ui->comboBox_3->clear();
    QSqlQuery labr;
    labr.prepare("SELECT name FROM patient WHERE doctor=:docname");
    labr.bindValue(":docname",loggedindocname);
    if(labr.exec())
    {
        while(labr.next())
        {
            QString patname= labr.value("name").toString();

            ui->comboBox_3->addItem(patname);
        }
    }
    else
    {
        qDebug()<<"Query Failed";
    }



}



void docwindow::on_pushButton_2_clicked()
{
    conndb();
    if(conndb())
    {
        struct pat{
            QString name;
            qint64 code;
            QString gender;
            QDate dob;
            qint64 cnic;
            qint64 contact;
            QString address;
        };
        pat p;
        QString doctor=loggedindocname;
        qDebug()<<doctor;
        QSqlQuery pa;
        pa.prepare("SELECT name,code,gender,cnic,contact,dob FROM patient WHERE doctor=:doctor");
        pa.bindValue(":doctor",doctor);
        if(pa.exec())
        {

            ui->tableWidget_4->clearContents();
            ui->tableWidget_4->setRowCount(0);
            while(pa.next())
            {
                p.name = pa.value("name").toString();
                p.code = pa.value("code").toLongLong();
                p.gender = pa.value("gender").toString();
                p.cnic = pa.value("cnic").toLongLong();
                p.contact = pa.value("contact").toLongLong();
                p.dob= pa.value("dob").toDate();


                int row= ui->tableWidget_4->rowCount();
                ui->tableWidget_4->insertRow(row);
                ui->tableWidget_4->setItem(row,0,new QTableWidgetItem (p.name));
                ui->tableWidget_4->setItem(row,1,new QTableWidgetItem (QString::number(p.code)));
                ui->tableWidget_4->setItem(row,2,new QTableWidgetItem (p.gender));
                ui->tableWidget_4->setItem(row,3,new QTableWidgetItem (p.dob.toString("dd/MM/yyyy")));
                ui->tableWidget_4->setItem(row,4,new QTableWidgetItem (QString::number(p.cnic)));
                ui->tableWidget_4->setItem(row,5,new QTableWidgetItem (QString::number(p.contact)));


                ui->tableWidget_4->update();
                row++;
            }
            ui->tableWidget_4->resizeRowsToContents();
            ui->tableWidget_4->resizeColumnsToContents();

        }
        else if(!pa.exec())
        {
            QMessageBox::information(this,"Contact Admin","Query Failed");
        }

    }

    else if(!conndb())
    {
        QMessageBox::critical(this,"Connection Failure", "Connection to Database failed");
    }

}


void docwindow::on_lineEdit_textChanged(const QString &arg1)
{
    int tablerow = ui->tableWidget_4->rowCount();
    int tablecolumn = ui->tableWidget_4->columnCount();

    for (int row = 0; row < tablerow; ++row)
    {
        bool matchFound = false;

        for (int column = 0; column < tablecolumn; ++column)
        {
            QTableWidgetItem* item = ui->tableWidget_4->item(row, column);

            if (item && !item->text().isEmpty() && item->text().contains(arg1, Qt::CaseInsensitive))
            {
                // If the cell's non-empty text contains the search text
                matchFound = true;
                break;  // Stop checking other columns for this row
            }
        }

        // Show or hide the row based on whether a match was found
        ui->tableWidget_4->setRowHidden(row, !matchFound);
    }
}


void docwindow::on_pushButton_clicked()
{
    QString currenthour = QTime::currentTime().toString("hh");
    QString currentminute = QTime::currentTime().toString("mm");
    QString currentsec = QTime::currentTime().toString("ss");

    double hourtosec = currenthour.toInt() * 3600.0;
    double minutetosec = currentminute.toInt() * 60.0;
    int sec = currentsec.toInt();
    dclogoutt = hourtosec + minutetosec + sec;
    qDebug() << "Before: " << dclogoutt;
    dclogoutt = dclogoutt / 3600.0;
    double diff = dclogoutt - dclogint;
    QString workday = QDate::currentDate().toString("yyyy-MM-dd");
    conndb();
    QSqlQuery work;

    work.prepare("SELECT hoursworked FROM salary WHERE name=:staffname AND date=:workday AND hoursworked IS NOT NULL");
    work.bindValue(":staffname", loggedindocname);  // Replace staffname with loggedindocname
    work.bindValue(":workday", workday);

    if (work.exec() && work.next())
    {
        double storedhours = work.value(0).toDouble();

        work.prepare("UPDATE salary SET hoursworked = :diff WHERE name = :staffname AND date = :workday");
        work.bindValue(":staffname", loggedindocname);  // Replace staffname with loggedindocname
        work.bindValue(":workday", workday);
        work.bindValue(":diff", diff + storedhours);
        if (!work.exec())
        {
            qDebug() << "UPDATE failed:";
        }
    } else
    {
        work.prepare("INSERT INTO salary (name, hoursworked, date) VALUES (:name, :hoursworked, :date)");
        work.bindValue(":name", loggedindocname);  // Replace staffname with loggedindocname
        work.bindValue(":hoursworked", diff);
        work.bindValue(":date", workday);
        if (!work.exec())
        {
            qDebug() << "INSERT failed:";
        }
    }
    close();
    MainWindow *mw= new MainWindow;
    mw->show();

}


void docwindow::on_pushButton_3_clicked()
{
    if (conndb())
    {
        QSqlQuery schedule;
        schedule.prepare("SELECT patname, day, tim FROM appointment WHERE docname=:docname");
        schedule.bindValue(":docname", loggedindocname);

        if (schedule.exec())
        {
            while (schedule.next())
            {
                QString patname = schedule.value("patname").toString();
                QString day = schedule.value("day").toString();
                QString tim = schedule.value("tim").toString();

                qDebug() << patname;
                qDebug() << day;
                qDebug() << tim;

                // Access the text in the row header of the specified row
                int rowToAccess = 1;  // Replace with the desired row index
                QString rowHeaderText = ui->tableWidget_2->verticalHeaderItem(rowToAccess)->text();
                qDebug() << "Row Header Text:" << rowHeaderText;

                // Access the text in the column header of the specified column
                int colToAccess = 1;  // Replace with the desired column index
                QString colHeaderText = ui->tableWidget_2->horizontalHeaderItem(colToAccess)->text();
                qDebug() << "Column Header Text:" << colHeaderText;


                for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
                {
                    if (ui->tableWidget_2->verticalHeaderItem(row)->text() == day)
                    {
                        for (int col = 0; col < ui->tableWidget_2->columnCount(); col++)
                        {
                            if (ui->tableWidget_2->horizontalHeaderItem(col)->text() == tim)
                            {
                                ui->tableWidget_2->setItem(row, col,new QTableWidgetItem(patname));

                            }
                        }
                    }

                }
            }
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Query Failed");
        }
    }
    else
    {
        QMessageBox::warning(this, "Failed", "Database Connection Failed");
    }
}

void docwindow::on_pushButton_4_clicked()
{
    QString test;
    if(ui->radioButton->isChecked())
    {
        test=ui->radioButton->text();
    }
    else if(ui->radioButton_2->isChecked())
    {
        test=ui->radioButton_2->text();
    }
    else if(ui->radioButton_3->isChecked())
    {
        test=ui->radioButton_3->text();
    }
    else if(ui->radioButton_7->isChecked())
    {
        test=ui->radioButton_7->text();
    }
    else if(ui->radioButton_8->isChecked())
    {
        test=ui->radioButton_8->text();
    }
    else if(ui->radioButton_9->isChecked())
    {
        test=ui->radioButton_9->text();
    }
    else if(ui->radioButton_10->isChecked())
    {
        test=ui->radioButton_10->text();
    }
    else if(ui->radioButton_11->isChecked())
    {
        test=ui->radioButton_11->text();
    }
    else if(ui->radioButton_12->isChecked())
    {
        test=ui->radioButton_12->text();
    }
    else if(ui->radioButton_13->isChecked())
    {
        test=ui->radioButton_13->text();
    }
    else if(ui->radioButton_14->isChecked())
    {
        test=ui->radioButton_14->text();
    }
    else if(ui->radioButton_15->isChecked())
    {
        test=ui->radioButton_15->text();
    }
    QSqlQuery up;
    up.prepare("INSERT INTO lab (docname,patname,testtype,status,requestdate) VALUES(:doctor,:patient,:test,:status,:date)");
    up.bindValue(":doctor",loggedindocname);
    up.bindValue(":patient", ui->comboBox_3->currentText());
    up.bindValue(":test",test);
    up.bindValue(":status","Pending");
    up.bindValue(":date",QDate::currentDate());
    if(!up.exec())
    {
        qDebug()<<"Failed";
    }
}




void docwindow::on_pushButton_5_clicked()
{
    if(conndb())
    {
        QSqlQuery uplab;
        uplab.prepare("SELECT * FROM lab WHERE docname=:docname");
        uplab.bindValue(":docname",loggedindocname);
        if(uplab.exec())
        {
            ui->tableWidget_3->clearContents();
            ui->tableWidget_3->setRowCount(0);

            while(uplab.next())
            {

                QString name=uplab.value("patname").toString();

                QString testtype=uplab.value("testtype").toString();
                QString status=uplab.value("status").toString();
                QString requestdate=uplab.value("requestdate").toString();
                QString result=uplab.value("result").toString();
                int row=ui->tableWidget_3->rowCount();
                ui->tableWidget_3->insertRow(row);
                ui->tableWidget_3->setItem(row,0,new QTableWidgetItem (name));
                ui->tableWidget_3->setItem(row,1,new QTableWidgetItem (testtype));
                ui->tableWidget_3->setItem(row,2,new QTableWidgetItem (status));
                ui->tableWidget_3->setItem(row,3,new QTableWidgetItem (requestdate));
                ui->tableWidget_3->setItem(row,4,new QTableWidgetItem (result));

            }
        }

    }
}



void docwindow::on_pushButton_11_clicked()
{
    QFile file("docnotes.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);

        // Get current date and day
        QString notes= ui->textEdit->toPlainText();
        QDateTime currentDate = QDateTime::currentDateTime();
        QString dateString = currentDate.toString("yyyy-MM-dd");
        QString dayString = currentDate.toString("dddd");

        // Write notes to the file with date and day
        stream << "Date: " << dateString << ", Day: " << dayString << "\n";
        stream << notes << "\n";

        // Add 4 lines as separators
        for (int i = 0; i < 4; ++i) {
            stream << "\n";
        }

        file.close();
    } else {
        // Handle file opening error
        qDebug() << "Error opening file for writing";
    }
}


void docwindow::on_pushButton_6_clicked()
{
    QFile file("docnotes.txt");
    QString notes;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        notes = stream.readAll();
        file.close();
        ui->textEdit->setText(notes);
    } else {
        // Handle file opening error
        qDebug() << "Error opening file for reading";
    }
}




