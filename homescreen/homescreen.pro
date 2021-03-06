# Copyright (C) 2016, 2017 Mentor Graphics Development (Deutschland) GmbH
# Copyright (c) 2017 TOYOTA MOTOR CORPORATION
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TEMPLATE = app
TARGET = HomeScreen
QT = qml quick websockets gui-private network
CONFIG += c++11 link_pkgconfig wayland-scanner create_pc create_prl no_install_prl
DESTDIR = $${OUT_PWD}/../package/root/bin
PKGCONFIG += qtappfw-weather qtappfw-network qtappfw-bt afb-helpers-qt wayland-client json-c libhomescreen

LIBS += -lhomescreen

CONFIG(release, debug|release) {
    QMAKE_POST_LINK = $(STRIP) --strip-unneeded $(TARGET)
}
#Add qt lib
headers.path = /usr/include
headers.files = qlibhomescreen.h

target.path = /usr/lib

QMAKE_PKGCONFIG_NAME = qlibhomescreen
QMAKE_PKGCONFIG_FILE = $${QMAKE_PKGCONFIG_NAME}
QMAKE_PKGCONFIG_VERSION = $${VERSION}
QMAKE_PKGCONFIG_DESCRIPTION = A wrapper interface for libhomescreen for Qt
QMAKE_PKGCONFIG_LIBDIR = ${prefix}/lib
QMAKE_PKGCONFIG_INCDIR = ${prefix}/include
QMAKE_PKGCONFIG_REQUIRES = libhomescreen
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
#end

SOURCES += \
    src/main.cpp \
    src/mainkauto.cpp \
    src/qlibhomescreen.cpp \
    src/statusbarmodel.cpp \
    src/statusbarserver.cpp \
    src/applicationlauncher.cpp \
    src/mastervolume.cpp \
    src/homescreenhandler.cpp \
    src/shell.cpp \
    src/aglsocketwrapper.cpp \
    src/chromecontroller.cpp \
    src/tcpsocket.cpp \
    src/websocketclient.cpp

HEADERS  += \
    src/mainkauto.h \
    src/qlibhomescreen.h \
    src/statusbarmodel.h \
    src/statusbarserver.h \
    src/applicationlauncher.h \
    src/mastervolume.h \
    src/homescreenhandler.h \
    src/shell.h \
    src/aglsocketwrapper.h \
    src/chromecontroller.h \
    src/constants.h \
    src/tcpsocket.h \
    src/websocketclient.h

OTHER_FILES += \
    README.md

RESOURCES += \
    qml/images/MediaPlayer/mediaplayer.qrc \
    qml/images/MediaMusic/mediamusic.qrc \
    qml/images/Weather/weather.qrc \
    qml/images/Shortcut/shortcut.qrc \
    qml/images/Status/status.qrc \
    qml/images/images.qrc \
    qml/qml.qrc \
    qml/images/SpeechChrome/speechchrome.qrc


WAYLANDCLIENTSOURCES += \
    protocol/agl-shell.xml
#Add qt lib
INSTALLS += target headers
#end

DISTFILES +=
