project(window LANGUAGES CXX)

pybind11_add_module(${PROJECT_NAME} impl.cc)

target_link_libraries(${PROJECT_NAME} PUBLIC gdi32 gdiplus user32)