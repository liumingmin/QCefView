﻿/*
 * File: QCefView_global.h
 * Project: QCefView
 * Created: 29th March 2016
 * Author: Sheen
 * Source: https://github.com/cefview/qcefview
 * Docs: https://cefview.github.io/QCefView/
 */
#ifndef QCEFEVIEW_GLOBAL_H
#define QCEFEVIEW_GLOBAL_H
#pragma once

// clang-format off
#pragma region qt_headers
#include <QtCore/qglobal.h>
#include <QMetaType>
#pragma endregion qt_headers

#ifdef QCEFVIEW_STATIC
    // Static library, no need export
    #define QCEFVIEW_EXPORT
#else
    // Dynamic library
    #ifdef QCEFVIEW_LIB
        // Build QCefView project, export API
        #define QCEFVIEW_EXPORT Q_DECL_EXPORT
    #else
        // Referenced by other project, import API 
        #define QCEFVIEW_EXPORT Q_DECL_IMPORT
        #if _WIN32
            #pragma comment(lib, "QCefView.lib")
        #endif
    #endif
#endif

// CEF version numbers
#define CEF_VERSION_MAJOR 102
/* #undef CEF_VERSION_MINOR */
#define CEF_VERSION_PATCH 10

// clang-format on

#endif // QCEFEVIEW_GLOBAL_H
