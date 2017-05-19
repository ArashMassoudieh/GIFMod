# LAPACK — Linear Algebra PACKage lib and include locations
win32 {

    LAPACK_INCLUDE = $${INCLUDE_DIR}
    #64 bits build
    contains(QMAKE_TARGET.arch, x86_64) {
        #debug
        CONFIG(debug, debug|release) {
            LAPACK_LIB_DIR = $$PWD/../libs/lapack-blas_lib_win64/debug
            LIBS += -llapack_win64_MTd \
                    -lblas_win64_MTd
        }
        #release
        CONFIG(release, debug|release) {
            LAPACK_LIB_DIR = $$PWD/../libs/lapack-blas_lib_win64/release
            LIBS += -llapack_win64_MT \
                    -lblas_win64_MT
        }
    }

    INCLUDEPATH += $${LAPACK_INCLUDE}   
    LIBS += -L$${LAPACK_LIB_DIR}
}
