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
    void listen(void);

private slots:
	void on_inputBox_returnPressed();
	void on_sendButton_clicked();

public slots:
    void closing();

private:
    Ui::MainWindow *ui;

};

void cli_recv(Ui::MainWindow* ui);


#endif // MAINWINDOW_H
