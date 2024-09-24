import com.steelsidekick.sguitar.Guitar
import com.steelsidekick.sguitar.GuitarAdjustment
import com.steelsidekick.sguitar.Note
import com.steelsidekick.sguitar.NoteValue
import com.steelsidekick.sguitar.StringAdjustment
import kotlin.test.Test
import kotlin.test.assertEquals

class GuitarTest {
    @Test
    fun testGuitar() {
        val guitar = Guitar()

        val guitarAdjustment = GuitarAdjustment()
        guitarAdjustment.addStringAdjustment(StringAdjustment(1, 1))
        guitarAdjustment.addStringAdjustment(StringAdjustment(2, 2))
        guitar.setAdjustment("A", guitarAdjustment)

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

        println("Guitar (no activations):")
        println(guitar.testDescription)
        val strings = guitar.fretboard
        assertEquals(strings.count(), 10)
        assertEquals(guitar.fretboard[0].notes.first().midiNote, 66)
        assertEquals(guitar.fretboard[1].notes.first().midiNote, 63)
        assertEquals(guitar.isAdjustmentActivated("A"), false)

        guitar.activate("A", true)
        assertEquals(guitar.fretboard[0].notes.first().midiNote, 67)
        assertEquals(guitar.fretboard[1].notes.first().midiNote, 65)
        assertEquals(guitar.isAdjustmentActivated("A"), true)
        println("A pedal activated")
        println(guitar.testDescription)

        guitar.resetStrings()
        assertEquals(guitar.fretboard[0].notes.first().midiNote, 66)
        assertEquals(guitar.fretboard[1].notes.first().midiNote, 63)
        println("Guitar reset (no activations)")
        println(guitar.testDescription)

        guitar.resetStrings()
        assertEquals(guitar.fretboard.count(), 10)
    }
}