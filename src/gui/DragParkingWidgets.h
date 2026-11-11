#ifndef DRAGPARKINGWIDGETS_H
#define DRAGPARKINGWIDGETS_H

#include <QPushButton>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QApplication>
#include <QPoint>
#include <functional>

// Button that starts a drag operation
class DraggableVehicleButton : public QPushButton
{
public:
    explicit DraggableVehicleButton(QWidget *parent = nullptr)
        : QPushButton("Drag Vehicle", parent)
    {
        setToolTip("Drag this button to an available parking space.");
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            dragStartPosition = event->position().toPoint();
        }

        QPushButton::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (!(event->buttons() & Qt::LeftButton))
            return;

        if ((event->position().toPoint() - dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
            return;

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();

        mimeData->setData(
            "application/x-parking-vehicle",
            QByteArray("vehicle")
        );

        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
    }

private:
    QPoint dragStartPosition;
};

// Parking space that accepts a dropped vehicle
class DroppableParkingSpace : public QPushButton
{
public:
    explicit DroppableParkingSpace(QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        setAcceptDrops(true);
    }

    std::function<void()> onVehicleDropped;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasFormat("application/x-parking-vehicle"))
        {
            event->acceptProposedAction();
        }
    }

    void dropEvent(QDropEvent *event) override
    {
        if (event->mimeData()->hasFormat("application/x-parking-vehicle"))
        {
            if (onVehicleDropped)
            {
                onVehicleDropped();
            }

            event->acceptProposedAction();
        }
    }
};

#endif