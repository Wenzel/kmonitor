#include <QDesktopWidget>


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_select_process_view(nullptr)
{
    ui->setupUi(this);
    center();
    connect(ui->actionExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(ui->actionSelectProcess, SIGNAL(triggered(bool)), this, SLOT(selectProcess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.5;
    int y=dw.height()*0.6;
    this->setFixedSize(x,y);

    // center
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

void MainWindow::selectProcess()
{
    if (m_select_process_view != nullptr)
        delete m_select_process_view;
    m_select_process_view = new SelectProcessView(nullptr);
    m_select_process_view->show();
}
