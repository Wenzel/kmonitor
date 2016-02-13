#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

#include "sysinfo.h"
#include "processinfo.h"
#include "mmap.h"
#include "selectprocessview.h"
#include "maptypemodel.h"

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
    MapTypeModel* m_map_type_model;
    std::vector<MMap> m_maps;


private slots:
    void selectProcess();
    void showProcessMap(int pid);

};

#endif // MAINWINDOW_H
