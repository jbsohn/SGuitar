package com.steelsidekick.sguitar

class Note {
    private val midiNote: Int

    constructor(midiNote: Int = -1) {
        this.midiNote = midiNote
    }

    constructor(note: NoteValue, octave: Int) {
        this.midiNote = (octave + 1) * 12 + note.value
    }

    fun getMidiNote(): Int {
        return midiNote
    }

    fun getNote(): NoteValue {
        return NoteValue.getByValue((midiNote - 12) % 12) ?: NoteValue.NONE
    }

    fun getOctave(): Int {
        return midiNote / 12 - 1
    }

    fun testDescription(): String {
        return "${getNote().nameSharp()}-${getOctave()}"
    }
}
