add_executable(render_test
        render_test.cpp
        #../framework/sphere.cpp
        ../framework/box.cpp
        #../framework/shape.cpp
        #../framework/material.cpp
        ../framework/scene.cpp
        ../framework/renderer.cpp
        )

target_link_libraries(render_test ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(render_test glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS render_test DESTINATION .)

