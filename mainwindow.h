#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QtWidgets>
#include <QApplication>
#include <QTextStream>
#include "memory.h"

class mainwindows : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindows(QWidget *parent = 0);
    ~mainwindows();
    void createActions();
    void createMenus();
    void createToolBars();
    void closeEvent(QCloseEvent *);
    bool isSafeToClose();
    void saveNewFile(const QString &file_name);
    void setNewWindowTitle(const QString &filename);
signals:
    
public slots:
    void fileNew();
    void fileSave();

private:
    sp::unique_ptr<QTextEdit> docWidget;

    sp::unique_ptr<QAction> aboutQtAction, cutAction, exitAction, newAction, saveAction;
    QMenu *mainMenu;
    QToolBar *toolBar;

    QString fileName;
};

#endif // MAINWINDOWS_H
