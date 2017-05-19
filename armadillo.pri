# LAPACK — Linear Algebra PACKage lib and include locations

# defines & includes used for this lib
DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS
INCLUDEPATH += $${INCLUDE_DIR}

win32 {
    #64 bits build
    contains(QMAKE_TARGET.arch, x86_64) {
        #debug
        CONFIG(debug, debug|release) {
            LAPACK_LIB_DIR = $$PWD/../lapack-blas_lib_win64/debug
            LIBS += -llapack_win64_MTd \
                    -lblas_win64_MTd
        }
        #release
        CONFIG(release, debug|release) {
            LAPACK_LIB_DIR = $$PWD/../lapack-blas_lib_win64/release
            LIBS += -llapack_win64_MT \
                    -lblas_win64_MT
        }
    }
    LIBS += -L$${LAPACK_LIB_DIR}
}
