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
    m_processdetailview = nullptr;

    // build custom menu
    m_menu = new QMenu();
    m_menu->addAction("Detail", this, SLOT(showProcessDetail()));
    // set custom menu
    ui->processView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->processView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(customMenu(const QPoint&)));

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

MainWindow::~MainWindow()
{
    delete ui;
    delete m_processmodel;
    delete m_socketunixmodel;
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

void MainWindow::customMenu(const QPoint& point)
{
    QModelIndex index = ui->processView->indexAt(point);
    if (index.isValid())
    {
        // store the index to be used by future slots
        m_selected_process = index;
        m_menu->exec(QCursor::pos());
    }
}

void MainWindow::showProcessDetail()
{
    // get the previously stored index
    ProcessInfo p = m_processmodel->dataAt(m_selected_process.row());
    // free previous view
    if (m_processdetailview != nullptr)
        delete m_processdetailview;
    m_processdetailview = new ProcessDetailView(p);
    m_processdetailview->show();
}
