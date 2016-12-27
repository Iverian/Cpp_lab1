declare variable $Doc external;
for $x in doc($Doc)/catalog/array
where matches ($x/Name, '.*Il Patio.*') and matches ($x/District, '.*Красносельский.*')
return ($x/Name,$x/Address,$x/District)