package com.steelsidekick.sguitar

class GuitarAdjustment {
    var adjustments = mutableListOf<StringAdjustment>()
        private set
    private var activated = false
    val testDescription: String
        get() {
            var s = ""
            for (adjustment in adjustments) {
                s += "${adjustment.testDescription}\n"
            }
            return s
        }

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
}