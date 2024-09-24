import com.steelsidekick.sguitar.GuitarAdjustment
import com.steelsidekick.sguitar.StringAdjustment
import kotlin.test.assertEquals
import kotlin.test.Test

class GuitarAdjustmentTest {
    @Test
    fun testGuitarAdjustment() {
        val guitarAdjustment = GuitarAdjustment()

        guitarAdjustment.addStringAdjustment(StringAdjustment(1, 1))
        assertEquals(guitarAdjustment.getStringAdjustments().count(), 1)
        assertEquals(guitarAdjustment.testDescription(), "adjustmentID: TEST\nstring_number: 1, step: 1\n")

        guitarAdjustment.clearAdjustments()
        assertEquals(guitarAdjustment.getStringAdjustments().count(), 0)
    }
}