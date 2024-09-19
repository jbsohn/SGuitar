package com.steelsidekick.sguitar

enum class NoteValue(val value: Int) {
    C(0),
    C_SHARP (1),
    D_FLAT(1),
    D(2),
    D_SHARP(3),
    E_FLAT(3),
    E(4),
    F(5),
    F_SHARP(6),
    G_FLAT(6),
    G(7),
    G_SHARP(8),
    A_FLAT(8),
    A(9),
    A_SHARP(10),
    B_FLAT(10),
    B(11);

    private val noteNameSharp = arrayOf(
        "C", "C\u266f", "D", "D\u266f", "E", "F", "F\u266f", "G",
        "G\u266f", "A", "A\u266f", "B")
    private val noteNamesFlat = arrayOf(
        "C", "D\u266d", "D", "E\u266d", "E", "F", "G\u266d",
        "G", "A\u266d", "A", "B\u266d", "B")

    fun nameSharp(): String {
        return noteNameSharp[value]
    }

    fun nameFlat(): String {
        return noteNamesFlat[value]
    }

    companion object {
        fun getByValue(value: Int) = entries.firstOrNull { it.value == value }
    }
}
