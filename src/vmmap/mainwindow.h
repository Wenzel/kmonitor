#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sysinfo.h"
#include "processinfo.h"
#include "selectprocessview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void center();

    Ui::MainWindow *ui;
    SelectProcessView* m_select_process_view;
    ProcessInfo* m_pinfo;
private slots:
    void selectProcess();
    void showProcessMap(int pid);

};

#endif // MAINWINDOW_H
