#include "MainWindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      lastWeight(0.0),
      lastUnit(Model::Kilograms),
      hasLastData(false) {

    // Создаём контроллер
    controller = new Controller(this);

    // Подключаемся к сигналам активной модели
    connect(controller->getModel(), &Model::dataChanged,
            this, &MainWindow::onDataChanged);
    connect(controller->getModel(), &Model::errorOccurred,
            this, &MainWindow::onErrorOccurred);

    // Создаём виджеты
    infoLabel = new QLabel("Нажмите \"Ввести данные\" для ввода веса", this);
    resultLabel = new QLabel("Суточная норма протеина: --", this);
    inputButton = new QPushButton("Ввести данные", this);
    clearButton = new QPushButton("Очистить", this);

    // Настраиваем layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(infoLabel);
    layout->addWidget(resultLabel);
    layout->addSpacing(10);
    layout->addWidget(inputButton);
    layout->addWidget(clearButton);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключаем кнопки
    connect(inputButton, &QPushButton::clicked,
            this, &MainWindow::onInputButtonClicked);
    connect(clearButton, &QPushButton::clicked,
            this, &MainWindow::onClearButtonClicked);

    // Настройки окна
    setFixedSize(420, 220);
    setWindowTitle("Расчёт суточной нормы протеина");
}

MainWindow::~MainWindow() {}

void MainWindow::onInputButtonClicked() {
    // Открываем диалог с последними введёнными данными
    InputDialog dialog(lastWeight, lastUnit, hasLastData, this);

    if (dialog.exec() == QDialog::Accepted) {
        double weight = dialog.getWeight();
        Model::WeightUnit unit = dialog.getUnit();

        // Запоминаем последние данные
        lastWeight = weight;
        lastUnit = unit;
        hasLastData = true;

        // Передаём данные в контроллер
        controller->processInput(weight, unit);
    }
}

void MainWindow::onClearButtonClicked() {
    hasLastData = false;
    lastWeight = 0.0;
    lastUnit = Model::Kilograms;

    controller->clearData();

    infoLabel->setText("Нажмите \"Ввести данные\" для ввода веса");
    resultLabel->setText("Суточная норма протеина: --");
}

void MainWindow::onDataChanged() {
    updateDisplay();
}

void MainWindow::onErrorOccurred(const QString& message) {
    QMessageBox::warning(this, "Ошибка", message);
}

void MainWindow::updateDisplay() {
    if (controller->isValidData()) {
        QString infoText = QString("Вес: %1 %2")
                .arg(controller->getWeight(), 0, 'f', 2)
                .arg(controller->getUnitString());

        QString resultText = QString("Суточная норма протеина: %1 г")
                .arg(controller->getProteinNorm(), 0, 'f', 2);

        infoLabel->setText(infoText);
        resultLabel->setText(resultText);
    }
}