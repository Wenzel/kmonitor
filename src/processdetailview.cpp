#include <QDesktopWidget>

#include "processdetailview.h"
#include "ui_processdetailview.h"

ProcessDetailView::ProcessDetailView(ProcessInfo &pinfo, QWidget *parent) :
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
    setupOpenedFiles();
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

    int x=dw.width()*0.5;
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
    // IDs
    ui->lineEdit_pid->setText(QString::number(m_pinfo.pid()));
    ui->lineEdit_ppid->setText(QString::number(m_pinfo.ppid()));
    ui->lineEdit_pgid->setText(QString::number(m_pinfo.pgid()));
    ui->lineEdit_sid->setText(QString::number(m_pinfo.sid()));
    QString tty_device = QString::fromUtf8(m_pinfo.ttyNr().data(), m_pinfo.ttyNr().size());
    ui->lineEdit_tty->setText(tty_device);
    ui->lineEdit_tpgid->setText(QString::number(m_pinfo.tpgid()));
    QDateTime currenttime = QDateTime::currentDateTime();
    QDateTime starttime = currenttime.addSecs(- m_pinfo.startTime()); // add negative diff
    ui->dateTimeEdit_starttime->setDateTime(starttime);
    QString state = QString::fromUtf8(m_pinfo.state().data(), m_pinfo.state().size());
    ui->label_state->setText(state);

    // Uids/Gids
    std::vector<int> uids = m_pinfo.uids();
    std::vector<int> gids = m_pinfo.gids();
    for (int i = 0 ; i < 4 ; i++)
    {
        ui->tableWidget_uids->setItem(0, i, new QTableWidgetItem(QString::number(uids[i])));
        ui->tableWidget_uids->setItem(1, i, new QTableWidgetItem(QString::number(gids[i])));
    }

    // paths
    QString exe = QString::fromUtf8(m_pinfo.exe().data(), m_pinfo.exe().size());
    ui->lineEdit_exe->setText(exe);
    QString cmdline = QString::fromUtf8(m_pinfo.cmdline().data(), m_pinfo.cmdline().size());
    ui->lineEdit_cmdline->setText(cmdline);
    QString cwd = QString::fromUtf8(m_pinfo.cwd().data(), m_pinfo.cwd().size());
    ui->lineEdit_cwd->setText(cwd);
}

void ProcessDetailView::setupEnvironmentView()
{
    const std::unordered_map<std::string, std::string>& environ = m_pinfo.environ();
    ui->tableWidet_env->setRowCount(environ.size());

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

void ProcessDetailView::setupOpenedFiles()
{
    const std::unordered_map<int, std::string> fds = m_pinfo.fds();
    ui->tableWidget_fds->setRowCount(fds.size());

    std::unordered_map<int, std::string>::const_iterator iter;
    for (iter = fds.begin(); iter != fds.end(); iter++)
    {
        QString fd = QString::number(iter->first);
        QString path = QString::fromUtf8(iter->second.data(), iter->second.size());
        QTableWidgetItem* item_fd = new QTableWidgetItem(fd);
        QTableWidgetItem* item_path = new QTableWidgetItem(path);
        int row = std::distance(fds.begin(), iter);
        ui->tableWidget_fds->setItem(row, 0, item_fd);
        ui->tableWidget_fds->setItem(row, 1, item_path);
    }
}
