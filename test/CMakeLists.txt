set(TestName record-test)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  ${TestName}
  main.cpp
  Record1.cpp
  Record2.cpp
  Record3.cpp
  Record4.cpp
  Record5.cpp
)
    
target_link_libraries(
  ${TestName}
  ${CONAN_LIBS}
)

add_test(
  NAME ${TestName}
  COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
