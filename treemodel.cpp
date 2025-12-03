#include "TreeModel.h"
#include <QModelIndex>

TreeModel::TreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << " " << "Наименование базы" << "Регион" << "Дата обновления" << "Размер";
    root = new TreeItem(rootData);
}

TreeModel::~TreeModel()
{
    delete root;
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return root->columnCount();
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : root;
    return parentItem->childCount();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : root;
    TreeItem* childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    if (!parentItem || parentItem == root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;

    return flags;
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
        return item->data(index.column());

    if (role == Qt::CheckStateRole && index.column() == 0)
        return item->checkState();

    return QVariant();
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    if (index.column() != 0 || role != Qt::EditRole)
        return false;

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());

    item->setCheckState(state);

    setChildCheckState(item, state);

    emit dataChanged(index, index, {Qt::CheckStateRole});
    updateChildIndexes(index);

    return true;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return root->data(section);

    return QVariant();
}

TreeItem* TreeModel::addNode(const QList<QVariant>& rowData, TreeItem* parentItem)
{
    if (!parentItem)
        parentItem = root;

    int pos = parentItem->childCount();
    beginInsertRows(createIndex(parentItem->row(), 0, parentItem), pos, pos);

    TreeItem* item = new TreeItem(rowData, parentItem);
    parentItem->appendChild(item);

    endInsertRows();
    return item;
}

TreeItem* TreeModel::rootItem() const
{
    return root;
}

void TreeModel::setChildCheckState(TreeItem* item, Qt::CheckState state)
{
    for (int i = 0; i < item->childCount(); ++i)
    {
        TreeItem* child = item->child(i);
        child->setCheckState(state);
        setChildCheckState(child, state);
    }
}

void TreeModel::updateChildIndexes(const QModelIndex& parentIndex)
{
    TreeItem* parentItem = static_cast<TreeItem*>(parentIndex.internalPointer());
    for (int i = 0; i < parentItem->childCount(); ++i)
    {
        QModelIndex childIndex = this->index(i, parentIndex.column(), parentIndex);
        emit dataChanged(childIndex, childIndex, {Qt::CheckStateRole});
        updateChildIndexes(childIndex);
    }
}
