import com.steelsidekick.sguitar.HarmonizedScale
import com.steelsidekick.sguitar.NoteValue
import kotlin.test.Test

class HaromizedScaleTest {
    @Test
    fun testCScale() {
        val harmonizedScale = HarmonizedScale(NoteValue.C, arrayListOf(2, 2, 1, 2, 2, 2))
        print("harmonizedScale: \n${harmonizedScale.testDescription}")
    }
}