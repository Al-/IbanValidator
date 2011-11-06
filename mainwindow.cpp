#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../kmymoney/kmymoney/wizards/newaccountwizard/ibanvalidator.h"

// free icons from "Developer Kit by Burak OZTURK", some modified - http://www.hadibe.com

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
   ui->setupUi(this);
   // for validate button (and first IBAN entry field)
   validateOk.addFile(QLatin1String(":validateicons/OK_green.png"));
   validateUnknown.addFile(QLatin1String(":validateicons/Information.png"));
   validateError.addFile(QLatin1String(":validateicons/Cancel.png"));
   ui->validateButton->setIcon(validateUnknown);
   // for second IBAN entry field
   IbanValidator* ibanValidator = new IbanValidator(this);
   ui->ibanEdit2->setValidator(ibanValidator);}

MainWindow::~MainWindow(){
    delete ui;}

void MainWindow::on_validateButton_clicked(){
   QString text = ui->ibanEdit1->text();
   int position(0);
   IbanValidator ibanValidator(this);
   QValidator::State state = ibanValidator.validate(text, position);
   switch (state) {
      case QValidator::Acceptable:
         ibanValidator.fixup(text);
         ui->ibanEdit1->setText(text);
         ui->validateButton->setIcon(validateOk);
         break;
      case QValidator::Intermediate:
         ui->validateButton->setIcon(validateError);
         break;
      case QValidator::Invalid:
         ui->validateButton->setIcon(validateError);
         break;}}

void MainWindow::on_ibanEdit1_textEdited(const QString& /*arg1*/){
   ui->validateButton->setIcon(validateUnknown);}
