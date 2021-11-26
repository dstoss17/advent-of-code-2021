################################################################################
# Advent-of-Code common framework and library
################################################################################

# common functions library (replace INTERFACE with PUBLIC if source files are added)
add_library(common INTERFACE)
target_include_directories(common INTERFACE include/)

# shared main for all non-test executables
add_library(common-main OBJECT src/main.cc)
target_link_libraries(common-main PRIVATE common)

# Add tests
#add_executable(common-test
#  )

#target_link_libraries(common-test
#  PRIVATE common
#  )

#add_gtest(common-test)
