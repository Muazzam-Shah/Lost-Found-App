#include "studentpage.h"
#include "ui_studentpage.h"
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>

Studentpage::Studentpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Studentpage)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->btnRetrieve, SIGNAL(clicked()), this, SLOT(retrieveItem()));

    dataFilePath = "lostandfounditems.txt";  // Set your desired file path

    // Load items directly when the student page is constructed
    loadItemsFromFile();
}

void Studentpage::saveItemsToFile()
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

void Studentpage::loadItemsFromFile()
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
    }
    else
    {
        QMessageBox::warning(this, "Error", "Unable to open the file for reading.");
    }
}
void Studentpage::addItem() {
    QString itemName = QInputDialog::getText(this, "Enter Item Name", "Item Name:");
    QString itemDescription = QInputDialog::getText(this, "Enter Item Description", "Item Description:");
    QString finderName = QInputDialog::getText(this, "Enter Finder's Name", "Finder's Name:");

    itemNames.append(itemName);
    itemDescriptions.append(itemDescription);
    finderNames.append(finderName);

    QMessageBox::information(this, "Success", "Item added to the lost and found.");

    ui->lineEditName->clear();
    ui->textEditDescription->clear();
    ui->lineEditFinder->clear();
}

void Studentpage::retrieveItem() {
    QString retrieveDescription = QInputDialog::getText(this, "Enter Item Name to Retrieve", "Item Name:");

    int index = itemNames.indexOf(retrieveDescription);
    if (index != -1) {
        QMessageBox::information(this, "Success", "Item retrieved. Please collect it from the admin office.");
    } else {
        QMessageBox::warning(this, "Error", "Item not found or access denied.");
    }
}

Studentpage::~Studentpage()
{
    // Save items directly when the student page is closed
    saveItemsToFile();
    delete ui;
}
