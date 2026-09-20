#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QString>

class Model : public QObject {
    Q_OBJECT

public:
    enum WeightUnit {
        Kilograms,
        Pounds
    };

private:
    double weight;              // вес
    WeightUnit unit;            // единицы измерения
    double proteinNorm;         // суточная норма протеина (г)
    bool isValid;               // корректны ли данные

public:
    explicit Model(QObject* parent = nullptr);

    // Сеттеры
    void setData(double weight, WeightUnit unit);
    void setWeight(double weight);
    void setUnit(WeightUnit unit);
    void clear();

    // Геттеры
    double getWeight() const;
    WeightUnit getUnit() const;
    double getProteinNorm() const;
    bool isValidData() const;
    QString getUnitString() const;

private:
    void calculate();           // пересчёт нормы
    double convertToKilograms() const;

signals:
    // Сигналы активной модели
    void dataChanged();
    void errorOccurred(const QString& message);
};

#endif // MODEL_H