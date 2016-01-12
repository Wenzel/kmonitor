#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

#include "processmodel.h"
#include "socketunixmodel.h"

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
    Ui::MainWindow *ui;
    ProcessModel* m_processmodel;
    SocketUNIXModel* m_socketunixmodel;
    QSortFilterProxyModel* m_proxy_processmodel;
    QSortFilterProxyModel* m_proxy_socketunixmodel;

    void center();
};

#endif // MAINWINDOW_H
