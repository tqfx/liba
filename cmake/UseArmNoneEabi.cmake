set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
find_program(CMAKE_AR ${CMAKE_TOOLCHAIN_PREFIX}-gcc-ar)
find_program(CMAKE_C_COMPILER ${CMAKE_TOOLCHAIN_PREFIX}-gcc)
find_program(CMAKE_CXX_COMPILER ${CMAKE_TOOLCHAIN_PREFIX}-g++)
find_program(CMAKE_RANLIB ${CMAKE_TOOLCHAIN_PREFIX}-gcc-ranlib)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER} -x assembler-with-cpp)
set(CMAKE_C_FLAGS_DEBUG_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_RELEASE_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fdata-sections -ffunction-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections")
find_program(CMAKE_SIZE ${CMAKE_TOOLCHAIN_PREFIX}-size)
find_program(CMAKE_DEBUGER ${CMAKE_TOOLCHAIN_PREFIX}-gdb)
find_program(CMAKE_OBJCOPY ${CMAKE_TOOLCHAIN_PREFIX}-objcopy)
find_program(CMAKE_OBJDUMP ${CMAKE_TOOLCHAIN_PREFIX}-objdump)
find_program(CMAKE_CPPFILT ${CMAKE_TOOLCHAIN_PREFIX}-c++filt)
get_filename_component(CMAKE_FIND_ROOT_PATH "${CMAKE_C_COMPILER}" DIRECTORY)
get_filename_component(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH}" DIRECTORY)
if(EXISTS "${CMAKE_FIND_ROOT_PATH}/lib/${CMAKE_TOOLCHAIN_PREFIX}")
  set(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH}/lib/${CMAKE_TOOLCHAIN_PREFIX}")
elseif(EXISTS "${CMAKE_FIND_ROOT_PATH}/${CMAKE_TOOLCHAIN_PREFIX}")
  set(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH}/${CMAKE_TOOLCHAIN_PREFIX}")
endif()
set(CMAKE_INSTALL_PREFIX ${CMAKE_FIND_ROOT_PATH} CACHE PATH
  "Install path prefix, prepended onto install directories."
)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
if(CMAKE_TOOLCHAIN_FILE)
endif()