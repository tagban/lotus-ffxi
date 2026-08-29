# A shared library rather than another executable on purpose: this is the shape
# PortJeuno's managed client actually loads, so building it here is what proves
# ffxi-lib is linkable from outside ffxi.exe.
add_library(portjeuno-native SHARED
    portjeuno_native.cpp
)

target_link_libraries(portjeuno-native PRIVATE ffxi-lib)
set_target_properties(portjeuno-native PROPERTIES CXX_VISIBILITY_PRESET hidden)
