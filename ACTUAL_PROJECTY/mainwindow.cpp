#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QString>
#include<globalvar.h>
#include<QMessageBox>
#include<staffwindow.h>
#include<QPixmap>
#include<QMovie>
#include<QTime>
#include<QRegularExpression>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<docwindow.h>
#include<QUuid>
using namespace std;
//function for checking email
bool em(QString &email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"); //used for setting the format for checking if enterd data is email or not which consists of digits and numbers a dot and an @ symbol
    return regex.match(email).hasMatch(); //checks if the entered email is valid or not and returns a boolean value
}
bool conndb()
{
    QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("hospital db");
    if(db.open())
    {
        return true;
    }
    else if(!db.open())
    {
        return false;
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //for background
    QImage bgpic("C:/Users/Hamza Athar/Documents/ACTUAL_PROJECTY/resources/bg.jpg");
    ui->bg_pic->setScaledContents(true);
    ui->bg_pic->setPixmap(QPixmap::fromImage(bgpic));
    ui->bg_pic->setVisible(true);

    QMovie* gif1 = new QMovie("C:/Users/Hamza Athar/Documents/ACTUAL_PROJECTY/resources/penguin.gif");
    ui->labelGif->setMovie(gif1);
    gif1->start();
    ui->labelGif->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//FOR DOCTOR LOGIN
void MainWindow::on_pushButton_9_clicked()
{

    //Connecting Database
    conndb();
    //Checks if database is open
    if(conndb())
    {
        // Retrieves input from user for login

        QString email=ui->ldocemail->text();
        QString password=ui->ldocpass->text();
        loggedindocemail=email;
        if(em(email)==true  && !email.isEmpty() && !password.isEmpty())
        {


        // Retrieving our user data from the database generated from wamp using sql query

        QSqlQuery q;
        q.prepare("SELECT email,password,name FROM dcredentials WHERE email= :email AND password= :password"); //Selects email password from dcredentials where it will only extract those values which are == to the entered password or email

        q.bindValue(":email",email);
        q.bindValue(":password",password);



        // If credentials were found in the database
        if(q.exec() && q.next())
        {
            loggedindocname=q.value("name").toString();
            qDebug()<<loggedindocname;
            QMessageBox::information(this,"Success","Login Successful");
            QString currenthour = QTime::currentTime().toString("hh");
            QString currentminute = QTime::currentTime().toString("mm");
            QString currentsec = QTime::currentTime().toString("ss");
            double hourtosec = currenthour.toInt() * 3600.0;
            double minutetosec = currentminute.toInt() * 60.0;
            int sec = currentsec.toInt();
            dclogint = hourtosec + minutetosec + sec;  // Replace stlogint with dclogint
            dclogint = dclogint / 3600.0;
            qDebug() << dclogint;

            hide();
            docwindow dw;
            dw.setModal(true);
            dw.exec();

        }
        //If credentials were NOT found in the database
        else
        {
            QMessageBox::warning(this,"Failed","Invalid Credentials");
        }
        }
        else
        {
        QMessageBox::warning(this,"Error","Fill out all the fields and use correct format for email");
        }
    }
    else
    {
        QMessageBox::critical(this,"Not Connected","Database is not connected");
    }
}

//FOR DOCTORS SIGN UP
void MainWindow::on_pushButton_11_clicked()
{
    //Connecting Database
    conndb();

    //Checks if database is open
    if(conndb())
    {
        QString doccode=QUuid::createUuid().toString().mid(1,8);
        qDebug()<<doccode;
        // Retrieving input from user for signup
        QString name=ui->sdocname->text();
        QString email=ui->sdocemail->text();
        QString password=ui->sdocpass->text();
        QString department=ui->sdocdep->currentText();

        //if email is valid and all the line edits arent empty
        if(em(email)==true && !name.isEmpty() && !email.isEmpty() && !password.isEmpty() && !department.isEmpty()) //checks if all the line edit boxes have some value entered in them and if the entered email follows the format of an email
        {
        // The following four lines clear the details entered in the signup bar
        ui->sdocname->clear();
        ui->sdocemail->clear();
        ui->sdocpass->clear();
        ui->sdocdep->setCurrentIndex(0);

        // Inserting our input data into the database generated from wamp using sql query

        QSqlQuery q;
        q.prepare("INSERT INTO dcredentials(name,code,email,password,department)" "Values(:name,:code,:email,:password,:department)" );
        q.bindValue(":name",name);
        q.bindValue(":email",email);
        q.bindValue(":password",password);
        q.bindValue(":department", department);
        q.bindValue(":code",doccode);



        // If Signup Successful/Information is stored successfully
        if(q.exec()){

            QMessageBox::information(this,"Success","SignUp Successful");

        }
        //If signup is unsuccessful/Information is not stored
        else if(!q.exec()){
            QMessageBox::warning(this,"Failed","SignUp Failed");
        }
        }
        //if email is not valid or a input field is empty
        else
        {
        QMessageBox::warning(this,"Error","Fill out all the fields and use correct format for email");
        }
    }
    //if Database is not connected
    else{
        QMessageBox::critical(this,"Not Connected","Database is not connected");
    }
}

//FOR STAFF LOGIN
void MainWindow::on_pushButton_10_clicked()
{
    conndb();

    if(conndb())
    {
        // Retrieving input from user for login

        QString email=ui->lstaffemail->text();
        loggedinstaffemail=email;
        QString password=ui->lstaffpass->text();

        if(em(email)==true  && !email.isEmpty() && !password.isEmpty())
        {


        // Retrieving our user data from the database generated from wamp using sql query

        QSqlQuery q;
        q.prepare("SELECT email,password,name FROM scredentials WHERE email= :email AND password= :password");

        q.bindValue(":email",email);
        q.bindValue(":password",password);


        // If Login is Successful/Entered credentials are correct
        if(q.exec() && q.next()){
            loggedinstaffname=q.value("name").toString();
            QMessageBox::information(this,"Success","Login Successful");

            QString currenthour= QTime::currentTime().toString("hh");
            QString currentminute= QTime::currentTime().toString("mm");
            QString currentsec=QTime::currentTime().toString("ss");
            double hourtosec= currenthour.toInt()*3600.0;
            double minutetosec=currentminute.toInt()*60.0;
            int sec=currentsec.toInt();
            stlogint= hourtosec+minutetosec+sec;
            stlogint= stlogint/3600.0;
            qDebug()<<stlogint;

            hide();
            staffwindow sw;
            sw.setModal(true);
            sw.exec();

        }
        //If Login in Unsuccessful/Entered credentials are incorrect
        else
        {
            QMessageBox::warning(this,"Failed","Invalid Credentials");
        }
        }
        else
        {
        QMessageBox::warning(this,"Error","Fill out all the fields and use correct format for email");
        }
    }
    else{
        QMessageBox::critical(this,"Not Connected","Database is not connected");
    }
}

//FOR STAFF SIGNUP
void MainWindow::on_pushButton_12_clicked()
{
    conndb();

    if(conndb())
    {
        QString staffcode=QUuid::createUuid().toString().mid(1,8);
        qDebug()<<"Staffcode"<<staffcode;
        // Retrieving input from user for signup
        QString name=ui->sstaffname->text();
        QString email=ui->sstaffemail->text();
        QString password=ui->sstaffpass->text();

        //if email is valid and variables created aren't empty
        if(em(email)==true && !name.isEmpty() && !email.isEmpty() && !password.isEmpty() )
        {
        //For clearing the input fields
        ui->sstaffname->clear();
        ui->sstaffemail->clear();
        ui->sstaffpass->clear();

        // Inserting our input data into the database generated from wamp using sql query

        QSqlQuery q;
        q.prepare("INSERT INTO scredentials(name,code,email,password)" "Values(:name,:code,:email,:password)" );
        q.bindValue(":name",name);
        q.bindValue(":email",email);
        q.bindValue(":password",password);
        q.bindValue(":code",staffcode);
        if(q.exec()){

            QMessageBox::information(this,"Success","SignUp Successful");

        }
        else{
            QMessageBox::information(this,"Failed","SignUp Failed");
        }
        }
        //If email is not valid
        else
        {
        QMessageBox::warning(this,"Error","Fill out all the fields and use correct format for email");
        }
    }
    //If database is not connected
    else{
        QMessageBox::critical(this,"Not Connected","Database is not connected");
    }
}

