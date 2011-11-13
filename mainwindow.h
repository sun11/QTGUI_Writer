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

protected:
//    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveFile(const QString &);
    bool saveAs();

    void about();
 //   void select_all();


private:
    Ui::MainWindow *ui;
    QString strippedName(const QString &);
    QString fileName;
    bool okToContinue();
};

#endif // MAINWINDOW_H
