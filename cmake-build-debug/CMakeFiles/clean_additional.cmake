# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Research_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Research_autogen.dir\\ParseCache.txt"
  "Research_autogen"
  )
endif()
