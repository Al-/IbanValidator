/*
 * Copyright (c) 2026, Andreas Christ
 * This file is part of "IbanValidator" and is licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

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
