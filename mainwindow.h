#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked(); // Обработчик кнопки "Рассчитать"
    void on_saveButton_clicked();      // Обработчик кнопки "Сохранить"

private:
    Ui::MainWindow *ui;
    double calculateBMR(); // Метод для расчёта BMR
};

#endif // MAINWINDOW_H
