package com.steelsidekick.sguitar

class Guitar {
    private var numberOfFrets = 0
    private var strings = mutableListOf<GuitarString>()
    private var adjustments = mutableListOf<GuitarAdjustment>()
    private var settings = mutableMapOf<String, Boolean>()

    init {
        numberOfFrets = 0
    }

    fun resetGuitar(notes: List<Note>, numberOfFrets: Int) {
        strings.clear()
        strings += GuitarString()
        for (note in notes) {
            strings += GuitarString(note, numberOfFrets)
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