![PCB](/pub.png)

# S.imple A.larm C.lock

A simple code project around the question:
How to make the simplest clock as possible?!

## [Website](https://stbretzel.github.io/simplealarmclock/) 

## How this work

This experimental project work with the internal arduino clock. Stop use rtc clock, there is a clock in arduino!

## Explanations

The Arduino's problem is the lot of leds tha consume too much around the microcontroller, so i created a pcb to exploit the Atmega328 without inutile component. The pcb is designed specialy for a specific alarm-clock, but, you can modify it as your wish! This is the magic of open-source.

## Parts list

```
- 2 simple pushbuttons (https://www.gotronic.fr/art-bouton-poussoir-sp86a15-4301.htm)
- 2 leds pushbuttons (https://www.gotronic.fr/art-bouton-poussoir-sp86a251-4303.htm)
- 4 Male JST connectors (https://www.gotronic.fr/art-cordon-jst-male-femelle-2-cts-jst2-21318.htm)
- 1 Atmega328 (https://www.gotronic.fr/art-circuit-atmega328-12423.htm)
- 1 16, 0000 MHz quartz oscillator (https://www.gotronic.fr/art-quartz-bas-profil-16-0000-mhz-17101.htm)
- 1 lcd 16x02 (https://www.gotronic.fr/art-afficheur-lcd16x2-31490.htm)
- 1 DHT11 sensor (https://www.gotronic.fr/art-capteur-de-t-et-d-humidite-dht11-20692.htm)
- 4 resistors (Look in cad files for references)
- 1 potentiometer (https://www.gotronic.fr/art-potentiometre-lineaire-1k-8486-11105.htm)
```
### Parts if you want to create the pcb

```
- 1 copper plate 100x160 1.5mm (https://www.gotronic.fr/art-epoxy-brut-2-faces-6714.htm)
```

## License

[MIT](https://choosealicense.com/licenses/mit/)

# Warning & Project status

I develop this project on my free time, this git is public but the project is still in progress. So warning the PCB was not tested. The circuit is not really good explained.
