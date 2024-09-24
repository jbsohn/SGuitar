package com.steelsidekick.sguitar

class StringAdjustment(val stringNumber: Int, val step: Int) {
    val testDescription: String
        get() {
            return "string_number: $stringNumber, step: $step"
        }
}