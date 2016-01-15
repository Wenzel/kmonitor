#include <QDesktopWidget>

#include "processdetailview.h"
#include "ui_processdetailview.h"

ProcessDetailView::ProcessDetailView(const ProcessInfo &pinfo, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ProcessDetailView),
    m_pinfo(pinfo),
    m_env_model(nullptr)
{
    ui->setupUi(this);
    center();
    QString name = QString::fromUtf8(pinfo.name().data(), pinfo.name().size());
    setWindowTitle(name);
    setupImageView();
    setupEnvironmentView();
}

ProcessDetailView::~ProcessDetailView()
{
    delete ui;
    delete m_env_model;
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

void ProcessDetailView::setupEnvironmentView()
{
    const std::unordered_map<std::string, std::string> environ = m_pinfo.environ();
    ui->tableWidet_env->setRowCount(environ.size());
    ui->tableWidet_env->setColumnCount(2);

    std::unordered_map<std::string, std::string>::const_iterator iter;
    for (iter = environ.begin(); iter != environ.end(); iter++)
    {
        QString str_key = QString::fromUtf8(iter->first.data(), iter->first.size());
        QString str_value = QString::fromUtf8(iter->second.data(), iter->second.size());
        QTableWidgetItem* item_key = new QTableWidgetItem(str_key);
        QTableWidgetItem* item_value = new QTableWidgetItem(str_value);
        int row = std::distance(environ.begin(), iter);
        ui->tableWidet_env->setItem(row, 0, item_key);
        ui->tableWidet_env->setItem(row, 1, item_value);
    }
}
