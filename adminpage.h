#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include <QVector>
#include <QStringList>

namespace Ui {
class Adminpage;
}

class Adminpage : public QDialog
{
    Q_OBJECT

public:
    explicit Adminpage(QWidget *parent = nullptr);
    ~Adminpage();

private slots:
    void displayItems();
    void removeItem();
    void saveItemsToFile();
    void loadItemsFromFile();

private:
    Ui::Adminpage *ui;
    QVector<QString> itemNames;
    QVector<QString> itemDescriptions;
    QVector<QString> finderNames;

    QString dataFilePath;  // Move the declaration here
};

#endif // ADMINPAGE_H
