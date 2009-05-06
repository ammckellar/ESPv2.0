#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPrintPreviewDialog>

#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    ui->setupUi(this);    
    setupFileActions();

    QString s1 = "asdf", s2 = "qwewrty";
    const QStringList ql = (QStringList() << s1 << s2);

    ui->comboBox->addItems(ql);
    ui->comboBox->addItem("hopefully git will");
    ui->comboBox->addItem("eventually work!");
    //ui->graphicsView->

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFileActions()
{
    QMenu *menu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    a = new QAction(QIcon(rsrcPath + "/filenew.png"), tr("&New"), this);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    menu->addAction(a);

    a = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("&Open"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    menu->addAction(a);

    menu->addSeparator();

    a = new QAction(tr("&Quit"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(a, SIGNAL(triggered()), qApp, SLOT(quit()));
    menu->addAction(a);
}

void MainWindow::fileNew()
{

}

void MainWindow::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open a File..."),
                 QString(), tr("All Files(*)"));
    //tr("Card Files (*.cd);;Text Files (*.txt *.rtf);;All Files (*)"));
    if (!fn.isEmpty())
        load(fn);
}

bool MainWindow::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        ui->textEdit->setHtml(str);
    } else {
        str = QString::fromLocal8Bit(data);
        ui->textEdit->setPlainText(str);
    }
    QStringList compoundList = str.split("\n");
    //Add each compound to the dropdown menu
    foreach(QString compound, compoundList)
       ui->comboBox->addItem(compound);


//    QMessageBox msgBox;
//    msgBox.setText(s.at(0));
//    msgBox.exec();

    setCurrentFileName(f);
    return true;
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    //textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.cd";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("ESP v2.0")));
    setWindowModified(false);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
        "rich text editing facilities in action, providing an example "
        "document for you to experiment with."));
}
