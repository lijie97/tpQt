#ifndef REGEXPDIALOG_H
#define REGEXPDIALOG_H

#include <QDialog>
#include <QtMultimedia/qsoundeffect.h>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

class RegExpDialog : public QDialog
{
    Q_OBJECT

public:
    RegExpDialog(QWidget *parent = 0);

private slots:
    void refresh();

private:
    QLabel *patternLabel;
    QLabel *syntaxLabel;
    QLabel *textLabel;
    QLabel *capturedLabel;
    QLabel *pitureLabel;
    QLineEdit *patternEdit;
    QLineEdit *textEdit;
    QLineEdit *caputredEdit;
    QImage *yesImage;
    QImage *noImage;
    QImage *maybeImage;
    QImage *showImage;
    QSoundEffect *sound;
};

#endif
