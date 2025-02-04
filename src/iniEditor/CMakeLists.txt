
add_compile_options(-Wall -Wpedantic)

add_executable(bridgecommand-ini
    main.cpp
    ../IniFile.cpp
    ../Lang.cpp
    ../Utilities.cpp
)

target_link_libraries(bridgecommand-ini
    bc-irrlicht
)
