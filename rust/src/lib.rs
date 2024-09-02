#![allow(dead_code)]
#![allow(unused_variables)]

mod note;
mod note_value;
mod note_names;
mod scale;
mod chord;
mod guitar_string;
mod string_adjustment;
mod guitar_adjustment;
mod guitar;

use note_value::NoteValue;
use chord::Chord;

#[cfg(test)]
mod tests {
}

uniffi::include_scaffolding!("sguitar");