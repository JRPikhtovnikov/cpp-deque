########
MOCK_LIB=../../../../mocks_library
########

QT += core gui widgets

CONFIG += c++20

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    algo.h \
    mainwindow.h \
    model.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
