/*
 * Copyright (c) 2026, Andreas Christ
 * This file is part of "IbanValidator" and is licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

#include "ibanvalidator.h"

#include <QStringList>
// #include <QDebug>

// IBAN templates, as provided by Wikipedia
// see http://en.wikipedia.org/wiki/International_Bank_Account_Number
struct IbanTemplate{
   IbanTemplate() :
      country(QLatin1String("")),
      length(0), format(QLatin1String("")),
      codes(QLatin1String("")) {}
   QString country;
   unsigned char length;
   QString format;
   QString codes;};


IbanValidator::IbanValidator(QObject *parent) : QRegExpValidator(parent) {
   // initialze templates, copied from http://en.wikipedia.org/wiki/International_Bank_Account_Number
   // templates could also be read from an external text file or from a database
   // LibreOffice calc (German locale) formula to create the entries from the copied text of wikipedia:
   // ="ibanTemplate["&ZEILE()-2&"].country = QLatin1String("""&A21&"""); ibanTemplate["&ZEILE()-2&"].length = "&B21&"; ibanTemplate["&ZEILE()-2&"].format = QLatin1String("""&C21&"""); ibanTemplate["&ZEILE()-2&"].codes = QLatin1String("""&LINKS(D21;2)&""");"
   QList<IbanTemplate> ibanTemplate;
   ibanTemplate.reserve(56);
   for (int i(0); i < 56; ++i) ibanTemplate.append(IbanTemplate());
   ibanTemplate[0].country = QLatin1String("Albania"); ibanTemplate[0].length = 28; ibanTemplate[0].format = QLatin1String("8n, 16c"); ibanTemplate[0].codes = QLatin1String("AL");
   ibanTemplate[1].country = QLatin1String("Andorra"); ibanTemplate[1].length = 24; ibanTemplate[1].format = QLatin1String("8n,12c"); ibanTemplate[1].codes = QLatin1String("AD");
   ibanTemplate[2].country = QLatin1String("Austria"); ibanTemplate[2].length = 20; ibanTemplate[2].format = QLatin1String("16n"); ibanTemplate[2].codes = QLatin1String("AT");
   ibanTemplate[3].country = QLatin1String("Belgium"); ibanTemplate[3].length = 16; ibanTemplate[3].format = QLatin1String("12n"); ibanTemplate[3].codes = QLatin1String("BE");
   ibanTemplate[4].country = QLatin1String("Bahrain"); ibanTemplate[4].length = 22; ibanTemplate[4].format = QLatin1String("4a,14c"); ibanTemplate[4].codes = QLatin1String("BH");
   ibanTemplate[5].country = QLatin1String("Bosnia and Herzegovina"); ibanTemplate[5].length = 20; ibanTemplate[5].format = QLatin1String("16n"); ibanTemplate[5].codes = QLatin1String("BA");
   ibanTemplate[6].country = QLatin1String("Bulgaria"); ibanTemplate[6].length = 22; ibanTemplate[6].format = QLatin1String("4a,6n,8c"); ibanTemplate[6].codes = QLatin1String("BG");
   ibanTemplate[7].country = QLatin1String("Croatia"); ibanTemplate[7].length = 21; ibanTemplate[7].format = QLatin1String("17n"); ibanTemplate[7].codes = QLatin1String("HR");
   ibanTemplate[8].country = QLatin1String("Cyprus"); ibanTemplate[8].length = 28; ibanTemplate[8].format = QLatin1String("8n,16c"); ibanTemplate[8].codes = QLatin1String("CY");
   ibanTemplate[9].country = QLatin1String("Czech Republic"); ibanTemplate[9].length = 24; ibanTemplate[9].format = QLatin1String("20n"); ibanTemplate[9].codes = QLatin1String("CZ");
   ibanTemplate[10].country = QLatin1String("Denmark"); ibanTemplate[10].length = 18; ibanTemplate[10].format = QLatin1String("14n"); ibanTemplate[10].codes = QLatin1String("DK");
   ibanTemplate[11].country = QLatin1String("Dominican Republic"); ibanTemplate[11].length = 28; ibanTemplate[11].format = QLatin1String("4a,20n"); ibanTemplate[11].codes = QLatin1String("DO");
   ibanTemplate[12].country = QLatin1String("Estonia"); ibanTemplate[12].length = 20; ibanTemplate[12].format = QLatin1String("16n"); ibanTemplate[12].codes = QLatin1String("EE");
   ibanTemplate[13].country = QLatin1String("Faroe Islands"); ibanTemplate[13].length = 18; ibanTemplate[13].format = QLatin1String("14n"); ibanTemplate[13].codes = QLatin1String("FO");
   ibanTemplate[14].country = QLatin1String("Finland"); ibanTemplate[14].length = 18; ibanTemplate[14].format = QLatin1String("14n"); ibanTemplate[14].codes = QLatin1String("FI");
   ibanTemplate[15].country = QLatin1String("France"); ibanTemplate[15].length = 27; ibanTemplate[15].format = QLatin1String("10n,11c,2n"); ibanTemplate[15].codes = QLatin1String("FR, TF, PF, YT, NC, PM, WF");
   ibanTemplate[16].country = QLatin1String("Georgia"); ibanTemplate[16].length = 22; ibanTemplate[16].format = QLatin1String("2c,16n"); ibanTemplate[16].codes = QLatin1String("GE");
   ibanTemplate[17].country = QLatin1String("Germany"); ibanTemplate[17].length = 22; ibanTemplate[17].format = QLatin1String("18n"); ibanTemplate[17].codes = QLatin1String("DE");
   ibanTemplate[18].country = QLatin1String("Gibraltar"); ibanTemplate[18].length = 23; ibanTemplate[18].format = QLatin1String("4a,15c"); ibanTemplate[18].codes = QLatin1String("GI");
   ibanTemplate[19].country = QLatin1String("Greece"); ibanTemplate[19].length = 27; ibanTemplate[19].format = QLatin1String("7n,16c"); ibanTemplate[19].codes = QLatin1String("GR");
   ibanTemplate[20].country = QLatin1String("Greenland[Note 1]"); ibanTemplate[20].length = 18; ibanTemplate[20].format = QLatin1String("14n"); ibanTemplate[20].codes = QLatin1String("GL");
   ibanTemplate[21].country = QLatin1String("Hungary"); ibanTemplate[21].length = 28; ibanTemplate[21].format = QLatin1String("24n"); ibanTemplate[21].codes = QLatin1String("HU");
   ibanTemplate[22].country = QLatin1String("Iceland"); ibanTemplate[22].length = 26; ibanTemplate[22].format = QLatin1String("22n"); ibanTemplate[22].codes = QLatin1String("IS");
   ibanTemplate[23].country = QLatin1String("Ireland"); ibanTemplate[23].length = 22; ibanTemplate[23].format = QLatin1String("4c,14n"); ibanTemplate[23].codes = QLatin1String("IE");
   ibanTemplate[24].country = QLatin1String("Israel"); ibanTemplate[24].length = 23; ibanTemplate[24].format = QLatin1String("19n"); ibanTemplate[24].codes = QLatin1String("IL");
   ibanTemplate[25].country = QLatin1String("Italy"); ibanTemplate[25].length = 27; ibanTemplate[25].format = QLatin1String("1a,10n,12c"); ibanTemplate[25].codes = QLatin1String("IT");
   ibanTemplate[26].country = QLatin1String("Kazakhstan"); ibanTemplate[26].length = 20; ibanTemplate[26].format = QLatin1String("3n,3c,10n"); ibanTemplate[26].codes = QLatin1String("KZ");
   ibanTemplate[27].country = QLatin1String("Kuwait"); ibanTemplate[27].length = 30; ibanTemplate[27].format = QLatin1String("4a, 22n"); ibanTemplate[27].codes = QLatin1String("KW");
   ibanTemplate[28].country = QLatin1String("Latvia"); ibanTemplate[28].length = 21; ibanTemplate[28].format = QLatin1String("4a,13c"); ibanTemplate[28].codes = QLatin1String("LV");
   ibanTemplate[29].country = QLatin1String("Lebanon"); ibanTemplate[29].length = 28; ibanTemplate[29].format = QLatin1String("4n,20c"); ibanTemplate[29].codes = QLatin1String("LB");
   ibanTemplate[30].country = QLatin1String("Liechtenstein"); ibanTemplate[30].length = 21; ibanTemplate[30].format = QLatin1String("5n,12c"); ibanTemplate[30].codes = QLatin1String("LI");
   ibanTemplate[31].country = QLatin1String("Lithuania"); ibanTemplate[31].length = 20; ibanTemplate[31].format = QLatin1String("16n"); ibanTemplate[31].codes = QLatin1String("LT");
   ibanTemplate[32].country = QLatin1String("Luxembourg"); ibanTemplate[32].length = 20; ibanTemplate[32].format = QLatin1String("3n,13c"); ibanTemplate[32].codes = QLatin1String("LU");
   ibanTemplate[33].country = QLatin1String("Macedonia"); ibanTemplate[33].length = 19; ibanTemplate[33].format = QLatin1String("3n,10c,2n"); ibanTemplate[33].codes = QLatin1String("MK");
   ibanTemplate[34].country = QLatin1String("Malta"); ibanTemplate[34].length = 31; ibanTemplate[34].format = QLatin1String("4a,5n,18c"); ibanTemplate[34].codes = QLatin1String("MT");
   ibanTemplate[35].country = QLatin1String("Mauritania"); ibanTemplate[35].length = 27; ibanTemplate[35].format = QLatin1String("23n"); ibanTemplate[35].codes = QLatin1String("MR");
   ibanTemplate[36].country = QLatin1String("Mauritius"); ibanTemplate[36].length = 30; ibanTemplate[36].format = QLatin1String("4a,19n,3a"); ibanTemplate[36].codes = QLatin1String("MU");
   ibanTemplate[37].country = QLatin1String("Monaco"); ibanTemplate[37].length = 27; ibanTemplate[37].format = QLatin1String("10n,11c,2n"); ibanTemplate[37].codes = QLatin1String("MC");
   ibanTemplate[38].country = QLatin1String("Montenegro"); ibanTemplate[38].length = 22; ibanTemplate[38].format = QLatin1String("18n"); ibanTemplate[38].codes = QLatin1String("ME");
   ibanTemplate[39].country = QLatin1String("Netherlands[Note 3]"); ibanTemplate[39].length = 18; ibanTemplate[39].format = QLatin1String("4a,10n"); ibanTemplate[39].codes = QLatin1String("NL");
   ibanTemplate[40].country = QLatin1String("Norway"); ibanTemplate[40].length = 15; ibanTemplate[40].format = QLatin1String("11n"); ibanTemplate[40].codes = QLatin1String("NO");
   ibanTemplate[41].country = QLatin1String("Poland"); ibanTemplate[41].length = 28; ibanTemplate[41].format = QLatin1String("24n"); ibanTemplate[41].codes = QLatin1String("PL");
   ibanTemplate[42].country = QLatin1String("Portugal"); ibanTemplate[42].length = 25; ibanTemplate[42].format = QLatin1String("21n"); ibanTemplate[42].codes = QLatin1String("PT");
   ibanTemplate[43].country = QLatin1String("Romania"); ibanTemplate[43].length = 24; ibanTemplate[43].format = QLatin1String("4a,16c"); ibanTemplate[43].codes = QLatin1String("RO");
   ibanTemplate[44].country = QLatin1String("San Marino"); ibanTemplate[44].length = 27; ibanTemplate[44].format = QLatin1String("1a,10n,12c"); ibanTemplate[44].codes = QLatin1String("SM");
   ibanTemplate[45].country = QLatin1String("Saudi Arabia"); ibanTemplate[45].length = 24; ibanTemplate[45].format = QLatin1String("2n,18c"); ibanTemplate[45].codes = QLatin1String("SA");
   ibanTemplate[46].country = QLatin1String("Serbia"); ibanTemplate[46].length = 22; ibanTemplate[46].format = QLatin1String("18n"); ibanTemplate[46].codes = QLatin1String("RS");
   ibanTemplate[47].country = QLatin1String("Slovakia"); ibanTemplate[47].length = 24; ibanTemplate[47].format = QLatin1String("20n"); ibanTemplate[47].codes = QLatin1String("SK");
   ibanTemplate[48].country = QLatin1String("Slovenia"); ibanTemplate[48].length = 19; ibanTemplate[48].format = QLatin1String("15n"); ibanTemplate[48].codes = QLatin1String("SI");
   ibanTemplate[49].country = QLatin1String("Spain"); ibanTemplate[49].length = 24; ibanTemplate[49].format = QLatin1String("20n"); ibanTemplate[49].codes = QLatin1String("ES");
   ibanTemplate[50].country = QLatin1String("Sweden"); ibanTemplate[50].length = 24; ibanTemplate[50].format = QLatin1String("20n"); ibanTemplate[50].codes = QLatin1String("SE");
   ibanTemplate[51].country = QLatin1String("Switzerland"); ibanTemplate[51].length = 21; ibanTemplate[51].format = QLatin1String("5n,12c"); ibanTemplate[51].codes = QLatin1String("CH");
   ibanTemplate[52].country = QLatin1String("Tunisia"); ibanTemplate[52].length = 24; ibanTemplate[52].format = QLatin1String("20n"); ibanTemplate[52].codes = QLatin1String("TN");
   ibanTemplate[53].country = QLatin1String("Turkey"); ibanTemplate[53].length = 26; ibanTemplate[53].format = QLatin1String("5n,17c"); ibanTemplate[53].codes = QLatin1String("TR");
   ibanTemplate[54].country = QLatin1String("United Arab Emirates"); ibanTemplate[54].length = 23; ibanTemplate[54].format = QLatin1String("3n,16n"); ibanTemplate[54].codes = QLatin1String("AE");
   ibanTemplate[55].country = QLatin1String("United Kingdom[Note 4]"); ibanTemplate[55].length = 22; ibanTemplate[55].format = QLatin1String("4a,14n"); ibanTemplate[55].codes = QLatin1String("GB");
   // create reg exp from templates
   QStringList regexp_all;
   foreach (IbanTemplate t, ibanTemplate){
      QString regexp1;
      // standardized first block: country codes (France uses more than one) and 2 checksum digits
      regexp1.append(QLatin1String("("))
             .append(QRegExp::escape(t.codes.remove(QLatin1Char(' '))).replace(QLatin1Char(','), QLatin1Char('|')))
             .append(QLatin1String(")"))
             .append(QLatin1String("\\d\\d"));
      // BBAN fields
      QStringList bbanFields = t.format.split(QLatin1Char(','));
      foreach (QString bbanField, bbanFields){
         bbanField.remove(QLatin1Char(' '));
         Q_ASSERT_X(bbanField.left(bbanField.length() - 1).toInt() > 0, "BBAN format: count is wrong for IBAN", t.country.toLatin1());
         QChar formatSymbol(bbanField.at(bbanField.length() - 1));
         if (formatSymbol == QLatin1Char('n')) regexp1.append(QLatin1String("[0-9]"));
         else if (formatSymbol == QLatin1Char('a')) regexp1.append(QLatin1String("[A-Z]"));
         else if (formatSymbol == QLatin1Char('c')) regexp1.append(QLatin1String("[A-Z0-9]"));
         else  Q_ASSERT_X(false, "BBAN format: format symbol is wrong for IBAN", t.country.toLatin1());
         regexp1.append(QLatin1String("{")).append(bbanField.left(bbanField.length() - 1)).append(QLatin1String("}"));}
      regexp_all.append(regexp1);}
   setRegExp(QRegExp(regexp_all.join(QLatin1String("|"))));
   Q_ASSERT_X(regExp().isValid(), "invalid regExp", regExp().pattern().toLatin1());}

IbanValidator::State IbanValidator::validate(QString& input, int& pos) const{
   // qDebug() << "IbanValidator::validate" << "validate IBAN string";
   QString iban(input);
   // qDebug() << "1. basic check by regular expression (parent class) of" << iban;
   iban.remove(QLatin1Char(' '));    // generously ignore spaces
   iban = iban.toUpper();            // generously accept non-capitalized letters
   State result = QRegExpValidator::validate(iban, pos);
   if (result != QValidator::Acceptable) return result;
   // qDebug() << "2. string passed reg exp validation and is forwarded to checksum calculation" << iban;
   QString first4(iban.left(4));
   iban.remove(0, 4);
   iban.append(first4);
   QString ibanNumeric;
   for (int i(0); i < iban.length(); ++i){
      QChar character(iban.at(i));
      Q_ASSERT_X(character.isDigit() || character.isUpper(), "illegal character survived QRegExp validation", QString(character).toLatin1());
      if (character.isDigit()) ibanNumeric.append(character);
      else ibanNumeric.append(QString::number(character.toAscii() - QChar(QLatin1Char('A')).toAscii() + 10));}
   if (mod97(ibanNumeric) == 1) return QValidator::Acceptable;
   else return QValidator::Invalid;}

void IbanValidator::fixup(QString& input) const {
   // qDebug() << "IbanValidator::fixup" << "nicely format IBAN";
   // qDebug() << "1. capitalize all letters in" << input;
   input = input.toUpper();
   // qDebug() << "2. remove all spaces in" << input;
   input.remove(QLatin1Char(' '));
   // qDebug() << "3. place spaces every four symbols in" << input;
   if (input.length() > 4) for (int i(input.length() / 4 * 4); i > 0; i = i - 4)
                input.insert(i, QLatin1String(" "));
   // qDebug() << "4. trim possibly added space at end of" << input;
   input = input.trimmed();}

unsigned int IbanValidator::mod97(const QString& input) const {
   // qDebug() << "IbanValidator::mod97" << "calculate module 97 of" << input;
   int a[30] = {1, 10, 3, 30, 9, 90, 27, 76, 81, 34, 49, 5, 50, 15, 53, 45, 62, 38, 89, 17, 73, 51, 25, 56, 75, 71, 31, 19, 93, 57};
   int ad(0);
   int len = input.length();
   for (int i(0); i < len; ++i) ad += a[i] * (input.at(len - 1- i).toAscii() - QChar(QLatin1Char('0')).toAscii());
   return ad % 97;}
