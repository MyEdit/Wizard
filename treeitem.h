#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <Qt>

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant>& data, TreeItem* parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);
    void setData(int column, const QVariant& value);
    void setCheckState(Qt::CheckState state);
    int childCount() const;
    int columnCount() const;
    int row() const;
    TreeItem* child(int row) const;
    TreeItem* parentItem() const;
    QVariant data(int column) const;
    Qt::CheckState checkState() const;

private:
    QList<TreeItem*> children;
    QList<QVariant> itemData;
    TreeItem* parent;
    Qt::CheckState checkStateValue;
};

#endif // TREEITEM_H
