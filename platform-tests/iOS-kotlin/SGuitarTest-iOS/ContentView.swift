//
//  ContentView.swift
//  SGuitarTest-iOS
//
//  Created by John on 9/17/24.
//

import SwiftUI
import SGuitar

struct ContentView: View {
    @State var note = ""
    @State var scale = ""
    
    var body: some View {
        VStack {
            Text("Note: \(note)")
            Text("Scale: \(scale)")
        }
        .onAppear() {
            let n = Note(midiNote: 48)
            note = n.getNote().description()
            
            let tones: [KotlinInt] = [2, 2, 1, 2, 2, 2]
            let s = Scale(
                rootNote: .c,
                semitones: tones)
            scale = s.testDescription()
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
