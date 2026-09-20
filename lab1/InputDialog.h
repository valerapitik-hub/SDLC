#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "Model.h"

class InputDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* weightEdit;
    QComboBox* unitCombo;
    QPushButton* okButton;
    QPushButton* cancelButton;

    double weight;
    Model::WeightUnit unit;

public:
    InputDialog(double lastWeight, Model::WeightUnit lastUnit,
                bool hasLastData, QWidget* parent = nullptr);

    double getWeight() const;
    Model::WeightUnit getUnit() const;

private slots:
    void onOkClicked();
};

#endif // INPUTDIALOG_H