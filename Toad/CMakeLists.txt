set(HEADER_FILES
	include/Toad.h
	src/ToadApplication.h
	src/Utility.h
	src/ToadWindow.h
	src/WindowImpl.h
	src/codeGLFW/WindowGLFW.h
	
)

set(SOURCE_FILES
    	src/ToadApplication.cpp
	src/ToadWindow.cpp
	src/codeGLFW/WindowGLFW.cpp
)

add_library(Toad SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_definitions(Toad
    	PUBLIC
        	$<$<CONFIG:Debug>:TOAD_DEBUG=2>
        	$<$<CONFIG:RelWithDebInfo>:TOAD_DEBUG=1>
    	PRIVATE 
        	TOAD_LIB
			TOAD_GLFW_WINDOW
)

if(MSVC)
    	target_compile_definitions(Toad PUBLIC TOAD_MS_COMPILER)
endif()

target_include_directories(Toad PRIVATE ../glfw/include)
target_include_directories(Toad PRIVATE ../Toad)

target_precompile_headers(Toad PRIVATE src/pch.h)

target_link_libraries(Toad glfw)
