cmake_minimum_required(VERSION 3.16..3.20 FATAL_ERROR)
# Project name


project(virtualspace VERSION 0.0.1 LANGUAGES CXX)


include(GNUInstallDirs)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(TargetName ${PROJECT_NAME})
#SET(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(virtualspace
		main.cc
)



target_compile_definitions(${TargetName} PUBLIC "${TargetName}_DEBUG=$<CONFIG:Debug>")
target_compile_features(${TargetName} PUBLIC cxx_std_17)

include(GenerateExportHeader)
#generate_export_header(${TargetName} EXPORT_FILE_NAME ${${PROJECT_NAME}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()

#target_include_directories(${TargetName} PUBLIC
#    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
#        )

#target_link_libraries(${TargetName} ${CMAKE_DL_LIBS} vxio sge)



target_link_libraries(virtualspace vxio sge sfml-graphics sfml-window sfml-system )
#add_dependencies(virtualspace.app sge)

install(DIRECTORY
        assets
        DESTINATION "${CMAKE_INSTALL_PREFIX}/games/${PROJECT_NAME}"
)

install(TARGETS ${TargetName} virtualspace
		EXPORT ${TargetName}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)


