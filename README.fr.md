# VL1-emulator

Un émulateur de Casio VL-Tone VL1, réalisé à partir du code source par PolyValens

[![État de la construction](https://travis-ci.com/linuxmao-org/VL1-emulator.svg?branch=master)](https://travis-ci.com/linuxmao-org/VL1-emulator)

Page d'accueil : http://www.polyvalens.com/blog/vl-1/

Les informations écrites sur la page officielle ne représentent pas forcément l'état actuel de ce logiciel dérivé.

![Casio VL-1](resources/images/casio_vl1_big.png)

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
- `libjack-jackd2-dev` ou `libjack-dev`
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

## Journal des modifications

**v1.1.0.0**

Cette version marque une nouvelle étape du développement, une modification
multi-plateformes du code source VSTi d'origine.
Les fonctionnalités sont quasiment identiques au logiciel original mais pas
tout à fait, et il reste à implémenter quelques éléments d'importance mineure.

- élimination d'un clic audible lorsqu'une voix est redéclenchée
- édition de l'image afin d'enlever la marque du fabriquant de l'instrument original
- gestion de l'enregistrement d'automatisation
- ajout des info-bulles facilitant la lecture
- modification des domaines de paramètres afin qu'ils soient compréhensibles pour l'utilisateur
- résolution de la gestion de la calculatrice et la mémoire ADSR, lorsque la localisation utilise « , » comme séparateur de décimales
- gestion immédiate des messages MIDI, sans mémoire tampon
- résolution de potentiels accès mémoire hors limites
- gestion d'instances multiples dans un même hôte
- gestion de nouveaux formats et plate-formes

**v1.0.?.?**

- importation du code source depuis l'aval
- changement de licence en `CC0-1.0 or MIT` par l'auteur PolyValens
