QT += gui

#CONFIG += c++14
#CONFIG += c++17
CONFIG += c++20
CONFIG += console
#CONFIG -= app_bundle
#QT += widgets

win32 {
#    message("win32")
    #LIBS += -lws2_32 -lWSock32 -lbthprops -lBcrypt
    #LIBS += -lshell32 -luser32
    #QT += winextras
}

linux64 {

}

#contains(QT_ARCH, i386) {
#    message("32-bit")
#} else {
#    message("64-bit")
#}


#QMAKE_CFLAGS_WARN_ON -= -W
QMAKE_CFLAGS_WARN_ON -= -W3
QMAKE_CFLAGS_WARN_ON += -Wall


g++* {
QMAKE_CXXFLAGS += -Wextra -Wattributes -pedantic-errors
}

#QMAKE_CFLAGS_WARN_OFF   =-W
#QMAKE_CFLAGS_RELEASE   = -O2
#QMAKE_CFLAGS_DEBUG     =
#QMAKE_CFLAGS_YACC      = -W

QMAKE_CXXFLAGS_WARN_ON   = $$QMAKE_CFLAGS_WARN_ON
#QMAKE_CXXFLAGS_WARN_OFF  = $$QMAKE_CFLAGS_WARN_OFF
#QMAKE_CXXFLAGS          = $$QMAKE_CFLAGS
#QMAKE_CXXFLAGS_DEPS     = $$QMAKE_CFLAGS_DEPS
#QMAKE_CXXFLAGS_RELEASE  = $$QMAKE_CFLAGS_RELEASE
#QMAKE_CXXFLAGS_DEBUG    = $$QMAKE_CFLAGS_DEBUG
#QMAKE_CXXFLAGS_YACC     = $$QMAKE_CFLAGS_YACC
#QMAKE_CXXFLAGS_THREAD   = $$QMAKE_CFLAGS_THREAD
#QMAKE_CXXFLAGS_RTTI_ON  = -frtti
#QMAKE_CXXFLAGS_RTTI_OFF = -fno-rtti
#QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions -mthreads
#QMAKE_CXXFLAGS_EXCEPTIONS_OFF = -fno-exceptions

android {
#    message("android")
#    QT += androidextras

#    ANDROID_API=21
#    __ANDROID_API__=android-21
#    DEFAULT_ANDROID_PLATFORM=21
#    ANDROID_NDK_PLATFORM=android-21
#    DEFAULT_ANDROID_PLATFORM=android-21
#    API_VERSION = android-21

    #CONFIG += mobility
    #MOBILITY =
    #LIBS += -lopengl32 -lglu32
#    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

#platform = $$eval(config.input.android-ndk-platform)
#isEmpty(platform): \
#    platform = Empty
#message($$platform)

#    !equals(DEFAULT_ANDROID_PLATFORM,android-21): error("Error ANDROID_NDK_PLATFORM=$$DEFAULT_ANDROID_PLATFORM expected ANDROID_NDK_PLATFORM=android-21")
}

unix:!android: {
#    message("unix:!android:")
#    CONFIG += link_pkgconfig
#    PKGCONFIG += bluez
#    LIBS += -lbluetooth
}
SOURCES += \
        logger.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    logger.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
