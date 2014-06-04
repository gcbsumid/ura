#include <QtWidgets>
#include <iostream>
#include "AppWindow.hpp"

AppWindow::AppWindow() {
    setWindowTitle("488 Tetrominoes on the Wall");

    QVBoxLayout *layout = new QVBoxLayout;
    // m_menubar = new QMenuBar;
    m_viewer = new Viewer(this);
    layout->addWidget(m_viewer);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    createActions();
    createMenu();
}

void AppWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    } else if (event->key() == Qt::Key_T) {
        std::cerr << "Hello!" << std::endl;
    } else {
        QWidget::keyPressEvent(event);
    }
}

void AppWindow::createActions() {
    // Creates a new action for quiting and pushes it onto the menu actions vector 
    QAction* quitAct = new QAction(tr("&Quit"), this);
    m_menu_actions.push_back(quitAct);

    // We set the accelerator keys
    // Alternatively, you could use: setShortcuts(Qt::CTRL + Qt::Key_P); 
    quitAct->setShortcuts(QKeySequence::Quit);

    // Set the tip
    quitAct->setStatusTip(tr("Exits the file"));

    // Connect the action with the signal and slot designated
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void AppWindow::createMenu() {
    m_menu_app = menuBar()->addMenu(tr("&Application"));

    for (auto& action : m_menu_actions) {
        m_menu_app->addAction(action);
    }
}

