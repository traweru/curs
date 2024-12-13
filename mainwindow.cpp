#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка выпадающего меню с формулами
    ui->formulaComboBox->addItem("Формула Харриса-Бенедикта");
    ui->formulaComboBox->addItem("Формула Миффлина-Сан Жеора");
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::calculateBMR()
{
    // Чтение параметров из пользовательского интерфейса
    double weight = ui->weightSpinBox->value(); // Вес в кг
    double height = ui->heightSpinBox->value(); // Рост в см
    int age = ui->ageSpinBox->value();          // Возраст в годах
    QString gender = ui->genderComboBox->currentText();
    QString formula = ui->formulaComboBox->currentText();

    // Проверка на недопустимые значения (например, нули)
    if (weight <= 0 || height <= 0 || age <= 0) {
        // Если какое-либо из значений равно нулю или отрицательно, возвращаем BMR = 0
        return 0.0;
    }

    double bmr = 0.0;

    // Расчёт в зависимости от выбранной формулы
    if (formula == "Формула Харриса-Бенедикта") {
        if (gender == "Мужчина") {
            bmr = 88.36 + (13.4 * weight) + (4.8 * height) - (5.7 * age);
        } else {
            bmr = 447.6 + (9.2 * weight) + (3.1 * height) - (4.3 * age);
        }
    } else if (formula == "Формула Миффлина-Сан Жеора") {
        if (gender == "Мужчина") {
            bmr = 10 * weight + 6.25 * height - 5 * age + 5;
        } else {
            bmr = 10 * weight + 6.25 * height - 5 * age - 161;
        }
    }

    return bmr;
}

void MainWindow::on_calculateButton_clicked()
{
    double bmr = calculateBMR();
    if (bmr == 0.0) {
        ui->resultLabel->setText("Недопустимые значения ввода.");
    } else {
        ui->resultLabel->setText(QString::number(bmr, 'f', 2) + " ккал/день");
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = "BMR_Report.txt";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Рост: " << ui->heightSpinBox->value() << " см\n";
        out << "Вес: " << ui->weightSpinBox->value() << " кг\n";
        out << "Возраст: " << ui->ageSpinBox->value() << " лет\n";
        out << "Пол: " << ui->genderComboBox->currentText() << "\n";
        out << "Формула: " << ui->formulaComboBox->currentText() << "\n";
        out << "BMR: " << ui->resultLabel->text() << "\n";
        file.close();
        QMessageBox::information(this, "Сохранение", "Отчёт успешно сохранён.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить отчёт.");
    }
}
