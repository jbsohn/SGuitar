package com.steelsidekick.sguitar

class GuitarString {
    private val startNote: Note
    private val numberOfFrets: Int
    private var notes: List<Note>

    constructor() {
        startNote = Note()
        numberOfFrets = 0
        notes = emptyList()
    }

    constructor(startNote: Note, numberOfFrets: Int) {
        this.startNote = startNote
        this.numberOfFrets = numberOfFrets
        this.notes = stringWithStartNote(startNote.getMidiNote(), numberOfFrets)
    }

    fun getStartNote(): Note {
        return startNote
    }

    fun getNotes(): List<Note> {
        return notes
    }

    fun adjustStringBySteps(steps: Int) {
        val startNoteMidiValue = notes[0].getMidiNote() + steps
        notes = stringWithStartNote(startNoteMidiValue, numberOfFrets)
    }

    fun reset() {
        notes = stringWithStartNote(startNote.getMidiNote(), numberOfFrets)
    }

    fun testDescription(): String {
        var s = ""
        for (note in notes) {
            s += note.testDescription()
        }
        return s
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