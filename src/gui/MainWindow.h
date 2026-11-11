#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>

#include "../cpp/ParkingSystem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QComboBox *vehicleType;
    QLineEdit *registrationInput;
    QLabel *statusLabel;

    QVector<QPushButton*> parkingSpaces;

    QVBoxLayout *mainLayout;

    ParkingSystem parkingSystem;

    void createParkingLayout();
    void parkVehicle();
    void showHelp();
    void updateParkingLayout();

    // Drag-and-drop
    void startVehicleDrag();
    void parkVehicleInSpace(int spaceIndex);
};

#endif