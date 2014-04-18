#include "mainwindows.h"

mainwindows::mainwindows(QWidget *parent) :
    QMainWindow(parent), docWidget(new QTextEdit(this)),
    aboutQtAction(new QAction(QIcon(tr(":/images/about.png")), tr("About &Qt"), this)),
    cutAction(new QAction(QIcon(tr(":/images/open.png")), tr("Cu&t"), this)),
    exitAction(new QAction(QIcon(tr(":/images/save.png")), tr("Exit &Window"), this)),
    newAction(new QAction(QIcon(tr(":/images/new.png")), tr("&New File"), this)),
    saveAction(new QAction(QIcon(tr(":/images/save.png")), tr("Save"), this)),
    mainMenu(new QMenu), toolBar(new QToolBar)
{
    setNewWindowTitle(QString(tr("%1[*] - %2")).arg(tr("unnamed")).arg(tr("SDI")));
    setCentralWidget(docWidget.get());
    createActions();
    createMenus();
    createToolBars();
    statusBar()->showMessage(tr("Done"));

    QObject::connect(docWidget->document(), SIGNAL(modificationChanged(bool)),
                     this, SLOT(setWindowModified(bool)));
}

void mainwindows::createActions()
{
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create new File"));
    QObject::connect(newAction.get(), SIGNAL(triggered()), this, SLOT(fileNew()));

    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut selected document"));
    cutAction->setEnabled(false);
    QObject::connect(docWidget.get(), SIGNAL(copyAvailable(bool)), cutAction.get(), SLOT(setEnabled(bool)));
    QObject::connect(cutAction.get(), SIGNAL(triggered()), docWidget.get(), SLOT(cut()));

    exitAction->setShortcut(tr("Ctrl+W"));
    exitAction->setStatusTip(tr("Close document and Exits"));
    QObject::connect(exitAction.get(), SIGNAL(triggered()), this, SLOT(close()));

    aboutQtAction->setStatusTip(tr("About Qt Toolkit"));
    QObject::connect(aboutQtAction.get(), SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save document"));
    QObject::connect(saveAction.get(), SIGNAL(triggered()), this, SLOT(fileSave()));
}

void mainwindows::createMenus()
{
    mainMenu = menuBar()->addMenu(tr("&File"));
    mainMenu->addAction(newAction.get());
    mainMenu->addAction(aboutQtAction.get());

    mainMenu->addAction(saveAction.get());
    mainMenu->addAction(exitAction.get());

    mainMenu = menuBar()->addMenu(tr("&Edit"));
    mainMenu->addAction(cutAction.get());
}

void mainwindows::createToolBars()
{
    toolBar = addToolBar(tr("File"));
    toolBar->addAction(newAction.get());
    toolBar->addSeparator();
    toolBar->addAction(cutAction.get());
    toolBar->addSeparator();
    toolBar->addAction(aboutQtAction.get());
    toolBar->addSeparator();
    toolBar->addAction(exitAction.get());
}

void mainwindows::fileNew()
{
    (new mainwindows())->show();
}

void mainwindows::fileSave()
{
    static bool fileSaved = false;
    if(!fileSaved){
        fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::currentPath());
        saveNewFile(fileName);
        if(!fileName.isEmpty()){
            QString new_fileName = fileName.mid(fileName.lastIndexOf('/')).remove(0, 1);
            setNewWindowTitle(new_fileName);
        }
        fileSaved = true;
    } else {
        if(docWidget->document()->isModified()){
            saveNewFile(fileName);
        } else {
            return;
        }
    }
}

void mainwindows::closeEvent(QCloseEvent *event)
{
    if(isSafeToClose()){
        event->accept();
    } else {
        event->ignore();
    }
}

bool mainwindows::isSafeToClose()
{
    if(isWindowModified()){
        switch(QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to exit?"),
                                    QMessageBox::Yes | QMessageBox::No))
        {
        case QMessageBox::Yes:
            return true;
        default:
            return false;
        }
    }
    return true;
}

void mainwindows::saveNewFile(const QString &file_name)
{
    QFile newFile(file_name);
    newFile.open(QFile::WriteOnly);
    QTextStream cout(&newFile);

    if(!newFile.isOpen()){
        QMessageBox::critical(this, tr("Error"), tr("Unable to save new changes"),
                              QMessageBox::Ok);
        return;
    }
    if(newFile.exists()){
        cout << docWidget->document()->toPlainText();
    } else {
        cout << docWidget->document()->toPlainText();
    }

    newFile.close();
}

void mainwindows::setNewWindowTitle(const QString &filename)
{
    setWindowTitle(QString(tr("%1").arg(filename)));
}

mainwindows::~mainwindows(){ }
