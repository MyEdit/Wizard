#include "TaskListPanel.h"

TaskListPanel::TaskListPanel(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void TaskListPanel::initUI()
{
    mainLayout = new QVBoxLayout(this);

    createButtons();
    createGrid();

    setLayout(mainLayout);
}

void TaskListPanel::createButtons()
{
    buttonsLayout = new QHBoxLayout();

    btnStop = new QPushButton();
    btnStop->setFixedSize(40, 40);
    btnStop->setIconSize(QSize(32, 32));
    btnStop->setIcon(QIcon(":/icons/Resources/Stop.svg"));
    btnStop->setToolTip("Стоп");

    btnDelete = new QPushButton();
    btnDelete->setFixedSize(40, 40);
    btnDelete->setIconSize(QSize(32, 32));
    btnDelete->setIcon(QIcon(":/icons/Resources/Remove.svg"));
    btnDelete->setToolTip("Удалить");

    btnEdit = new QPushButton();
    btnEdit->setFixedSize(40, 40);
    btnEdit->setIconSize(QSize(32, 32));
    btnEdit->setIcon(QIcon(":/icons/Resources/Change.svg"));
    btnEdit->setToolTip("Изменить");

    buttonsLayout->addWidget(btnStop);
    buttonsLayout->addWidget(btnDelete);
    buttonsLayout->addWidget(btnEdit);
    buttonsLayout->addStretch();

    mainLayout->addLayout(buttonsLayout);
}

void TaskListPanel::createGrid()
{
    grid = new Qtitan::Grid(this);
    grid->setViewType(Qtitan::Grid::TableView);

    setupModel();

    Qtitan::GridTableView* view = grid->view<Qtitan::GridTableView>();
    view->setModel(model);
    view->tableOptions().setColumnAutoWidth(true);

    mainLayout->addWidget(grid);
}

void TaskListPanel::setupModel()
{
    model = new QStandardItemModel(3, 3, this);

    model->setHeaderData(0, Qt::Horizontal, "Задача");
    model->setHeaderData(1, Qt::Horizontal, "Файл");
    model->setHeaderData(2, Qt::Horizontal, "Статус");

    model->setItem(0, 0, new QStandardItem("XXXX-XXXX-XXXX"));
    model->setItem(0, 1, new QStandardItem("file.db"));
    model->setItem(0, 2, new QStandardItem("Готово"));
}
