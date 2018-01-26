tee lab7.txt;
use books;

# query 1 - What is the average price of the books
SELECT ROUND(AVG(price),2) AS "Average Price" FROM titles;

# query 2 - How many books are in the table
SELECT COUNT(title_id) AS "Qty" FROM titles;

# query 3 - What is the total sales volume (sales*price) of the books
SELECT SUM((sales*price)) AS "Volume" FROM titles;

# query 4 - What is the average number of pages by book type
SELECT type,ROUND(AVG(pages)) AS "Average Pages" FROM titles GROUP BY type;

# query 5 - Display all book types and the average number of pages if the average is greater than 500
SELECT type,ROUND(AVG(pages)) AS "Average Pages" FROM titles GROUP BY type HAVING ROUND(AVG(pages))>500;

# query 6 - Same as #5 only sort by the average number of page
SELECT type,ROUND(AVG(pages)) AS "Average Pages" FROM titles GROUP BY type HAVING ROUND(AVG(pages))>500 ORDER BY type DESC;

# query 7 - How many different states are there in the authors table
SELECT COUNT(DISTINCT(state)) AS "Number of States" FROM authors;

# query 8 - Subtotal the number of authors from each state
SELECT state,COUNT(au_id) AS "# of Authors" FROM authors GROUP BY state;

# query 9 - Subtotal the # of books in each type except children
SELECT type,COUNT(type) AS "# of books" FROM titles GROUP BY type HAVING type !='children';

# query 10 - Same as #9 but only include the subtotals greater than or equal to 3 and sort them by the type of book
SELECT type,COUNT(type) AS "# of books" FROM titles GROUP BY type HAVING COUNT(type)>=3;


#last command -
#source lab7.sql;

