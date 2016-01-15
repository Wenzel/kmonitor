#ifndef PROCESSDETAILVIEW_H
#define PROCESSDETAILVIEW_H

#include <QTabWidget>

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

private:
    const ProcessInfo& m_pinfo;
    Ui::ProcessDetailView *ui;
};

#endif // PROCESSDETAILVIEW_H
