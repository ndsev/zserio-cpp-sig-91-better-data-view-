project(approach_5_global_data_view)

set(SRC
    main.cpp
    nds/data/struct_templated_field/Compound.h
    nds/data/struct_templated_field/Compound.cpp
    nds/data/struct_templated_field/Field.h
    nds/data/struct_templated_field/StructTemplatedField.h
    nds/data/struct_templated_field/StructTemplatedField.cpp
    nds/view/struct_templated_field/Compound.h
    nds/view/struct_templated_field/Compound.cpp
    nds/view/struct_templated_field/Field.h
    nds/view/struct_templated_field/StructTemplatedField.h
    nds/view/struct_templated_field/StructTemplatedField.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE ZserioCpp17Runtime)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
