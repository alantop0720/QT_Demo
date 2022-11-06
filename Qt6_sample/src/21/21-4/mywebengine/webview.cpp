#include "webview.h"
#include "mainwindow.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
}

QWebEngineView *WebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
    mainWindow = new MainWindow(this);
    mainWindow->show();
    return mainWindow->createView();
}
