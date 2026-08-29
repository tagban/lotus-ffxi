add_executable(ffxi
    main.cpp
)
target_sources(ffxi PUBLIC
    FILE_SET CXX_MODULES
    FILES
    config.cppm
    ffxi.cppm
    game.cppm
    particle_tester.cppm
    scheduler_resources.cppm
    system_dat.cppm
    test_loader.cppm
    vana_time.cppm
    PRIVATE
    game.cpp
    particle_tester.cpp
    scheduler_resources.cpp
    stb.cpp
    system_dat.cpp
)

target_include_directories(ffxi PRIVATE "." )
target_include_directories(ffxi PRIVATE "../external/stb" )
target_compile_features(ffxi PUBLIC cxx_std_23)
target_link_libraries(ffxi PUBLIC lotus-engine)

if (MSVC)
    # This used to copy ${SDL2_DLL}, left over from SDL2 and empty ever since, so
    # nothing was copied and the built exe could not start: a missing SDL3.dll
    # shows up only as exit code 0xC0000135, with no message anywhere.
    # TARGET_RUNTIME_DLLS resolves whatever the imported targets actually need.
    add_custom_command(TARGET ffxi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:ffxi> $<TARGET_FILE_DIR:ffxi>
        COMMAND_EXPAND_LISTS
    )
endif()

file(COPY textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(audio)
add_subdirectory(dat)
add_subdirectory(entity)
add_subdirectory(shaders)
