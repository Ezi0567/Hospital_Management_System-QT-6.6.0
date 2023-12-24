#include "staffwindow.h"
#include "ui_staffwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <globalvar.h>
#include<QFile>
#include<mainwindow.h>
#include<QUuid>
#include<QDate>
bool conndb();
void staffwindow::resetrad() //Function for resetting all radio buttons (had to declare the function in the header file's private slot to access the ui)
{
    ui->radioButton->setEnabled(true);
    ui->radioButton->setChecked(false);

    ui->radioButton_2->setEnabled(true);
    ui->radioButton_2->setChecked(false);

    ui->radioButton_3->setEnabled(true);
    ui->radioButton_3->setChecked(false);

    ui->radioButton_4->setEnabled(true);
    ui->radioButton_4->setChecked(false);

    ui->radioButton_5->setEnabled(true);
    ui->radioButton_5->setChecked(false);

    ui->radioButton_6->setEnabled(true);
    ui->radioButton_6->setChecked(false);
}



void staffwindow::trtime(const QString &day, QString docname, QString department) //trtime function for checking if an appointment is already booked based upon doctorname and time
{
    conndb(); //connecting database
    if (conndb()) //if connection successful
    {
        resetrad(); //reset radio buttons before every query
        QSqlQuery checkrad; //query for retreiving data
        checkrad.prepare("SELECT tim FROM appointment WHERE day=:day AND docname=:docname AND department =:department "); //retreives the data stored in tim if the day and docname selected by the user match the data stored in the database
        checkrad.bindValue(":day", day);   //binds values/replaces
        checkrad.bindValue(":docname", docname);    //binds values/replaces
        checkrad.bindValue(":department" ,department );
        if (checkrad.exec()) //if query was executed
        {
            while (checkrad.next()) //if values were found
            {
                QString bookedtime = checkrad.value("tim").toString(); //Stores the value stored in the column of tim in the bookedtime variable
                qDebug()<<bookedtime;
                // if conditionals to check if radio button matches the booked time, if it does then it will disable the radio button and if the radio button is checked it will uncheck it this step continues for all the radio buttons
                if (ui->radioButton->text() == bookedtime)
                {
                    ui->radioButton->setDisabled(true);
                    if(ui->radioButton->isChecked())
                    {
                        ui->radioButton->setChecked(false);
                    }
                }
                else if (ui->radioButton_2->text() == bookedtime)
                {
                    ui->radioButton_2->setDisabled(true);
                    if(ui->radioButton_2->isChecked())
                    {
                        ui->radioButton_2->setChecked(false);
                    }
                }
                else if (ui->radioButton_3->text() == bookedtime)
                {
                    ui->radioButton_3->setDisabled(true);
                    if(ui->radioButton_3->isChecked())
                    {
                        ui->radioButton_3->setChecked(false);
                    }
                }
                else if (ui->radioButton_4->text() == bookedtime)
                {
                    ui->radioButton_4->setDisabled(true);
                    if(ui->radioButton_4->isChecked())
                    {
                        ui->radioButton_4->setChecked(false);
                    }
                }
                else if (ui->radioButton_5->text() == bookedtime)
                {
                    ui->radioButton_5->setDisabled(true);
                    if(ui->radioButton_5->isChecked())
                    {
                        ui->radioButton_5->setChecked(false);
                    }
                }
                else if (ui->radioButton_6->text() == bookedtime)
                {
                    ui->radioButton_6->setDisabled(true);
                    if(ui->radioButton_6->isChecked())
                    {
                        ui->radioButton_6->setChecked(false);
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this,"Error","Query Failed");
        }
    }

    else     //If database connection fails
    {
        QMessageBox::warning(this, "Connection Error", "Error Connecting"); //Messagebox to display that the connection failed
    }
}
//For checking if the radio button is disabled or not (had to declare the function in the header file's private slot to access the ui)
int staffwindow::Isdisabled()
{
    int k = 0;
    if (ui->radioButton->isChecked())
    {
        ui->radioButton->setDisabled(true);
        k++;
    }
    else if (ui->radioButton_2->isChecked())
    {
        ui->radioButton_2->setDisabled(true);
        k++;
    }
    else if (ui->radioButton_3->isChecked())
    {
        ui->radioButton_3->setDisabled(true);
        k++;
    }
    else if (ui->radioButton_4->isChecked())
    {
        ui->radioButton_4->setDisabled(true);
        k++;
    }
    else if (ui->radioButton_5->isChecked())
    {
        ui->radioButton_5->setDisabled(true);
        k++;
    }
    else if (ui->radioButton_6->isChecked())
    {
        ui->radioButton_6->setDisabled(true);
        k++;
    }
    return k;
}

staffwindow::staffwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffwindow)
{
    ui->setupUi(this);
}

staffwindow::~staffwindow()
{
    delete ui;
}

void staffwindow::on_tabWidget_tabBarClicked(int index)
{

        struct staff {
            QString name;
            QString department;
            QString gender;
            QDate dob;
            qint64 cnic;
            qint64 contact;
        };

        conndb();
        QString tempmail = loggedinstaffemail;
        staff st;

        if (conndb()) {
            QSqlQuery ba;
            ba.prepare("SELECT name, gender, dob, cnic, contact FROM scredentials WHERE email=:email");
            ba.bindValue(":email", tempmail);

            if (ba.exec() && ba.next()) {


                st.name = ba.value("name").toString();
                st.gender = ba.value("gender").toString();
                st.cnic = ba.value("cnic").toInt();
                st.dob = ba.value("dob").toDate();
                st.contact = ba.value("contact").toInt();

                QString resultText = "Name: " + st.name + "\n\n"
                                     + "Gender: " + st.gender + "\n\n"
                                     + "CNIC: " + QString::number(st.cnic) + "\n\n"
                                     + "DOB: " + (st.dob.toString("dd/MM/yyyy")) + "\n\n"
                                     + "Contact: " + QString::number(st.contact) + "\n\n";

                ui->textBrowser_7->setText(resultText);
                qDebug() << st.dob.toString("yyyy/MM/dd");
                qDebug() << st.cnic;
            } else {
                QMessageBox::information(this, "Contact Admin", "Query Failed");
            }
            qint32 k=0;
            double hoursworked;
            double totalhours=0;
            QSqlQuery salary;
            salary.prepare("SELECT * FROM salary WHERE name=:loggedname");
            salary.bindValue(":loggedname",loggedinstaffname);
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
                double salary= totalhours*15;
                QString saltext= "Your Salary Uptill Now Is: "+QString::number(salary);
                ui->textBrowser_salary2->setText(saltext);

            }
        }








        else if (!conndb())
        {
            QMessageBox::information(this, "Error", "Database connection failed");
        }
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->comboBox_3->clear();
        QSqlQuery ltest;
        ltest.prepare("SELECT patname, testtype FROM lab");
            if (ltest.exec())
        {
            while (ltest.next())
            {
                QString patname = ltest.value("patname").toString();
                QString testtype = ltest.value("testtype").toString();
                if(ui->comboBox->findText(patname)==-1)
                {
                ui->comboBox->addItem(patname);
                }
                ui->comboBox_2->addItem(testtype);
            }
        }
        else
        {
            qDebug()<<"Failed";
        }

}



void staffwindow::on_pushButton_11_clicked() //FOR WRITING TO FILE
{
        QFile file("staffnotes.txt");
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

void staffwindow::on_pushButton_12_clicked() //FOR READING FROM FILE
{
    QFile file("staffnotes.txt");

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


void staffwindow::on_departmentcombo_currentIndexChanged(int index) //This function checks if the first combobox (which is department) selected value changes and based on the current selected value will select the doctor registered in that department for appointment
{
    //Structure for appointment
    struct app{
        QString department;
        QString name;
        QString pat;
    };
    app ap;
    ap.department = ui->departmentcombo->currentText(); //storing value of the first combobox (which is department) into ap.department
    conndb();    //For connecting Database
    if(conndb()) //If connection successful
    {
        resetrad();
        QSqlQuery appo; //Using QSqlQuery to execute the query by creating the object appo
        appo.prepare("SELECT name FROM dcredentials WHERE department=:department"); //Retrieves data from database and selects doctors from the department which is selected
        appo.bindValue(":department",ap.department ); //binds/replaces value
        ui->doctorcombo->setCurrentIndex(0); //sets the index of the doctor combobox to 0
        if(appo.exec())       //if query executes
        {
            ui->doctorcombo->clear(); // Clear previously set text before adding items

            while(appo.next())  //if query finds values
            {
                ap.name = appo.value("name").toString(); //stores name of doctor in ap.name
                ui->doctorcombo->addItem(ap.name);  //Adds the name of the doctor in the doctors combobox
            }
        }
        appo.prepare("SELECT name FROM patient"); //Another query for selecting the name of patients from the patient table
        if(appo.exec()) // If query executes
        {
            ui->patientcombo->clear();   //clears the patient combobox before adding items

            while(appo.next()) //If query finds values
            {
                ap.pat=appo.value("name").toString(); //stores name of patient in ap.pat
                ui->patientcombo->addItem(ap.pat); //Adds the name of patient in the combobox
            }
        }
    }
    else if(!conndb()) //If database doesnt connect
    {
        QMessageBox::warning(this,"Connection Failed","Failed to connect to database"); //Messagebox to display that the connection failed
    }
}

void staffwindow::on_pushButton_9_clicked() //When the submit button is clicked
{
    QString tim; //tim variable for storing time (wanted to create it as a Time datatype variable and name it as time but due to various errors and issues changed it to QString and tim)
    QString day = ui->daycombo->currentText(); //Day which stores the selected day of the day combobox

    //Checks which radio button is checked and stores the text of that radio in tim
    if(ui->radioButton->isChecked())
    {
        tim = ui->radioButton->text();
    }
    else if(ui->radioButton_2->isChecked())
    {
        tim= ui->radioButton_2->text();
    }
    else if(ui->radioButton_3->isChecked())
    {
        tim=ui->radioButton_3->text();
    }
    else if(ui->radioButton_4->isChecked())
    {
        tim=ui->radioButton_4->text();
    }
    else if(ui->radioButton_5->isChecked())
    {
        tim=ui->radioButton_5->text();
    }
    else if(ui->radioButton_6->isChecked())
    {
        tim=ui->radioButton_6->text();
    }
    QString docname = ui->doctorcombo->currentText(); //stores the selected name of doctor into the docname variable
    QString patname = ui->patientcombo->currentText(); //Stores the selected name of patient into the patname variable
    QString department = ui->departmentcombo->currentText(); //Stores the selected department into the department variable

    conndb(); //Connects database
    QSqlQuery a; //QSqlQuery and its object a
    a.prepare("INSERT INTO appointment (department, day, tim, docname, patname) VALUES (:department, :day, :tim, :docname, :patname)"); //Stores the value into the database table appointment and its columns department,day,tim,docname,patname
    //Binding Values
    a.bindValue(":department", department);
    a.bindValue(":day", day);
    a.bindValue(":tim", tim);
    a.bindValue(":docname", docname);
    a.bindValue(":patname", patname);

    if (a.exec()) //If query executes
    {
        // Remove the selected time from the radio
        if(ui->radioButton->isChecked())
        {
            ui->radioButton->setDisabled(true);
        }
        else if(ui->radioButton_2->isChecked())
        {
            ui->radioButton_2->setDisabled(true);
        }
        else if(ui->radioButton_3->isChecked())
        {
            ui->radioButton_3->setDisabled(true);
        }
        else if(ui->radioButton_4->isChecked())
        {
            ui->radioButton_4->setDisabled(true);
        }
        else if(ui->radioButton_5->isChecked())
        {
            ui->radioButton_5->setDisabled(true);
        }
        else if(ui->radioButton_6->isChecked())
        {
            ui->radioButton_6->setDisabled(true);
        }

        // Check if all radio buttons are disabled
        int disabled= Isdisabled();
        if (disabled==6)
        {
            // Remove the selected day if there are no more times
            ui->daycombo->removeItem(ui->daycombo->currentIndex());
        }
    }
    else
    {
        QMessageBox::warning(this, "Failed", "Query Failed"); //If query fails
    }
}

void staffwindow::on_daycombo_currentIndexChanged(int index) //Executes when the day combobox executes, it uses the trtime function defined in the beginning for checking if appointment is already booked
{
    resetrad();       //resets radiobuttons

    //trtime function is called in each case and the "day" and the value stored in the doctor combobox and the department is passed as arguments and same happens with the rest of the cases.
    switch(index)  //switch statement working on the index of the day combobox
    {
    //In each case the value of index is evaluated which is mentioned after the keyword case
    case 1:
        trtime("Monday", ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    case 2:
        trtime("Tuesday",ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    case 3:
        trtime("Wednesday",ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    case 4:
        trtime("Thursday",ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    case 5:
        trtime("Friday",ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    case 6:
        trtime("Saturday",ui->doctorcombo->currentText(), ui->departmentcombo->currentText());
        break;
    }
}

void staffwindow::on_doctorcombo_currentIndexChanged(int index)
{
    ui->daycombo->setCurrentIndex(0);
}


void staffwindow::on_pushButton_clicked()
{
    QString currenthour = QTime::currentTime().toString("hh");
    QString currentminute = QTime::currentTime().toString("mm");
    QString currentsec = QTime::currentTime().toString("ss");

    double hourtosec = currenthour.toInt() * 3600.0;
    double minutetosec = currentminute.toInt() * 60.0;
    int sec = currentsec.toInt();
    stlogoutt = hourtosec + minutetosec + sec;
    qDebug() << "Before: " << stlogoutt;
    stlogoutt = stlogoutt / 3600.0;
    double diff = stlogoutt - stlogint;
    QString workday = QDate::currentDate().toString("yyyy-MM-dd");
    conndb();
    QSqlQuery work;

    work.prepare("SELECT hoursworked FROM salary WHERE name=:staffname AND date=:workday AND hoursworked IS NOT NULL");
    work.bindValue(":staffname", loggedinstaffname);
    work.bindValue(":workday", workday);

    if (work.exec() && work.next())
    {
        double storedhours = work.value(0).toDouble();

        work.prepare("UPDATE salary SET hoursworked = :diff WHERE name = :staffname AND date = :workday");
        work.bindValue(":staffname", loggedinstaffname);
        work.bindValue(":workday", workday);
        work.bindValue(":diff", diff + storedhours);
        if (!work.exec())
        {
            qDebug() << "UPDATE failed:";
        }
    }
    else
    {
        work.prepare("INSERT INTO salary (name, hoursworked, date) VALUES (:name, :hoursworked, :date)");
        work.bindValue(":name", loggedinstaffname);
        work.bindValue(":hoursworked", diff);
        work.bindValue(":date", workday);
        if (!work.exec())
        {
            qDebug() << "INSERT failed:";
        }
    }
    hide();
    MainWindow *mw= new MainWindow;
    mw->show();

}
void staffwindow::on_pushButton_10_clicked()
{
    QSqlQuery update;
    update.prepare("UPDATE lab SET status=:status, result=:result WHERE patname=:name AND testtype=:testname");
    update.bindValue(":name",ui->comboBox->currentText());
    update.bindValue(":status",ui->comboBox_3->currentText());
    update.bindValue(":result",ui->comboBox_4->currentText());
    update.bindValue(":testname",ui->comboBox_2->currentText());
    if(!update.exec())
    {
        qDebug()<<"Failed";
    }
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->comboBox_4->setCurrentIndex(0);
}


void staffwindow::on_pushButton_3_clicked()
{
    if(conndb())
    {
        QSqlQuery uplab;
        uplab.prepare("SELECT * FROM lab");
        if(uplab.exec())
        {
            ui->tableWidget_9->clearContents();
            ui->tableWidget_9->setRowCount(0);

            while(uplab.next())
            {

                QString name=uplab.value("patname").toString();
                QString doctor=uplab.value("docname").toString();
                QString testtype=uplab.value("testtype").toString();
                QString status=uplab.value("status").toString();
                QString requestdate=uplab.value("requestdate").toString();
                QString result=uplab.value("result").toString();
                int row=ui->tableWidget_9->rowCount();
                ui->tableWidget_9->insertRow(row);
                ui->tableWidget_9->setItem(row,0,new QTableWidgetItem (name));

                ui->tableWidget_9->setItem(row,1,new QTableWidgetItem (testtype));
                ui->tableWidget_9->setItem(row,2,new QTableWidgetItem (testtype));
                ui->tableWidget_9->setItem(row,3,new QTableWidgetItem (status));
                ui->tableWidget_9->setItem(row,4,new QTableWidgetItem (requestdate));
                ui->tableWidget_9->setItem(row,5,new QTableWidgetItem (result));

            }
        }

    }
}


void staffwindow::on_pushButton_4_clicked()
{
    conndb();
    if(conndb())
    {
        struct doc{
            QString name;
            QString code;
            QString department;
            QString gender;
            QDate dob;
            qint64 cnic;
            qint64 contact;
            QString address;
        };
        doc de;
        QSqlQuery pa;
        pa.prepare("SELECT * FROM dcredentials");

        if(pa.exec())
        {

            ui->tableWidget_5->clearContents();
            ui->tableWidget_5->setRowCount(0);
            while(pa.next())
            {
                de.name = pa.value("name").toString();
                de.code=pa.value("code").toString();
                de.department = pa.value("department").toString();
                de.gender = pa.value("gender").toString();
                de.cnic = pa.value("cnic").toLongLong();
                de.contact = pa.value("contact").toLongLong();
                de.dob= pa.value("dob").toDate();


                int row= ui->tableWidget_5->rowCount();
                ui->tableWidget_5->insertRow(row);
                ui->tableWidget_5->setItem(row,0,new QTableWidgetItem (de.name));
                ui->tableWidget_5->setItem(row,1,new QTableWidgetItem (de.code));
                ui->tableWidget_5->setItem(row,2,new QTableWidgetItem (de.department));
                ui->tableWidget_5->setItem(row,3,new QTableWidgetItem (de.gender));
                 ui->tableWidget_5->setItem(row,4,new QTableWidgetItem (QString::number(de.cnic)));
                ui->tableWidget_5->setItem(row,5,new QTableWidgetItem (de.dob.toString("dd/MM/yyyy")));
                ui->tableWidget_5->setItem(row,6,new QTableWidgetItem (QString::number(de.contact)));


                ui->tableWidget_5->update();
                row++;
            }
            ui->tableWidget_5->resizeRowsToContents();
            ui->tableWidget_5->resizeColumnsToContents();

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


void staffwindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    int tablerow = ui->tableWidget_5->rowCount();
    int tablecolumn = ui->tableWidget_5->columnCount();

    for (int row = 0; row < tablerow; ++row)
    {
        bool matchFound = false;

        for (int column = 0; column < tablecolumn; ++column)
        {
            QTableWidgetItem* item = ui->tableWidget_5->item(row, column);

            if (item && !item->text().isEmpty() && item->text().contains(arg1, Qt::CaseInsensitive))
            {
                // If the cell's non-empty text contains the search text
                matchFound = true;
                break;  // Stop checking other columns for this row
            }
        }

        // Show or hide the row based on whether a match was found
        ui->tableWidget_5->setRowHidden(row, !matchFound);
    }
}


void staffwindow::on_pushButton_2_clicked()
{

    if(conndb())
    {
        QDate dob;
        dob=ui->dateEdit->date();
        QSqlQuery up;
        up.prepare("INSERT INTO patient (doctor, name, code, gender, dob, cnic, contact) VALUES (:docname,:patname,:code, :gender, :dob, :cnic, :contact)");
        up.bindValue(":docname",ui->assigdoc->currentText());
        up.bindValue(":patname",ui->lineEdit_78->text());
        up.bindValue(":code",patcode);
        up.bindValue(":gender",ui->lineEdit_80->text());
        up.bindValue(":dob",dob.toString("yyyy-MM-dd"));
        up.bindValue(":cnic",ui->lineEdit_77->text());
        up.bindValue(":contact",ui->lineEdit_123->text());
        if(!up.exec())
        {
            qDebug()<<"Failed";
        }
    }
}




void staffwindow::on_patdocdep_currentIndexChanged(int index)
{
    QString department = ui->patdocdep->currentText();
    conndb();    //For connecting Database
    if(conndb()) //If connection successful
    {

        QSqlQuery appo; //Using QSqlQuery to execute the query by creating the object appo
        appo.prepare("SELECT name FROM dcredentials WHERE department=:department"); //Retrieves data from database and selects doctors from the department which is selected
        appo.bindValue(":department",department ); //binds/replaces value

        ui->assigdoc->setCurrentIndex(0); //sets the index of the doctor combobox to 0
        if(appo.exec())       //if query executes
        {
            ui->assigdoc->clear(); // Clear previously set text before adding items

            while(appo.next())  //if query finds values
            {
                QString name=appo.value("name").toString();
                ui->assigdoc->addItem(name);  //Adds the name of the doctor in the doctors combobox
            }
        }
        else
        {
            qDebug()<<"FAiled";
        }
    }
}


void staffwindow::on_lineEdit_78_editingFinished()
{
    if(!ui->lineEdit_78->text().isEmpty())
    {
        patcode=QUuid::createUuid().toString().mid(1,8);
        ui->lineEdit_124->setText(patcode);
    }
}


void staffwindow::on_pushButton_5_clicked()
{
    if(conndb())
    {
    QSqlQuery tab;
    tab.prepare("SELECT * FROM patient");

        if(tab.exec())
        {

            ui->tableWidget_4->clearContents();
            ui->tableWidget_4->setRowCount(0);
            while(tab.next())
            {

                QString doctor= tab.value("doctor").toString();
                QString patient= tab.value("name").toString();
                QString code=tab.value("code").toString();
                QString gender= tab.value("gender").toString();
                QDate dob=tab.value("dob").toDate();
                QString cnic=tab.value("cnic").toString();
                QString contact=tab.value("contact").toString();
                int row= ui->tableWidget_4->rowCount();
                ui->tableWidget_4->insertRow(row);
                ui->tableWidget_4->setItem(row,0,new QTableWidgetItem (patient));
                ui->tableWidget_4->setItem(row,1,new QTableWidgetItem (code));
                ui->tableWidget_4->setItem(row,2,new QTableWidgetItem (doctor));
                ui->tableWidget_4->setItem(row,3,new QTableWidgetItem (dob.toString("dd/MM/yyyy")));
                ui->tableWidget_4->setItem(row,4,new QTableWidgetItem (cnic));
                ui->tableWidget_4->setItem(row,5,new QTableWidgetItem (gender));
                ui->tableWidget_4->setItem(row,6,new QTableWidgetItem (contact));


                ui->tableWidget_4->update();
                row++;
            }
            ui->tableWidget_4->resizeRowsToContents();
            ui->tableWidget_4->resizeColumnsToContents();

        }
        else if(!tab.exec())
        {
            QMessageBox::information(this,"Contact Admin","Query Failed");
        }

    }

    else if(!conndb())
    {
        QMessageBox::critical(this,"Connection Failure", "Connection to Database failed");
    }

}


void staffwindow::on_lineEdit_2_textChanged(const QString &arg1)
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


void staffwindow::on_pushButton_6_clicked()
{
    QSqlQuery app;
    app.prepare("SELECT * FROM appointment");
    app.bindValue("doctor",loggedindocname);
        if(app.exec())
    {

        ui->tableWidget_7->clearContents();
        ui->tableWidget_7->setRowCount(0);
        while(app.next())
        {

            QString doctor= app.value("docname").toString();
            QString patient= app.value("patname").toString();
            QString day=app.value("day").toString();
            QString tim=app.value("tim").toString();
            int row= ui->tableWidget_7->rowCount();
            ui->tableWidget_7->insertRow(row);
            ui->tableWidget_7->setItem(row,0,new QTableWidgetItem (patient));
            ui->tableWidget_7->setItem(row,1,new QTableWidgetItem (doctor));
            ui->tableWidget_7->setItem(row,2,new QTableWidgetItem (day));
            ui->tableWidget_7->setItem(row,3,new QTableWidgetItem (tim));


            ui->tableWidget_7->update();
            row++;
        }
        ui->tableWidget_7->resizeRowsToContents();
        ui->tableWidget_7->resizeColumnsToContents();
    }
}



void staffwindow::on_pushButton_7_clicked()
{
    // Assuming conndb() is a function that establishes a database connection

    if (conndb())
    {
        QSqlQuery patientQuery("SELECT name FROM patient");

        if (patientQuery.exec())
        {
            // Clear the existing items in the combo box
            ui->comboBill->clear();

            // Iterate through the results and add names to the combo box
            while (patientQuery.next())
            {
                QString patientName = patientQuery.value("name").toString();
                ui->comboBill->addItem(patientName);
            }
        }
        else
        {
            // Handle query execution error
            qDebug() << "Error executing patient query:" ;
        }
    }
    else
    {
        // Handle database connection error
        qDebug() << "Database connection failed";
    }
}

//void staffwindow::on_comboBill_currentIndexChanged(int index)
//{

//    }



void staffwindow::on_pushButton_8_clicked()
{
    double totalAppPrice=0.0;
    double totalLabPrice=0.0;
    double totalPrice=0.0;
    QString userName= ui->comboBill->currentText();
    QSqlQuery billQuery;
    billQuery.prepare("SELECT department, COUNT(*) AS numAppointments "
                      "FROM appointment "
                      "WHERE patname=:patientName "
                      "GROUP BY department");
    billQuery.bindValue(":patientName", userName);

    if (billQuery.exec()) {


        while (billQuery.next()) {
            QString department = billQuery.value("department").toString();
            int numAppointments = billQuery.value("numAppointments").toInt();

            // Process the price based on the department
            double deptPrice = 0.0;

            if (department == "Cardiology")
                deptPrice = 1500.0;
            else if (department == "Dermatology")
                deptPrice = 1250.0;
            else if (department == "Emergency Medicine")
                deptPrice = 1200.0;
            else if (department == "Endocrinology")
                deptPrice = 1300.0;
            else if (department == "Gastroenterology")
                deptPrice = 1450.0;
            else if (department == "General Surgery")
                deptPrice = 1350.0;
            else if (department == "Internal Medicine")
                deptPrice = 1550.0;
            else if (department == "Neurology")
                deptPrice = 1800.0;
            else if (department == "Obstetrics and Gynecology")
                deptPrice = 1900.0;
            else if (department == "Oncology")
                deptPrice = 1850.0;
            else if (department == "Ophthalmology")
                deptPrice = 1750.0;
            else if (department == "Orthopedics")
                deptPrice = 1550.0;
            else if (department == "Pediatrics")
                deptPrice = 1100.0;
            else if (department == "Psychiatry")
                deptPrice = 1700.0;
            else if (department == "Pulmonary Medicine")
                deptPrice = 2000.0;
            else if (department == "Rheumatology")
                deptPrice = 1600.0;
            else if (department == "Urology")
                deptPrice = 1650.0;

            // Calculate total price for the specific department
            double totalPriceForApp = numAppointments * deptPrice;
            totalAppPrice += totalPriceForApp;

            // Display or use information as needed
            qDebug() << "Department: " << department << ", Num Appointments: " << numAppointments << ", Total Price: " << totalPriceForApp;
        }

        qDebug() << "Total Appointments Price: " << totalAppPrice;
    } else {
        // Handle query execution error
        qDebug() << "Error executing appointment query:";
    }

    if (conndb())
    {
        QSqlQuery labQuery;
        labQuery.prepare("SELECT testtype, COUNT(*) AS numTests "
                         "FROM lab "
                         "WHERE patname = :userName "
                         "GROUP BY testtype");
        labQuery.bindValue(":userName", userName);

        if (labQuery.exec())
        {


            while (labQuery.next())
            {
                QString testType = labQuery.value("testtype").toString();
                int testCount = labQuery.value("numTests").toInt();

                // Process the price based on the test type
                double testPrice = 0.0;

                if (testType == "CBC")
                    testPrice = 500.0;
                else if (testType == "BMP")
                    testPrice = 300.0;
                else if (testType == "Blood Type")
                    testPrice = 250.0;
                else if (testType == "Urinalysis")
                    testPrice = 350.0;
                else if (testType == "Allergy Test")
                    testPrice = 320.0;
                else if (testType == "Hormone Test")
                    testPrice = 400.0;
                else if (testType == "ECG")
                    testPrice = 450.0;
                else if (testType == "X-Ray")
                    testPrice = 700.0;
                else if (testType == "Ultrasound")
                    testPrice = 650.0;
                else if (testType == "CT Scan")
                    testPrice = 600.0;
                else if (testType == "Glucose Test")
                    testPrice = 550.0;
                else if (testType == "Covid Test")
                    testPrice = 150.0;
                // Add other test types...

                // Calculate total price for the specific test type
                double totalPriceForTest = testPrice * testCount;
                totalLabPrice += totalPriceForTest;

                // Display or use information as needed
                qDebug() << "Test Type: " << testType << ", Count: " << testCount << ", Total Price: " << totalPriceForTest;

            }

            qDebug() << "Total Lab Price: " << totalLabPrice;
        }
        else
        {
            // Handle query execution error
            qDebug() << "Error executing lab query:";
        }
    }
    else
    {
        // Handle database connection error
        qDebug() << "Database connection failed";
    }
    QString resultText = "Patient Name: "+ userName+
                         "\n\nTotal Appointments Price: " + QString::number(totalAppPrice) +
                         "\n\nTotal Lab Price: " + QString::number(totalLabPrice);
    ui->textBrowser_19->setText(resultText);
    totalPrice=totalAppPrice+totalLabPrice;
    QString fullbill= "\nYour Full Bill is: "+ QString::number(totalPrice);
    ui->textBrowser_20->setText(fullbill);
}



