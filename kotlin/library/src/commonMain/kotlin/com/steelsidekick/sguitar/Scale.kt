package com.steelsidekick.sguitar

class Scale(rootNote: NoteValue, semitones: List<Int>) {
    private val notes: List<NoteValue>

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

    fun getNotes(): List<NoteValue> {
        return notes
    }

    fun testDescription(): String {
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