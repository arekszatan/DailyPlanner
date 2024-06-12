#include <QObject>
#include <QString>
#include <QFileDialog>
#include "exportFile.h""

class ExcelGenerator : public QObject
{
    Q_OBJECT

public:
    explicit ExcelGenerator(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void generateExcel()
    {
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx)");
        if (fileName.isEmpty())
            return;

        QXlsx::Document xlsx;
        xlsx.write("A1", "Header 1");
        xlsx.write("B1", "Header 2");
        xlsx.write("A2", "Data 1");
        xlsx.write("B2", "Data 2");

        if (xlsx.saveAs(fileName))
        {
            emit excelGenerated("Excel file saved successfully.");
        }
        else
        {
            emit excelGenerated("Failed to save Excel file.");
        }
    }

signals:
    void excelGenerated(const QString &message);
};
