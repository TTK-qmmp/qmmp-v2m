
include($$PWD/common/common.pri)

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

CONFIG += warn_on plugin link_pkgconfig c++11

TEMPLATE = lib

QMAKE_CLEAN += lib$${TARGET}.so

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += qmmp

  QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
  PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/Input
  LOCAL_INCLUDES = $${QMMP_PREFIX}/include
  LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
  INCLUDEPATH += $$LOCAL_INCLUDES

  plugin.path = $${PLUGIN_DIR}
  plugin.files = lib$${TARGET}.so
  INSTALLS += plugin
}
