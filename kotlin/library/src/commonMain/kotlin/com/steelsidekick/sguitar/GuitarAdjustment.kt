package com.steelsidekick.sguitar

class GuitarAdjustment {
    private var adjustments = mutableListOf<StringAdjustment>()
    private var activated = false

    fun clearAdjustments() {
        adjustments.clear()
    }

    fun setActivated(activated: Boolean) {
        this.activated = activated
    }

    fun isActivated(): Boolean {
        return activated
    }

    fun addStringAdjustment(adjustment: StringAdjustment) {
        adjustments.add(adjustment)
    }

    fun getStringAdjustments(): List<StringAdjustment> {
        return adjustments
    }

    fun testDescription(): String {
        var s = ""
        for (adjustment in adjustments) {
            s += adjustment.testDescription()
            s += "\n"
        }
        return s
    }
}