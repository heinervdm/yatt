project(yatt)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(yatt_SRCS drivertable.cpp adddriver.cpp contesttable.cpp contestdata.cpp yatttablemodel.cpp main.cpp)
qt4_automoc(${yatt_SRCS})
add_executable(yatt ${yatt_SRCS})
target_link_libraries(yatt ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSQL_LIBRARY})
