use crate::note_names::NOTE_NAMES_SHARP;
use crate::note_value::NoteValue;

pub struct Scale {
    notes: Vec<NoteValue>,
}

impl Scale {
    fn new(root_note: NoteValue, semitones: Vec<i32>) -> Self {
        let mut notes = Vec::new();
        let mut cur_note_value = root_note;
        notes.push(cur_note_value);

        for semitone in semitones {
            cur_note_value = Scale::note_value_for_interval(cur_note_value, semitone);
            notes.push(cur_note_value)
        }

        Scale {
            notes
        }
    }

    pub fn get_notes(&self) -> Vec<NoteValue> {
        self.notes.clone()
    }

    fn description(self) -> String {
        let mut desc = String::new();
        for note in self.notes {
            desc = format!("{}{}", desc, NOTE_NAMES_SHARP[note as usize]);
        }
        desc
    }

    fn note_value_for_interval(note_value: NoteValue, semitone: i32) -> NoteValue {
        let mut note_value = (note_value as i32) + semitone;
        if note_value > NoteValue::B as i32 {
            note_value = (NoteValue::B as i32) - 1;
        }
        NoteValue::from(note_value)
    }
}

#[cfg(test)]
mod tests {
    use crate::note_value::NoteValue;
    use crate::scale::Scale;

    #[test]
    fn test_new_from_note_value() {
        let semitones: Vec<i32> = vec![2, 2, 1, 2, 2, 2];
        let scale = Scale::new(NoteValue::C, semitones);
        assert_eq!(scale.description(), "CDEFGAB");
    }

    #[test]
    fn test_new_from_note_value_count() {
        let semitones: Vec<i32> = vec![2, 2, 1, 2, 2, 2];
        let scale = Scale::new(NoteValue::C, semitones);
        assert_eq!(scale.get_notes().len(), 7);
    }
}
