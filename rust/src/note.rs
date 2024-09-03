use crate::note_value::NoteValue;
use crate::note_names::NOTE_NAMES_SHARP;

#[derive(Clone)]
pub struct Note {
    midi_note: i32,
}

impl Note {
    pub fn new(note: NoteValue, octave: i32) -> Self {
        Self {
            midi_note: (octave + 1) * 12 + note as i32,
        }
    }

    pub fn new_note_with_midi_note(midi_note: i32) -> Self {
        Self { midi_note }
    }

    pub fn get_midi_note(&self) -> i32 {
        self.midi_note
    }

    pub fn get_note(&self) -> NoteValue {
        NoteValue::from((self.midi_note - 12) % 12)
    }

    pub fn get_octave(&self) -> i32 {
        self.midi_note / 12 - 1
    }

    pub fn description(self) -> String {
        format!("{}-{}", NOTE_NAMES_SHARP[self.get_note() as usize], self.get_octave()).clone()
    }
}

#[cfg(test)]
mod tests {
    use crate::note::Note;
    use crate::note_value::NoteValue;

    #[test]
    fn test_new_note_value() {
        let note = Note::new(NoteValue::C, 4);
        assert_eq!(note.get_note(), NoteValue::C);
        assert_eq!(note.get_midi_note(), 60);
        assert_eq!(note.get_octave(), 4);
        assert_eq!(note.description(), "C-4")
    }

    #[test]
    fn test_new_midi_value() {
        let note = Note::new_note_with_midi_note(60);
        assert_eq!(note.get_note(), NoteValue::C);
        assert_eq!(note.get_midi_note(), 60);
        assert_eq!(note.get_octave(), 4);
        assert_eq!(note.description(), "C-4")
    }
}
