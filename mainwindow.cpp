#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->action_New->setShortcut(QKeySequence::New);
    connect(ui->action_New,SIGNAL(triggered()),this,SLOT(newFile()));

    ui->action_Open->setShortcut(QKeySequence::Open);
    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(open()));

    ui->action_Save->setShortcut(QKeySequence::Save);
    connect(ui->action_Save,SIGNAL(triggered()),this,SLOT(save()));

    ui->action_Save_As->setShortcut(QKeySequence::SaveAs);
    connect(ui->action_Save_As,SIGNAL(triggered()),this,SLOT(saveAs()));

    ui->action_Exit->setShortcut(QKeySequence::Quit);
    connect(ui->action_Exit,SIGNAL(triggered()),this,SLOT(close()));

    ui->action_Cut->setShortcut(QKeySequence::Cut);
    connect(ui->action_Cut,SIGNAL(triggered()),ui->myText,SLOT(cut()));

    ui->action_Copy->setShortcut(QKeySequence::Copy);
    connect(ui->action_Copy,SIGNAL(triggered()),ui->myText,SLOT(copy()));

    ui->action_Paste->setShortcut(QKeySequence::Paste);
    connect(ui->action_Paste,SIGNAL(triggered()),ui->myText,SLOT(paste()));

    ui->action_Undo->setShortcut(QKeySequence::Undo);
    connect(ui->action_Undo,SIGNAL(triggered()),ui->myText,SLOT(undo()));

    ui->action_Redo->setShortcut(QKeySequence::Redo);
    connect(ui->action_Redo,SIGNAL(triggered()),ui->myText,SLOT(redo()));

    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(about()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if (okToContinue()){
        ui->myText->clear();
        ui->statusBar->showMessage(tr("Created a new file"),2000);
    }
}

void MainWindow::open()
{
    if  (okToContinue()){
        fileName = QFileDialog::getOpenFileName(this,
                                                   tr("Open Text"),"",
                                                   tr("Text files(*.txt);;All files(*)"));
        if (!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,tr("Error"),
                                  tr("Could not open file"));
            return;
        }
        QString contents = file.readAll().constData();
        ui->myText->setPlainText(contents);
        file.close();
        setWindowTitle(strippedName(fileName));
        ui->statusBar->showMessage(tr("Opened file %1").arg(fileName),2000);
        }

    }
}

bool MainWindow::save()
{
    if (fileName.isEmpty()) {
        return saveAs();
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            return false;
        } else {
            QTextStream stream(&file);
            stream << ui->myText->toPlainText();
            stream.flush();
            file.close();
            ui->statusBar->showMessage(tr("File %1 saved").arg(fileName),2000);
            return true;
        }
    }
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    } else {
        QTextStream stream(&file);
        stream << ui->myText->toPlainText();
        stream.flush();
        file.close();
    }


    ui->statusBar->showMessage(tr("File %1 saved").arg(fileName),2000);
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Text"),".",
                                                    tr("Text Files  (*.txt)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
    QMessageBox::about(this,tr("About QTGUI Writer"),
                       tr("<h2>QTGUI Writer 1.0</h2>"
                          "<h4>by 11</h4>"
                          "<p>based on a example<br/>"
                          "in C++ GUI Programming<br/>"
                          "with Qt4 and a tutorial<br/>"
                          "in Nokia's website.</p>"));
}


bool MainWindow::okToContinue()
{
    if (isWindowModified()){
        int r = QMessageBox::warning(this,tr("Text"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (r == QMessageBox::Yes){
            return save();
        } else if (r == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

