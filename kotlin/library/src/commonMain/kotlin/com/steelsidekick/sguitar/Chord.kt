package com.steelsidekick.sguitar

class Chord {
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

    constructor(notes: List<NoteValue>) {
        this.notes = notes
    }

    constructor(rootNote: NoteValue, intervals: List<Int>) {
        val notes = mutableListOf<NoteValue>()
        for (interval in intervals) {
            val note = noteForNoteInterval(interval, rootNote)
            notes += note
        }
        this.notes = notes
    }

    private fun noteForNoteInterval(interval: Int, rootNote: NoteValue): NoteValue {
        var value: Int = rootNote.value + interval
        if (value > NoteValue.B.value) {
            value -= (NoteValue.B.value - 1)
        }
        return NoteValue.getByValue(value) ?: NoteValue.NONE
    }
}
