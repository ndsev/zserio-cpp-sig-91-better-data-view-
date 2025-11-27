project(approach_4_top_view)

set(SRC
    main.cpp
    struct_templated_field/Compound.h
    struct_templated_field/Compound.cpp
    struct_templated_field/Field.h
    struct_templated_field/StructTemplatedField.h
    struct_templated_field/StructTemplatedField.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE ZserioCpp17Runtime)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
