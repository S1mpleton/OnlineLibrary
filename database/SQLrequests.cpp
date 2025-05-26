#include "database/SQLrequests.h"

#include <QMultiMap>

QMultiMap<QString, Genres> all_genres(){
    QMultiMap<QString, Genres> all_genres_insert;

    Genres autobiography(1, "Автобиография");
    Genres detective(2, "Детектив");
    Genres fantasy(3, "Фантастика");
    Genres thriller(4, "Триллер");
    Genres comedy(5, "Комедия");
    Genres novel(6, "Роман");
    Genres tragedy(7, "Трагедия");
    Genres fantasy_1(8, "Фэнтези");
    Genres satire(9, "Сатира");

    all_genres_insert.insert("Автобиография", autobiography);
    all_genres_insert.insert("Детектив", detective);
    all_genres_insert.insert("Фантастика", fantasy);
    all_genres_insert.insert("Триллер", thriller);
    all_genres_insert.insert("Комедия", comedy);
    all_genres_insert.insert("Роман", novel);
    all_genres_insert.insert("Трагедия", tragedy);
    all_genres_insert.insert("Фэнтези", fantasy_1);
    all_genres_insert.insert("Сатира", satire);

    return all_genres_insert;
}

QMultiMap<QString, Authors> all_authors(){
    QMultiMap<QString, Authors> all_authors_insert;

    Authors Tolstoy("Толстой", "Лев", "Николаевич", 1);
    Authors Ilif("Ильф", "Илья", "Арнольдович", 2);
    Authors Katef("Катаев", "Евгений", "Петрович", 3);
    Authors Sfift("Джо́натан", "Свифт", "", 4);

    all_authors_insert.insert("Толстой Лев Николаевич", Tolstoy);
    all_authors_insert.insert("Ильф Илья Арнольдович", Ilif);
    all_authors_insert.insert("Катаев Евгений Петрович", Katef);
    all_authors_insert.insert("Джонатан Свифт", Sfift);

    return all_authors_insert;
}


BookGenres InitialData::GENRES(){
    BookGenres ganres;

    for (Genres genre : all_genres()){
        ganres.add_ganre(genre);
    }

    return ganres;
}

BookAuthors InitialData::AUTHORS(){
    BookAuthors authors;

    for (Authors author : all_authors()){
        authors.add_author(author);
    }

    return authors;
}


QList<Book> InitialData::BOOK(){
    QList<Book> books;
    QMultiMap<QString, Genres> all_genres_insert = all_genres();
    QMultiMap<QString, Authors> all_authors_insert = all_authors();


   //-- Война и Мир --
    Book war_and_peace(
        "Война и Мир",
        "«Война́ и мир» (рус. дореф. «Война и миръ») — роман-эпопея Льва Николаевича Толстого, описывающий русское "
        "общество в эпоху войн против Наполеона в 1805—1812 годах. Эпилог романа доводит повествование до 1820 года.",
        1500,
        15,
        10,
        1
    );

    BookGenres war_and_peace_ganres;
    war_and_peace_ganres.add_ganre(all_genres_insert.values("Роман").first());
    war_and_peace.set_genres(war_and_peace_ganres);

    BookAuthors war_and_peace_authors;
    war_and_peace_authors.add_author(all_authors_insert.values("Толстой Лев Николаевич").first());
    war_and_peace.set_authors(war_and_peace_authors);


    //-- Двенадцать стульев --
    Book twenty_chairs(
        "Двенадцать стульев",
        "«Двена́дцать сту́льев» — роман Ильи Ильфа и Евгения Петрова, написанный в 1927 году и являющийся первой совместной "
        "работой соавторов. В 1928 году опубликован в художественно-литературном журнале «Тридцать дней» (№ 1—7); в том же "
        "году издан отдельной книгой. В основе сюжета — поиски бриллиантов, спрятанных в одном из двенадцати стульев мадам "
        "Петуховой, однако история, изложенная в произведении, не ограничена рамками приключенческого жанра: в ней, по "
        "мнению исследователей, дан «глобальный образ эпохи».",
        400,
        25,
        6,
        2
        );

    BookGenres twenty_chairs_ganres;
    twenty_chairs_ganres.add_ganre(all_genres_insert.values("Роман").first());
    twenty_chairs.set_genres(twenty_chairs_ganres);

    BookAuthors twenty_chairs_authors;
    twenty_chairs_authors.add_author(all_authors_insert.values("Ильф Илья Арнольдович").first());
    twenty_chairs_authors.add_author(all_authors_insert.values("Катаев Евгений Петрович").first());
    twenty_chairs.set_authors(twenty_chairs_authors);


    //-- Анна Каренина --
    Book anna_karenina(
        "Анна Каренина",
        "«А́нна Каре́нина» (1873—1877; журнальная публикация 1875—1877; первое книжное издание 1878) — роман Льва "
        "Толстого о трагической любви замужней дамы Анны Карениной и блестящего офицера Алексея Вронского на фоне "
        "счастливой семейной жизни дворян Константина Лёвина и Кити Щербацкой. Масштабная картина нравов и быта "
        "дворянской среды Петербурга и Москвы второй половины XIX века, сочетающая философские размышления авторского "
        "alter ego Лёвина с передовыми в русской литературе психологическими зарисовками, а также сценами из жизни крестьян.",
        900,
        8,
        20,
        3
        );

    BookGenres anna_karenina_ganres;
    anna_karenina_ganres.add_ganre(all_genres_insert.values("Роман").first());
    anna_karenina.set_genres(anna_karenina_ganres);

    BookAuthors anna_karenina_authors;
    anna_karenina_authors.add_author(all_authors_insert.values("Толстой Лев Николаевич").first());
    anna_karenina.set_authors(anna_karenina_authors);


    //-- Путешествия Гулливера --
    Book travel_gulever(
        "Путешествия Гулливера",
        "«Библиотека школьной классики» — элегантная, изящная серия книг, необходимых в каждом доме. "
        "Каждый том серии — это встреча с прекрасным, которая запомнится навсегда.",
        600,
        7,
        30,
        4
        );

    BookGenres travel_gulever_ganres;
    travel_gulever_ganres.add_ganre(all_genres_insert.values("Роман").first());
    travel_gulever_ganres.add_ganre(all_genres_insert.values("Фэнтези").first());
    travel_gulever_ganres.add_ganre(all_genres_insert.values("Сатира").first());
    travel_gulever.set_genres(travel_gulever_ganres);

    BookAuthors travel_gulever_authors;
    travel_gulever_authors.add_author(all_authors_insert.values("Джонатан Свифт").first());
    travel_gulever.set_authors(travel_gulever_authors);




    books.append(war_and_peace);
    books.append(twenty_chairs);
    books.append(anna_karenina);
    books.append(travel_gulever);

    return books;
}


