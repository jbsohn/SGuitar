delete
from guitar;
delete
from guitar_string;
delete
from guitar_adjustment;
delete
from guitar_string_adjustment;
update sqlite_sequence
set seq=0
where name = 'guitar';
update sqlite_sequence
set seq=0
where name = 'guitar_string';
update sqlite_sequence
set seq=0
where name = 'guitar_adjustment';
update sqlite_sequence
set seq=0
where name = 'guitar_string_adjustment';
