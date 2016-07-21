#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T10:20:10
#
#-------------------------------------------------

QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#Use new standard
CONFIG += c++11
CONFIG += qwt

TARGET = PhonoSpeechStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp \
    phonoaudiosettings.cpp \
    processingsettings.cpp

HEADERS  += mainwindow.h \
    util.h \
    config.h \
    phonoaudiosettings.h \
    processingsettings.h

FORMS    += mainwindow.ui \
    phonoaudiosettings.ui \
    processingsettings.ui

RESOURCES += \
    images.qrc \
    others.qrc

QMAKE_CXXFLAGS += -Wno-ignored-qualifiers


#Include subproject
include(phonowidget/phonowidget.pri)
include(phonoaudio/phonoaudio.pri)
include(phonomath/phonomath.pri)

win32 {
    #Include QWT for Windows
    CONFIG(release, debug|release): LIBS += -L$$PWD/libs/qwt-6.1.2/lib/ -lqwt
    CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/qwt-6.1.2/lib/ -lqwtd
    INCLUDEPATH += $$PWD/libs/qwt-6.1.2/include
    DEPENDPATH += $$PWD/libs/qwt-6.1.2/include

    #Include FFTW for Windows
    LIBS += -L$$PWD/libs/fftw-3.3.4/ -lfftw3-3
    INCLUDEPATH += $$PWD/libs/fftw-3.3.4/
    DEPENDPATH += $$PWD/libs/fftw-3.3.4/

    #Include BOOST for Windows
    INCLUDEPATH += $$PWD/libs/boost_1_60_0/

    #Include AQUILA for Windows
    LIBS += -L$$PWD/'../../../../Program Files (x86)/Aquila/lib/' -lAquila
    INCLUDEPATH += $$PWD/'../../../../Program Files (x86)/Aquila/include/'
    DEPENDPATH += $$PWD/'../../../../Program Files (x86)/Aquila/include/'

    #Include PORTAUDIO for Windows
    LIBS += -L$$PWD/libs/portaudio/lib/.libs/ -llibportaudio.dll
    INCLUDEPATH += $$PWD/libs/portaudio/include
    DEPENDPATH += $$PWD/libs/portaudio/include

    #Include LIBSNDFILE for Windows
    LIBS += -L$$PWD/'../../../../Program Files (x86)/Mega-Nerd/libsndfile/bin/' -lsndfile-1
    INCLUDEPATH += $$PWD/'../../../../Program Files (x86)/Mega-Nerd/libsndfile/include'
    DEPENDPATH += $$PWD/'../../../../Program Files (x86)/Mega-Nerd/libsndfile/include'
}

unix:!macx {

    LIBS += -lfftw3
    LIBS += -lportaudio
    LIBS += -lAquila
    unix:!macx: LIBS += -L/usr/local/qwt-6.1.2/lib/ -lqwt
    INCLUDEPATH += /usr/local/qwt-6.1.2/include
    DEPENDPATH += /usr/local/qwt-6.1.2/include
}

unix:macx {
    #Define MAC OS SDK
    MAC_SDK  = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk
    if( !exists( $$MAC_SDK) ) {
      error("The selected Mac OSX SDK does not exist at $$MAC_SDK!")
    }
    QMAKE_MAC_SDK = macosx10.11

    INCLUDEPATH += $$MAC_SDK/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers
    INCLUDEPATH += $$MAC_SDK/System/Library/Frameworks/CoreServices.framework/Versions/A/Headers
    INCLUDEPATH += $$MAC_SDK/System/Library/Frameworks/CoreAudio.framework/Versions/A/Headers
    INCLUDEPATH += $$MAC_SDK/System/Library/Frameworks/AudioToolbox.framework/Versions/A/Headers
    INCLUDEPATH += $$MAC_SDK/System/Library/Frameworks/AudioUnit.framework/Versions/A/Headers

    DEPENDPATH += $$MAC_SDK/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers
    DEPENDPATH += $$MAC_SDK/System/Library/Frameworks/CoreServices.framework/Versions/A/Headers
    DEPENDPATH += $$MAC_SDK/System/Library/Frameworks/CoreAudio.framework/Versions/A/Headers
    DEPENDPATH += $$MAC_SDK/System/Library/Frameworks/AudioToolbox.framework/Versions/A/Headers
    DEPENDPATH += $$MAC_SDK/System/Library/Frameworks/AudioUnit.framework/Versions/A/Headers

    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioToolbox.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioUnit.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreFoundation.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreServices.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreAudio.framework/

    LIBS += -framework AudioToolbox
    LIBS += -framework AudioUnit
    LIBS += -framework CoreAudio
    LIBS += -framework CoreFoundation
    LIBS += -framework CoreServices

    #Incude Qwt
    include (/usr/local/qwt-6.1.2/features/qwt.prf)

    #Include PortAudio
    LIBS += -L$$PWD/libs/portaudio/lib/ -lportaudio
    INCLUDEPATH += $$PWD/libs/portaudio/include
    DEPENDPATH += $$PWD/libs/portaudio/include

    #Include boost
    INCLUDEPATH += $$PWD/libs/boost_1_60_0/

}



