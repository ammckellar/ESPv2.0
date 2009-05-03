#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();    

private:
    Ui::MainWindow *ui;
    QString fileName;
    void setupFileActions();    
    void setCurrentFileName(const QString &f);
    bool load(const QString &f);

public slots:
    void fileNew();
    void fileOpen();
    void about();


};

#endif // MAINWINDOW_H
