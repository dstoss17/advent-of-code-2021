# Rule to copy test files and scripts to build tree
macro(setup_test_env DAY_NAME)
  message(STATUS "Adding rule to copy files for ${DAY_NAME}")
  add_custom_target(
    copy-test-files-${DAY_NAME} ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_BINARY_DIR}/tests
  )
endMacro()

macro(setup_unit_test DAY_NAME)
  message(STATUS "Adding tests for ${DAY_NAME}")
  setup_test_env(${DAY_NAME})
  add_test(
    NAME unit-test-${DAY_NAME}
    COMMAND tests/run_tests.sh ${DAY_NAME}
    DEPENDS copy-test-files-${DAY_NAME}
  )
endMacro()

macro(add_aoc_dir DAY_NAME)
  if(EXISTS ${DAY_NAME})
    add_subdirectory(${DAY_NAME})
  endif()
endMacro()