# CMakeList.txt : CMake project for JXS_21122_LAB, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (JXS_1Dcodec "JXS_1Dcodec.c" "file_io.c")

target_link_libraries(JXS_1Dcodec debug ${CMAKE_SOURCE_DIR}/JXS_1Dcodec/jxsd.lib optimized ${CMAKE_SOURCE_DIR}/JXS_1Dcodec/jxs.lib)