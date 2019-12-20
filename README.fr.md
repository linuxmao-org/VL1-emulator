# VL1-emulator

Un émulateur de Casio VL-Tone VL1, réalisé à partir du code source par PolyValens

[![État de la construction](https://travis-ci.com/linuxmao-org/VL1-emulator.svg?branch=master)](https://travis-ci.com/linuxmao-org/VL1-emulator)

Page d'accueil : http://www.polyvalens.com/blog/vl-1/

Les informations écrites sur la page officielle ne représentent pas forcément l'état actuel de ce logiciel dérivé.

## Téléchargements

**En développement**

- Tous : télécharger les [Constructions automatiques](https://github.com/linuxmao-org/VL1-emulator/releases/tag/automatic).

## Instructions de construction

1. Récupérer les pré-requis

Installer les paquets nécessaires :

- `git`
- `build-essential`
- `pkg-config`
- `libx11-dev`
- `libcairo2-dev`
- `libjack-jackd2-dev` or `libjack-dev`
- `mesa-common-dev`

2. Cloner le dépôt et ses sous-modules

```
git clone https://github.com/linuxmao-org/VL1-emulator.git
cd VL1-emulator
git submodule update --init
```

3. Compiler

```
make
```

4. Installer

```
sudo make install  # pour installer dans les dossiers système, or
make install-user  # pour installer dans le dossier utilisateur
```
