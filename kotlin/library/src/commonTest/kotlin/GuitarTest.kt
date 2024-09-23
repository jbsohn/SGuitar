import com.steelsidekick.sguitar.Guitar
import com.steelsidekick.sguitar.Note
import com.steelsidekick.sguitar.NoteValue
import kotlin.test.Test
import kotlin.test.assertEquals

class GuitarTest {
    @Test
    fun testGuitar() {
        val guitar = Guitar()
        val notes = listOf(
            Note(NoteValue.F_SHARP, 4),
            Note(NoteValue.D_SHARP, 4),
            Note(NoteValue.G_SHARP, 4),
            Note(NoteValue.E, 4),
            Note(NoteValue.B, 3),
            Note(NoteValue.G_SHARP, 4),
            Note(NoteValue.F_SHARP, 3),
            Note(NoteValue.E, 3),
            Note(NoteValue.D, 3),
            Note(NoteValue.B, 2))
        guitar.resetGuitar(notes, 23)

        val strings = guitar.getStrings()
        assertEquals(strings.count(), 10)

        println("guitar:")
        println(guitar.testDescription())

        guitar.resetStrings()
        assertEquals(guitar.getStrings().count(), 10)
    }
}