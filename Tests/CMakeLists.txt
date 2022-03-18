project(Tests LANGUAGES CXX)

set(SOURCES
	Main.cpp	
	test1.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
