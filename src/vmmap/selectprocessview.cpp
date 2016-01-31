#include <QDesktopWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <algorithm>

#include "selectprocessview.h"
#include "ui_selectprocessview.h"

SelectProcessView::SelectProcessView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectProcessView)
{
    ui->setupUi(this);
    center();
    refresh();
    QStringList headers;
    headers << "Name" << "PID" << "User";
    ui->tableWidget_selectprocess->setHorizontalHeaderLabels(headers);
}

SelectProcessView::~SelectProcessView()
{
    delete ui;
}

void SelectProcessView::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.3;
    int y=dw.height()*0.5;
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

void SelectProcessView::refresh()
{
    m_processes = processList();
    ui->tableWidget_selectprocess->setColumnCount(3);
    ui->tableWidget_selectprocess->setRowCount(m_processes.size());
    std::vector<ProcessInfo>::iterator it;
    for (it = m_processes.begin() ; it != m_processes.end(); it++)
    {
        int row = std::distance(m_processes.begin(), it);
        // name
        QString name = QString::fromUtf8(it->name().data(), it->name().size());
        QTableWidgetItem* item_name = new QTableWidgetItem(name);
        ui->tableWidget_selectprocess->setItem(row, 0, item_name);
        // pid
        QString pid = QString::number(it->pid());
        QTableWidgetItem* item_pid = new QTableWidgetItem(pid);
        ui->tableWidget_selectprocess->setItem(row, 1, item_pid);
        // user
        QString user = QString::fromUtf8(it->userName().data(), it->userName().size());
        QTableWidgetItem* item_user = new QTableWidgetItem(user);
        ui->tableWidget_selectprocess->setItem(row, 2, item_user);
    }
}
