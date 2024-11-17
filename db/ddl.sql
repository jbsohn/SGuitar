create table chord
(
    id        INTEGER not null
        primary key autoincrement
        unique,
    name      TEXT,
    intervals TEXT
);

create table guitar
(
    id              integer not null
        constraint guitar_pk
            primary key autoincrement,
    name            TEXT    not null,
    number_of_frets integer,
    fret_markers    TEXT,
    type            integer
);

create table guitar_adjustment
(
    id        integer
        constraint guitar_adjustment_pk
            primary key autoincrement,
    guitar_id INT,
    name      TEXT,
    position  INT,
    "order"   INT
);

create table guitar_string
(
    id            integer not null
        constraint guitar_string_pk
            primary key autoincrement,
    guitar_id     integer,
    string_number INT,
    start_note    TEXT,
    octave        integer
);

create table guitar_string_adjustment
(
    id                   integer
        constraint string_adjustment_pk
            primary key autoincrement,
    guitar_adjustment_id integer,
    string_number        integer,
    step                 integer
);

create table guitar_type
(
    id   integer
        constraint guitar_type_pk
            primary key autoincrement,
    name TEXT not null
);

create table scale
(
    id        INTEGER not null
        primary key autoincrement
        unique,
    name      TEXT,
    semitones TEXT
);

