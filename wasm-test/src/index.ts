// https://nodejs.org/en/learn/getting-started/nodejs-with-webassembly
//  npx tsc
//  node dist/index.js


import fs from 'node:fs';
import Module from './SGuitarModule.js';

// (async () => {
//     const module = await Module();

//     var note = new module.Note.createWithMidiNote(60);
//     console.log(note.getMidiNoteNumber());
// })();


var note = new Module.Note.createWithMidiNote(60);