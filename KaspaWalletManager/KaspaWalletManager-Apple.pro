# This file is intended to be used on MacOS host machine to build applications for MacOs, IOS and Android.

QT       += core gui network websockets multimedia multimediawidgets

#unix: QMAKE_CXXFLAGS += -std=c++11
#unix: QMAKE_LFLAGS_DEBUG += -std=c++11
#win32-g++: QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

unix:!macx {

}
macx: {
    TARGET = ../KaspaWalletManager_MacOsX/KaspaWalletManager_MacOsX
    CONFIG += QMAKE_APPLE_DEVICE_ARCHS="x86_64 x86_64h arm64"
    CONFIG += app_bundle
    CONFIG += sdk_no_version_check
    MACDEPLOY = `echo $$QMAKE_QMAKE | sed 's/qmake/macdeployqt/g'`
    #QMAKE_POST_LINK = $$MACDEPLOY $$OUT_PWD/$$TARGET\.app -qmldir=$$PWD -verbose=1
    QMAKE_INFO_PLIST = macos/Info.plist
    INCLUDEPATH += $$PWD/lib
    DEPENDPATH += $$PWD/lib
    INCLUDEPATH += $$PWD/lib/absl
    DEPENDPATH += $$PWD/lib/absl
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    LIBS +=  $$PWD/lib/libprotobuf/macosx/libprotobuf.a
    INCLUDEPATH += $$PWD/lib/libgrpc
    DEPENDPATH += $$PWD/lib/libgrpc
    LIBS += -L$$PWD/lib/libgrpc/macosx/ -lgrpc++.1.51.1

    INCLUDEPATH += $$PWD/lib/openssl
    DEPENDPATH += $$PWD/lib/openssl
    LIBS +=  $$PWD/lib/openssl/macosx/libcrypto.a
    LIBS +=  $$PWD/lib/openssl/macosx/libssl.a
    # LIBS += -L$$PWD/lib/openssl/macosx/ -lcrypto.1.1
    # LIBS += -L$$PWD/lib/openssl/macosx/ -lssl.1.1

SOURCES += \
    api/grpc/protos/macosx/kaspawalletd.grpc.pb.cc \
    api/grpc/protos/macosx/kaspawalletd.pb.cc \
    api/grpc/protos/macosx/messages.grpc.pb.cc \
    api/grpc/protos/macosx/messages.pb.cc \
    api/grpc/protos/macosx/p2p.grpc.pb.cc \
    api/grpc/protos/macosx/p2p.pb.cc \
    api/grpc/protos/macosx/rpc.grpc.pb.cc \
    api/grpc/protos/macosx/rpc.pb.cc
HEADERS += \
    api/grpc/protos/macosx/kaspawalletd.grpc.pb.h \
    api/grpc/protos/macosx/kaspawalletd.pb.h \
    api/grpc/protos/macosx/messages.grpc.pb.h \
    api/grpc/protos/macosx/messages.pb.h \
    api/grpc/protos/macosx/p2p.grpc.pb.h \
    api/grpc/protos/macosx/p2p.pb.h \
    api/grpc/protos/macosx/rpc.grpc.pb.h \
    api/grpc/protos/macosx/rpc.pb.h
}
ios {
    TARGET = ../KaspaWalletManager_iOS/KaspaWalletManager_iOS
    QMAKE_INFO_PLIST = ios/Info.plist
    ios_icon.files = $$files($$PWD/ios/*.png)
    QMAKE_BUNDLE_DATA += ios_icon
    INCLUDEPATH += $$PWD/lib
    DEPENDPATH += $$PWD/lib
    INCLUDEPATH += $$PWD/lib/absl
    DEPENDPATH += $$PWD/lib/absl
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    LIBS +=  $$PWD/lib/libprotobuf/android/libprotobuf.a
    INCLUDEPATH += $$PWD/lib/libgrpc
    DEPENDPATH += $$PWD/lib/libgrpc
    LIBS += -L$$PWD/lib/libgrpc/android/ -lgrpc++.1.51.1
}
android: {
    TARGET = ../KaspaWalletManager_Android/KaspaWalletManager_Android
    #LIBS +=  $$PWD/lib/libprotobuf/android/libprotobuf.so
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    #include(/Users/cry/Library/Android/sdk/android_openssl/openssl.pri)
    #LIBS += -L$$PWD/lib/libprotobuf/android -lprotobuf

    #PRE_TARGETDEPS += $$PWD/lib/libprotobuf/android/libprotobuf.so

DISTFILES += \
        android/AndroidManifest.xml \
	android/build.gradle \
	android/gradle.properties \
	android/gradle/wrapper/gradle-wrapper.jar \
	android/gradle/wrapper/gradle-wrapper.properties \
	android/gradlew \
	android/gradlew.bat \
	android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

}
win32: {
    TARGET = ../../KaspaWalletManager_Windows/KaspaWalletManager
    LIBS +=  $$PWD/lib/libprotobuf/win64/libprotobuf.a
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/grpc/grpc.cpp \
    api/grpc/message.cpp \
    api/web/webclass.cpp \
    api/web/webget.cpp \
    crypto/aes.cpp \
    crypto/base58Encoding.cpp \
    crypto/bip32.c \
    crypto/bip39.c \
    crypto/ecc.cpp \
    crypto/hmac.c \
    crypto/libbase58.c \
    crypto/memzero.c \
    crypto/pbkdf2.c \
    crypto/rand.c \
    crypto/sha2.c \
    crypto/signatures.cpp \
    extensions/qrcodegen.cpp \
    external/externaladdressvalidator.cpp \
    globakaspa.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    page/account/pageaccount.cpp \
    page/account/pageaccountlist/pageaccountitemdelegate.cpp \
    page/account/pageaccountlist/pageaccountlist.cpp \
    page/account/subpage/history/pagehistory.cpp \
    page/account/subpage/history/pagehistorylist/pagehistorylist.cpp \
    page/account/subpage/history/pagehistorylist/pagehistorylistmain.cpp \
    page/account/subpage/history/pagetransactiondetail.cpp \
    page/account/subpage/receive/pagereceive.cpp \
    page/account/subpage/send/camera.cpp \
    page/account/subpage/send/pagesend.cpp \
    page/accountManagement/pagenewaccount.cpp \
    page/accountManagement/pageimportwallet.cpp \
    page/accountManagement/pagenewwallet.cpp \
    page/accountManagement/pageopenwallet.cpp \
    page/accountManagement/pagerecoveraccount.cpp \
    page/accountManagement/pageshowseed.cpp \
    page/more/pagemore.cpp \
    page/more/subpage/settings/pagesettings.cpp \
    storage/storagecommon.cpp \
    storage/storageinternal.cpp \
    storage/storagesettings.cpp \
    translate/translate.cpp \
    util/bech32.cpp \
    wallet/history.cpp \
    wallet/walletgrpc.cpp

HEADERS += \
    api/grpc/base_message.h \
    api/grpc/error.h \
    api/grpc/get_balance_by_address.h \
    api/grpc/message.h \
    api/grpc/grpc.h \
    api/web/webclass.h \
    api/web/webget.h \
    crypto/aes.h \
    crypto/base58Encoding.h \
    crypto/bip32.h \
    crypto/bip39.h \
    crypto/bip39_english.h \
    crypto/ecc.h \
    crypto/hmac.h \
    crypto/libbase58.h \
    crypto/memzero.h \
    crypto/options.h \
    crypto/pbkdf2.h \
    crypto/rand.h \
    crypto/sha2.h \
    crypto/signatures.h \
    errors.h \
    extensions/qrcodegen.h \
    external/externaladdressvalidator.h \
    globakaspa.h \
    global.h \
    color.h \
    mainwindow.h \
    page/account/pageaccountlist/pageaccountitemdelegateprivate.h \
    page/account/pageaccount.h \
    page/account/pageaccountlist/pageaccountitemdelegate.h \
    page/account/pageaccountlist/pageaccountlist.h \
    page/account/subpage/history/pagehistory.h \
    page/account/subpage/history/pagehistorylist/pagehistorylist.h \
    page/account/subpage/history/pagehistorylist/pagehistorylistmain.h \
    page/account/subpage/history/pagetransactiondetail.h \
    page/account/subpage/receive/pagereceive.h \
    page/account/subpage/send/camera.h \
    page/account/subpage/send/pagesend.h \
    page/accountManagement/pagenewaccount.h \
    page/accountManagement/pageimportwallet.h \
    page/accountManagement/pagenewwallet.h \
    page/accountManagement/pageopenwallet.h \
    page/accountManagement/pagerecoveraccount.h \
    page/accountManagement/pageshowseed.h \
    page/more/pagemore.h \
    page/more/subpage/settings/pagesettings.h \
    storage/storagecommon.h \
    storage/storageinternal.h \
    storage/storagesettings.h \
    style.h \
    translate/translate.h \
    util/bech32.h \
    wallet/history.h \
    wallet/walletgrpc.h

FORMS += \
    mainwindow.ui \
    page/account/pageaccount.ui \
    page/account/subpage/history/pagehistory.ui \
    page/account/subpage/history/pagehistorylist/pagehistorylist.ui \
    page/account/subpage/history/pagehistorylist/pagehistorylistmain.ui \
    page/account/subpage/history/pagetransactiondetail.ui \
    page/account/subpage/receive/pagereceive.ui \
    page/account/subpage/send/camera.ui \
    page/account/subpage/send/pagesend.ui \
    page/accountManagement/pagenewaccount.ui \
    page/accountManagement/pageimportwallet.ui \
    page/accountManagement/pagenewwallet.ui \
    page/accountManagement/pageopenwallet.ui \
    page/accountManagement/pagerecoveraccount.ui \
    page/accountManagement/pageshowseed.ui \
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

include(extensions/QZXing/QZXing.pri)


