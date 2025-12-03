#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox.h>

#include <QtnRibbonMainWindow.h>
#include <QtnRibbonBar.h>
#include <QtnRibbonPage.h>
#include <QtnRibbonGroup.h>
#include <QtnRibbonButton.h>
#include <QtnGrid.h>
#include <QtitanDocking.h>

#include "TreeModel.h"
#include "TaskListPanel.h"
#include "LogPanel.h"

class MainWindow : public Qtitan::RibbonMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

    QTabWidget* m_tabWidget;
    QTabWidget* m_bottomTabs;
    TreeModel* m_treeModel;

    Qtitan::TreeGrid* m_treeGrid;
    Qtitan::DockPanelManager* m_dockManager;
    Qtitan::DockWidgetPanel* m_bottomDock;

    TaskListPanel* m_taskPanel;
    LogPanel* m_logPanel;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initToolbar();
    void initWorkspace();
    void initBottomDockPanel();
    QWidget* initBasesTab();

private Q_SLOTS:
    void pressButton();
    void pressSettingsButton();
    void onTaskListToggled();
    void onLogToggled();
};

#endif // MAINWINDOW_H
