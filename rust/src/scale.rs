use super::note_value::NoteValue;
use super::note::NOTE_NAMES_SHARP;

#[derive(Debug, Clone)]
pub struct Scale {
    notes: Vec<NoteValue>,
}

impl Scale {
    fn new_from_note_value(root_note_value: NoteValue, semitones: Vec<i32>) -> Self {
        let mut notes = Vec::new();
        let mut cur_note_value = root_note_value;
        notes.push(cur_note_value);

        for semitone in semitones {
            cur_note_value = Scale::note_value_for_interval(cur_note_value, semitone);
            notes.push(cur_note_value)
        }

        Scale {
            notes
        }
    }
 
    pub fn note_values(self) -> Vec<NoteValue> {
        self.notes
    }

    fn note_value_for_interval(note_value: NoteValue, semitone: i32) -> NoteValue {
        let mut note_value = (note_value as i32) + semitone;
        if note_value > NoteValue::B as i32 {
            note_value = (NoteValue::B as i32) - 1;
        }
        NoteValue::from_i32(note_value)
    }

    fn description(self) -> String {
        let mut desc = String::new();
        //format!("{}-{}", crate::note::NOTE_NAMES_SHARP[self.note_value() as usize], self.octave()).to_owned()

        for note in self.notes {
            let test = format!("{} ", NOTE_NAMES_SHARP[note as usize]);
            desc += &*test;
        }
        desc
    }
}

#[cfg(test)]
mod tests {
    use super::Scale;
    use super::NoteValue;

    #[test]
    fn test_new_from_note_value() {
        // 2, 2, 1, 2, 2, 2
        let semitones: Vec<i32> = vec![2, 2, 1, 2, 2, 2];
        let scale = Scale::new_from_note_value(NoteValue::C, semitones);
        assert_eq!(scale.description(), "C D E F G A B ");
    }

    #[test]
    fn test_new_from_note_value_count() {
        // 2, 2, 1, 2, 2, 2
        let semitones: Vec<i32> = vec![2, 2, 1, 2, 2, 2];
        let scale = Scale::new_from_note_value(NoteValue::C, semitones);
        assert_eq!(scale.note_values().iter().count(), 7);
    }
}
