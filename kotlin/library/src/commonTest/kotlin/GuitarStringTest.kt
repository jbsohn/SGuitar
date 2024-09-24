import com.steelsidekick.sguitar.GuitarString
import com.steelsidekick.sguitar.Note
import kotlin.test.Test
import kotlin.test.assertEquals

class GuitarStringTest {
    @Test
    fun testGuitarString() {
        val guitarString = GuitarString(Note(48), 12)
        assertEquals(guitarString.getNotes().count(), 12)
        assertEquals(guitarString.testDescription(), "C-3C♯-3D-3D♯-3E-3F-3F♯-3G-3G♯-3A-3A♯-3B-3")
        assertEquals(guitarString.getStartNote().getMidiNote(), 48)
    }

    @Test
    fun testEmptyGuitarString() {
        val guitarString = GuitarString()
        assertEquals(guitarString.getNotes().count(), 0)
    }

    @Test
    fun testAdjustedGuitarString() {
        val guitarString = GuitarString(Note(48), 12)
        assertEquals(guitarString.getNotes()[0].getMidiNote(), 48)

        guitarString.adjustStringBySteps(1)
        assertEquals(guitarString.getNotes()[0].getMidiNote(), 49)

        guitarString.reset()
        assertEquals(guitarString.getNotes()[0].getMidiNote(), 48)
    }
}