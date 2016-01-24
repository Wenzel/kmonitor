#ifndef PROCESSDETAILVIEW_H
#define PROCESSDETAILVIEW_H

#include <QTabWidget>
#include <QStandardItemModel>
#include <QStandardItem>

#include "processinfo.h"


namespace Ui {
class ProcessDetailView;
}

class ProcessDetailView : public QTabWidget
{
    Q_OBJECT

public:
    explicit ProcessDetailView(ProcessInfo& pinfo, QWidget *parent = 0);
    ~ProcessDetailView();
    void center();
    void timerEvent(QTimerEvent *event);
    void display();
    void setupImageView();
    void setupEnvironmentView();
    void setupOpenedFiles();
    void setupDetails();
    void setupPages();

private:
    Ui::ProcessDetailView *ui;
    ProcessInfo m_pinfo;
    QStandardItemModel* m_env_model;
    int m_timerId;
};

#endif // PROCESSDETAILVIEW_H
