package com.steelsidekick.sguitar

class Note {
    val midiNote: Int
    val note: NoteValue
        get() {
            return NoteValue.getByValue((midiNote - 12) % 12) ?: NoteValue.NONE
        }
    val octave: Int
        get() {
            return midiNote / 12 - 1
        }
    val testDescription: String
        get() {
            return "${note.nameSharp()}-${octave}"
        }

    constructor(midiNote: Int = -1) {
        this.midiNote = midiNote
    }

    constructor(note: NoteValue, octave: Int) {
        this.midiNote = (octave + 1) * 12 + note.value
    }
}
