#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

#include "processmodel.h"
#include "socketunixmodel.h"
#include "processdetailview.h"

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
    QMenu* m_menu;
    ProcessDetailView* m_processdetailview;
    // temporary variable to pass data between slots
    QModelIndex m_selected_process;

    void center();

private slots:
    void customMenu(const QPoint& point);
    void showProcessDetail();
};

#endif // MAINWINDOW_H
