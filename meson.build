deps = [
    dependency('GL'),
    dependency('glew'),
    dependency('sfml-window'),
    dependency('sfml-graphics'),
    dependency('sfml-system')
]

oopgl_lib = library(
    'oopgl',
    [
        'objects/object.cpp',

        'shaders/shader.cpp',
        'shaders/vertex_shader.cpp',
        'shaders/fragment_shader.cpp',
        
        'app.cpp',
        'window.cpp',        
        'renderer.hpp',
        'vertex_array.cpp'
    ],
    cpp_args: [
        '-std=c++23'
    ],
    dependencies : deps
)