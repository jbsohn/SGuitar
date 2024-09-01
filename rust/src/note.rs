use super::note_value::NoteValue;

#[allow(dead_code)]
pub(crate) const NOTE_NAMES_SHARP: &'static [&'static str] = &[
    "C", "C♯", "D", "D♯", "E", "F", "F♯", "G", "G♯", "A", "A♯", "B",
];

#[allow(dead_code)]
const NOTE_NAMES_FLAT: &'static [&'static str] = &[
    "C", "D♭", "D", "E♭", "E", "F", "G♭", "G", "A♭", "A", "B♭", "B",
];

#[derive(Clone)]
pub struct Note {
    midi_value: i32,
}

impl Note {
    pub fn new_note_with_note_value(note_value: NoteValue, octave: i32) -> Self {
        Self {
            midi_value: ((octave + 1) * 12) + note_value as i32,
        }
    }

    pub fn new_note_with_midi_value(midi_value: i32) -> Self {
        Self { midi_value }
    }

    pub fn midi_value(&self) -> i32 {
        self.midi_value
    }

    pub fn note_value(&self) -> NoteValue {
        NoteValue::from_i32((self.midi_value - 12) % 12)
    }

    pub fn octave(&self) -> i32 {
        (self.midi_value / 12) - 1
    }

    pub fn description(self) -> String {
        format!("{}-{}", NOTE_NAMES_SHARP[self.note_value() as usize], self.octave()).to_owned()
    }
}

#[cfg(test)]
mod tests {
    use super::Note;
    use super::NoteValue;

    #[test]
    fn test_new_note_value() {
        let note = Note::new_note_with_note_value(NoteValue::C, 4);
        assert_eq!(note.note_value(), NoteValue::C);
        assert_eq!(note.midi_value(), 60);
        assert_eq!(note.octave(), 4);
        assert_eq!(note.description(), "C-4")
    }

    #[test]
    fn test_new_midi_value() {
        let note = Note::new_note_with_midi_value(60);
        assert_eq!(note.note_value(), NoteValue::C);
        assert_eq!(note.midi_value(), 60);
        assert_eq!(note.octave(), 4);
        assert_eq!(note.description(), "C-4")
    }
}
