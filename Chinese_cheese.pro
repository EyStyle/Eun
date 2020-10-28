HEADERS += \
    Board.h \
    Stone.h \
    MainWnd.h \
    CtrlPanel.h \
    Step.h \
    ChooseDlg.h \
    SingleGame.h \
    MultiGame.h \
    NetGame.h \
    loginui.h

SOURCES += \
    Board.cpp \
    main.cpp \
    Stone.cpp \
    MainWnd.cpp \
    CtrlPanel.cpp \
    Step.cpp \
    ChooseDlg.cpp \
    SingleGame.cpp \
    MultiGame.cpp \
    NetGame.cpp \
    loginui.cpp

QT += widgets gui network

FORMS += \
    loginui.ui
