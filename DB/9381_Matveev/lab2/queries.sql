use lab2;

# Репертуар кинотеатра(-ов)
SELECT DISTINCT Cinema.name,  F.filmName   FROM Cinema
    INNER  JOIN  SessionInCinema SIC on Cinema.cinemaId = SIC.cinemaId
    INNER JOIN Session S on SIC.sessionId = S.sessionId
    INNER JOIN SessionFilm SF on S.sessionId = SF.sessionId
    INNER JOIN Film F on SF.filmId = F.filmId;

# Адрес и район кинотеатра
SELECT name, location FROM Cinema;

# Число свободных мест на данный сеанс в указанном кинотеатре
SELECT Cinema.name, S.dateAndTime, H.seatsCount - COUNT(ticketId) AS `Free seats' count` FROM Cinema
        INNER JOIN Hall H on Cinema.cinemaId = H.cinemaId
        INNER JOIN Ticket T on H.hallId = T.hallId
        INNER JOIN Session S on T.sessionId = S.sessionId
        GROUP BY S.dateAndTime, Cinema.name, H.seatsCount
        HAVING COUNT(ticketId) = 0;

#Цена билетов на данный сеанс в указанном кинотеатре
SELECT Cinema.name, S.dateAndTime, T.price AS `Ticket price` FROM Cinema
        INNER JOIN Hall H on Cinema.cinemaId = H.cinemaId
        INNER JOIN Ticket T on H.hallId = T.hallId
        INNER JOIN Session S on T.sessionId = S.sessionId;

# Жанр, производство и режиссер данного фильма
SELECT DISTINCT  filmName, G.name AS Genre, production, director FROM Film
    INNER JOIN FilmGenre FG on Film.filmId = FG.filmId
    INNER JOIN Genre JOIN Genre G on FG.genreId = G.genreId
WHERE filmName = 'Дом у дороги';
# Какие фильмы имеют награды, когда и в каких кинотеатрах они демонстрируются?
SELECT DISTINCT filmName, availabilityOfPrizes, S.dateAndTime, C.name FROM Film
    INNER JOIN SessionFilm SF on Film.filmId = SF.filmId
    INNER JOIN Session JOIN Session S on SF.sessionId = S.sessionId
    INNER JOIN SessionInCinema SIC on Session.sessionId = SIC.sessionId
    INNER JOIN Cinema C on SIC.cinemaId = C.cinemaId
WHERE availabilityOfPrizes <> '-';

#В каких кинотеатрах в указанный день на указанных сеансах демонстрируется комедия?
SELECT  Cinema.name, dateAndTime, filmName, G.name FROM Cinema
    INNER JOIN SessionInCinema SIC on Cinema.cinemaId = SIC.cinemaId
    INNER JOIN Session S on SIC.sessionId = S.sessionId
    INNER JOIN SessionFilm SF on S.sessionId = SF.sessionId
    INNER JOIN Film F on SF.filmId = F.filmId
    INNER JOIN FilmGenre FG on F.filmId = FG.filmId
    INNER JOIN Genre G on FG.genreId = G.genreId
WHERE G.name = 'Комедия' AND S.dateAndTime = '2013-03-02 19:12:01.000';


