HEADERS += decoderv2mfactory.h \
           decoder_v2m.h \
           v2mhelper.h \
           archivereader.h

SOURCES += decoderv2mfactory.cpp \
           decoder_v2m.cpp \
           v2mhelper.cpp \
           archivereader.cpp \
           libv2m/sounddef.cpp \
           libv2m/synth_core.cpp \
           libv2m/v2mconv.cpp \
           libv2m/v2mplayer.cpp

INCLUDEPATH += $$PWD/libv2m

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/v2m

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        PKGCONFIG += qmmp-1

        PLUGIN_DIR = $$system(pkg-config qmmp-1 --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config qmmp-1 --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
