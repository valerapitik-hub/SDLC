#include "InputDialog.h"
#include <QMessageBox>

InputDialog::InputDialog(double lastWeight, Model::WeightUnit lastUnit,
                         bool hasLastData, QWidget* parent)
    : QDialog(parent), weight(0.0), unit(Model::Kilograms) {

    setWindowTitle("Ввод данных");
    setFixedSize(400, 200);

    // Поле ввода веса
    weightEdit = new QLineEdit(this);

    // Выпадающий список единиц измерения
    unitCombo = new QComboBox(this);
    unitCombo->addItem("кг (килограммы)", Model::Kilograms);
    unitCombo->addItem("фунты", Model::Pounds);

    // Восстанавливаем последние введённые данные
    if (hasLastData) {
        weightEdit->setText(QString::number(lastWeight));
        if (lastUnit == Model::Kilograms) {
            unitCombo->setCurrentIndex(0);
        } else {
            unitCombo->setCurrentIndex(1);
        }
    }

    // Кнопки
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Отмена", this);

    // Layout
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Вес:", weightEdit);
    formLayout->addRow("Единицы измерения:", unitCombo);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Подключения
    connect(okButton, &QPushButton::clicked, this, &InputDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(weightEdit, &QLineEdit::returnPressed, this, &InputDialog::onOkClicked);

    // Фокус на поле ввода
    weightEdit->setFocus();
    if (hasLastData) {
        weightEdit->selectAll();
    }
}

double InputDialog::getWeight() const {
    return weight;
}

Model::WeightUnit InputDialog::getUnit() const {
    return unit;
}

void InputDialog::onOkClicked() {
    QString text = weightEdit->text().trimmed();

    // Проверка на пустоту
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
            "Поле веса не может быть пустым!");
        return;
    }

    // Проверка на число
    bool ok = false;
    double value = text.toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка",
            "Введите корректное число!\n"
            "Например: 70.5 или 70,5");
        return;
    }

    // Проверка на положительное значение
    if (value <= 0) {
        QMessageBox::warning(this, "Ошибка",
            "Вес должен быть положительным числом!");
        return;
    }

    // Проверка разумных пределов
    if (value > 1000) {
        QMessageBox::warning(this, "Ошибка",
            "Слишком большое значение веса!\n"
            "Проверьте правильность ввода.");
        return;
    }

    // Сохраняем данные
    weight = value;
    unit = static_cast<Model::WeightUnit>(unitCombo->currentData().toInt());

    accept();
}