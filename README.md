# SGuitar

# DJINNI

To regenerate the djinni files, run the following command:

```
cmake -DDJINNI_RUN=./djinni/src/run -DDJINNI_GENERATED_SRC=./generated-src -DDJINNI_IDL=./idl/sguitar.djinni -P ./scripts/run-djinni.cmake
```

# Integration Testing

These arguments get passed into DocTest app when running the integration tests:

```
$ProjectFileDir$/db/ddl.sql "$ProjectFileDir$/import/Lap Steel" "$ProjectFileDir$/import/Pedal Steel"
```