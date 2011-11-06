#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
  void on_validateButton_clicked();

  void on_ibanEdit1_textEdited(const QString &arg1);

private:
   Ui::MainWindow *ui;
   QIcon validateOk;
   QIcon validateUnknown;
   QIcon validateError;
};

#endif // MAINWINDOW_H
