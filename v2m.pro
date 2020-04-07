include(../../plugins.pri)
include($$PWD/common/common.pri)

TARGET = $$PLUGINS_PREFIX/Input/v2m

HEADERS += decoderv2mfactory.h \
           decoder_v2m.h \
           v2mhelper.h \
           tool/file.h \
           libv2.h \
           phonemtab.h \
           sounddef.h \
           synth.h \
           types.h \
           v2mconv.h \
           v2mplayer.h
    
SOURCES += decoderv2mfactory.cpp \
           decoder_v2m.cpp \
           v2mhelper.cpp \
           tool/file.cpp \
           sounddef.cpp \
           synth_core.cpp \
           v2mconv.cpp \
           v2mplayer.cpp

INCLUDEPATH += $$PWD

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libv2m.so
}
