#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_inputBox_returnPressed();
	void on_sendButton_clicked();
	void cli_recv();

public slots:
    void closing();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
