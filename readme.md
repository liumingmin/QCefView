# QCefView https://cefview.github.io/QCefView/

## [Quick Start](https://cefview.github.io/QCefView/)

**!important: Edit generate-win-x86_64.bat file content,modify QTDIR and http_proxy/https_proxy to your config. enjoy!**
> cef lib version: https://cef-builds.spotifycdn.com/index.html#windows64:89 <br>
 cef source code: https://chromium.googlesource.com/chromium/src/+/refs/tags/89.0.4389.114

QCefView is a Qt based QWidget which encapsulates [CEF](https://bitbucket.org/chromiumembedded/cef). With QCefView you can build your application UI in frontend developing way to boost your project. And what's more you can completely decouple the UI and business logic in your project.

| Platform |  Lastest Build Status  | OSR Production Ready  | NCW Production Ready  |
|---|---|---|---|
| Windows-x86_64 | [![Build on Windows](https://github.com/CefView/QCefView/actions/workflows/build-windows-x86_64.yml/badge.svg)](https://github.com/CefView/QCefView/actions/workflows/build-windows-x86_64.yml) | :heavy_check_mark: | :heavy_check_mark: |
| macOS-x86_64 | [![Build on macOS](https://github.com/CefView/QCefView/actions/workflows/build-macos-x86_64.yml/badge.svg)](https://github.com/CefView/QCefView/actions/workflows/build-macos-x86_64.yml)          | :heavy_check_mark: | :heavy_check_mark: |
| Linux-x86_64 | [![Build on Linux](https://github.com/CefView/QCefView/actions/workflows/build-linux-x86_64.yml/badge.svg)](https://github.com/CefView/QCefView/actions/workflows/build-linux-x86_64.yml)         | :heavy_check_mark: | :x: |

**OSR** = Offscreen Rendering Mode **NCW** = Native Child Window Mode

## About OSR mode

QCefView supports CEF offscreen rendering mode and this feature is enabled by default at runtime, to disable OSR mode you need to set the config item  setWindowlessRenderingEnabled to false
```cpp
  QCefConfig config;

// WindowlessRenderingEnabled is set to true by default, set to false to disable the OSR mode
 QCefConfig.setWindowlessRenderingEnabled(false)
 ```

QCefView currently uses Qt Software Rasterizer as the backend paint engine for best compatibility, thus the rendering performance is not so good to be applied for all business scenarios. If you are going to host WegGL games, video sites or some other Web Apps with high rendering performance, Non OSR mode (Native Child Window mode) is recommended.

### Why not OpenGL/DirectX/Metal?

QCefView was designed to be a common Qt widget for Desktop application, so the compatibility is the first important requirement. We can switch the backend engine from Software Rasterizer to OpenGL/DirectX/Metal but this will increase the complexity and decrease the compatibility of QCefView. 

For example if we use OpenGL as the backend engine then all the applications with QCefView introduced will be switched to OpenGL backend automatically. I believe not all users want this to happen. 

DirectX/Metal are platform dependent and they are not supported natively by Qt. If we provide QCefView with extra dependencies individually, this makes QCefView so different with other components in Qt Framework.

But if you must use OSR and the rendering performance is vital, you can try to switch the backend with whatever you want.

## Contributing
This project welcomes contributions and suggestions. Make sure to align your code style with the configuration defined by .clang-format file

Making contributions is not a hard thing.

- Solving an issue(maybe just answering a question raised in issues list or gitter)
- Fixing/Issuing a bug
- Improving the documents and even fixing a typo 

are important contributions to QCefView
If you would like to become one of QCefView's maintainers to contribute more (e.g. help merge PR, triage issues), please contact me by email(sheentianshen#gmail.com). I am glad to help you to set the right permission.
