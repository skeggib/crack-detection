# APP5 - Crack detection

Projet 1 du cours de traitement d'image.

## Compilation

### Windows

Créer le dossier 'build' et se placer dedans.

```bash
mkdir build
cd build
```

Générer le projet (utiliser `cmake --help` pour voir la liste des générateur). Par exemple :

```bash
cmake .. -G "Visual Studio 15 2017 Win64"
```

Compiler le projet.

```bash
msbuild ALL_BUILD.vcxproj [/property:Configuration=Release]
```

Mettre des DLL d'OpenCV dans les dossiers `build/Debug` et `build/Release`.

### Linux

Créer le dossier 'build' et se placer dedans.

```bash
mkdir build
cd build
```
Générer le projet.

```bash
cmake ..
```

Compiler le projet :

```bash
make
```