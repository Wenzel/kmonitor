#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void selectProcess();
    void showProcessMap(const QString& name);

};

#endif // MAINWINDOW_H
