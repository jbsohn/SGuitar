package com.steelsidekick.sguitar

class Scale(rootNote: NoteValue, semitones: Array<Int>) {
    private val notes: Array<NoteValue>

    init {
        var notes = emptyArray<NoteValue>()
        var curNoteValue = rootNote
        notes += curNoteValue

        for (semitone in semitones) {
            curNoteValue = nextNoteInScale(curNoteValue, semitone)
            notes += curNoteValue
        }

        this.notes = notes
    }

    fun getNotes(): Array<NoteValue> {
        return notes
    }

    fun description(): String {
        var s = ""
        for (note in notes) {
            s += note.nameSharp()
        }
        return s
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