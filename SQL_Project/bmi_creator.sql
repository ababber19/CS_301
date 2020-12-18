# Adds bmi col of float type
ALTER TABLE zovid.census
ADD bmi float;


# Creates temp_census table
CREATE table temp_census AS
(SELECT zovid.census.*, zovid.patient_info.height_cm, zovid.patient_info.weight_kg
from zovid.census
LEFT JOIN zovid.patient_info ON zovid.census.id_Number = zovid.patient_info.id_Number
ORDER BY zovid.census.id_Number);

# Sets bmi var to correct value using equation (weight(kg) / height(m))
UPDATE temp_census
SET bmi = round(CAST(temp_census.weight_kg as DECIMAL) /POWER(CAST(temp_census.height_cm as DECIMAL) / 100.0, 2), 3);

# Drops weight, height vars from table
ALTER TABLE temp_census
DROP weight_kg,
DROP height_cm;

# Drops census table
DROP table census;

# Sets census back to temp_census table
CREATE table census as (
SELECT * from temp_census);

# Drops temp_census table
DROP TABLE temp_census;

# Prints result
SELECT * from census;
