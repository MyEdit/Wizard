#include "mainwindow.h"
#include "SettingsDialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : Qtitan::RibbonMainWindow(parent)
{
    Qtitan::RibbonBar* ribbon = ribbonBar();
    ribbon->setFont(QFont("Segoe UI", 8));
    ribbon->setFrameThemeEnabled();
    this->initToolbar();
    this->initWorkspace();
    this->initBottomDockPanel();
    this->setMinimumSize(500, 400);
}

MainWindow::~MainWindow()
{
    //Empty
}

void MainWindow::initToolbar()
{
    Qtitan::RibbonBar* ribbon = ribbonBar();
    Qtitan::RibbonPage* page = ribbon->addPage(tr("Главная"));
    Qtitan::RibbonGroup* groupData = page->addGroup(tr("Данные"));
    Qtitan::RibbonGroup* groupSettings = page->addGroup(tr("Настройки"));
    Qtitan::RibbonGroup* groupView = page->addGroup(tr("Вид"));

    QMenu* downloadPopup = new QMenu(ribbon);
    connect(downloadPopup->addAction(QIcon(":/icons/Resources/DownloadDB.svg"), tr("Скачать только базы")), SIGNAL(triggered()), this, SLOT(pressButton()));
    connect(downloadPopup->addAction(QIcon(":/icons/Resources/DownloadLic.svg"), tr("Скачать только лицензии")), SIGNAL(triggered()), this, SLOT(pressButton()));

    QAction* aboutBtn = ribbon->addAction(QIcon(":/icons/Resources/about.png"), tr(""), Qt::ToolButtonIconOnly);
    QAction* minimizeBtn = ribbon->addAction(QIcon(":/icons/Resources/ribbonMinimize.png"), tr(""), Qt::ToolButtonIconOnly);
    QAction* updateBtn = groupData->addAction(QIcon(":/icons/Resources/Update.svg"), tr("Обновить информацию"), Qt::ToolButtonTextUnderIcon);
    QAction* downloadBtn = groupData->addAction(QIcon(":/icons/Resources/FileDownloading.svg"), tr("Скачать"), Qt::ToolButtonTextUnderIcon, downloadPopup);
    QAction* settingsBtn = groupSettings->addAction(QIcon(":/icons/Resources/Settings.svg"), tr("Настройки"), Qt::ToolButtonTextUnderIcon);
    QAction* taskListBtn = groupView->addAction(QIcon(":/icons/Resources/TaskList.svg"), tr("Список задач"), Qt::ToolButtonTextUnderIcon);
    QAction* logBtn = groupView->addAction(QIcon(":/icons/Resources/Log.svg"), tr("Протокол работы"), Qt::ToolButtonTextUnderIcon);

    aboutBtn->setToolTip(tr("<b>О программе</b><br/><br/>Информация о программе, версии и защите прав"));
    taskListBtn->setCheckable(true);
    taskListBtn->setChecked(true);
    logBtn->setCheckable(true);
    logBtn->setChecked(true);

    connect(updateBtn, SIGNAL(triggered()), this, SLOT(pressButton()));
    connect(downloadBtn, SIGNAL(triggered()), this, SLOT(pressButton()));
    connect(settingsBtn, SIGNAL(triggered()), this, SLOT(pressSettingsButton()));
    connect(taskListBtn, SIGNAL(triggered()), this, SLOT(onTaskListToggled()));
    connect(logBtn, SIGNAL(triggered()), this, SLOT(onLogToggled()));
    connect(aboutBtn, SIGNAL(triggered()), this, SLOT(pressButton()));
    connect(minimizeBtn, SIGNAL(triggered()), this, SLOT(pressButton()));
}

void MainWindow::initWorkspace()
{
    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setIconSize(QSize(32, 32));
    m_tabWidget->addTab(this->initBasesTab(), QIcon(":/icons/Resources/DB.svg"), tr("Базы данных"));
    m_tabWidget->addTab(this->initBasesTab(), QIcon(":/icons/Resources/Program.svg"), tr("Программные продукты"));
    setCentralWidget(m_tabWidget);
}

void MainWindow::initBottomDockPanel()
{
    m_dockManager = new Qtitan::DockPanelManager(this);

    m_bottomDock = new Qtitan::DockWidgetPanel(tr("Служебные панели"), m_dockManager);
    m_bottomDock->setAutoHide(false);

    m_bottomTabs = new QTabWidget();
    m_bottomTabs->setTabPosition(QTabWidget::South);

    m_taskPanel = new TaskListPanel(this);
    m_logPanel = new LogPanel(this);

    m_bottomTabs->addTab(m_taskPanel, tr("Список задач"));
    m_bottomTabs->addTab(m_logPanel, tr("Протокол"));

    m_bottomDock->setWidget(m_bottomTabs);

    m_dockManager->insertDockPanel(m_bottomDock, Qtitan::BottomDockPanelArea);

    m_bottomDock->showPanel();
}

QWidget* MainWindow::initBasesTab()
{
    QWidget* basesTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(basesTab);

    m_treeGrid = new Qtitan::TreeGrid(basesTab);
    m_treeGrid->setViewType(Qtitan::TreeGrid::TreeView);
    Qtitan::GridTreeView* view = m_treeGrid->view<Qtitan::GridTreeView>();

    m_treeModel = new TreeModel(this);
    TreeItem* root = m_treeModel->rootItem();
    TreeItem* smeta = m_treeModel->addNode({"", "SmetaWIZARD4", "", ""}, root);
    TreeItem* gos = m_treeModel->addNode({"", "государственные", "", ""}, smeta);
    m_treeModel->addNode({"", "1984 прейскуранты v4.0", "", "15.08.2022"}, gos);
    m_treeModel->addNode({"", "1984 доп. к ерер, вып. 1, 2, 3", "Ленинград", "30.01.2022"}, gos);

    view->setModel(m_treeModel);
    view->beginUpdate();

    Qtitan::GridTableColumn* checkCol = (Qtitan::GridTableColumn*)view->getColumn(0);
    if (checkCol)
    {
        checkCol->setEditorType(Qtitan::GridEditor::CheckBox);
        checkCol->setCheckable(true);
        checkCol->editorRepository()->setEditable(true);
        checkCol->editorRepository()->setEditorActivationPolicy(Qtitan::GridEditor::ActivateByClick);
    }

    view->bestFit(Qtitan::FitToHeaderAndContent);
    view->expandToLevel(5);
    view->expandAll();
    view->endUpdate();

    layout->addWidget(m_treeGrid);
    basesTab->setLayout(layout);

    return basesTab;
}

void MainWindow::pressButton()
{
    QMessageBox::warning
        (
            this,
            QObject::tr("Предупреждение"),
            QObject::tr("Не реализовано"),
            QMessageBox::Ok
        );
}

void MainWindow::pressSettingsButton()
{
    SettingsDialog dlg(this);
    dlg.exec();
}

void MainWindow::onTaskListToggled()
{
    QAction* action = qobject_cast<QAction*>(sender());
    bool show = action->isChecked();
    int idx = m_bottomTabs->indexOf(m_taskPanel);

    if (show)
    {
        if (idx == -1)
        {
            m_bottomTabs->addTab(m_taskPanel, tr("Список задач"));
        }

        m_bottomTabs->setCurrentWidget(m_taskPanel);
    }
    else
    {
        if (idx != -1)
        {
            m_bottomTabs->removeTab(idx);
        }
    }

    if (m_bottomTabs->count() == 0)
    {
        m_bottomDock->closePanel();
    }
    else
    {
        m_bottomDock->showPanel();
    }
}

void MainWindow::onLogToggled()
{
    QAction* action = qobject_cast<QAction*>(sender());
    bool show = action->isChecked();
    int idx = m_bottomTabs->indexOf(m_logPanel);

    if (show)
    {
        if (idx == -1)
        {
            m_bottomTabs->addTab(m_logPanel, tr("Протокол"));
        }

        m_bottomTabs->setCurrentWidget(m_logPanel);
    }
    else
    {
        if (idx != -1)
        {
            m_bottomTabs->removeTab(idx);
        }
    }

    if (m_bottomTabs->count() == 0)
    {
        m_bottomDock->closePanel();
    }
    else
    {
        m_bottomDock->showPanel();
    }
}
