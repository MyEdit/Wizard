#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPointer>

#include <QtitanGrid.h>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = nullptr);

private slots:
    void onSelectFolderClicked();

private:
    void initUI();
    void initTabSerials();
    void initPathSection();
    void initSerialNumbersSection();
    void initConnections();

    QLayout* initBottomButtons();

    QPointer<QTabWidget> tabs;
    QPointer<QWidget> tabConnection;
    QPointer<QWidget> tabSerials;
    QPointer<QLineEdit> pathEdit;
    QPointer<QCheckBox> chkPackage;
    QPointer<QGroupBox> groupSerials;
    QPointer<Qtitan::Grid> grid;
    QPointer<QStandardItemModel> model;

    QPointer<QPushButton> okBtn;
    QPointer<QPushButton> cancelBtn;
    QPointer<QPushButton> btnAdd;
    QPointer<QPushButton> btnRemove;
    QPointer<QPushButton> btnDetect;
    QPointer<QPushButton> btnSelectFolder;

    QPointer<QVBoxLayout> mainLayout;
    QPointer<QVBoxLayout> tabLayout;
    QPointer<QVBoxLayout> groupLayout;
};

#endif // SETTINGSDIALOG_H
