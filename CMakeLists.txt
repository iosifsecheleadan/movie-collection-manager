cmake_minimum_required(VERSION 3.15)

project(movieDB)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/sechelea/Qt5.14.1/5.14.1/gcc_64/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "--coverage")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(movieDB
        project/main/cpp/main/main.cpp
        project/main/cpp/ui/UserInterface.h project/main/cpp/ui/Console.cpp project/main/cpp/ui/Console.h project/main/cpp/ui/UserInterfaceException.h
        project/main/cpp/ctrl/ControllerException.h project/main/cpp/ctrl/Administrator.h project/main/cpp/ctrl/Controller.h
        project/main/cpp/repo/Repository.h project/main/cpp/repo/DynamicVector.h project/main/cpp/repo/StlVector.h
        project/main/cpp/repo/RepositoryException.h
        project/main/cpp/domain/entity/Movie.cpp project/main/cpp/domain/entity/Movie.h
        project/main/cpp/main/MainException.h
        project/main/cpp/domain/validator/Validator.h project/main/cpp/domain/validator/MovieValidator.h
        project/main/cpp/domain/validator/ValidatorException.h
        project/test/cpp/domain/integer/IntegerValidator.h

        project/test/cpp/domain/entity/TestMovie.cpp project/test/cpp/domain/entity/TestMovie.h
        project/test/cpp/domain/integer/Integer.cpp project/test/cpp/domain/integer/Integer.h project/test/cpp/domain/integer/TestInteger.cpp project/test/cpp/domain/integer/TestInteger.h
        project/test/cpp/repo/TestDynamicVector.cpp project/test/cpp/repo/TestDynamicVector.h project/test/cpp/repo/TestRepository.cpp project/test/cpp/repo/TestRepository.h
        project/test/cpp/ctrl/TestController.cpp project/test/cpp/ctrl/TestController.h project/test/cpp/ctrl/TestAdministrator.cpp project/test/cpp/ctrl/TestAdministrator.h
        project/test/cpp/repo/TestStlVector.cpp project/test/cpp/repo/TestStlVector.h
        project/test/cpp/domain/validator/TestMovieValidator.cpp project/test/cpp/domain/validator/TestMovieValidator.h project/main/cpp/ui/MainWindow.h project/main/cpp/ctrl/UndoRedoController.h)

target_link_libraries(movieDB PRIVATE Qt5::Widgets)
