package com.steelsidekick.sguitar

class GuitarString {
    val startNote: Note
    private val numberOfFrets: Int
    var notes: List<Note>
        private set
    val testDescription: String
        get() {
            var s = ""
            for (i in 0..<notes.count() - 1) {
                s += "${notes[i].testDescription},"
            }
            s += notes.last().testDescription
            return s
        }

    constructor() {
        startNote = Note()
        numberOfFrets = 0
        notes = emptyList()
    }

    constructor(startNote: Note, numberOfFrets: Int) {
        this.startNote = startNote
        this.numberOfFrets = numberOfFrets
        this.notes = stringWithStartNote(startNote.midiNote, numberOfFrets)
    }

    fun adjustStringBySteps(steps: Int) {
        val startNoteMidiValue = notes[0].midiNote + steps
        notes = stringWithStartNote(startNoteMidiValue, numberOfFrets)
    }

    fun reset() {
        notes = stringWithStartNote(startNote.midiNote, numberOfFrets)
    }

    private fun stringWithStartNote(midiStartNote: Int, numberOfFrets: Int): List<Note> {
        val notes = mutableListOf<Note>()
        var curMidiValue: Int = midiStartNote

        for (i in 0..<numberOfFrets) {
            notes += Note(curMidiValue)
            curMidiValue++
        }
        return notes
    }
}