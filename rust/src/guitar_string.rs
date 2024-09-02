
use crate::note::Note;
use crate::note_names::NOTE_NAMES_SHARP;

struct GuitarString {
    start_note: Note,
    notes: Vec<Note>,
    number_of_frets: i32,
}

impl GuitarString {
    pub fn new(start_note: Note, number_of_frets: i32) -> Self {
        let notes = GuitarString::string_with_start_note(start_note.midi_value(), number_of_frets);
        GuitarString {
            start_note,
            notes,
            number_of_frets,
        }
    }

    pub fn adjust_string_by_step(&mut self, steps: i32) {
       let start_note_midi = self.notes[0].midi_value() + steps;
       let notes = GuitarString::string_with_start_note(start_note_midi, self.number_of_frets);
       self.notes = notes;
    }

    pub fn reset(&mut self) {
        self.notes = GuitarString::string_with_start_note(self.start_note.midi_value(), self.number_of_frets)
    }

    fn string_with_start_note(midi_start_node: i32, number_of_frets: i32) -> Vec<Note> {
        let mut notes = Vec::<Note>::new();
        let mut cur_midi_value = midi_start_node; 
        for _ in 0..number_of_frets {
            notes.push(Note::new_note_with_midi_value(cur_midi_value));
            cur_midi_value += 1;
        }
        notes
    }

    fn description(self) -> String {
        let mut desc = String::new();
        for note in self.notes {
            desc = format!("{}{}", desc, NOTE_NAMES_SHARP[note.note_value() as usize]);
        }
        desc
    }
}

#[cfg(test)]
mod tests {
    use crate::guitar_string::GuitarString;
    use crate::note::Note;
    use crate::note_value::NoteValue;

    #[test]
    fn test_new_guitar_string() {
        let start_note = Note::new(NoteValue::C, 4);
        let guitar_string = GuitarString::new(start_note, 13);
        assert_eq!(guitar_string.description(), "CC♯DD♯EFF♯GG♯AA♯BC");
    }

    #[test]
    fn test_adjust_string_by_step() {
        let start_note = Note::new(NoteValue::C, 4);
        let mut guitar_string = GuitarString::new(start_note, 13);
        guitar_string.adjust_string_by_step(2);
        assert_eq!(guitar_string.description(), "DD♯EFF♯GG♯AA♯BCC♯D");
    }

    #[test]
    fn test_reset() {
        let start_note = Note::new(NoteValue::C, 4);
        let mut guitar_string = GuitarString::new(start_note, 13);
        guitar_string.adjust_string_by_step(2);
        guitar_string.reset();
        assert_eq!(guitar_string.description(), "CC♯DD♯EFF♯GG♯AA♯BC");
    }
}
