/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https:
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https:
** information use the contact form at https:
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtWidgets>
#include <QPushButton>
#include "regexpdialog.h"
RegExpDialog::RegExpDialog(QWidget *parent)
    : QDialog(parent)
{
    patternEdit = new QLineEdit;
    patternEdit->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Preferred);
    patternLabel = new QLabel(tr("&QRegExp à tester"));
    patternLabel->setBuddy(patternEdit);

    textEdit = new QLineEdit;
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    textLabel = new QLabel(tr("&Texte à tester:"));
    textLabel->setBuddy(textEdit);
    caputredEdit = new QLineEdit;
    caputredEdit->setReadOnly(true);
    capturedLabel = new QLabel(tr("Texte capturée"));
    pitureLabel=new QLabel();
    yesImage = new QImage();
    noImage = new QImage();
    maybeImage = new QImage();
    yesImage->load(":/ressource/yes.png");
    noImage->load(":/ressource/no.png");
    maybeImage->load(":/ressource/maybe.png");
    capturedLabel->setBuddy(caputredEdit);
    QPushButton *tester = new QPushButton();
    tester->setText("tester");
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(patternLabel, 0, 0);
    mainLayout->addWidget(patternEdit, 0, 1);
    mainLayout->addWidget(textLabel, 4, 0);
    mainLayout->addWidget(textEdit, 4, 1);
    mainLayout->addWidget(pitureLabel, 4, 2);
    mainLayout->addWidget(capturedLabel, 5, 0);
    mainLayout->addWidget(caputredEdit, 5, 1);
    mainLayout->addWidget(tester, 5, 2);
    setLayout(mainLayout);
    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/ressource/pop.wav"));
    patternEdit->setText(tr("a+"));
    textEdit->setText(tr("aab"));
    setWindowTitle(tr("RegExp"));
    setFixedHeight(sizeHint().height());
    refresh();
    connect(tester, SIGNAL(released()),
            this, SLOT(refresh()));
}
void RegExpDialog::refresh()
{
    setUpdatesEnabled(false);
    qInfo() << "onClick()";
    sound->play();
    QString pattern = patternEdit->text();
    QString text = textEdit->text();
    QRegularExpression rx(pattern);
    QRegularExpressionMatch match = rx.match(text);
    QPalette palette = patternEdit->palette();
    if (rx.isValid()) {
        palette.setColor(QPalette::Text,
                         textEdit->palette().color(QPalette::Text));
    } else {
        palette.setColor(QPalette::Text, Qt::red);
    }
    patternEdit->setPalette(palette);
    QString captured =match.captured();
    caputredEdit->setText(captured); //QString::number(rx.exactMatch(text))
    showImage = captured.size()==text.size()?yesImage:maybeImage;
    showImage = captured.size()==0?noImage:showImage;
    pitureLabel->setPixmap(QPixmap::fromImage(*showImage));
    setUpdatesEnabled(true);
}
