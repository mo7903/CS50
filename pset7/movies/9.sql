SELECT name FROM people WHERE id IN
(SELECT DISTINCT(people.id) FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND year = 2004)
ORDER BY birth;