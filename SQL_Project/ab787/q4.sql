# Creates temp_1 table (combines audiences with fitness_score)
CREATE TABLE temp_1 AS
(SELECT audiences.*, census.score
from audiences
LEFT JOIN census ON audiences.id_Number = census.id_Number);

# Creates temp_2 table (combines temp_1 with zovid12 test_result)
CREATE TABLE temp_2 AS
(SELECT temp_1.*, zovid12test.result AS test_result
from temp_1
LEFT JOIN zovid12test ON temp_1.id_Number = zovid12test.id_Number);

# Drops audiences
DROP TABLE audiences;

# Sets audiences to temp_2
CREATE TABLE audiences as
(select * from temp_2);

# Drop both temp tables
DROP TABLE temp_1;
DROP TABLE temp_2;

# Prints result
select * from audiences;