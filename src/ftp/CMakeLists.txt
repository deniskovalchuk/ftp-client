add_library(ftp
        STATIC
            client.cpp
            client.hpp
            ftp_exception.hpp
            detail/connection_exception.hpp
            detail/control_connection.cpp
            detail/control_connection.hpp
            detail/data_connection.cpp
            detail/data_connection.hpp
            detail/reply.hpp
            detail/utils.cpp
            detail/utils.hpp)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system)

target_link_libraries(ftp
        PRIVATE
            ${Boost_LIBRARIES})

target_include_directories(ftp
        PRIVATE
            ${Boost_INCLUDE_DIRS})