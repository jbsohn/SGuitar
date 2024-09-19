import com.steelsidekick.sguitar.NoteValue
import com.steelsidekick.sguitar.Scale
import kotlin.test.Test
import kotlin.test.assertEquals

class ScaleTest {
    @Test
    fun testCScale() {
        val scale = Scale(NoteValue.C, arrayOf(2, 2, 1, 2, 2, 2))
        assertEquals(scale.description(), "CDEFGAB")
        assertEquals(scale.getNotes().count(), 7)
    }
}