#include "Model.h"

Model::Model(QObject* parent)
    : QObject(parent), weight(0.0), unit(Kilograms), proteinNorm(0.0), isValid(false) {
}

void Model::setData(double w, WeightUnit u) {
    weight = w;
    unit = u;
    isValid = (weight > 0);

    if (isValid) {
        calculate();
        emit dataChanged();       // уведомляем об изменении
    } else {
        proteinNorm = 0.0;
        emit errorOccurred("Вес должен быть положительным числом!");
    }
}

void Model::setWeight(double w) {
    setData(w, unit);
}

void Model::setUnit(WeightUnit u) {
    setData(weight, u);
}

void Model::clear() {
    weight = 0.0;
    proteinNorm = 0.0;
    isValid = false;
    emit dataChanged();
}

double Model::getWeight() const {
    return weight;
}

Model::WeightUnit Model::getUnit() const {
    return unit;
}

double Model::getProteinNorm() const {
    return proteinNorm;
}

bool Model::isValidData() const {
    return isValid;
}

QString Model::getUnitString() const {
    return (unit == Kilograms) ? "кг" : "фунты";
}

double Model::convertToKilograms() const {
    if (unit == Kilograms) {
        return weight;
    } else {
        // 1 фунт = 0.453592 кг
        return weight * 0.453592;
    }
}

void Model::calculate() {
    // Формула: 1.6 г протеина на 1 кг веса
    double weightKg = convertToKilograms();
    proteinNorm = weightKg * 1.6;
}