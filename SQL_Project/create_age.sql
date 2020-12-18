# Adds age col
ALTER TABLE census
ADD age int;

# Calculates age from id_Nuaudiencesmber, sets age col to calculated value
UPDATE census
SET age = 2020 - substring(id_Number, 6, 4);

# Prints results to user
SELECT * from zovid.census;