# CMakeList.txt : CMake project for JXS_21122_LAB, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (JXS_SequenceEncoder "cmdline_options.c" "file_io.c" "file_sequence.c" "image_open.c" "JXS_SequenceEncoder")

if(MSVC)
target_link_libraries(JXS_SequenceEncoder 
    debug ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/jxsd.lib 
    optimized ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/jxs.lib
    debug ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/jxs_utils_d.lib 
    optimized ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/jxs_utils.lib)
else()
# Handle libm.
find_library(M_LIBRARY NAMES libm.a)
if(M_LIBRARY)
    set(M_LIBRARY "m")
else()
    set(M_LIBRARY "")
endif()
target_link_libraries(JXS_SequenceEncoder 
    debug ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/libjxsd.a m 
    optimized ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/libjxs.a m
    debug ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/libjxs_utils_d.a m 
    optimized ${CMAKE_SOURCE_DIR}/JXS_SequenceEncoder/libjxs_utils.a m)
endif()