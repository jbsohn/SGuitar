
class Note(midiNote: Int = -1) {
    var midiNote: Int = -1

    init {
        this.midiNote = midiNote
    }

    constructor(note: NoteValue, octave: Int) : this() {
        midiNote = (octave + 1) * 12 + note.value
    }

    fun getMidiNote(): Int {
        return midiNote
    }

    fun getNote(): NoteValue? {
        return NoteValue.getByValue((midiNote - 12) % 12)
    }

    fun getOctave(): Int {
        return midiNote / 12 - 1
    }

    fun description(): String {
        return "TODO"
    }
}
