#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "Controller.h"
#include "InputDialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Controller* controller;
    QLabel* infoLabel;
    QLabel* resultLabel;

    QPushButton* inputButton;
    QPushButton* clearButton;

    // Последние введённые данные
    double lastWeight;
    Model::WeightUnit lastUnit;
    bool hasLastData;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onInputButtonClicked();
    void onClearButtonClicked();
    void onDataChanged();
    void onErrorOccurred(const QString& message);

private:
    void updateDisplay();
};

#endif // MAINWINDOW_H