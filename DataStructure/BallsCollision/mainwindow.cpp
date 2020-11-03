#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //START Button
{
    if (ui->lineEdit->text().toInt() > 10000)
    {
        ui->textBrowser->append("Inputs should less than 1e4.");
        return;
    }
    ui->lcdNumber->setDecMode();
    ui->lcdNumber->display(0);
    ui->lcdNumber_2->setDecMode();
    ui->lcdNumber_2->display(0);
    bool flag = false;
    if (!ui->widget->m_vsp.empty())
    {
        ui->textBrowser->append("Please press the STOP button first.");
        return;
    }
    unsigned int ballcount = ui->lineEdit->text().toUInt(&flag);
    if (!flag)
    {
        ui->textBrowser->append("Inputs are limited to INTEGER.");
        return;
    }
    if (!ui->widget->m_balls.empty())
    {
        ui->widget->m_balls.clear();
    }
    std::vector<GameObject> balls;
    balls = Game::Start(ui, ballcount);
    ui->widget->m_balls = balls;
    ui->widget->m_ballscount = ballcount;
}

void MainWindow::on_pushButton_2_clicked() //STOP Button
{
    ui->textBrowser->clear();
    ui->widget->m_vsp.clear();
    ui->widget->m_balls.clear();
    //Game::End();
}
