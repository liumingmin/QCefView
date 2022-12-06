set QTDIR=E:\cpp\5.15.2_vs2017_dynamic_x64

set http_proxy=http://127.0.0.1:10808
set https_proxy=http://127.0.0.1:10808

cmake -S . ^
-G "Visual Studio 15 2017" ^
-B .build/windows.x86_64 ^
-A x64 ^
-DPROJECT_ARCH=x86_64 ^
-DBUILD_DEMO=ON ^
-DCMAKE_INSTALL_PREFIX:PATH="%cd%/out/windows.x86_64"