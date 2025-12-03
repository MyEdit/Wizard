#include "LogPanel.h"

LogPanel::LogPanel(QWidget* parent)
    : QWidget(parent)
{
    initUI();
}

void LogPanel::initUI()
{
    createGrid();

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(grid);

    setLayout(mainLayout);
}

void LogPanel::createGrid()
{
    grid = new Qtitan::Grid(this);
    grid->setViewType(Qtitan::Grid::TableView);

    setupModel();

    Qtitan::GridTableView* view = grid->view<Qtitan::GridTableView>();
    view->setModel(model);
    view->tableOptions().setColumnAutoWidth(true);
}

void LogPanel::setupModel()
{
    model = new QStandardItemModel(5, 3, this);

    model->setHeaderData(0, Qt::Horizontal, "Время");
    model->setHeaderData(1, Qt::Horizontal, "Тип");
    model->setHeaderData(2, Qt::Horizontal, "Сообщение");

    model->setItem(0, 0, new QStandardItem("14:21:23"));
    model->setItem(0, 1, new QStandardItem("ИНФО"));
    model->setItem(0, 2, new QStandardItem("Старт"));
}
