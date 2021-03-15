include(${CMAKE_SOURCE_DIR}/cmake/AddGoogleTest.cmake)

set(TESTLIB_NAME "testlib")
set(TEST_HEADER)
set(TEST_SOURCE)
file(GLOB_RECURSE TEST_HEADER ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE TEST_SOURCE ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(${TESTLIB_NAME} SHARED ${TEST_HEADER} ${TEST_SOURCE})
target_include_directories(${TESTLIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        )
target_link_libraries(${TESTLIB_NAME} cocos2d project_dependency)
target_include_directories(${TESTLIB_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        )
target_compile_features(${TESTLIB_NAME} PRIVATE cxx_std_17)
target_compile_options(${TESTLIB_NAME} PRIVATE -Wall)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    target_compile_features(${ARG_TARGET} PRIVATE cxx_std_17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    add_gtest(${ARG_TARGET})
    add_deps_to_test(${ARG_TARGET} ${TESTLIB_NAME})
endfunction()

function(ADD_DEPS_TO_TEST ARG_TARGET)
    target_link_libraries(
            ${ARG_TARGET} PUBLIC ${ARGN})
endfunction()

################### All tests ###################
init_test(TestDatabases ./TestDatabases.cpp)

