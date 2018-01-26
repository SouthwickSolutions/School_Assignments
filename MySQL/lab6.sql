tee lab6.txt;
use books;

#query1
SELECT title_id,title_name,price,.10 AS "Discount",(price * .9) AS "New Price" FROM titles;

#query2
SELECT CONCAT(au_lname, ',', au_fname) AS "name" FROM authors ORDER BY au_lname ASC, au_fname ASC;

#query3
SELECT UPPER(CONCAT(SUBSTRING(au_lname FROM 1 FOR 3),SUBSTRING(phone FROM 9))) AS "Search ID", CONCAT(au_lname, ',', au_fname) AS "name" from authors;

#query4
SELECT au_lname, CHARACTER_LENGTH(au_lname) AS "length" from authors;

#query5
SELECT title_id,title_name,EXTRACT(year FROM pubdate) AS "year" from titles;

#query6
SELECT title_id,title_name,pubdate,DATE_ADD(pubdate, INTERVAL 28 YEAR) AS "copyright date" FROM titles;

#query7
SELECT title_id,title_name,price,IF(type='history',(price*.9),(price*.8)) AS 'New Price' FROM titles;

#query8
SELECT title_id,title_name,COALESCE(price,'priceless') AS 'retail' FROM titles;

#query9
SELECT NOW() AS "Current Time";

#query10
SELECT SUBSTRING(CURRENT_USER FROM 6) AS "Server";
