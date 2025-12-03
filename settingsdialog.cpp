#include "SettingsDialog.h"
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Настройки");
    resize(700, 500);
    setMinimumSize(500, 400);

    initUI();
}

void SettingsDialog::initUI()
{
    initTabSerials();
    initBottomButtons();

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabs);
    mainLayout->addLayout(initBottomButtons());

    setLayout(mainLayout);
    initConnections();
}

void SettingsDialog::initTabSerials()
{
    tabs = new QTabWidget(this);

    tabSerials = new QWidget(this);
    tabConnection = new QWidget();
    tabLayout = new QVBoxLayout(tabSerials);

    initPathSection();
    initSerialNumbersSection();

    tabs->addTab(tabSerials, "Серийные номера и загрузка");
    tabs->addTab(tabConnection, "Настройки подключения");
}

void SettingsDialog::initPathSection()
{
    QHBoxLayout* pathLayout = new QHBoxLayout();

    pathEdit = new QLineEdit();

    btnSelectFolder = new QPushButton();
    btnSelectFolder->setFixedSize(32, 32);
    btnSelectFolder->setIconSize(QSize(20, 20));
    btnSelectFolder->setIcon(QIcon(":/icons/Resources/Change.svg"));
    btnSelectFolder->setToolTip("Выбрать папку");

    pathLayout->addWidget(new QLabel("Папка по умолчанию:"));
    pathLayout->addWidget(pathEdit);
    pathLayout->addWidget(btnSelectFolder);

    tabLayout->addLayout(pathLayout);

    chkPackage = new QCheckBox("Формировать пакет обновлений db5update");
    chkPackage->setChecked(true);
    tabLayout->addWidget(chkPackage);
}

void SettingsDialog::initSerialNumbersSection()
{
    groupSerials = new QGroupBox("Серийные номера:");
    groupLayout = new QVBoxLayout(groupSerials);

    QHBoxLayout* btnsLayout = new QHBoxLayout();

    btnAdd = new QPushButton(QIcon(":/icons/Resources/Add.svg"), "");
    btnRemove = new QPushButton(QIcon(":/icons/Resources/Remove.svg"), "");
    btnDetect = new QPushButton("Определить серийный номер");

    btnAdd->setFixedSize(42, 42);
    btnAdd->setIconSize(QSize(28, 28));
    btnRemove->setFixedSize(42, 42);
    btnRemove->setIconSize(QSize(28, 28));
    btnDetect->setFixedSize(209, 42);

    btnsLayout->addWidget(btnAdd);
    btnsLayout->addWidget(btnRemove);
    btnsLayout->addStretch();
    btnsLayout->addWidget(btnDetect);

    groupLayout->addLayout(btnsLayout);

    grid = new Qtitan::Grid(groupSerials);
    grid->setViewType(Qtitan::Grid::TableView);

    model = new QStandardItemModel(1, 3, this);
    model->setHeaderData(0, Qt::Horizontal, "Серийный номер");
    model->setHeaderData(1, Qt::Horizontal, "ID ключа");
    model->setHeaderData(2, Qt::Horizontal, "Имя ключа");

    model->setItem(0, 0, new QStandardItem("222"));
    model->setItem(0, 1, new QStandardItem("XXX-XXX-XXX-XXX"));
    model->setItem(0, 2, new QStandardItem("XXX-XXX-XXX-XXX"));

    Qtitan::GridTableView* view = grid->view<Qtitan::GridTableView>();
    view->setModel(model);
    view->tableOptions().setColumnAutoWidth(true);

    groupLayout->addWidget(grid);
    tabLayout->addWidget(groupSerials);
}

QLayout* SettingsDialog::initBottomButtons()
{
    QHBoxLayout* bottomLayout = new QHBoxLayout();

    okBtn = new QPushButton("OK");
    cancelBtn = new QPushButton("Отмена");

    bottomLayout->addStretch();
    bottomLayout->addWidget(okBtn);
    bottomLayout->addWidget(cancelBtn);

    return bottomLayout;
}

void SettingsDialog::initConnections()
{
    connect(okBtn, SIGNAL(&QPushButton::clicked), this, SLOT(&QDialog::accept));
    connect(cancelBtn, SIGNAL(&QPushButton::clicked), this, SLOT(&QDialog::reject));
    connect(btnSelectFolder, SIGNAL(&QPushButton::clicked), this, SLOT(&SettingsDialog::onSelectFolderClicked));
}

void SettingsDialog::onSelectFolderClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выбрать папку");

    if (!dir.isEmpty())
        pathEdit->setText(dir);
}
