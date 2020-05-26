//
// Created by sechelea on 3/28/20.
//

#include "TestMovie.h"
#include "../../../../main/cpp/domain/validator/ValidatorException.h"

#include<cassert>

TestMovie::~TestMovie() {
    //delete &this->one;
    //delete &this->two;
    //delete &this->three;
}

void TestMovie::testAll() {
    TestMovie* tests = new TestMovie();

    tests->testDefaultConstructor();
    tests->testParametrizedConstructor();
    tests->testCsvFormatConstructor();
    tests->testCopyConstructor();

    tests->testDestructor();

    tests->testDefaultToString();
    tests->testSeparatorToString();
    tests->testToHtmlTableHead();
    tests->testToHtmlTableRow();

    tests->testGetGenre();
    tests->testGetLinkToTrailer();
    tests->testGetLinkToMovie();
    tests->testGetNoLikes();

    tests->testSetNoLikes();

    tests->testEquality();
    tests->testInequality();
}

void TestMovie::testDefaultConstructor() {
    one = * new Movie();
    two = * new Movie();
    three = * new Movie();

    assert(one == two); assert(two == three); assert(one == three);

    assert(one.getNoLikes() == 0);

    assert(one.getLinkToTrailer() == one.getLinkToMovie());
    assert(one.getLinkToMovie() == one.getGenre());
    assert(one.getGenre().empty());
}

void TestMovie::testParametrizedConstructor() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    three = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");

    assert(one == two); assert(one != three); assert(two != three);

    assert(one.getNoLikes() == two.getNoLikes());
    assert(one.getNoLikes() == 2);
    assert(one.getNoLikes() != three.getNoLikes());
    assert(two.getNoLikes() != three.getNoLikes());
    assert(three.getNoLikes() == 20);

    assert(one.getGenre() == two.getGenre());
    assert(one.getGenre() == "genre"); assert(two.getGenre() == "genre");
    assert(one.getGenre() != three.getGenre());
    assert(two.getGenre() != three.getGenre());
    assert(three.getGenre() == "no genre");

    assert(one.getLinkToTrailer() == two.getLinkToTrailer());
    assert(one.getLinkToTrailer() == "trailer"); assert(two.getLinkToTrailer() == "trailer");
    assert(one.getLinkToTrailer() != three.getLinkToTrailer());
    assert(two.getLinkToTrailer() != three.getLinkToTrailer());
    assert(three.getLinkToTrailer() == "no trailer");

    assert(one.getLinkToMovie() == two.getLinkToMovie());
    assert(one.getLinkToMovie() == "movie"); assert(two.getLinkToMovie() == "movie");
    assert(one.getLinkToMovie() != three.getLinkToMovie());
    assert(two.getLinkToMovie() != three.getLinkToMovie());
    assert(three.getLinkToMovie() == "no movie");
}

void TestMovie::testCsvFormatConstructor() {
    try { one = * new Movie("what,when,1,2,where,who,why"); assert(false);
    } catch (ValidatorException& e) {
        std::string errorMessage = "String not formatted correctly";
        assert(e.what() == errorMessage);
    }
    try { two = * new Movie("what,when,where,who,why,seriously though"); assert(false);
    } catch (ValidatorException& e) {
        std::string errorMessage = "String not formatted correctly";
        assert(e.what() == errorMessage);
    }
    three = * new Movie("what,where,1,2,when,who");

}

void TestMovie::testCopyConstructor() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie(two);

    assert(one == two); assert(two == three); assert(one == three);

    assert(one.getNoLikes() == two.getNoLikes());
    assert(one.getNoLikes() == three.getNoLikes());
    assert(two.getNoLikes() == three.getNoLikes());

    assert(one.getGenre() == two.getGenre());
    assert(one.getGenre() == three.getGenre());
    assert(two.getGenre() == three.getGenre());

    assert(one.getLinkToTrailer() == two.getLinkToTrailer());
    assert(one.getLinkToTrailer() == three.getLinkToTrailer());
    assert(two.getLinkToTrailer() == three.getLinkToTrailer());

    assert(one.getLinkToMovie() == two.getLinkToMovie());
    assert(one.getLinkToMovie() == three.getLinkToMovie());
    assert(two.getLinkToMovie() == three.getLinkToMovie());
}

void TestMovie::testDestructor() {
    Movie* movie = new Movie();
    delete movie;

    movie = new Movie("title", "genre", 1, 2, "trailer", "movie");
    delete movie;

    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    movie = new Movie(one);
    delete movie;
    assert(one.getNoLikes() == 2);
    assert(one.getGenre() == "genre");
    assert(one.getLinkToMovie() == "movie");
    assert(one.getLinkToTrailer() == "trailer");
}

void TestMovie::testDefaultToString() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");
    three = * new Movie();
    assert(one.toString() == "\nTitle : title\nGenre : genre\nYear of Release : 1\nLikes : 2\nTrailer : trailer\nMovie : movie");
    assert(two.toString() == "\nTitle : no title\nGenre : no genre\nYear of Release : 10\nLikes : 20\nTrailer : no trailer\nMovie : no movie");
    assert(three.toString() == "\nTitle : \nGenre : \nYear of Release : 0\nLikes : 0\nTrailer : \nMovie : ");
}

void TestMovie::testSeparatorToString() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");
    three = * new Movie();
    assert(one.toString(" - ") == "title - genre - 1 - 2 - trailer - movie");
    assert(two.toString(", ") == "no title, no genre, 10, 20, no trailer, no movie");
    assert(three.toString("no! ") == "no! no! 0no! 0no! no! ");
}

void TestMovie::testToHtmlTableHead() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");
    three = * new Movie();
    assert(one.toHtmlTableHead(0) == two.toHtmlTableHead(0));
    assert(one.toHtmlTableHead(1) == three.toHtmlTableHead(1));
    assert(two.toHtmlTableHead(0) != three.toHtmlTableHead(1));
    assert(one.toHtmlTableHead(0) == "<tr>\n\t"
                                     "<td>Title</td>\n\t"
                                     "<td>Genre</td>\n\t"
                                     "<td>Year of Release</td>\n\t"
                                     "<td>Likes</td>\n\t"
                                     "<td>Trailer</td>\n\t"
                                     "<td>Movie</td>\n"
                                     "</tr>\n");
    assert(two.toHtmlTableHead(2) == "\t\t<tr>\n\t\t\t"
                                     "<td>Title</td>\n\t\t\t"
                                     "<td>Genre</td>\n\t\t\t"
                                     "<td>Year of Release</td>\n\t\t\t"
                                     "<td>Likes</td>\n\t\t\t"
                                     "<td>Trailer</td>\n\t\t\t"
                                     "<td>Movie</td>\n\t\t"
                                     "</tr>\n");
}

void TestMovie::testToHtmlTableRow() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");
    three = * new Movie();
    assert(one.toHtmlTableRow(0) != two.toHtmlTableRow(0));
    assert(two.toHtmlTableRow(1) != three.toHtmlTableRow(1));
    assert(three.toHtmlTableRow(2) != one.toHtmlTableRow(2));
    assert(one.toHtmlTableRow(0) == "<tr>\n\t"
                                    "<td>title</td>\n\t"
                                    "<td>genre</td>\n\t"
                                    "<td>1</td>\n\t"
                                    "<td>2</td>\n\t"
                                    "<td> <a href=\"trailer\">Watch</a> </td>\n\t"
                                    "<td> <a href=\"movie\">Stream</a> </td>\n"
                                    "</tr>\n");
    assert(two.toHtmlTableRow(2) == "\t\t<tr>\n\t\t\t"
                                    "<td>no title</td>\n\t\t\t"
                                    "<td>no genre</td>\n\t\t\t"
                                    "<td>10</td>\n\t\t\t"
                                    "<td>20</td>\n\t\t\t"
                                    "<td> <a href=\"no trailer\">Watch</a> </td>\n\t\t\t"
                                    "<td> <a href=\"no movie\">Stream</a> </td>\n\t\t"
                                    "</tr>\n");
}

void TestMovie::testGetGenre() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie();

    assert(one.getGenre() == two.getGenre());
    assert(one.getGenre() == "genre"); assert(two.getGenre() == "genre");
    assert(three.getGenre().empty());
}

void TestMovie::testGetLinkToTrailer() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie();

    assert(one.getLinkToTrailer() == two.getLinkToTrailer());
    assert(one.getLinkToTrailer() == "trailer"); assert(two.getLinkToTrailer() == "trailer");
    assert(three.getLinkToTrailer().empty());
}

void TestMovie::testGetLinkToMovie() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie();

    assert(one.getLinkToMovie() == two.getLinkToMovie());
    assert(one.getLinkToMovie() == "movie"); assert(two.getLinkToMovie() == "movie");
    assert(three.getLinkToMovie().empty());
}

void TestMovie::testGetNoLikes() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie();

    assert(one.getNoLikes() == two.getNoLikes());
    assert(one.getNoLikes() == 2); assert(two.getNoLikes() == 2);
    assert(three.getNoLikes() == 0);
}

void TestMovie::testSetNoLikes() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie();

    one.setNoLikes(100);
    three.setNoLikes(100.54);
    assert(one.getNoLikes() == three.getNoLikes());

    two.setNoLikes('2');
    assert(two.getNoLikes() == 50);
}

void TestMovie::testEquality() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie(one);
    three = * new Movie(two);

    assert(one == two); assert(two == three); assert(one == three);
}

void TestMovie::testInequality() {
    one = * new Movie("title", "genre", 1, 2, "trailer", "movie");
    two = * new Movie("no title", "no genre", 10, 20, "no trailer", "no movie");
    three = * new Movie();

    assert(one != two); assert(one != three); assert(two != three);
    one = * new Movie(two);
    two = * new Movie(three);
    assert(one != two); assert(one != three);
}


