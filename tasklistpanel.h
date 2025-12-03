#ifndef TASKLISTPANEL_H
#define TASKLISTPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QPointer>

#include <QtitanGrid.h>

class TaskListPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListPanel(QWidget* parent = nullptr);

private:
    void initUI();
    void createButtons();
    void createGrid();
    void setupModel();

    QPointer<QPushButton> btnStop;
    QPointer<QPushButton> btnDelete;
    QPointer<QPushButton> btnEdit;
    QPointer<Qtitan::Grid> grid;
    QPointer<QStandardItemModel> model;
    QPointer<QVBoxLayout> mainLayout;
    QPointer<QHBoxLayout> buttonsLayout;
};

#endif // TASKLISTPANEL_H
