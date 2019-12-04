#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>
#include <QTextCodec>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtSql/QSqlRecord>
#include<QtSql/QSqlError>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QSqlDatabase::addDatabase("QSQLITE", "MyDBConnectionName");


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}

void Dialog::on_pushButton_clicked()
{
    if( QSqlDatabase::contains( "MyDBConnectionName" ) )
        {
            QSqlDatabase db1 = QSqlDatabase::database( "MyDBConnectionName" );
        db1.setDatabaseName("chambers");
        if (!db1.open())
        {
            qDebug() << "Cannot open database" << db1.lastError();
        }

        QSqlQuery query(db1);
        QString   str  = "CREATE TABLE параметры(number TEXT(12), "
                         "name   TEXT(15), "
                         "type  TEXT(12), "
                         "volume  TEXT(12), "
                         "sensibility TEXT(3));";
        if (!query.exec(str)) {
            qDebug() << "Unable to create a table";
        }

        QString strF =
              "INSERT INTO  параметры (number, name, type, volume, sensibility) "
              "VALUES('%1', '%2', '%3', '%4', '%5');";

        str = strF.arg("1")
                  .arg("БМК-500")
                  .arg("Сферическая")
                  .arg("500")
                  .arg("0.05");
        if (!query.exec(str)) {
            qDebug() << "Unable to do insert opeation";
        }

        if (!query.exec("SELECT * FROM параметры;")) {
            qDebug() << "Unable to execute query - exiting";
            }
        //Reading of the data
        QSqlRecord rec = query.record();
        QString        nNumber = 0;
        QString    strName;
        QString    strPhone;
        QString    strEmail;
        QString    strSensebility;

        while (query.next()) {
            nNumber  = query.value(rec.indexOf("number")).toString();
            strName  = query.value(rec.indexOf("name")).toString();
            strPhone = query.value(rec.indexOf("type")).toString();
            strEmail = query.value(rec.indexOf("volume")).toString();
            strSensebility = query.value(rec.indexOf("sensibility")).toString();

            qDebug() << nNumber <<  strName << "\t"
                     << strPhone << "\t" << strEmail << "\t" << strSensebility;

            qDebug() << db1.tables();
            //ui->lineEdit->setText("strName"+" "+"strPhone"+" "+"strEmail"+" "+"strSensebility");
            db1.close();
            QSqlDatabase::removeDatabase("chambers");
            }
        }
        else qDebug()<<"jopa";

}
void Dialog::cppSlot(QString str)
{
    ui->label->setText(str);
    //close();
}

void Dialog::on_pushButton_3_clicked()
{
    if (QSqlDatabase::contains("MyDBConnectionName"))
    {
        QSqlDatabase db=QSqlDatabase::database("MyDBConnectionName");
        db.setDatabaseName("chambers");
        if (!db.open())
        {
            qDebug()<<"db dont opened";
        }
QSqlQuery query(db);
        QString str=
                "INSERT INTO параметры (number, name, type, volume, sensibility)"
          "VALUES ('%1','%2','%3','%4','%5');";

              if( !query.prepare(str) )
              {
              qDebug() << "Prepare:" << query.lastError();
              }
              QString str1=str.arg("2")
                              .arg("БМК-50")
                              .arg("Сферическая")
                              .arg("50")
                              .arg("0.005");

              //query.prepare(str1);


        if (!query.exec(str1))
        {
            qDebug()<<"ne ne ne";
        }
    }
}

void Dialog::on_pushButton_4_clicked()
{
    if (QSqlDatabase::contains("MyDBConnectionName"))
    {
        QSqlDatabase db=QSqlDatabase::database("MyDBConnectionName");
        db.setDatabaseName("chambers");
        if (!db.open())
        {
            qDebug()<<"db dont opened";
        }

         QSqlQuery query(db);
        if (!query.exec("SELECT * FROM параметры;")) {
            qDebug() << "Unable to execute query - exiting";
            }
        //Reading of the data
        QSqlRecord rec = query.record();
        QString        nNumber = 0;
        QString    strName;
        QString    strPhone;
        QString    strEmail;
        QString    strSensebility;

        while (query.next()) {
            nNumber  = query.value(rec.indexOf("number")).toString();
            strName  = query.value(rec.indexOf("name")).toString();
            strPhone = query.value(rec.indexOf("type")).toString();
            strEmail = query.value(rec.indexOf("volume")).toString();
            strSensebility = query.value(rec.indexOf("sensibility")).toString();

            qDebug() << nNumber <<  strName << "\t"
                     << strPhone << "\t" << strEmail << "\t" << strSensebility;

            qDebug() << db.tables();
            //ui->lineEdit->setText("strName"+" "+"strPhone"+" "+"strEmail"+" "+"strSensebility");
            //db.close();
           // QSqlDatabase::removeDatabase("chambers");
            }

    }
}

void Dialog::on_pushButton_5_clicked()
{
    if (QSqlDatabase::contains("MyDBConnectionName"))
    {
        QSqlDatabase db=QSqlDatabase::database("MyDBConnectionName");
        db.setDatabaseName("chambers");
        if (!db.open())
        {
            qDebug()<<"db is not open";
        }

        QSqlQuery query(db);
        //QString str = "UPDATE параметры SET name=%1";
        //QString str1=str.arg(ui->lineEdit->text());
        query.prepare("UPDATE параметры SET name=:j WHERE number=:i");
        query.bindValue(":i",ui->lineEdit->text());
        query.bindValue(":j",ui->lineEdit_2->text());
        if (!query.exec())
        {
            qDebug()<<"ne ne ne";
        }



    }
}

void Dialog::on_pushButton_6_clicked()
{
    if (QSqlDatabase::contains("MyDBConnectionName"))
    {
        QSqlDatabase db = QSqlDatabase::database("MyDBConnectionName");
        db.setDatabaseName("chambers");
        if(!db.open())
        {
            qDebug()<<"db is not open";
        }
        QSqlQuery query(db);
        QString str = ("DELETE FROM параметры WHERE number=%1;");
        QString str1=str.arg(ui->lineEdit->text());
        if (!query.exec(str1))
        {
            qDebug()<<"dont delete";
        }
    }
}
