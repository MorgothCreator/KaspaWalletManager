# This file is intended to be used on MacOS host machine to build applications for MacOs, IOS and Android.

QT       += core gui network websockets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

android: {
    #TARGET = ../KaspaWalletManager_Android/KaspaWalletManager_Android
    #LIBS +=  $$PWD/lib/libprotobuf/android/libprotobuf.a
    TARGET = ../KaspaWalletManager_Android/KaspaWalletManager_Android
    LIBS +=  $$PWD/lib/libprotobuf/android/libprotobuf.so
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    #LIBS += -L$$PWD/lib/libprotobuf/android -lprotobuf


    #PRE_TARGETDEPS += $$PWD/lib/libprotobuf/android/libprotobuf.so
}
win32: {
    TARGET = ../../KaspaWalletManager_Windows/KaspaWalletManager
    LIBS += $$PWD/lib/libprotobuf/win64/libprotobuf.a
    LIBS += -L$$PWD/lib/libprotobuf/win64/ -lprotobuf
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/grpc/protos/kaspawalletd.pb.cc \
    api/grpc/grpc.cpp \
    api/rpc/rpcsocket.cpp \
    api/web/webclass.cpp \
    api/web/webget.cpp \
    crypto/aes.cpp \
    crypto/base58Encoding.cpp \
    crypto/ecc.cpp \
    crypto/signatures.cpp \
    extensions/qrcodegen.cpp \
    external/externaladdressvalidator.cpp \
    global.cpp \
    globallyra.cpp \
    main.cpp \
    mainwindow.cpp \
    api/rpc/rpcclass.cpp \
    page/account/pageaccount.cpp \
    page/account/pageaccountlist/pageaccountitemdelegate.cpp \
    page/account/pageaccountlist/pageaccountlist.cpp \
    page/account/subpage/history/pagehistory.cpp \
    page/account/subpage/history/pagehistorylist/pagehistoryitemdelegate.cpp \
    page/account/subpage/history/pagehistorylist/pagehistorylist.cpp \
    page/account/subpage/history/pagetransactiondetail.cpp \
    page/account/subpage/receive/pagereceive.cpp \
    page/account/subpage/send/camera.cpp \
    page/account/subpage/send/pagesend.cpp \
    page/accountManagement/pagenewaccount.cpp \
    page/accountManagement/pageimportwallet.cpp \
    page/accountManagement/pagenewwallet.cpp \
    page/accountManagement/pageopenwallet.cpp \
    page/accountManagement/pagerecoveraccount.cpp \
    page/more/pagemore.cpp \
    page/more/subpage/settings/pagesettings.cpp \
    storage/storagecommon.cpp \
    storage/storageinternal.cpp \
    storage/storagesettings.cpp \
    translate/translate.cpp \
    wallet/history.cpp \
    wallet/walletrpc.cpp

HEADERS += \
    api/grpc/protos/kaspawalletd.pb.h \
    api/grpc/grpc.h \
    api/rpc/rpcsocket.h \
    api/web/webclass.h \
    api/web/webget.h \
    crypto/aes.h \
    crypto/base58Encoding.h \
    crypto/ecc.h \
    crypto/signatures.h \
    errors.h \
    extensions/qrcodegen.h \
    external/externaladdressvalidator.h \
    global.h \
    color.h \
    globallyra.h \
    mainwindow.h \
    api/rpc/rpcclass.h \
    page/account/pageaccountlist/pageaccountitemdelegateprivate.h \
    page/account/pageaccount.h \
    page/account/pageaccountlist/pageaccountitemdelegate.h \
    page/account/pageaccountlist/pageaccountlist.h \
    page/account/subpage/history/pagehistory.h \
    page/account/subpage/history/pagehistorylist/pagehistorylist.h \
    page/account/subpage/history/pagehistorylist/pagehistoryitemdelegate.h \
    page/account/subpage/history/pagehistorylist/pagehistoryitemdelegateprivate.h \
    page/account/subpage/history/pagetransactiondetail.h \
    page/account/subpage/receive/pagereceive.h \
    page/account/subpage/send/camera.h \
    page/account/subpage/send/pagesend.h \
    page/accountManagement/pagenewaccount.h \
    page/accountManagement/pageimportwallet.h \
    page/accountManagement/pagenewwallet.h \
    page/accountManagement/pageopenwallet.h \
    page/accountManagement/pagerecoveraccount.h \
    page/more/pagemore.h \
    page/more/subpage/settings/pagesettings.h \
    storage/storagecommon.h \
    storage/storageinternal.h \
    storage/storagesettings.h \
    style.h \
    translate/translate.h \
    wallet/history.h \
    wallet/walletrpc.h

FORMS += \
    mainwindow.ui \
    page/account/pageaccount.ui \
    page/account/subpage/history/pagehistory.ui \
    page/account/subpage/history/pagetransactiondetail.ui \
    page/account/subpage/receive/pagereceive.ui \
    page/account/subpage/send/camera.ui \
    page/account/subpage/send/pagesend.ui \
    page/accountManagement/pagenewaccount.ui \
    page/accountManagement/pageimportwallet.ui \
    page/accountManagement/pagenewwallet.ui \
    page/accountManagement/pageopenwallet.ui \
    page/accountManagement/pagerecoveraccount.ui \
    page/more/pagemore.ui \
    page/more/subpage/settings/pagesettings.ui


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
RC_ICONS = res/ic/icon.ico
ICON = res/ic/icon.icns

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

include(extensions/QZXing/QZXing.pri)

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

