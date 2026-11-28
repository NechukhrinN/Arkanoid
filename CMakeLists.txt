cmake_minimum_required(VERSION 3.16)

project(Arkanoid VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ARKANOID_FETCH_SFML "Download and build SFML when it is not installed" ON)

# Prefer an installed SFML 2.x; otherwise fetch and build it from source.
find_package(SFML 2 COMPONENTS graphics window system QUIET)

if(SFML_FOUND)
	message(STATUS "Using installed SFML ${SFML_VERSION}")
elseif(ARKANOID_FETCH_SFML)
	message(STATUS "SFML not found - fetching SFML 2.6.2")
	include(FetchContent)

	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
	set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
	set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
	set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 2.6.2
		GIT_SHALLOW TRUE
	)
	FetchContent_MakeAvailable(SFML)
else()
	message(FATAL_ERROR
		"SFML was not found. Install SFML 2.x (e.g. with vcpkg) or configure "
		"with -DARKANOID_FETCH_SFML=ON to download and build it automatically.")
endif()

add_executable(Arkanoid
	Arkanoid/main.cpp
	Arkanoid/MainGame.cpp
	Arkanoid/menu.cpp
	Arkanoid/ball.cpp
	Arkanoid/paddle.cpp
	Arkanoid/highscore.cpp
	Arkanoid/productinfo.cpp
	Arkanoid/settings.h
	Arkanoid/productinfo.h
)

target_include_directories(Arkanoid PRIVATE Arkanoid)

# Link against the imported (installed) or in-tree (fetched) SFML targets.
if(TARGET SFML::Graphics)
	target_link_libraries(Arkanoid PRIVATE SFML::Graphics SFML::Window SFML::System)
else()
	target_link_libraries(Arkanoid PRIVATE sfml-graphics sfml-window sfml-system)
endif()

if(MSVC)
	target_compile_options(Arkanoid PRIVATE /W3 /permissive-)
	target_compile_definitions(Arkanoid PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# The game loads everything through paths relative to the working directory,
# so keep a copy of the resources next to the executable.
add_custom_command(TARGET Arkanoid POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/Arkanoid/res"
		"$<TARGET_FILE_DIR:Arkanoid>/res"
	COMMENT "Copying game resources"
)

install(TARGETS Arkanoid RUNTIME DESTINATION .)
install(DIRECTORY Arkanoid/res DESTINATION .)
