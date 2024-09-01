
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[allow(dead_code)]
pub enum NoteValue {
    C = 0,
    CSharp = 1,
    D = 2,
    DSharp = 3,
    E = 4,
    F = 5,
    FSharp = 6,
    G = 7,
    GSharp = 8,
    A = 9,
    ASharp = 10,
    B = 11,
}

impl NoteValue {
    #[allow(dead_code)]
    pub const DFLAT: NoteValue = NoteValue::CSharp;
    #[allow(dead_code)]
    pub const EFLAT: NoteValue = NoteValue::DSharp;
    #[allow(dead_code)]
    pub const GFLAT: NoteValue = NoteValue::FSharp;
    #[allow(dead_code)]
    pub const AFLAT: NoteValue = NoteValue::GSharp;
    #[allow(dead_code)]
    pub const BFLAT: NoteValue = NoteValue::ASharp;

    pub fn from(note_value: i32) -> Self {
        match note_value {
            0 => Self::C,
            1 => Self::CSharp,
            2 => Self::D,
            3 => Self::DSharp,
            4 => Self::E,
            5 => Self::F,
            6 => Self::FSharp,
            7 => Self::G,
            8 => Self::GSharp,
            9 => Self::A,
            10 => Self::ASharp,
            11 => Self::B,
            _ => {
                panic!("Unknown value: {}", note_value)
            }
        }
    }
}
