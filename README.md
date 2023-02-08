![PCB](/pub.png)

# Horloge simple basée sur arduino

## Comment ça marche ?

Le code se fait via l'interface de programmation arduino ainsi qu'avec le bootloader arduino installé sur l'atmega 328.
Au lieu d'utiliser une horloge RTC externe, ce projet utilise l'horloge interne de l'arduino.

## Pourquoi utiliser l'horloge interne ?

L'aduino dispose déjà d'une horloge, alors pourquoi utiliser une horloge externe ? Cela consomme plus d'énergie et coûte plus cher.

## Liste des composants

```
- 2 boutons poussoirs (https://www.gotronic.fr/art-bouton-poussoir-sp86a15-4301.htm)
- 2 boutons poussoirs équipés d'une led (https://www.gotronic.fr/art-bouton-poussoir-sp86a251-4303.htm)
- 4 connecteurs JST mâles (https://www.gotronic.fr/art-cordon-jst-male-femelle-2-cts-jst2-21318.htm)
- 1 Atmega328 (https://www.gotronic.fr/art-circuit-atmega328-12423.htm)
- 1 16,0000 MHz oscillateur quartz (https://www.gotronic.fr/art-quartz-bas-profil-16-0000-mhz-17101.htm)
- 1 lcd 16x02 (https://www.gotronic.fr/art-afficheur-lcd16x2-31490.htm)
- 1 capteur DHT11 (https://www.gotronic.fr/art-capteur-de-t-et-d-humidite-dht11-20692.htm)
- 4 resistances (Regarder dans le CAD pour les références)
- 1 potentiomètre (https://www.gotronic.fr/art-potentiometre-lineaire-1k-8486-11105.htm)
```
### Composants pour construire le PCB

```
- 1 plaque de cuivre 100x160 1.5mm (https://www.gotronic.fr/art-epoxy-brut-2-faces-6714.htm)
```

## License

[MIT](https://choosealicense.com/licenses/mit/)

# Avertissement et status du projet

Si vous tombez sur ce projet, sachez qu'il n'est pas développé pour être reproduit par tout le monde. Ainsi ce n'est pas sur qu'il marche comme indiqué dans les fichiers et est développé sur mon temps libre à titre de hobby.
