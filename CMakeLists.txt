# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.

cmake_minimum_required (VERSION 3.8)#3.10
# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project(CMakeProject1)

set(CMAKE_CXX_STANDARD 17)

# Подключение libcurl
find_package(CURL REQUIRED)

#add_executable(CMakeProject1 src/main.cpp)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject1 "Main.cpp" "CMakeProject1.h")

# Линковка с библиотекой libcurl
target_link_libraries(CMakeProject1 PRIVATE CURL::libcurl)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(CMakeProject1 PUBLIC "LINUX_OS")
    #target_link_libraries(curltest curl)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(CMakeProject1 PUBLIC "WINDOWS_OS")
    target_include_directories(CMakeProject1 PUBLIC "C:\\curl\\include")
	#target_link_libraries(curltest C:\\curl\\lib\\libcurl.lib)
endif()







if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()


#install(TARGETS CMakeProject1)#доп
# TODO: Добавьте тесты и целевые объекты, если это необходимо.