QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Comment.cpp \
    FordevC.cpp \
    Interaction.cpp \
    Person.cpp \
    biography.cpp \
    followers.cpp \
    home.cpp \
    information.cpp \
    login.cpp \
    main.cpp \
    fordev.cpp \
    myfollowed.cpp \
    mypublications.cpp \
    postu.cpp \
    postuser.cpp \
    register.cpp \
    searchperson.cpp

HEADERS += \
    ../../semana 13/AVL tree/AVL.h \
    ../../semana 13/AVL tree/AVL.h \
    AVL.h \
    Comment.h \
    FordevC.h \
    Interaction.h \
    List.h \
    Person.h \
    Stack.h \
    biography.h \
    followers.h \
    fordev.h \
    home.h \
    information.h \
    login.h \
    myfollowed.h \
    mypublications.h \
    postu.h \
    postuser.h \
    register.h \
    searchperson.h

FORMS += \
    biography.ui \
    followers.ui \
    fordev.ui \
    home.ui \
    information.ui \
    login.ui \
    myfollowed.ui \
    mypublications.ui \
    postuser.ui \
    register.ui \
    searchperson.ui

# Default rules for deployment.
RC_ICONS = logo.ico
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
