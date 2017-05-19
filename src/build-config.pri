ARCH = plateformarch
win32 { ARCH = $$QMAKE_TARGET.arch }
unix { ARCH = $$QMAKE_HOST.arch }
BUILD_CONFIG = buildconf

CONFIG(debug, debug|release) { BUILD_CONFIG = debug }
CONFIG(release, debug|release) { BUILD_CONFIG = release }

BUILD_DIR = $$PWD/../builds/builds-$${ARCH}-$${BUILD_CONFIG}
DEPLOY_DIR = $$PWD/../builds/deploys-$${ARCH}-$${BUILD_CONFIG}


DESTDIR = $$BUILD_DIR
LIBS+= -L$$BUILD_DIR


MOC_DIR = $${BUILD_DIR}/moc
OBJECTS_DIR = $${BUILD_DIR}/obj


UI_DIR = $${BUILD_DIR}/tmp-UI
RCC_DIR = $${BUILD_DIR}/tmp-RCC
INCLUDEPATH += $${BUILD_DIR}/tmp-UI
win32:QMAKE_CXXFLAGS += /MP
