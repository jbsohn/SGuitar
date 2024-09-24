package com.steelsidekick.sguitar

class Guitar {
    private var numberOfFrets = 0
    private var strings = mutableListOf<GuitarString>()
    private var adjustments = mutableMapOf<String, GuitarAdjustment>()

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

    fun getStrings(): List<GuitarString> {
        return strings.dropWhile { guitarString ->  guitarString == strings.first() }
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
            for (stringAdjustment in guitarAdjustment.getStringAdjustments()) {
                val step = if (activated) {
                    stringAdjustment.getStep()
                } else {
                    (-stringAdjustment.getStep())
                }
                strings[stringAdjustment.getStringNumber()].adjustStringBySteps(step)
            }
            guitarAdjustment.setActivated(activated)
        }
    }

    fun setAdjustment(adjustmentID: String, adjustment: GuitarAdjustment) {
        adjustments[adjustmentID] = adjustment
    }

    fun testDescription(): String {
        var s = ""
        getStrings().forEachIndexed { index, string ->
            s += "string "
            s += index + 1
            s += ": "
            s += string.testDescription()
            s += "\n"
        }
        return s
    }
}