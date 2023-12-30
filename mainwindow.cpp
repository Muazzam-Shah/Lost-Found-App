#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminpage.h"
// #include "studentpage.h"
// #include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Do not create and show Adminpage and StudentPage here
    // adminPage = new Adminpage(this);
    // studentPage = new StudentPage(this);

    // Connect signals for buttons in main window
    // connect(ui->btnAdmin, SIGNAL(clicked()), this, SLOT(on_btnAdmin_clicked()));
    // connect(ui->btnStudent, SIGNAL(clicked()), this, SLOT(on_btnStudent_clicked()));
}

void MainWindow::on_btnAdmin_clicked()
{
    qDebug() << "Admin button clicked";
    // if (!adminPage) {
    // adminPage = new Adminpage(this);
    // connect(adminPage, SIGNAL(destroyed()), this, SLOT(show()));
    // }

    // studentPage->hide();
    // adminPage->setFixedSize(400, 300);
    // adminPage->exec();

    Adminpage adminpage;
    adminpage.exec();
    // Dialog dialog;
    // dialog.exec();
}

void MainWindow::on_btnStudent_clicked()
{
    qDebug() << "student button clicked";
    // if (!studentPage) {
    //     studentPage = new Studentpage(this);
    //     // connect(studentPage, SIGNAL(destroyed()), this, SLOT(show()));
    // }

    // adminPage->hide();
    // studentPage->setFixedSize(400, 300);
    // studentPage->show();

    Studentpage studentpage;
    studentpage.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
