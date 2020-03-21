cmake_minimum_required(VERSION 2.8)

project (middleware)

SET(CMAKE_SYSTEM_NAME Linux)  

if(APPLE)
  include_directories( /usr/local/include )
  link_directories( /usr/local/lib/ )
  set(CMAKE_MACOSX_RPATH ON)
endif()

include_directories( lib/include/ )
file(GLOB headers "lib/include/*.h" )
file(GLOB sources "lib/src/*.c" )

add_library(middleware SHARED ${sources} ${headers})
target_link_libraries(middleware utils)  

set (VERSION 1.0.0)
add_definitions (-DCMAKE -DVERSION=\"${VERSION}\")

set_target_properties(middleware PROPERTIES
  OUTPUT_NAME middleware
  VERSION ${VERSION}
  SOVERSION 1
)

install(TARGETS middleware DESTINATION /usr/local/lib)
install(FILES "lib/include/middleware.h" DESTINATION /usr/local/include)
