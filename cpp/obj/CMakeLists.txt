project(obj LANGUAGES CXX)

pybind11_add_module(${PROJECT_NAME} impl.cc)
