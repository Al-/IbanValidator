#ifndef IBANVALIDATOR_H
#define IBANVALIDATOR_H

#include <QRegExpValidator>

class IbanValidator : public QRegExpValidator {
    Q_OBJECT
public:
   explicit IbanValidator(QObject *parent = 0);
   virtual void fixup (QString& input) const;
   virtual State validate (QString& input, int& pos) const;
private:
   unsigned int mod97(const QString& input) const;};

#endif // IBANVALIDATOR_H
