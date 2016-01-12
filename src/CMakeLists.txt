add_executable(kmonitor
    kmonitor.cpp
    mainwindow.cpp
    mainwindow.ui
    processmodel.cpp
    socketunixmodel.cpp
)

target_link_libraries(kmonitor 
    sysinfo 
    Qt5::Widgets
)
