//
//  ContentView.swift
//  iOS-rust
//
//  Created by John on 9/8/24.
//

import SwiftUI
import SGuitarFFI

struct ContentView: View {
    @State var description = "Not set"
    
    var body: some View {
        VStack {
            Button("Test Chord") {
                let chord = Chord(rootNoteValue: .c, intervals: [0,4,7])
                description = chord.description()
            }
            Text(description)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
