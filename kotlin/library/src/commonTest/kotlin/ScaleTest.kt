import com.steelsidekick.sguitar.NoteValue
import com.steelsidekick.sguitar.Scale
import kotlin.test.Test
import kotlin.test.assertEquals

class ScaleTest {
    @Test
    fun testCScale() {
        val scale = Scale(NoteValue.C, arrayListOf(2, 2, 1, 2, 2, 2))
        assertEquals(scale.testDescription, "C,D,E,F,G,A,B")
        assertEquals(scale.notes.count(), 7)
    }
}