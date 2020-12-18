SELECT supervisor from q1 where person = "Alice";


SELECT S.supervisor
from q1 AS T, q1 S
Where T.supervisor = S.person and T.person="bob";


(SELECT supervisor
FROM q1
WHERE person = "Bob")
UNION
(SELECT S.supervisor
FROM q1 AS T, q1 S
WHERE T.supervisor = S.person AND T.person = "Bob");


(SELECT S.supervisor
FROM q1 AS T, q1 S
WHERE T.supervisor = S.person AND T.person = "Bob")
UNION
(SELECT supervisor
FROM q1
WHERE person = "Bob");


# PART IV QUERY
(select supervisor from q1
where person = "Bob")
UNION
select supervisor from q1
where person =
(select supervisor from q1
where person = "Bob");


CREATE TABLE testing_1 AS
(select supervisor from q1
where person = "Bob");

select supervisor from (select supervisor from testing_1);
# Error Code: 1248. Every derived table must have its own alias


(Select supervisor
from q1
where person = "Bob")
UNION
(SELECT s.supervisor
from q1 AS T, q1 S
where T.supervisor = S.person AND T.person = "Bob");





# QUERY 1
SELECT name, price from item
WHERE price = (select max(price) from item);





# QUERY 2
CREATE TABLE temp_1 AS
(SELECT item.*, itemsale.transid, itemsale.qty
from item
LEFT JOIN itemsale ON item.itemid = itemsale.itemid);

select category, (sum(qty) * sum(price)) from temp_1
group by category;


# QUERY 3
CREATE TABLE temp_2 AS
(SELECT temp_1.itemid, temp_1.category, temp_1.transid, transaction.custid
from temp_1
LEFT JOIN transaction ON temp_1.transid = transaction.transid);


CREATE TABLE temp_3 AS
(SELECT temp_2.itemid, temp_2.category, customer.city
from temp_2
LEFT JOIN customer ON temp_2.custid = customer.custid);


SELECT * from temp_3
where city != "Kunshan";



# QUERY 4
CREATE TABLE temp_4 AS
(select transaction.custid, itemsale.itemid
from transaction
LEFT JOIN itemsale ON transaction.transid = itemsale.transid);

CREATE TABLE temp_5 AS
(SELECT temp_4.custid, item.category
from temp_4
LEFT JOIN item ON temp_4.itemid = item.itemid);


select distinct(custid) from temp_5
WHERE category NOT IN ("Electronics");
