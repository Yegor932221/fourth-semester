#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainterPath>
#include <QSpacerItem>
#include "HashTableCellWidget.h"

#include "HashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QGridLayout(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_layout);
    setLayout(mainLayout);
    m_layout->setColumnStretch(0, 0);
    m_layout->setColumnStretch(1, 1);

    QSpacerItem *verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_layout->addItem(verticalSpacer, m_buckets.size(), 0, 1, 2);

    m_layout->setRowStretch(0, 0);
    m_layout->setRowStretch(1, 1);
}

HashTableWidget::BucketWidget::~BucketWidget()
{
    NodeWidget *current = head;
    while (current != nullptr)
    {
        NodeWidget *next = current->next;
        delete current->widget;
        delete current;
        current = next;
    }
}

HashTableWidget::~HashTableWidget()
{
    clear();
}

void HashTableWidget::addRow(int key, const QString &value)
{
    m_hashTable.AddEl(key, value);
    int i = m_hashTable.m_hashFunction->hash(key, m_hashTable.Getsize());

    HashTableCellWidget* cell = new HashTableCellWidget(this);
    cell->setKey(key);
    cell->setValue(value);
    connect(cell, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);

    QHBoxLayout* rowLayout = nullptr;
    if (m_layout->itemAtPosition(i, 1) != nullptr)
    {
        rowLayout = dynamic_cast<QHBoxLayout*>(m_layout->itemAtPosition(i, 1)->layout());
    }

    if (rowLayout == nullptr)
    {
        rowLayout = new QHBoxLayout();
        rowLayout->setSpacing(100);
        rowLayout->setContentsMargins(0, 0, 0, 0);
        m_layout->addLayout(rowLayout, i, 1, Qt::AlignLeft);
    }

    rowLayout->addWidget(cell);
    addNodeToBucket(i, cell);
    m_layout->setRowStretch(m_buckets.size() - 1, 1);
    update();
}

bool HashTableWidget::removeRow(int key) {

    if (m_hashTable.Erase(key))
    {
        int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.Getsize());
        removeNodeFromBucket(bucketIndex, key);
        return true;
    }
    return false;
}

void HashTableWidget::resize(int newSize)
{
    if (newSize <= 0)
    {
        return;
    }
    std::vector<std::pair<int, QString>> oldData;
    for (const BucketWidget& bucket : m_buckets)
    {
        NodeWidget* current = bucket.head;
        while (current != nullptr)
        {
            oldData.push_back({current->widget->key(), current->widget->value()});
            current = current->next;
        }
    }

    clearLayout();
    m_buckets.clear();
    m_hashTable.Resize(newSize);
    m_buckets.resize(newSize);
    for (int i = 0; i < newSize; ++i)
    {
        m_buckets[i].indexLabel = new QLabel(QString::number(i) + ":", this);
        m_buckets[i].indexLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        m_layout->addWidget(m_buckets[i].indexLabel, i, 0, Qt::AlignRight);

        QHBoxLayout* rowLayout = new QHBoxLayout();
        rowLayout->setSpacing(100);
        rowLayout->setContentsMargins(0, 0, 0, 0);
        m_layout->addLayout(rowLayout, i, 1, Qt::AlignLeft);

        for (const auto& data : oldData)
        {
            int bucketIndex = m_hashTable.m_hashFunction->hash(data.first, m_hashTable.Getsize());
            if (bucketIndex == i)
            {
                HashTableCellWidget* cell = new HashTableCellWidget(this);
                cell->setKey(data.first);
                cell->setValue(data.second);
                connect(cell, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);
                rowLayout->addWidget(cell);
                addNodeToBucket(bucketIndex, cell);
            }
        }
    }
    m_layout->setRowStretch(m_buckets.size() - 1, 1);
    update();
}


void HashTableWidget::clearLayout()
{
    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
}

void HashTableWidget::clear()
{
    m_hashTable.Clear();
    for (BucketWidget& bucket : m_buckets)
    {
        NodeWidget* current = bucket.head;
        while (current != nullptr)
        {
            NodeWidget* next = current->next;
            delete current->widget;
            delete current;
            current = next;
        }
        bucket.head = nullptr;
    }

    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    m_buckets.clear();
}


void HashTableWidget::clearBucket(BucketWidget* bucket)
{
    NodeWidget* current = bucket->head;
    while (current != nullptr) {
        NodeWidget* next = current->next;
        delete current->widget;
        delete current;
        current = next;
    }
    bucket->head = nullptr;
    delete bucket->indexLabel;
    bucket->indexLabel = nullptr;
}

void HashTableWidget::paintEvent(QPaintEvent *event)
{

    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int bucketIndex = 0; bucketIndex < m_buckets.size(); ++bucketIndex)
    {
        NodeWidget* current = m_buckets[bucketIndex].head;
        if (current == nullptr || current->next == nullptr)
        {
            continue;
        }

        while (current != nullptr && current->next != nullptr)
        {
            QPoint currentPos = current->widget->pos();
            currentPos.setY(currentPos.y() + current->widget->height() / 2);
            currentPos.setX(currentPos.x() + current->widget->width());

            QPoint nextPos = current->next->widget->pos();
            nextPos.setY(nextPos.y() + current->next->widget->height() / 2);
            int arrowOffset = 10;
            QPoint arrowStart = QPoint(currentPos.x() + arrowOffset, currentPos.y());
            QPoint arrowEnd = QPoint(nextPos.x() - arrowOffset, nextPos.y());
            drawArrow(painter, arrowStart, arrowEnd);
            current = current->next;
        }
    }
    if (m_targetCell)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawRect(m_targetCell->geometry().adjusted(-3, 3, 3, -3));
    }
}

void HashTableWidget::drawArrow(QPainter& painter, const QPoint& start, const QPoint& end)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(start, end);
    qreal angle = atan2(start.y() - end.y(), start.x() - end.x());
    int arrowSize = 10;
    QPointF arrowP1 = end + QPointF(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6));
    QPointF arrowP2 = end + QPointF(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6));
    painter.setBrush(Qt::black);
    painter.drawPolygon(QPolygonF() << end << arrowP1 << arrowP2);
}

void HashTableWidget::addConnection(int fromKey, int toKey)
{
    int fromBucketIndex = m_hashTable.m_hashFunction->hash(fromKey, m_hashTable.Getsize());
    int toBucketIndex = m_hashTable.m_hashFunction->hash(toKey, m_hashTable.Getsize());
    HashTableCellWidget* fromWidget = nullptr;
    HashTableCellWidget* toWidget = nullptr;
    NodeWidget* current = m_buckets[fromBucketIndex].head;
    while (current != nullptr && fromWidget == nullptr)
    {
        if (current->widget->key() == fromKey)
        {
            fromWidget = current->widget;
        }
        current = current->next;
    }
    current = m_buckets[toBucketIndex].head;
    while (current != nullptr && toWidget == nullptr)
    {
        if (current->widget->key() == toKey)
        {
            toWidget = current->widget;
        }
        current = current->next;
    }
    if (fromWidget == nullptr || toWidget == nullptr)
    {
        qWarning() << "HashTableWidget::addConnection: Widgets not found for keys"<< fromKey << "and" << toKey;
        return;
    }
    NodeWidget* newNode = new NodeWidget(toWidget);
    current = m_buckets[fromBucketIndex].head;
    if (current == nullptr)
    {
        m_buckets[fromBucketIndex].head = newNode;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void HashTableWidget::removeConnections(int key)
{
    int bucketIndex = m_hashTable.m_hashFunction->hash(key, m_hashTable.Getsize());
    BucketWidget& bucket = m_buckets[bucketIndex];
    NodeWidget* current = bucket.head;
    NodeWidget* prev = nullptr;

    while (current != nullptr)
    {
        if (current->widget->key() == key)
        {
            if (prev == nullptr)
            {
                bucket.head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current->widget;
            delete current;
            update();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashTableWidget::onValueChanged(HashTableCellWidget *item)
{
    if (m_hashTable.Contains(item->key()))
    {
        m_hashTable[item->key()] = QString::fromStdString(item->value().toStdString());
    }
}

void HashTableWidget::addNodeToBucket(int bucketIndex, HashTableCellWidget* cell)
{
    NodeWidget* newNode = new NodeWidget(cell);
    if (m_buckets[bucketIndex].head == nullptr)
    {
        m_buckets[bucketIndex].head = newNode;
        return;
    }
    NodeWidget* current = m_buckets[bucketIndex].head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
}

void HashTableWidget::removeNodeFromBucket(int bucketIndex, int key)
{
    BucketWidget& bucket = m_buckets[bucketIndex];
    NodeWidget* current = bucket.head;
    NodeWidget* prev = nullptr;

    while (current != nullptr)
    {
        if (current->widget->key() == key)
        {
            if (prev == nullptr)
            {
                bucket.head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current->widget;
            delete current;
            update();
            return;
        }
        prev = current;
        current = current->next;
    }
}

const HashTableWidget::BucketWidget* HashTableWidget::findBucket(int key) const
{
    int i = m_hashTable.m_hashFunction->hash(key, m_hashTable.Getsize());
    return &(m_buckets[i]);
}

void HashTableWidget::setHashFunction(HashFunction* newHashFunction)
{
    if (newHashFunction)
    {
        m_hashTable.ChangeHashFunction(newHashFunction);
        resize(m_hashTable.Getsize());
    }
}




