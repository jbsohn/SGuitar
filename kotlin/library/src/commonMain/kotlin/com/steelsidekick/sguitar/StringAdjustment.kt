package com.steelsidekick.sguitar

class StringAdjustment(private val stringNumber: Int, private val step: Int) {

    fun getStringNumber(): Int {
        return stringNumber
    }

    fun getStep(): Int {
        return step
    }

    fun testDescription(): String {
        var s = ""
        s += "string_number: "
        s += stringNumber
        s += ", step: "
        s += step
        return s
    }
}