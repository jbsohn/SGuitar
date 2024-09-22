import com.steelsidekick.sguitar.Chord
import com.steelsidekick.sguitar.NoteValue
import kotlin.test.Test
import kotlin.test.assertEquals

class ChordTest {
    @Test
    fun testCChord() {
        val chord = Chord(NoteValue.C, arrayListOf(0, 4, 7))
        assertEquals(chord.testDescription(), "CEG")
        assertEquals(chord.getNotes().count(), 3)
    }
}