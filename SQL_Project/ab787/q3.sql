
# Creates temp_census table with combined info of census and physical exam
CREATE table temp_census AS
(SELECT census.*, patients_physical_exam.vital_cap, patients_physical_exam.metabolism, patients_physical_exam.exam_date
from census
LEFT JOIN patients_physical_exam ON census.id_Number = patients_physical_exam.id_Number);


# Creates temp_2 table from temp_census table, but only most recent exam date
CREATE table temp_2
(SELECT temp_census.*
from
(SELECT id_Number, MAX(exam_date) AS exam_date
from temp_census
GROUP BY id_Number) as most_recent_exams
INNER JOIN temp_census
on temp_census.id_Number = most_recent_exams.id_Number AND
temp_census.exam_date = most_recent_exams.exam_date);


# Gets rid of duplicate 24 people who take a physical exam on the same day
# We do it by choosing the exam with the max metabolism
CREATE table temp_3
(SELECT temp_2.*
from
(SELECT id_Number, MAX(metabolism) AS metabolism
from temp_2
GROUP BY id_Number) as max_metabolisms
INNER JOIN temp_2
on temp_2.id_Number = max_metabolisms.id_Number AND
temp_2.metabolism = max_metabolisms.metabolism);

select count(*) from temp_3;
# Drops table temp_2
DROP TABLE temp_2;

# Create score var
ALTER TABLE temp_3
ADD score float;

# Calculate Score for each person in temp_3
UPDATE temp_3
SET score = 
((vital_cap / 5200.0) + 
(metabolism / 2800.0) + 
(1.0 - abs(age - 25.0) / 75.0) + 
(1.0 - abs(bmi - 23.0) / 30.0)) *
25;


# Creates temp_census table
CREATE table temp_census AS
(SELECT census.*, temp_3.score
from census
LEFT JOIN temp_3 ON census.id_Number = temp_3.id_Number);

# Set null scores (people without scores) to the average score from all scores available
UPDATE temp_census
SET score = (SELECT AVG(score) from temp_3)
WHERE score IS NULL;

# Drops census (will be replaced later)
DROP TABLE census;

# Sets census back to temp_census table
CREATE table census as (
SELECT * from temp_census);

# Drops temp_census, temp_3
DROP TABLE temp_census;
DROP TABLE temp_3;

# Prints result
SELECT * from census;