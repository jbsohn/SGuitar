import com.steelsidekick.sguitar.GuitarString
import com.steelsidekick.sguitar.Note
import kotlin.test.Test
import kotlin.test.assertEquals

class GuitarStringTest {
    @Test
    fun testGuitarString() {
        val guitarString = GuitarString(Note(48), 12)
        assertEquals(guitarString.notes.count(), 12)
        assertEquals(guitarString.testDescription, "C-3,C♯-3,D-3,D♯-3,E-3,F-3,F♯-3,G-3,G♯-3,A-3,A♯-3,B-3")
        assertEquals(guitarString.startNote.midiNote, 48)
    }

    @Test
    fun testEmptyGuitarString() {
        val guitarString = GuitarString()
        assertEquals(guitarString.notes.count(), 0)
    }

    @Test
    fun testAdjustedGuitarString() {
        val guitarString = GuitarString(Note(48), 12)
        assertEquals(guitarString.notes[0].midiNote, 48)

        guitarString.adjustStringBySteps(1)
        assertEquals(guitarString.notes[0].midiNote, 49)

        guitarString.reset()
        assertEquals(guitarString.notes[0].midiNote, 48)
    }
}