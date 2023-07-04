SELECT title, rating FROM movies, ratings
WHERE movie_id = movies.id
AND year = 2010
ORDER BY rating DESC, title;