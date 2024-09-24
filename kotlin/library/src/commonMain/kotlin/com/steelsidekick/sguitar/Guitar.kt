package com.steelsidekick.sguitar

class Guitar {
    private var numberOfFrets = 0
    private var strings = mutableListOf<GuitarString>()
    private var adjustments = mutableMapOf<String, GuitarAdjustment>()
    val fretboard: List<GuitarString>
        get() {
            return strings.dropWhile { guitarString -> guitarString == strings.first() }
        }
    val testDescription: String
        get() {
            var s = ""
            fretboard.forEachIndexed { index, string ->
                s += "string ${index + 1}: ${string.testDescription}\n"
            }
            return s
        }

    init {
        numberOfFrets = 0
    }

    fun resetGuitar(notes: List<Note>, numberOfFrets: Int) {
        strings.clear()
        strings += GuitarString()
        for (note in notes) {
            strings += GuitarString(note, numberOfFrets)
        }

        for ((_, value) in adjustments) {
            value.setActivated(false)
        }
    }

    fun resetStrings() {
        for (string in strings) {
            string.reset()
        }
    }

    fun isAdjustmentActivated(adjustmentID: String): Boolean {
        return adjustments[adjustmentID]?.isActivated() ?: false
    }

    fun activate(adjustmentID: String, activated: Boolean) {
        adjustments[adjustmentID]?.let { guitarAdjustment ->
            for (stringAdjustment in guitarAdjustment.adjustments) {
                val step = if (activated) {
                    stringAdjustment.step
                } else {
                    (-stringAdjustment.step)
                }
                strings[stringAdjustment.stringNumber].adjustStringBySteps(step)
            }
            guitarAdjustment.setActivated(activated)
        }
    }

    fun setAdjustment(adjustmentID: String, adjustment: GuitarAdjustment) {
        adjustments[adjustmentID] = adjustment
    }
}