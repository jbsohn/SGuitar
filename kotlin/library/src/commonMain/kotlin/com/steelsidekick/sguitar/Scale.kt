package com.steelsidekick.sguitar

class Scale(rootNote: NoteValue, semitones: List<Int>) {
    val notes: List<NoteValue>
    val testDescription: String
        get() {
            var s = ""
            for (i in 0..<notes.count() - 1) {
                s += "${notes[i].nameSharp()},"
            }
            s += notes.last().nameSharp()
            return s
        }

    init {
        val notes = mutableListOf<NoteValue>()
        var curNoteValue = rootNote
        notes += curNoteValue

        for (semitone in semitones) {
            curNoteValue = nextNoteInScale(curNoteValue, semitone)
            notes += curNoteValue
        }
        this.notes = notes
    }

    private fun nextNoteInScale(note: NoteValue, semitone: Int): NoteValue {
        var curNoteValue: Int = note.value
        curNoteValue += semitone

        if (curNoteValue > NoteValue.B.value) {
            curNoteValue -= (NoteValue.B.value + 1)
        }
        return NoteValue.getByValue(curNoteValue) ?: NoteValue.C
    }
}