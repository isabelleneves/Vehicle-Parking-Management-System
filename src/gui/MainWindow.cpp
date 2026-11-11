#include "MainWindow.h"
#include "DragParkingWidgets.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QString>

// Main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Vehicle Parking Management System");
    resize(1100, 750);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    // Main title
    QLabel *title = new QLabel(
        "VEHICLE PARKING MANAGEMENT SYSTEM"
    );

    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "padding: 15px;"
    );

    mainLayout->addWidget(title);

    // Create parking spaces
    createParkingLayout();

    // Vehicle registration section
    QGroupBox *controlBox = new QGroupBox(
        "Vehicle Registration"
    );

    QHBoxLayout *controlLayout = new QHBoxLayout(controlBox);

    vehicleType = new QComboBox();
    vehicleType->addItems({
        "Motorcycle",
        "Car",
        "Bus"
    });

    registrationInput = new QLineEdit();
    registrationInput->setPlaceholderText(
        "Registration number"
    );

    QPushButton *parkButton = new QPushButton("Park Vehicle");
    QPushButton *helpButton = new QPushButton("Help");

    // Draggable vehicle button
    DraggableVehicleButton *dragButton =
        new DraggableVehicleButton();

    controlLayout->addWidget(new QLabel("Vehicle type:"));
    controlLayout->addWidget(vehicleType);
    controlLayout->addWidget(registrationInput);
    controlLayout->addWidget(parkButton);
    controlLayout->addWidget(dragButton);
    controlLayout->addWidget(helpButton);

    mainLayout->addWidget(controlBox);

    // Status message
    statusLabel = new QLabel(
        "All parking spaces are currently available."
    );

    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "font-size: 14px;"
        "padding: 10px;"
    );

    mainLayout->addWidget(statusLabel);

    // Button connections
    connect(
        parkButton,
        &QPushButton::clicked,
        this,
        &MainWindow::parkVehicle
    );

    connect(
        helpButton,
        &QPushButton::clicked,
        this,
        &MainWindow::showHelp
    );

    updateParkingLayout();
}


// Create parking layout
void MainWindow::createParkingLayout()
{
    QGroupBox *parkingBox = new QGroupBox("Parking Layout");
    QGridLayout *parkingGrid = new QGridLayout(parkingBox);

    for (int floor = 1; floor <= 2; floor++)
    {
        QLabel *floorLabel = new QLabel(
            "FLOOR " + QString::number(floor)
        );

        floorLabel->setStyleSheet(
            "font-size: 18px;"
            "font-weight: bold;"
            "padding: 8px;"
        );

        parkingGrid->addWidget(
            floorLabel,
            (floor - 1) * 3,
            0,
            1,
            8
        );

        for (int row = 1; row <= 2; row++)
        {
            for (int space = 1; space <= 8; space++)
            {
                int spaceIndex = parkingSpaces.size();

                DroppableParkingSpace *button =
                    new DroppableParkingSpace();

                button->setText(QString::number(space));
                button->setMinimumSize(75, 45);

                QString sizeType =
                    (space <= 3) ? "Compact" : "Large";

                button->setToolTip(
                    "Floor " + QString::number(floor) +
                    ", Row " + QString::number(row) +
                    ", " + sizeType + " space"
                );

                button->setStyleSheet(
                    "background-color: #90EE90;"
                    "border: 1px solid #555;"
                    "border-radius: 5px;"
                );

                // Connect the drop event to the selected space
                button->onVehicleDropped = [this, spaceIndex]()
                {
                    parkVehicleInSpace(spaceIndex);
                };

                parkingGrid->addWidget(
                    button,
                    (floor - 1) * 3 + row,
                    space - 1
                );

                parkingSpaces.append(button);
            }
        }
    }

    mainLayout->addWidget(parkingBox);
}


// Park vehicle using the button
void MainWindow::parkVehicle()
{
    QString registration =
        registrationInput->text().trimmed();

    if (registration.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Invalid Input",
            "Please enter a registration number."
        );
        return;
    }

    std::string plate = registration.toStdString();
    QString type = vehicleType->currentText();

    std::string existingType;

    if (parkingSystem.vehicleHash.getVehicleType(
            plate, existingType))
    {
        QMessageBox::warning(
            this,
            "Vehicle Already Registered",
            "This vehicle is already registered."
        );
        return;
    }

    if (type == "Motorcycle")
    {
        Vehicle::Motorcycle vehicle(plate);
        parkingSystem.parkVehicle(vehicle);
    }
    else if (type == "Car")
    {
        Vehicle::Car vehicle(plate);
        parkingSystem.parkVehicle(vehicle);
    }
    else if (type == "Bus")
    {
        Vehicle::Bus vehicle(plate);
        parkingSystem.parkVehicle(vehicle);
    }

    updateParkingLayout();

    if (parkingSystem.searchVehicle(plate))
    {
        statusLabel->setText(
            type + " registered successfully: " + registration
        );
        registrationInput->clear();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Parking Full",
            "No compatible parking spaces are available."
        );
    }
}


// Park vehicle in a selected space using drag-and-drop
void MainWindow::parkVehicleInSpace(int spaceIndex)
{
    QString registration =
        registrationInput->text().trimmed();

    if (registration.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Invalid Input",
            "Please enter a registration number before dragging."
        );
        return;
    }

    int floor = (spaceIndex / 16) + 1;
    int row = ((spaceIndex % 16) / 8) + 1;
    int space = (spaceIndex % 8) + 1;

    std::string plate = registration.toStdString();
    QString type = vehicleType->currentText();

    bool success = false;

    if (type == "Motorcycle")
    {
        Vehicle::Motorcycle vehicle(plate);
        success = parkingSystem.occupySpace(
            floor, row, space, vehicle
        );
    }
    else if (type == "Car")
    {
        Vehicle::Car vehicle(plate);
        success = parkingSystem.occupySpace(
            floor, row, space, vehicle
        );
    }
    else if (type == "Bus")
    {
        Vehicle::Bus vehicle(plate);
        success = parkingSystem.occupySpace(
            floor, row, space, vehicle
        );
    }

    if (success)
    {
        updateParkingLayout();

        statusLabel->setText(
            type + " parked successfully: " + registration
        );

        registrationInput->clear();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Parking Not Available",
            "This space is not available or is not suitable "
            "for the selected vehicle."
        );
    }
}


// Update parking spaces
void MainWindow::updateParkingLayout()
{
    int index = 0;

    for (const auto& floor : parkingSystem.floors)
    {
        for (const auto& row : floor.rows)
        {
            for (const auto& space : row.spaces)
            {
                if (index >= parkingSpaces.size())
                    return;

                QPushButton *button = parkingSpaces[index];

                if (space.occupied)
                {
                    button->setStyleSheet(
                        "background-color: #FF6B6B;"
                        "border: 1px solid #555;"
                        "border-radius: 5px;"
                        "font-weight: bold;"
                    );

                    button->setText(
                        QString::fromStdString(
                            space.registrationNumber
                        )
                    );
                }
                else
                {
                    button->setStyleSheet(
                        "background-color: #90EE90;"
                        "border: 1px solid #555;"
                        "border-radius: 5px;"
                    );

                    button->setText(
                        QString::number(space.spaceNumber)
                    );
                }

                index++;
            }
        }
    }
}


// Help information
void MainWindow::showHelp()
{
    QMessageBox::information(
        this,
        "Help - Vehicle Parking Management System",
        "HOW TO USE THE PARKING SYSTEM\n\n"
        "1. Select the vehicle type.\n"
        "2. Enter the registration number.\n"
        "3. Click Park Vehicle or drag the vehicle button "
        "to an available space.\n\n"
        "PARKING RULES\n\n"
        "Motorcycles can use any parking space.\n"
        "Cars can use compact or large spaces.\n"
        "Buses need five consecutive large spaces "
        "in the same row.\n"
        "For buses, drop on the first of five large spaces.\n\n"
        "PARKING COLOURS\n\n"
        "Green = Available\n"
        "Red = Occupied"
    );
}
