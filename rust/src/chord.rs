use crate::note_value::NoteValue;
use crate::note_names::NOTE_NAMES_SHARP;

struct Chord {
    notes: Vec<NoteValue>,
}

impl Chord {
    pub fn new(root_note_value: NoteValue, intervals: Vec<i32>) -> Self {
        let mut notes = Vec::<NoteValue>::new();
        for interval in intervals {
            let note_value = Chord::note_value_for_interval(root_note_value, interval);
            notes.push(note_value);
        }

        Chord {
            notes
        }
    }

    pub fn description(self) -> String {
        let mut desc = String::new();
        for note in self.notes {
            desc = format!("{}{}", desc, NOTE_NAMES_SHARP[note as usize]);
        }
        desc
    }

    fn note_value_for_interval(root_note_value: NoteValue, interval: i32) -> NoteValue {
        let mut note_value = root_note_value as i32 + interval;
        if note_value > NoteValue::B as i32 {
            note_value = note_value - NoteValue::B as i32 - 1;
        }
        NoteValue::from(note_value)
    }
}

#[cfg(test)]
mod tests {
    use crate::chord::Chord;
    use crate::note_value::NoteValue;

    #[test]
    fn test_new_chord_from_root_note() {
        let intervals: Vec<i32> = vec![0, 4, 7];
        let scale = Chord::new(NoteValue::C, intervals);
        assert_eq!(scale.description(), "CEG");
    }
}
