#ifndef LOGPANEL_H
#define LOGPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QPointer>

#include <QtitanGrid.h>

class LogPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LogPanel(QWidget* parent = nullptr);

private:
    void initUI();
    void createGrid();
    void setupModel();

    QPointer<Qtitan::Grid> grid;
    QPointer<QStandardItemModel> model;
    QPointer<QVBoxLayout> mainLayout;
};

#endif // LOGPANEL_H
