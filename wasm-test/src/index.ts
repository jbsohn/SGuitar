// https://nodejs.org/en/learn/getting-started/nodejs-with-webassembly
//  npx tsc
//  node dist/index.js

import fs from 'node:fs';

const wasmBuffer = fs.readFileSync('./dist/SGuitarLib.wasm');
WebAssembly.instantiate(wasmBuffer).then(wasmModule => {
    // Exported function lives under instance.exports object
    const { test } = wasmModule.instance.exports;
    console.log(test);
});
