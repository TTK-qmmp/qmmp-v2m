include($$PWD/../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/v2m

HEADERS += decoderv2mfactory.h \
           decoder_v2m.h \
           v2mhelper.h
    
SOURCES += decoderv2mfactory.cpp \
           decoder_v2m.cpp \
           v2mhelper.cpp \
           libv2m/sounddef.cpp \
           libv2m/synth_core.cpp \
           libv2m/v2mconv.cpp \
           libv2m/v2mplayer.cpp

INCLUDEPATH += $$PWD/libv2m

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
}
