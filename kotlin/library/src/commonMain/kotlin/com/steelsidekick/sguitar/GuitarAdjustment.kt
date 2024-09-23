package com.steelsidekick.sguitar

class GuitarAdjustment(private val adjustmentID: String) {
    private var adjustments = mutableListOf<StringAdjustment>()

    fun getAdjustmentID(): String {
        return adjustmentID
    }

    fun clearAdjustments() {
        adjustments.clear()
    }

    fun addStringAdjustment(adjustment: StringAdjustment) {
        adjustments.add(adjustment)
    }

    fun getStringAdjustments(): List<StringAdjustment> {
        return adjustments
    }

    fun testDescription(): String {
        var s = ""
        s += "adjustmentID: "
        s += adjustmentID
        s += "\n"

        for (adjustment in adjustments) {
            s += adjustment.testDescription()
            s += "\n"
        }
        return s
    }
}