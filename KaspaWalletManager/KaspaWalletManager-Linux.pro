# This file is intended to be used on MacOS host machine to build applications for MacOs, IOS and Android.

QT       += core gui network websockets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

linux-g++ | linux-g++-64 | linux-g++-32 {
    TARGET = ../KaspaWalletManager_Linux/Package/KaspaWalletManager

#QMAKE_CXXFLAGS += pkg-config --cflags= protobuf grpc
#QMAKE_CXXFLAGS += -std=c++11
#QMAKE_LIBS += --libs= protobuf grpc++ -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl

INCLUDEPATH += $$PWD/lib/absl
#DEPENDPATH += $$PWD/lib/absl
INCLUDEPATH += $$PWD/lib/absl/linux
#DEPENDPATH += $$PWD/lib/absl/linux
#LIBS += -L$$PWD/lib/absl/linux/ -l -labsl_synchronization
#LIBS += $$PWD/lib/absl/linux/libabsl_synchronization.a

    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    LIBS += -L$$PWD/lib/libprotobuf/linux/ -lprotobuf
    LIBS += -L$$PWD/lib/libprotobuf/linux/ -lprotobuf-lite
    INCLUDEPATH += $$PWD/lib/libprotobuf/linux
    DEPENDPATH += $$PWD/lib/libprotobuf/linux
    PRE_TARGETDEPS += $$PWD/lib/libprotobuf/linux/libprotobuf.a

    INCLUDEPATH += $$PWD/lib/libgrpc
    DEPENDPATH += $$PWD/lib/libgrpc
    #LIBS += -L$$PWD/lib/libgrpc/linux/ -lgrpcpp
    INCLUDEPATH += $$PWD/lib/libgrpc/linux
    DEPENDPATH += $$PWD/lib/libgrpc/linux
    #LIBS += $$PWD/lib/libgrpc/linux/libgrpcpp.a
    LIBS += $$PWD/lib/common/linux/libcommon.a
    LIBS += -L$$PWD/lib/common/linux/ -lcommon
    #LIBS += $$PWD/lib/libgrpc/linux/libgrpc++.a $$PWD/lib/libgrpc/linux/libgpr.a $$PWD/lib/libgrpc/linux/libaddress_sorting.a $$PWD/lib/absl/linux/libaddress_sorting.a $$PWD/lib/absl/linux/libabsl_cord.a $$PWD/lib/absl/linux/libabsl_status.a $$PWD/lib/absl/linux/libabsl_strings.a  $$PWD/lib/absl/linux/libabsl_synchronization.a $$PWD/lib/absl/linux/libabsl_statusor.a $$PWD/lib/absl/linux/libabsl_bad_optional_access.a  $$PWD/lib/absl/linux/libabsl_bad_variant_access.a $$PWD/lib/absl/linux/libabsl_time.a $$PWD/lib/absl/linux/libabsl_time_zone.a $$PWD/lib/absl/linux/libabsl_throw_delegate.a $$PWD/lib/absl/linux/libabsl_hash.a  $$PWD/lib/absl/linux/libabsl_raw_logging_internal.a $$PWD/lib/absl/linux/libabsl_log_severity.a $$PWD/lib/absl/linux/libabsl_strings_internal.a $$PWD/lib/absl/linux/libabsl_malloc_internal.a $$PWD/lib/absl/linux/libre2.a $$PWD/lib/absl/linux/libupb.a $$PWD/lib/absl/linux/libabsl_base.a $$PWD/lib/absl/linux/libabsl_spinlock_wait.a $$PWD/lib/absl/linux/libabsl_symbolize.a $$PWD/lib/absl/linux/libabsl_str_format_internal.a $$PWD/lib/absl/linux/libabsl_random_internal_randen.a $$PWD/lib/absl/linux/libabsl_random_internal_randen_hwaes.a $$PWD/lib/absl/linux/libabsl_random_internal_randen_hwaes_impl.a $$PWD/lib/absl/linux/libabsl_random_internal_randen_slow.a $$PWD/lib/absl/linux/libabsl_random_internal_pool_urbg.a $$PWD/lib/absl/linux/libabsl_random_internal_platform.a $$PWD/lib/absl/linux/libabsl_random_internal_seed_material.a $$PWD/lib/absl/linux/libabsl_random_seed_gen_exception.a $$PWD/lib/absl/linux/libabsl_cord.a $$PWD/lib/absl/linux/libabsl_cord_internal.a $$PWD/lib/absl/linux/libabsl_cordz_functions.a $$PWD/lib/absl/linux/libabsl_cordz_info.a  $$PWD/lib/absl/linux/libabsl_int128.a $$PWD/lib/absl/linux/libabsl_demangle_internal.a $$PWD/lib/absl/linux/libabsl_stacktrace.a $$PWD/lib/absl/linux/libabsl_debugging_internal.a $$PWD/lib/absl/linux/libabsl_cordz_handle.a $$PWD/lib/absl/linux/libabsl_city.a $$PWD/lib/absl/linux/libabsl_low_level_hash.a $$PWD/lib/absl/linux/libabsl_exponential_biased.a -lcrypto -lstdc++

SOURCES += \
    api/grpc/protos/linux/kaspawalletd.grpc.pb.cc \
    api/grpc/protos/linux/kaspawalletd.pb.cc \
    api/grpc/protos/linux/messages.grpc.pb.cc \
    api/grpc/protos/linux/messages.pb.cc \
    api/grpc/protos/linux/p2p.grpc.pb.cc \
    api/grpc/protos/linux/p2p.pb.cc \
    api/grpc/protos/linux/rpc.grpc.pb.cc \
    api/grpc/protos/linux/rpc.pb.cc
HEADERS += \
    api/grpc/protos/linux/kaspawalletd.grpc.pb.h \
    api/grpc/protos/linux/kaspawalletd.pb.h \
    api/grpc/protos/linux/messages.grpc.pb.h \
    api/grpc/protos/linux/messages.pb.h \
    api/grpc/protos/linux/p2p.grpc.pb.h \
    api/grpc/protos/linux/p2p.pb.h \
    api/grpc/protos/linux/rpc.grpc.pb.h \
    api/grpc/protos/linux/rpc.pb.h
}
android: {
    TARGET = ../KaspaWalletManager_Android/KaspaWalletManager_Android
    #LIBS +=  $$PWD/lib/libprotobuf/android/libprotobuf.so
    INCLUDEPATH += $$PWD/lib
    DEPENDPATH += $$PWD/lib
    INCLUDEPATH += $$PWD/lib/libgrpc
    DEPENDPATH += $$PWD/lib/libgrpc
    LIBS += -L$$PWD/lib/libgrpc/android/ -lgrpc++
    INCLUDEPATH += $$PWD/lib/libprotobuf
    DEPENDPATH += $$PWD/lib/libprotobuf
    #include(/Users/cry/Library/Android/sdk/android_openssl/openssl.pri)
    LIBS += -L$$PWD/lib/libprotobuf/android -lprotobuf

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
    crypto/ecc.cpp \
    crypto/signatures.cpp \
    extensions/bip39/bip39.cpp \
    extensions/bip39/util.cpp \
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
    crypto/ecc.h \
    crypto/signatures.h \
    errors.h \
    extensions/bip39/dictionary/chinese_simplified.h \
    extensions/bip39/dictionary/chinese_simplified_str.h \
    extensions/bip39/dictionary/chinese_traditional.h \
    extensions/bip39/dictionary/chinese_traditional_str.h \
    extensions/bip39/dictionary/english.h \
    extensions/bip39/dictionary/english_str.h \
    extensions/bip39/dictionary/french.h \
    extensions/bip39/dictionary/french_str.h \
    extensions/bip39/dictionary/italian.h \
    extensions/bip39/dictionary/italian_str.h \
    extensions/bip39/dictionary/japanese.h \
    extensions/bip39/dictionary/japanese_str.h \
    extensions/bip39/dictionary/korean.h \
    extensions/bip39/dictionary/korean_str.h \
    extensions/bip39/dictionary/spanish.h \
    extensions/bip39/dictionary/spanish_str.h \
    extensions/bip39/include/bip39/bip39.h \
    extensions/bip39/include/bip39/word_list.h \
    extensions/bip39/lib/PicoSHA2/picosha2.h \
    extensions/bip39/util.h \
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
