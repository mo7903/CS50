SELECT name FROM movies, stars, people
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND title = "Toy Story";