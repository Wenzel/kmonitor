#include <QDesktopWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <sstream>

#include "processdetailview.h"
#include "ui_processdetailview.h"

ProcessDetailView::ProcessDetailView(ProcessInfo& pinfo, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ProcessDetailView),
    m_pinfo(pinfo),
    m_env_model(nullptr)
{
    ui->setupUi(this);
    m_timerId = startTimer(1000);
    center();
    QString name = QString::fromUtf8(pinfo.name().data(), pinfo.name().size());
    setWindowTitle(name);
    display();
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

void ProcessDetailView::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    m_pinfo.needUpdate();
    display();
}

void ProcessDetailView::display()
{
    setupImageView();
    setupEnvironmentView();
    setupOpenedFiles();
    setupDetails();
}

void ProcessDetailView::setupImageView()
{
    // groupbox 1
    QString name = QString::fromUtf8(m_pinfo.name().data(), m_pinfo.name().size());
    ui->lineEdit_name->setText(name);
    QString exe = QString::fromUtf8(m_pinfo.exe().data(), m_pinfo.exe().size());
    ui->lineEdit_exe->setText(exe);
    const std::vector<std::string>& cmdline = m_pinfo.cmdline();
    std::ostringstream imploded;
    std::copy(cmdline.begin(), cmdline.end(), std::ostream_iterator<std::string>(imploded, " "));
    QString qcmdline = QString::fromUtf8(imploded.str().data(), imploded.str().size());
    ui->lineEdit_cmdline->setText(qcmdline);

    QString cwd = QString::fromUtf8(m_pinfo.cwd().data(), m_pinfo.cwd().size());
    ui->lineEdit_cwd->setText(cwd);
    QString state = QString::fromUtf8(m_pinfo.state().data(), m_pinfo.state().size());
    ui->lineEdit_state->setText(state);
    QString num_threads = QString::number(m_pinfo.numThreads());
    ui->lineEdit_num_threads->setText(num_threads);

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

}

void ProcessDetailView::setupEnvironmentView()
{
    ui->tableWidet_env->clear();
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
    ui->tableWidget_fds->clear();
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

void ProcessDetailView::setupDetails()
{
    // fault
    QString minflt = QString::number(m_pinfo.minflt());
    ui->label_minflt->setText(minflt);

    QString majflt = QString::number(m_pinfo.majflt());
    ui->label_majflt->setText(majflt);

    QString cminflt = QString::number(m_pinfo.cminflt());
    ui->label_cminflt->setText(cminflt);

    QString cmajflt = QString::number(m_pinfo.cmajflt());
    ui->label_cmajflt->setText(cmajflt);

    // time
    QString utime = QString::number(m_pinfo.utime());
    ui->label_utime->setText(utime);

    QString stime = QString::number(m_pinfo.stime());
    ui->label_stime->setText(stime);

    QString guest_time = QString::number(m_pinfo.guestTime());
    ui->label_guest_time->setText(guest_time);

    QString cutime = QString::number(m_pinfo.cutime());
    ui->label_cutime->setText(cutime);

    QString cstime = QString::number(m_pinfo.cstime());
    ui->label_cstime->setText(cstime);

    QString cguest_time = QString::number(m_pinfo.cguestTime());
    ui->label_cguest_time->setText(cguest_time);

    // scheduling
    QString priority = QString::number(m_pinfo.priority());
    ui->label_priority->setText(priority);

    QString rt_priority = QString::number(m_pinfo.rtPriority());
    ui->label_rt_priority->setText(rt_priority);

    QString nice = QString::number(m_pinfo.nice());
    ui->label_nice->setText(nice);

    QString processor = QString::number(m_pinfo.processor());
    ui->label_processor->setText(processor);

    QString policy = QString::fromUtf8(m_pinfo.policy().data(), m_pinfo.policy().size());
    ui->label_policy->setText(policy);

    QString delayacct_blkio_ticks = QString::number(m_pinfo.delayacctBlkioTicks());
    ui->label_delayacct_blkio_ticks->setText(delayacct_blkio_ticks);

    QString wchan_addr = QString::number(m_pinfo.wchanAddr(), 16);
    ui->label_wchan_addr->setText(wchan_addr);

    QString wchan_name = QString::fromUtf8(m_pinfo.wchanName().data(), m_pinfo.wchanName().size());
    ui->label_wchan_name->setText(wchan_name);

    // start/end*
    QString start_code = QString::number(m_pinfo.startCode(), 16);
    ui->label_start_code->setText(start_code);

    QString end_code = QString::number(m_pinfo.endCode(), 16);
    ui->label_end_code->setText(end_code);

    QString esp = QString::number(m_pinfo.kstkEsp(), 16);
    ui->label_kstkesp->setText(esp);

    QString eip = QString::number(m_pinfo.kstkEip(), 16);
    ui->label_kstkeip->setText(eip);

    QString start_data = QString::number(m_pinfo.startData(), 16);
    ui->label_start_data->setText(start_data);

    QString end_data = QString::number(m_pinfo.endData(), 16);
    ui->label_end_data->setText(end_data);

    QString start_brk = QString::number(m_pinfo.startBrk(), 16);
    ui->label_start_brk->setText(start_brk);

    QString start_arg = QString::number(m_pinfo.startArg(), 16);
    ui->label_start_arg->setText(start_arg);

    QString end_arg = QString::number(m_pinfo.endArg(), 16);
    ui->label_end_arg->setText(end_arg);

    QString start_env = QString::number(m_pinfo.startEnv(), 16);
    ui->label_start_env->setText(start_env);

    QString end_env = QString::number(m_pinfo.endEnv(), 16);
    ui->label_end_env->setText(end_env);

    // Uids/Gids
    std::vector<int> uids = m_pinfo.uids();
    std::vector<int> gids = m_pinfo.gids();
    for (int i = 0 ; i < 4 ; i++)
    {
        ui->tableWidget_uids->setItem(0, i, new QTableWidgetItem(QString::number(uids[i])));
        ui->tableWidget_uids->setItem(1, i, new QTableWidgetItem(QString::number(gids[i])));
    }

    // flags
    unsigned int flags = m_pinfo.flags();
    if (flags & PF_DUMPCORE)
        ui->label_pf_dumpcore->setEnabled(true);
    else if (flags & PF_EXITING)
        ui->label_pf_exiting->setEnabled(true);
    else if (flags & PF_EXITPIDONE)
        ui->label_pf_exitpidone->setEnabled(true);
    else if (flags & PF_FORKNOEXEC)
        ui->label_pf_forknoexec->setEnabled(true);
    else if (flags & PF_FREEZER_SKIP)
        ui->label_pf_freezer_skip->setEnabled(true);
    else if (flags & PF_FROZEN)
        ui->label_pf_frozen->setEnabled(true);
    else if (flags & PF_FSTRANS)
        ui->label_pf_fstrans->setEnabled(true);
    else if (flags & PF_KSWAPD)
        ui->label_pf_kswapd->setEnabled(true);
    else if (flags & PF_KTHREAD)
        ui->label_pf_kthread->setEnabled(true);
    else if (flags & PF_LESS_THROTTLE)
        ui->label_pf_less_throttle->setEnabled(true);
    else if (flags & PF_MCE_EARLY)
        ui->label_pf_mce_early->setEnabled(true);
    else if (flags & PF_MCE_PROCESS)
        ui->label_pf_mce_process->setEnabled(true);
    else if (flags & PF_MEMALLOC)
        ui->label_pf_memalloc->setEnabled(true);
    else if (flags & PF_MEMALLOC_NOIO)
        ui->label_pf_memalloc_noio->setEnabled(true);
    else if (flags & PF_MUTEX_TESTER)
        ui->label_pf_mutex_tester->setEnabled(true);
    else if (flags & PF_NOFREEZE)
        ui->label->setEnabled(true);
    else if (flags & PF_NO_SETAFFINITY)
        ui->label_pf_no_setaffinity->setEnabled(true);
    else if (flags & PF_NPROC_EXCEEDED)
        ui->label_pf_nproc_exceeded->setEnabled(true);
    else if (flags & PF_RANDOMIZE)
        ui->label_pf_randomize->setEnabled(true);
    else if (flags & PF_SIGNALED)
        ui->label_pf_signaled->setEnabled(true);
    else if (flags & PF_SUPERPRIV)
        ui->label_pf_superpriv->setEnabled(true);
    else if (flags & PF_SUSPEND_TASK)
        ui->label_pf_suspend_task->setEnabled(true);
    else if (flags & PF_SWAPWRITE)
        ui->label_pf_swapwrite->setEnabled(true);
    else if (flags & PF_USED_ASYNC)
        ui->label_pf_used_async->setEnabled(true);
    else if (flags & PF_USED_MATH)
        ui->label_pf_used_math->setEnabled(true);
    else if (flags & PF_VCPU)
        ui->label_pf_vcpu->setEnabled(true);
    else if (flags & PF_WQ_WORKER)
        ui->label_pf_wq_worker->setEnabled(true);
}
