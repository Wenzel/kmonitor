add_executable(kmonitor
    kmonitor.cpp
    kmonitor.qrc
    socketunixmodel.cpp
    processmodel.cpp
)

target_link_libraries(kmonitor
    sysinfo 
    Qt5::Widgets 
    Qt5::Declarative 
    Qt5::Qml
)
