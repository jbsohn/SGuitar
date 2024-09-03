use std::collections::HashMap;
use std::vec;
use crate::guitar_adjustment::GuitarAdjustment;
use crate::guitar_string::GuitarString;
use crate::note::Note;

pub struct Guitar {
    number_of_frets: i32,
    strings: Vec<GuitarString>,
    adjustments: Vec<GuitarAdjustment>,
    activations: HashMap<String, bool>,
}

impl Guitar {
    pub fn new() -> Self {
        Guitar {
            number_of_frets: 0,
            strings: vec![],
            adjustments: vec![],
            activations: HashMap::new()
        }
    }

    pub fn reset_guitar(&mut self, notes: Vec<Note>, number_of_frets: i32) {
        self.strings.clear();
        self.strings.push(GuitarString::new(Note::new_note_with_midi_note(0), 0));

        for note in notes {
            self.strings.push(GuitarString::new(note, number_of_frets));
        }
    }

    pub fn get_strings(&self) -> Vec<GuitarString> {
        let mut strings_skip0: Vec<GuitarString> = vec![];
        for string in self.strings.clone().iter().skip(1) {
            strings_skip0.push(string.clone())
        }
        strings_skip0
    }

    pub fn reset_strings(&mut self) {
        for string in self.strings.iter_mut() {
            string.reset();
        }
    }

    pub fn description(&self) -> String {
        let mut description = String::new();
        for string in  self.strings.clone() {
            description = format!("{}{}\n", description, string.description())
        }
        description
    }
}

#[cfg(test)]
mod tests {
    use crate::guitar::Guitar;
    use crate::note::Note;
    use crate::note_value::NoteValue;

    #[test]
    fn test_new_guitar() {
        let mut guitar = Guitar::new();
        let string_notes: Vec<Note> = vec![
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4),
            Note::new(NoteValue::C, 4)];
        guitar.reset_guitar(string_notes, 13);
        let description = guitar.description();
        print!("{}", description);

        for string in guitar.get_strings() {
            assert_eq!(string.description(), "CC♯DD♯EFF♯GG♯AA♯BC");
        }

        guitar.reset_strings();
        for string in guitar.get_strings() {
            assert_eq!(string.description(), "CC♯DD♯EFF♯GG♯AA♯BC");
        }
    }
}
