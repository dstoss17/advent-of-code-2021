#
#
# Downloads GTest and provides a helper macro to add tests. Add make check, as well, which
# gives output on failed tests without having to set an environment variable.
#
#

include(FetchContent)
FetchContent_Declare(googletest
 GIT_REPOSITORY      https://github.com/google/googletest.git
 GIT_TAG             release-1.11.0)
#FetchContent_GetProperties(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON  CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


if(CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure
        --build-config "$<CONFIGURATION>")
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure)
endif()
set_target_properties(check PROPERTIES FOLDER "Scripts")

if(GOOGLE_TEST_INDIVIDUAL)
  include(GoogleTest)
endif()

# Target must already exist
macro(add_gtest TESTNAME)
  target_link_libraries(${TESTNAME} PUBLIC gtest gtest_main)

    if(GOOGLE_TEST_INDIVIDUAL)
        gtest_discover_tests(${TESTNAME}
            TEST_PREFIX "${TESTNAME}."
            PROPERTIES FOLDER "Tests")
    else()
        add_test(${TESTNAME} ${TESTNAME})
        set_target_properties(${TESTNAME} PROPERTIES FOLDER "Tests")
    endif()

endmacro()

mark_as_advanced(
gmock_build_tests
gtest_build_samples
gtest_build_tests
gtest_disable_pthreads
gtest_force_shared_crt
gtest_hide_internal_symbols
BUILD_GMOCK
BUILD_GTEST
)

set_target_properties(gtest gtest_main
    PROPERTIES FOLDER "Extern")
