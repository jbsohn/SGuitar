
use super::note::Note;
use super::note_names::NOTE_NAMES_SHARP;
use super::note_value::NoteValue;

struct GuitarString {
    start_note: Note,
    notes: Vec<Note>,
    number_of_frets: i32,
}

impl GuitarString {
    pub fn new() -> Self {
        Self {
            start_note: Note::new_note_with_midi_value(0),
            notes: Vec::new(),
            number_of_frets: 0,
        }
    }

    pub fn new_guitar_string_from_note(start_note: Note, number_of_frets: i32) -> Self {
        let notes = GuitarString::string_with_start_note(start_note.clone(), number_of_frets);
        return GuitarString {
            start_note,
            notes,
            number_of_frets,
        };
    }

    pub fn adjust_string_by_step(&mut self, steps: i32) {
       let start_note_midi = self.notes[0].midi_value() + steps;
       let notes = GuitarString::string_with_start_note(Note::new_note_with_midi_value(start_note_midi), self.number_of_frets);
       self.notes = notes;
    }

    pub fn reset(mut self) {
        self.notes = GuitarString::string_with_start_note(self.start_note, self.number_of_frets)
    }

    fn string_with_start_note(start_note: Note, number_of_frets: i32) -> Vec<Note> {
        let mut notes = Vec::<Note>::new();
        let mut cur_midi_value = start_note.midi_value();
        for _ in 0..number_of_frets {
            notes.push(Note::new_note_with_midi_value(cur_midi_value));
            cur_midi_value += 1;
        }
        return notes;
    }

    fn description(self) -> String {
        let mut desc = String::new();
        for note in self.notes {
            let note_value = note.note_value();
            let name = NOTE_NAMES_SHARP[note_value as usize];
            let test = format!("{} ", name);
            desc += &*test;
        }
        desc
    }
}

#[cfg(test)]
mod tests {
    use super::GuitarString;
    use super::Note;
    use super::NoteValue;

    #[test]
    fn test_new_guitar_string_from_note() {
        let start_note = Note::new_note_with_note_value(NoteValue::C, 4);
        let guitar_string = GuitarString::new_guitar_string_from_note(start_note, 13);
        assert_eq!(guitar_string.description(), "C C♯ D D♯ E F F♯ G G♯ A A♯ B C ");
    }

    #[test]
    fn test_adjust_string_by_step() {
        let start_note = Note::new_note_with_note_value(NoteValue::C, 4);
        let mut guitar_string = GuitarString::new_guitar_string_from_note(start_note, 13);
        guitar_string.adjust_string_by_step(2);
        assert_eq!(guitar_string.description(), "D D♯ E F F♯ G G♯ A A♯ B C C♯ D ");
    }
}
