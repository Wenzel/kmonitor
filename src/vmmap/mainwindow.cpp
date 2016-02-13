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
    m_select_process_view = new SelectProcessView(nullptr);
    connect(m_select_process_view, SIGNAL(processChoosen(int)), this, SLOT(showProcessMap(int)));
    m_select_process_view->show();
}


void MainWindow::showProcessMap(int pid)
{
    // delete subwindow
    m_select_process_view->close();
    delete m_select_process_view;
    m_select_process_view = nullptr;

    m_pinfo = new ProcessInfo(pid);

    // fill header
    // name
    QString name = QString::fromUtf8(m_pinfo->name().data(), m_pinfo->name().size());
    ui->label_process_name->setText(name);
    // icon
    QIcon icon = QIcon::fromTheme(name, QIcon());
    ui->label_icon->setPixmap(icon.pixmap(48));
    // pid
    QString str_pid = QString::number(pid);
    ui->label_process_pid->setText(str_pid);
}

