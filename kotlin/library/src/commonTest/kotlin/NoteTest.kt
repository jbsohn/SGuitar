import com.steelsidekick.sguitar.Note
import com.steelsidekick.sguitar.NoteValue
import kotlin.test.Test
import kotlin.test.assertEquals

class NoteTest {
    @Test
    fun testNoteValue() {
        val noteValue = NoteValue.C
        assertEquals(noteValue.nameSharp(), "C")
        assertEquals(noteValue.nameFlat(), "C")
    }

    @Test
    fun testNote() {
        val note = Note(48)
        assertEquals(note.getMidiNote(), 48)
        assertEquals(note.getNote(), NoteValue.C)
        assertEquals(note.getOctave(), 3)
        assertEquals(note.description(), "C-3")
    }

    @Test
    fun testNoteWithOctave() {
        val note = Note(NoteValue.C, 3)
        assertEquals(note.getMidiNote(), 48)
        assertEquals(note.getNote(), NoteValue.C)
        assertEquals(note.getOctave(), 3)
        assertEquals(note.description(), "C-3")
    }
}