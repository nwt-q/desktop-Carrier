# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Carrier_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Carrier_autogen.dir\\ParseCache.txt"
  "Carrier_autogen"
  )
endif()
