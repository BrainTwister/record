set(TestName cpp-settings-test)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_executable(
  ${TestName}
  main.cpp
  #Settings1.cpp
  Settings2.cpp
  Settings3.cpp
  Settings4.cpp
  Settings5.cpp
)
    
target_link_libraries(
  ${TestName}
  ${CONAN_LIBS}
)

add_test(
  NAME ${TestName}
  COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
