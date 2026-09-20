#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Model.h"

class Controller : public QObject {
    Q_OBJECT

private:
    Model* model;

public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    Model* getModel() const;

    // Методы для работы с моделью
    void processInput(double weight, Model::WeightUnit unit);
    void clearData();

    // Геттеры
    double getWeight() const;
    Model::WeightUnit getUnit() const;
    double getProteinNorm() const;
    bool isValidData() const;
    QString getUnitString() const;
};

#endif // CONTROLLER_H