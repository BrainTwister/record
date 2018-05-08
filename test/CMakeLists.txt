set(TestName record-test)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  ${TestName}
  collections.cpp
  main.cpp
  nested.cpp
  pointer.cpp
  polymorph.cpp
  simple.cpp
)
    
target_link_libraries(
  ${TestName}
  ${CONAN_LIBS}
)

add_test(
  NAME ${TestName}
  COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
