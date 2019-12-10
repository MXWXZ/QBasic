#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->textEdit->append("Minimal BASIC -- Type HELP for help.\n\n");
    this->setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow() { delete ui; }
