#include "adminpage.h"
#include "ui_adminpage.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QMessageBox>

Adminpage::Adminpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adminpage)
{
    ui->setupUi(this);

    connect(ui->btnDisplay, SIGNAL(clicked()), this, SLOT(displayItems()));
    connect(ui->btnRemove, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));

    dataFilePath = "lostandfounditems.txt";  // Set your desired file path

    // Load items directly when the admin page is constructed
    loadItemsFromFile();
}

void Adminpage::saveItemsToFile()
{
    QFile file(dataFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        // Save each item in a new line with a specific format
        for (int i = 0; i < itemNames.size(); ++i)
        {
            out << itemNames.at(i) << "," << itemDescriptions.at(i) << "," << finderNames.at(i) << "\n";
        }

        file.close();
        QMessageBox::information(this, "Success", "Items saved to file.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unable to open the file for writing.");
    }
}

void Adminpage::loadItemsFromFile()
{
    QFile file(dataFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        itemNames.clear();
        itemDescriptions.clear();
        finderNames.clear();

        // Read each line and split the values using ","
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3)
            {
                itemNames.append(parts.at(0));
                itemDescriptions.append(parts.at(1));
                finderNames.append(parts.at(2));
            }
        }

        file.close();
        QMessageBox::information(this, "Success", "Items loaded from file.");
        displayItems();  // Update the UI with the loaded items
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unable to open the file for reading.");
    }
}

void Adminpage::displayItems() {
    ui->textEditDescription->clear();

    if (itemNames.isEmpty()) {
        ui->textEditDescription->setText("No items in the lost and found.");
    } else {
        ui->textEditDescription->setText("Lost Items:");
        for (int i = 0; i < itemNames.size(); ++i) {
            QString itemInfo = "Name: " + itemNames.at(i) +
                               ", Description: " + itemDescriptions.at(i) +
                               ", Finder: " + finderNames.at(i);
            ui->textEditDescription->append(itemInfo);
        }
    }
}

void Adminpage::removeItem() {
    QString itemName = QInputDialog::getText(this, "Enter Item Name", "Item Name:");
    QString finderName = QInputDialog::getText(this, "Enter Finder's Name", "Finder's Name:");
    QString description = QInputDialog::getText(this, "Enter Description", "Item Description:");

    int index = -1;
    for (int i = 0; i < itemNames.size(); ++i) {
        if (itemNames.at(i) == itemName && finderNames.at(i) == finderName && itemDescriptions.at(i) == description) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        itemNames.remove(index);
        itemDescriptions.remove(index);
        finderNames.remove(index);

        QMessageBox::information(this, "Success", "Item removed from the lost and found.");
    } else {
        QMessageBox::warning(this, "Error", "Item not found or access denied.");
    }

    displayItems();
}

Adminpage::~Adminpage()
{
    // Save items directly when the admin page is closed
    saveItemsToFile();
    delete ui;
}
