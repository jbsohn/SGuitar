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
    
    var body: some View {
        VStack {
            Button("Test") {
                let n = Note(midiNote: 48)
                note = n.getNote().description()
            }
            Text(note)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
