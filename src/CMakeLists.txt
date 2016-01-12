add_executable(kmonitor
    kmonitor.cpp
    mainwindow.cpp
    processmodel.cpp
    mainwindow.ui
)

target_link_libraries(kmonitor 
    sysinfo 
    Qt5::Widgets
)
