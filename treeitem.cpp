#include "TreeItem.h"

TreeItem::TreeItem(const QList<QVariant>& data, TreeItem* parent)
    : itemData(data),
    parent(parent),
    checkStateValue(Qt::Unchecked)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(children);
}

void TreeItem::appendChild(TreeItem* child)
{
    children.append(child);
}

TreeItem* TreeItem::child(int row) const
{
    return children.value(row);
}

int TreeItem::childCount() const
{
    return children.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

void TreeItem::setData(int column, const QVariant& value)
{
    if (column >= 0 && column < itemData.size())
        itemData[column] = value;
}

TreeItem* TreeItem::parentItem() const
{
    return parent;
}

int TreeItem::row() const
{
    if (parent)
        return parent->children.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

Qt::CheckState TreeItem::checkState() const
{
    return checkStateValue;
}

void TreeItem::setCheckState(Qt::CheckState state)
{
    checkStateValue = state;
}
