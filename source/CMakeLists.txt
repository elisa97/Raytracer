add_executable(render_test
        render_test.cpp
        #../framework/sphere.cpp
        ../framework/box.cpp
        #../framework/shape.cpp
        #../framework/material.cpp
        ../framework/scene.cpp
        ../framework/renderer.cpp
        ../framework/triangle.cpp
        )

target_link_libraries(render_test ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(render_test glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS render_test DESTINATION .)

add_executable(test_2
        test_2.cpp
        #../framework/sphere.cpp
        ../framework/box.cpp
        #../framework/shape.cpp
        #../framework/material.cpp
        ../framework/scene.cpp
        ../framework/renderer.cpp
        ../framework/triangle.cpp
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

add_executable(scene_load_test
  scene_load_test.cpp
)
target_link_libraries(scene_load_test
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )