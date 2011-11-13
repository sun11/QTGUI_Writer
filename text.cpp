#include <QtGui>
#include "text.h"
#include "ui_mainwindow.h"

Text::Text(QWidget *parent) : QWidget(parent)
{
 //   text = new Text;
    myText = new QTextEdit;
}


bool Text::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this,tr("Text"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString str = Text.toPlainText();
    out << str;
    }
    QApplication::restoreOverrideCursor();
    return true;
}
