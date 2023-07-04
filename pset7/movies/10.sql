SELECT name FROM people WHERE people.id IN
(SELECT DISTINCT(person_id) FROM movies, ratings, directors, people
WHERE movies.id = directors.movie_id
AND movies.id = ratings.movie_id
AND people.id = person_id
AND rating >= 9.0);