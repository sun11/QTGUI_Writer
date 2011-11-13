#ifndef TEXT_H
#define TEXT_H

#include <QTextEdit>
#include <mainwindow.h>

enum{ MagicNumber =0x7F51C883 };
class Text : public QWidget
{
 public:
    QString str;
    QTextEdit *myText;
    bool writeFile(const QString &fileName);
//    bool readFile(const QString &fileName);
};
#endif // TEXT_H
