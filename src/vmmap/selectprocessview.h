#ifndef SELECTPROCESSVIEW_H
#define SELECTPROCESSVIEW_H

#include <QWidget>
#include <vector>
#include <sysinfo.h>


namespace Ui {
class SelectProcessView;
}

class SelectProcessView : public QWidget
{
    Q_OBJECT

public:
    explicit SelectProcessView(QWidget *parent = 0);
    ~SelectProcessView();

private:
    void center();

    Ui::SelectProcessView *ui;
    std::vector<ProcessInfo> m_processes;

private slots:
    void refresh();
};

#endif // SELECTPROCESSVIEW_H
