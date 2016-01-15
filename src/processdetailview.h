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
    explicit ProcessDetailView(const ProcessInfo& pinfo, QWidget *parent = 0);
    ~ProcessDetailView();
    void center();
    void setupImageView();
    void setupEnvironmentView();

private:
    Ui::ProcessDetailView *ui;
    const ProcessInfo& m_pinfo;
    QStandardItemModel* m_env_model;
};

#endif // PROCESSDETAILVIEW_H
