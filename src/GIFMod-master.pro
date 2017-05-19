CONFIG += debug_and_release debug_and_release_target

INCLUDE_DIR =  $$PWD../include
include ($$PWD/build-config.pri)
include ($$PWD/lapack.pri)


QT += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#defines
DEFINES += UNICODE ARMA_USE_LAPACK ARMA_USE_BLAS GIFMOD

CONFIG += c++14


TARGET = GIFMod-master
TEMPLATE = app
INCLUDEPATH += $${INCLUDE_DIR} \
               GUI  \
               icons \
               duktape \
               dukglue \
               core \
               scripting

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include (./GIFMod.pri)

# post link actions to copy externals and resources
win32{

    COPY_EXTRA_FILES +=
    CONFIG(debug, debug|release) {
        COPY_EXTRA_FILES +=  $${LAPACK_LIB_DIR}/lapack_win64_MTd.dll \
                           $${LAPACK_LIB_DIR}/blas_win64_MTd.dll
    }
    CONFIG(release, debug|release) {
        COPY_EXTRA_FILES +=  $${LAPACK_LIB_DIR}/lapack_win64_MT.dll \
                           $${LAPACK_LIB_DIR}/blas_win64_MT.dll
    }
    COPY_EXTRA_FILES += $$PWD/GIFModGUIPropList.csv


    for(FILE,COPY_EXTRA_FILES){
                QMAKE_POST_LINK +=copy /Y "$$system_path($${FILE})" "$$system_path($$BUILD_DIR)" &&
    }


    QMAKE_POST_LINK += xcopy /I "$$system_path($$PWD/GUI/Icons)" "$$system_path($${BUILD_DIR}/Icons)" &&
    QMAKE_POST_LINK += echo
}

