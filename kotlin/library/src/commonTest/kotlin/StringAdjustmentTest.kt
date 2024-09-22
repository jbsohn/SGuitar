import com.steelsidekick.sguitar.StringAdjustment
import kotlin.test.Test
import kotlin.test.assertEquals

class StringAdjustmentTest {
    @Test
    fun testStringAdjustment() {
        val stringAdjustment = StringAdjustment(1, 1)
        assertEquals(stringAdjustment.getStringNumber(), 1)
        assertEquals(stringAdjustment.getStep(), 1)
        assertEquals(stringAdjustment.testDescription(), "string_number: 1, step: 1")
    }
}