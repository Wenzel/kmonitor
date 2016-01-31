add_executable(vmmap
    vmmap.cpp
    mainwindow.cpp
    mainwindow.ui
    selectprocessview.cpp
    selectprocessview.ui
)

target_link_libraries(vmmap
    sysinfo 
    Qt5::Widgets
)
