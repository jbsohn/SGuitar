package com.steelsidekick.sguitar

class Chord(rootNote: NoteValue, intervals: List<Int>) {
    private val notes: List<NoteValue>

    init {
        val notes = mutableListOf<NoteValue>()
        for (interval in intervals) {
            val note = noteForNoteInterval(interval, rootNote)
            notes += note
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

    private fun noteForNoteInterval(interval: Int, rootNote: NoteValue): NoteValue {
        var value: Int = rootNote.value + interval
        if (value > NoteValue.B.value) {
            value -= (NoteValue.B.value - 1)
        }
        return NoteValue.getByValue(value) ?: NoteValue.NONE
    }
}
