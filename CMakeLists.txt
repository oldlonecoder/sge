cmake_minimum_required(VERSION 3.16..3.20 FATAL_ERROR)
# Project name


project(sge VERSION 0.0.1 LANGUAGES CXX)


include(GNUInstallDirs)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(TargetName ${PROJECT_NAME})
SET(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
        sge
        SHARED

		cc/sge.cc include/sge/sge.h
		cc/entity.cc include/sge/entity.h
		cc/vec2.cc include/sge/vec2.h
		cc/component.cc include/sge/component.h
		cc/player.cc cc/player.h
		cc/scene.cc include/sge/scene.h cc/gameconfigs.cc include/sge/gameconfigs.h)


target_compile_definitions(${TargetName} PUBLIC "${TargetName}_DEBUG=$<CONFIG:Debug>")
target_compile_features(${TargetName} PUBLIC cxx_std_17)

include(GenerateExportHeader)
generate_export_header(${TargetName} EXPORT_FILE_NAME ${${PROJECT_NAME}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()

target_include_directories(${TargetName} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

target_link_libraries(${TargetName} ${CMAKE_DL_LIBS} vxio)


#add_executable(sge.app
#		cc/main.cc
#)

#target_link_libraries(sge.app vxio sge sfml-graphics sfml-window sfml-system )
#add_dependencies(sge.app sge)

install(DIRECTORY
        include/${FrameWorkName}/${PROJECT_NAME}/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}"
)

install(TARGETS ${TargetName} #sge.app
		EXPORT ${TargetName}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
