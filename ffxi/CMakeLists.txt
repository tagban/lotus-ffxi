# Everything except main.cpp lives in a library, so that something other than
# this executable can link the game: PortJeuno drives the renderer through its
# own native layer, and could not while every source file was welded onto an
# add_executable target. The executable is now only an entry point.
add_library(ffxi-lib STATIC)
# Linux needs this to be able to link the library into a shared object later.
set_target_properties(ffxi-lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_sources(ffxi-lib PUBLIC
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

# PUBLIC: consumers of the library compile against these headers too.
target_include_directories(ffxi-lib PUBLIC "." )
target_include_directories(ffxi-lib PRIVATE "../external/stb" )
target_compile_features(ffxi-lib PUBLIC cxx_std_23)
target_link_libraries(ffxi-lib PUBLIC lotus-engine)

add_executable(ffxi main.cpp)
target_link_libraries(ffxi PRIVATE ffxi-lib)

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
