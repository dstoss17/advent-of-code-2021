################################################################################
# Advent-of-Code 2021 CMakeLists.txt
# Individual day CMakeLists file
################################################################################

# Name of project day
set(TARGET_DAY day08)

add_library(${TARGET_DAY}-impl
  src/main.cc
  )

target_include_directories(${TARGET_DAY}-impl
  PUBLIC include/
  )

target_link_libraries(${TARGET_DAY}-impl PUBLIC common)

add_executable(${TARGET_DAY}
  $<TARGET_OBJECTS:common-main>
  )

# Link in the AOC framework library and common code
target_link_libraries(${TARGET_DAY}
  PRIVATE ${TARGET_DAY}-impl
  )

# Add tests
add_executable(${TARGET_DAY}-test
  test/test.cc
  )

target_link_libraries(${TARGET_DAY}-test
  PRIVATE ${TARGET_DAY}-impl
  )

add_gtest(${TARGET_DAY}-test)

if(ENABLE_SYMLINK_RULES)
  # Add symlink to run executable in the current directory
  add_custom_target(${TARGET_DAY}-symlink
      ALL ln --force -s ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DAY} ${CMAKE_SOURCE_DIR}/${TARGET_DAY}/run
      DEPENDS ${TARGET_DAY}
      )

  set_directory_properties(
      PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${TARGET_DAY}/run
  )

  message("Added rule in ${TARGET_DAY} to build symlink")
endif()
