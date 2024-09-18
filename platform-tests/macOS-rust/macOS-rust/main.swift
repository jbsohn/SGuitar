//
//  main.swift
//  macOS-rust
//
//  Created by John on 9/5/24.
//

import Foundation
import SGuitarFFI

while true {
    let chord = Chord(rootNoteValue: NoteValue.c, intervals: [0, 4, 7])
    print("chord: \(chord.description())")
    sleep(1)
}
