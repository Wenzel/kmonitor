add_executable(vmmap
    vmmap.cpp
    mainwindow.cpp
    mainwindow.ui
)

target_link_libraries(vmmap
    sysinfo 
    Qt5::Widgets
)
