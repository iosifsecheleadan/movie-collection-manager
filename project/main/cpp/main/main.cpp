#include <QtWidgets/QApplication>
#include <project/main/cpp/ui/MainWindow.h>
#include <project/main/cpp/ctrl/UndoRedoController.h>

#include "../domain/entity/Movie.h"
#include "../domain/validator/Validator.h"
#include "../domain/validator/MovieValidator.h"
#include "../repo/Repository.h"
#include "../repo/DynamicVector.h"
#include "../ui/UserInterface.h"
#include "../ui/Console.h"

#include "../../../test/cpp/domain/entity/TestMovie.h"
#include "../../../test/cpp/repo/TestDynamicVector.h"
#include "../../../test/cpp/repo/TestRepository.h"
#include "../../../test/cpp/domain/integer/TestInteger.h"
#include "../../../test/cpp/ctrl/TestController.h"
#include "../../../test/cpp/ctrl/TestAdministrator.h"
#include "../../../test/cpp/repo/TestStlVector.h"
#include "../../../test/cpp/domain/validator/TestMovieValidator.h"

void testAll();

void run();

int runQT(int argc, char *argv[]);

void test();

int main(int argc, char *argv[]) {
    // testAll();
    // run();
    //test();
    return runQT(argc, argv);

    return 0;
}

void test() {
}

/**
 * Run the GUI program
 */
int runQT(int argc, char *argv[]) {
    QApplication application(argc, argv);

    Validator<Movie>* validator = new MovieValidator();

    Repository<Movie>* dataBase = new StlVector<Movie>();
    Repository<Movie>* watchList = new StlVector<Movie>();

    UndoRedoController<Movie>* undoRedo = new UndoRedoController<Movie>();

    Controller<Movie>* admin = new Administrator(validator, dataBase);
    Controller<Movie>* user = new Controller<Movie>(validator, watchList);


    MainWindow* window = new MainWindow(admin, user, undoRedo,
                                        "/home/sechelea/Documents/programming/projects/C++/oopII/movieDB/project/main/resources");
    window->run();

    return application.exec();
}

/**
 * Run the console program
 */
void run() {
    // Repository<Movie>* dataBase = new DynamicVector<Movie>();
    // Repository<Movie>* watchList = new DynamicVector<Movie>();

    Validator<Movie>* validator = new MovieValidator();

    Repository<Movie>* dataBase = new StlVector<Movie>();
    Repository<Movie>* watchList = new StlVector<Movie>();

    Controller<Movie>* admin = new Administrator(validator, dataBase);
    Controller<Movie>* user = new Controller<Movie>(validator, watchList);

    UserInterface* userInterface = new Console(admin, user,
            "/home/sechelea/Documents/programming/projects/C++/oopII/movieDB/project/main/resources");
    userInterface->run();

    delete userInterface;
}

/**
 * Run tests for the program.
 */
void testAll() {
    TestMovie::testAll();
    TestMovieValidator::testAll();
    TestInteger::testAll();

    TestDynamicVector::testAll();
    TestStlVector::testAll();
    TestRepository::testAll();

    TestController::testAll();
    TestAdministrator::testAll();

    std::cout << "All tests passed successfully";
}

