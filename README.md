# SGuitar

**SGuitar** is a cross-platform C++ library for modeling and manipulating steel guitar tunings, scales, chords, and pedal/lever changes. It powers the core logic of the Steel Sidekick app on iOS, Android, and WebAssembly.

---

## 🛠 Dependencies

This project uses [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) to fetch dependencies:

- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) for database access
- [fmt](https://github.com/fmtlib/fmt) for formatting
- [doctest](https://github.com/doctest/doctest) for unit testing

---

## 🔁 DJINNI Code Generation

To regenerate all Djinni bindings:

```bash
cmake \
  -DDJINNI=./djinni \
  -DDJINNI_GENERATED_SRC=./generated-src \
  -DDJINNI_IDL=./idl/sguitar.djinni \
  -P ./cmake/run-djinni.cmake
```

This regenerates Objective-C, Java, JNI, and C++ bridge code into the `generated-src/` directory.

---

## ✅ Running Unit Tests

### Integration Test Usage

The test binary expects three arguments: a DDL SQL file, and two import paths for lap steel and pedal steel data.

Example:
```bash
./tests ./db/ddl.sql ./import/Lap\ Steel ./import/Pedal\ Steel
```

### In CLion / CMake:
You can pass these as test arguments:
```text
$ProjectFileDir$/db/ddl.sql "$ProjectFileDir$/import/Lap Steel" "$ProjectFileDir$/import/Pedal Steel"
```

---

## 📱 Building for iOS (Xcode Framework)

To generate an Xcode project that builds SGuitar as an iOS framework:

```bash
cmake -S . -B build -G Xcode -DIOS=1
```

Then open the `build` directory in Xcode.

---

## 🌐 Building for WebAssembly with Emscripten

SGuitar can be compiled to WebAssembly using [Emscripten](https://emscripten.org/). The project uses [Embind](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html) for JS bindings.

### Emscripten Build Flags Used

```bash
--bind                         # Use Embind to expose C++ classes to JavaScript
-s MALLOC=emmalloc             # Smaller malloc implementation
-s MODULARIZE=1                # Export the module as an ES6-style factory function
-s WASM_BIGINT=1               # Allow passing 64-bit integers (int64_t) to JS
```

### Build Steps

```bash
emcmake cmake -S . -B .build
cd .build
emmake make
```

This produces `SGuitar.js` and `SGuitar.wasm` in the `.build/` directory.

---

## 🧪 Supported Platforms

| Platform     | Target Type         | Status       |
|--------------|----------------------|--------------|
| Linux/macOS  | Static Library       | ✅ Working    |
| iOS          | Framework (Xcode)    | ✅ Working    |
| Android      | Shared Library (.so) | ✅ Working    |
| WebAssembly  | .wasm + JS glue code | ✅ Working    |

---

## 🔄 Planned Improvements

- 📦 Swift Package and AAR builds via GitHub Actions
- 📦 NPM packaging for Emscripten/WebAssembly build
- 🧪 Better documentation and automation for Djinni integration
- 📚 Documentation and API examples

---

## 📃 License

This project is licensed under the GNU General Public License v2.0 (GPLv2).

You are free to use, study, modify, and share this code under the terms of the GPL. This means that any distributed modifications or derivatives must also be open source and GPL-compatible.

The author retains all rights to license the code under alternative terms for private or commercial use. If you're interested in using this code in a closed-source or proprietary application — such as a commercial iOS or Android app — please contact me.

🎓 Academic users are welcome! If you use SGuitar in a class project, thesis, or paper, I’d love to hear about it — feel free to reach out.

© 2025 John Sohn