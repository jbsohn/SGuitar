package com.steelsidekick.sguitar

class HarmonizedScale(rootNote: NoteValue, semitones: List<Int>) {
    private val chords: List<Chord>
    val testDescription: String
        get() {
            var s = ""
            for (chord in chords) {
                s += chord.testDescription
                s += "\n"
            }
            return s
        }

    init {
        // https://www.bluesguitarinstitute.com/how-to-harmonize-a-scale/
        val scaleNotes = Scale(rootNote, semitones).notes
        val notesTable = mutableListOf<List<NoteValue>>()
        val chords = mutableListOf<Chord>()

        notesTable += scaleNotes.drop(0) + scaleNotes.take(0)
        notesTable += scaleNotes.drop(2) + scaleNotes.take(2)
        notesTable += scaleNotes.drop(4) + scaleNotes.take(4)

        for (i in scaleNotes.indices) {
            val notes = mutableListOf<NoteValue>()
            for (curNotes in notesTable) {
                notes += curNotes[i]
            }
            chords += Chord(notes)

        }
        this.chords = chords
    }
}
