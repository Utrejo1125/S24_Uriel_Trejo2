set(HEADER_FILES
	include/Toad.h
	src/ToadApplication.h
	src/Utility.h
	src/ToadWindow.h
	src/WindowImpl.h
	src/codeGLFW/WindowGLFW.h
	src/Renderer.h
	src/RendererImplement.h
	src/codeOpenGL/RendererOpenGL.h
	src/Shader.h
	src/ShaderImplement.h
	src/codeOpenGL/ShaderOpenGL.h
	src/Image.h
	src/ImageImplement.h
	src/codeOpenGL/ImageOpenGL.h
	src/ToadEvents.h
	src/ToadKeys.h
	src/Unit.h
)

set(SOURCE_FILES
    src/ToadApplication.cpp
	src/ToadWindow.cpp
	src/codeGLFW/WindowGLFW.cpp
	src/Renderer.cpp
	src/codeOpenGL/RendererOpenGL.cpp
	src/Shader.cpp
	src/codeOpenGL/ShaderOpenGL.cpp
	src/Image.cpp
	src/codeOpenGL/ImageOpenGL.cpp
	src/ToadEvents.cpp
	src/Unit.cpp
)

add_library(Toad SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_definitions(Toad
    	PUBLIC
        	$<$<CONFIG:Debug>:TOAD_DEBUG=2>
        	$<$<CONFIG:RelWithDebInfo>:TOAD_DEBUG=1>
    	PRIVATE 
        	TOAD_LIB
			TOAD_GLFW_WINDOW
			TOAD_OPENGL
)

if(MSVC)
    	target_compile_definitions(Toad PUBLIC TOAD_MS_COMPILER)
endif()

target_include_directories(Toad PRIVATE ../glfw/include)
target_include_directories(Toad PRIVATE ../Toad/src)
target_include_directories(Toad PRIVATE ../glad/include)
target_include_directories(Toad PRIVATE ../stbi)

target_precompile_headers(Toad PRIVATE src/pch.h)

target_link_libraries(Toad glfw)
target_link_libraries(Toad glad)
target_link_libraries(Toad stbi)

file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Toad)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Debug/Toad)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Release/Toad)