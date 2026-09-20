#include "Controller.h"

Controller::Controller(QObject* parent)
    : QObject(parent) {
    model = new Model(this);
}

Controller::~Controller() {}

Model* Controller::getModel() const {
    return model;
}

void Controller::processInput(double weight, Model::WeightUnit unit) {
    model->setData(weight, unit);
}

void Controller::clearData() {
    model->clear();
}

double Controller::getWeight() const {
    return model->getWeight();
}

Model::WeightUnit Controller::getUnit() const {
    return model->getUnit();
}

double Controller::getProteinNorm() const {
    return model->getProteinNorm();
}

bool Controller::isValidData() const {
    return model->isValidData();
}

QString Controller::getUnitString() const {
    return model->getUnitString();
}