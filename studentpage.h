#ifndef STUDENTPAGE_H
#define STUDENTPAGE_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Studentpage;
}

class Studentpage : public QDialog
{
    Q_OBJECT

public:
    explicit Studentpage(QWidget *parent = nullptr);
    ~Studentpage();

private slots:
    void addItem();
    void retrieveItem();
    void saveItemsToFile();
    void loadItemsFromFile();

private:
    Ui::Studentpage *ui;
    QVector<QString> itemNames;
    QVector<QString> itemDescriptions;
    QVector<QString> finderNames;

    QString dataFilePath;  // Move the declaration here
};

#endif // STUDENTPAGE_H
