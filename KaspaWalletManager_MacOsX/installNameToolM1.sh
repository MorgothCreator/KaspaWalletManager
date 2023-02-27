#!/bin/bash


install_name_tool -change @rpath/QtMultimediaWidgets.framework/Versions/A/QtMultimediaWidgets @executable_path/../Frameworks/QtMultimediaWidgets.framework/Versions/A/QtMultimediaWidgets ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtMultimedia.framework/Versions/A/QtMultimedia @executable_path/../Frameworks/QtMultimedia.framework/Versions/A/QtMultimedia ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtQuick.framework/Versions/A/QtQuick @executable_path/../Frameworks/QtQuick.framework/Versions/A/QtQuick ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtQmlModels.framework/Versions/A/QtQmlModels @executable_path/../Frameworks/QtQmlModels.framework/Versions/A/QtQmlModels ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtQml.framework/Versions/A/QtQml @executable_path/../Frameworks/QtQml.framework/Versions/A/QtQml ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtCharts.framework/Versions/A/QtCharts @executable_path/../Frameworks/QtCharts.framework/Versions/A/QtCharts ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtOpenGLWidgets.framework/Versions/A/QtOpenGLWidgets @executable_path/../Frameworks/QtOpenGLWidgets.framework/Versions/A/QtOpenGLWidgets ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtWidgets.framework/Versions/A/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/A/QtWidgets ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtOpenGL.framework/Versions/A/QtOpenGL @executable_path/../Frameworks/QtOpenGL.framework/Versions/A/QtOpenGL ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtGui.framework/Versions/A/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/A/QtGui ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtWebSockets.framework/Versions/A/QtWebSockets @executable_path/../Frameworks/QtWebSockets.framework/Versions/A/QtWebSockets ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtNetwork.framework/Versions/A/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/A/QtNetwork ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtCore5Compat.framework/Versions/A/QtCore5Compat @executable_path/../Frameworks/QtCore5Compat.framework/Versions/A/QtCore5Compat ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change @rpath/QtCore.framework/Versions/A/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/A/QtCore ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
install_name_tool -change /opt/homebrew/opt/grpc/lib/libgrpc++.1.51.dylib @executable_path/../Frameworks/libgrpc++.1.51.dylib ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX
otool -l ~/Documents/GitHub_Kaspa/KaspaWalletManager/KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX.app/Contents/MacOS/KaspaWalletManager_MacOsX