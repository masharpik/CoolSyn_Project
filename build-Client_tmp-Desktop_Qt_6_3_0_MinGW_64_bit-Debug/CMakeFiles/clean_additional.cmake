# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Client_tmp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Client_tmp_autogen.dir\\ParseCache.txt"
  "Client_tmp_autogen"
  )
endif()
