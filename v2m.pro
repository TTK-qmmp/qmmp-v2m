include(../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/v2m

HEADERS += decoderv2mfactory.h \
           decoder_v2m.h \
           v2mhelper.h \
           libv2.h \
           sounddef.h \
           synth.h \
           v2mconv.h \
           v2mplayer.h
    
SOURCES += decoderv2mfactory.cpp \
           decoder_v2m.cpp \
           v2mhelper.cpp \
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
