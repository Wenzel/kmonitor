#include <QDesktopWidget>

#include "processdetailview.h"
#include "ui_processdetailview.h"

ProcessDetailView::ProcessDetailView(const ProcessInfo &pinfo, QWidget *parent) :
    QTabWidget(parent),
    m_pinfo(pinfo),
    ui(new Ui::ProcessDetailView)
{
    ui->setupUi(this);
    center();
    setupImageView();
}

ProcessDetailView::~ProcessDetailView()
{
    delete ui;
}

void ProcessDetailView::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.4;
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

void ProcessDetailView::setupImageView()
{
    QString exe = QString::fromUtf8(m_pinfo.exe().data(), m_pinfo.exe().size());
    ui->lineEdit_exe->setText(exe);
    QString cmdline = QString::fromUtf8(m_pinfo.cmdline().data(), m_pinfo.cmdline().size());
    ui->lineEdit_cmdline->setText(cmdline);
    QString cwd = QString::fromUtf8(m_pinfo.cwd().data(), m_pinfo.cwd().size());
    ui->lineEdit_cwd->setText(cwd);
}

