#include <QStyle>
#include <QDesktopWidget>
#include <QTableView>

#include <sysinfo.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    center();

    // process
    m_processmodel = new ProcessModel(this);
    m_proxy_processmodel = new QSortFilterProxyModel(this);
    m_proxy_processmodel->setSourceModel(m_processmodel);
    ui->processView->setModel(m_proxy_processmodel);

    // socket unix
    m_socketunixmodel = new SocketUNIXModel(this);
    m_proxy_socketunixmodel = new QSortFilterProxyModel(this);
    m_proxy_socketunixmodel->setSourceModel(m_socketunixmodel);
    ui->connView->setModel(m_proxy_socketunixmodel);
}

void MainWindow::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.7;
    int y=dw.height()*0.7;
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

MainWindow::~MainWindow()
{
    delete ui;
    delete m_processmodel;
    delete m_socketunixmodel;
}
