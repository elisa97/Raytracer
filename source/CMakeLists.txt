add_executable(render_test
  render_test.cpp
  )

target_link_libraries(render_test ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(render_test glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS render_test DESTINATION .)

add_executable(test_2
  test_2.cpp
  )

target_link_libraries(test_2 ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(test_2 glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS test_2 DESTINATION .)

add_executable(tests
  tests.cpp
)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )

add_executable(load_scene
  load_scene.cpp
)
target_link_libraries(load_scene
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )
add_dependencies(load_scene glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS load_scene DESTINATION .)