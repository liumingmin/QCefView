﻿#include "QCefWindow.h"

#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QDebug>
#pragma endregion qt_headers

QCefWindow::QCefWindow(QWindow* parent, QCefView* hostView /*= 0*/)
  : QWindow(parent)
  , hwndCefBrowser_(0)
{
  setFlags(Qt::FramelessWindowHint);
}

QCefWindow::~QCefWindow()
{
  if (hwndCefBrowser_) {
    hwndCefBrowser_ = 0;
  }
}

void
QCefWindow::setCefBrowserWindow(CefWindowHandle win)
{
  hwndCefBrowser_ = win;
  syncCefBrowserWindow();
}

void
QCefWindow::syncCefBrowserWindow()
{
#if defined(OS_WINDOWS)
  double w = width() * devicePixelRatio();
  double h = height() * devicePixelRatio();
  if (hwndCefBrowser_)
    ::SetWindowPos(hwndCefBrowser_, NULL, 0, 0, ceil(w), ceil(h), SWP_NOZORDER | SWP_NOSENDCHANGING | SWP_DEFERERASE);
#else
  return;
#endif
}

void
QCefWindow::exposeEvent(QExposeEvent* e)
{
  syncCefBrowserWindow();
  QWindow::exposeEvent(e);
}

void
QCefWindow::resizeEvent(QResizeEvent* e)
{
  syncCefBrowserWindow();
  QWindow::resizeEvent(e);
}
