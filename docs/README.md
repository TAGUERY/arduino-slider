# Documentation  

## Recherche et conception  

`À l’origine, je voulais créer un slider motorisé pour une caméra. Mais en prenant en compte le temps à disposition, le matériel et le budget, j’ai décidé d’adapter l’idée tout en gardant le concept du slider.`  

`Ce projet est conçu pour être installé sous une corbeille à papier. L’objectif est d’ajouter un défi lors du recyclage des feuilles : au lieu de simplement jeter le papier, les utilisateurs doivent viser une poubelle qui bouge. Le slider se déplace de manière aléatoire de droite à gauche, ce qui ajoute une difficulté supplémentaire.`  

`Le mouvement est contrôlé par un moteur et des capteurs. Il effectue des allers-retours entre deux extrémités, et un capteur détecte lorsque la plateforme atteint un bord pour la faire repartir dans l’autre sens.`  


Construction (voir les images en suivant les étapes):
1. Couper le bois en 3 parties : 2x 20x10 cm et 1x 23x20 cm.
2. Percer deux trous parallèles à mi-hauteur, d’un diamètre de 1 cm, avec un espacement d’environ 15 cm.
3. Planter 4 clous à 12 cm chacun sur la plateforme (planche de 23x20 cm) pour guider celle-ci le long des deux tubes.
4. Fixer 2 équerres (du côté des clous) pour y placer les deux capteurs avec du double-face, en veillant à ce qu’ils soient orientés vers l’extérieur.
5. Insérer les tiges dans les 2 planches de 20x10 cm.
6. Fixer les équerres et installer le moteur (écart de 31 mm entre les deux pas de vis, si c'est un NEMA 17).
7. Planter un clou avec une roue crantée, en s’assurant qu’elle puisse tourner librement.
8. Sur le profil de la plateforme, fixer une équerre avec la pince à courroie.
9. Installer la courroie. Si elle est trop courte, faire passer les tubes à travers la planche latérale pour rapprocher les deux planches.
10. Remplacer les fils des capteurs par des fils d’au moins 1 mètre, afin qu’ils puissent se déplacer avec la plateforme.


![Breadboard](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/breadBoard.png)  
![capteurs sous la plateforme](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/capteur.png)  
![autre angle des capteurs sous la plateforme](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/capteur2.png)  
![moteur avec le couroie](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/moteur.png)  
![couroie attachée à la plateforme](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/pince.png)  
![moteur vissé à la planche principale](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/plancheMoteur.png)  


---

## Circuit électronique  

`Le circuit est basé sur un Arduino Uno, un moteur pas à pas et des capteurs de distance.`  

---

### Schéma  

![Schéma du circuit](https://github.com/TAGUERY/arduino-slider/blob/main/docs/assets/schematics-slider.png)  

`Attention au raccordement des fils du moteur, il faut contrôler le branchement correct des câbles avec un multimètre.`  

---


### BOM  

| Réf | Composant                           | Quantité | Description                                | Fournisseur / Lien                                            |
| --- | ----------------------------------- | -------- | ------------------------------------------ | ------------------------------------------------------------- |
| 1   | Arduino Uno R3                      | 1        | Microcontrôleur ATmega328P                 | [Arduino](https://store.arduino.cc/products/arduino-uno-rev3) |
| 2   | Breadboard                          | 1        | Plaque de prototypage                      |                             |
| 3   | HC-SR04 Sensor                      | 2        | Capteur de distance pour détecter les bords | [Distrelec](https://www.distrelec.ch/en/hc-sr04-ultrasonic-distance-sensor-sparkfun-electronics-sen-15569/p/30160395)                                                                             |
| 4   | Alimentation 12 V                   | 1        | Alimentation pour le moteur                |                                                    |
| 5   | Shield Adafruit V3                  | 1        | Shield pour contrôler le moteur            | [Digikey](https://www.digikey.ch/de/products/detail/adafruit-industries-llc/2601/9452124?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_High%20ROAS&utm_term=&productid=9452124&utm_content=&utm_id=go_cmp-20198980972_adg-_ad-__dev-c_ext-_prd-9452124_sig-CjwKCAiArKW-BhAzEiwAZhWsIJ-voKXVw4z7aFOvFLgQ1sOqvUQzhf2ccaoVZMaWZJu2GoJ2JaB6whoCe2QQAvD_BwE&gad_source=4&gclid=CjwKCAiArKW-BhAzEiwAZhWsIJ-voKXVw4z7aFOvFLgQ1sOqvUQzhf2ccaoVZMaWZJu2GoJ2JaB6whoCe2QQAvD_BwE&gclsrc=aw.ds)                                                     |
| 6   | Moteur pas à pas Mercury Motor SM 42BYG011-25 | 1 | Moteur pour déplacer le slider | [Digikey](https://www.distrelec.ch/de/bipolarer-schrittmotor-nema-17-12v-sparkfun-electronics-sm-42byg011-25/p/30145493?pup_e=1&pup_cid=361191&pup_id=30145493&cq_src=google_ads&cq_cmp=18261832767&cq_con=&cq_term=&cq_med=pla&cq_plac=&cq_net=x&cq_pos=&cq_plt=gp&gclsrc=aw.ds&gclsrc=aw.ds&gad_source=1&gclid=CjwKCAiArKW-BhAzEiwAZhWsIFcOM6eNVSic06VEV4xT4TpYKsGN65yJZL114n0mOFrMSeDaqals7xoCwowQAvD_BwE) |
| 7   | Poulie Z40 GT2-6 (5 mm)             | 1        | Poulie pour la courroie GT2                | [Bastelgarage](https://www.bastelgarage.ch/poulie-z40-gt2-6-avec-un-alesage-de-5mm-et-un-siege-de-16mm) |
| 8   | Kit de réparation de courroie GT2 (2000 mm) | 1 | Courroie GT2 pour le déplacement du slider | [Bastelgarage](https://www.bastelgarage.ch/kit-de-reparation-de-courroie-gt2-2000mm) |
| 9   | Poulie Z20 GT2-6 (5 mm)             | 1        | Deuxième poulie GT2                        | [Bastelgarage](https://www.bastelgarage.ch/poulie-z20-gt2-6-avec-alesage-de-5mm-et-siege-de-16mm) |
| 10  | Pince à courroie GT2 (9 mm)         | 1        | Fixation de la courroie                    | [Bastelgarage](https://www.bastelgarage.ch/pince-a-courroie-gt2-9mm) |
| 11  | Vis M3                              | 2        | Fixation du moteur                         |  |
| 12  | Rondelles                           | 5        | Renforts pour la fixation                  |  |
| 13  | Équerres                            | 5        | Support pour la structure                  |  |
| 14  | Tubes                            | 2        | barres pour faire glisser la plateforme                  | [Jumbo](https://www.jumbo.ch/fr/gros-outillage-atelier/ferrures-boites-aux-lettres/profiles/profiles-en-aluminium/alfer-tube-rond-en-aluminium---10-mm--1-m/p/3198038) |
| 15  | Planche compressée                           | 1        | 20cm X 63cm                  | [Jumbo](https://www.jumbo.ch/fr/construction-renovation/bois/decoupe-du-bois/c/060201) |


## Programme  

### Bibliothèques utilisées  
- **Wire.h** : Communication I2C utilisée par le Shield moteur.  
- **Adafruit_MotorShield.h** : Gestion du moteur pas à pas via le Shield Adafruit.  

### Structure du programme  
- **Initialisation** :  
  - Configuration des broches, des boutons et des capteurs à ultrasons.  
  - Vérification de la connexion du Shield moteur.  
  - Définition de la vitesse du moteur.  

- **Fonctionnement principal** :  
  - **Gestion des boutons** : Détection avec anti-rebond pour le changement de direction et l'activation/désactivation du moteur.  
  - **Contrôle de la vitesse** : Lecture d'un potentiomètre et adaptation de la vitesse en temps réel.  
  - **Changement de direction** : Automatique basé sur une logique de changement aléatoire ou en fonction des capteurs.  
  - **Capteurs à ultrasons** : Détection d'obstacles pour modifier le sens du moteur si la distance est inférieure à un seuil défini.  
  - **Exécution du moteur** : Mouvement du moteur pas à pas avec gestion du sens et libération du moteur lorsqu'il est éteint.  

### Particularités  
- **Détection d'obstacles** avec deux capteurs **HC-SR04**, permettant d'inverser la direction du moteur.  
- **Changement aléatoire de direction** après un intervalle de temps défini.  
- **Contrôle manuel** via deux boutons pour changer la direction ou activer/désactiver le moteur.  
- **Réglage dynamique de la vitesse** avec un potentiomètre.  

### Points d'amélioration  
- Ajouter une gestion plus fine des courbes de vitesse pour éviter les à-coups.  
- Optimiser la gestion des interruptions pour la lecture des capteurs.  
- Le système de glissement sur les deux barres en acier pour fluidifier les changements de direction.  

---


## Roadmap  

`- Ajouter un signal sonore ou une LED pour indiquer qu’un papier a bien été lancé dans la corbeille.` 

`- Mettre en place un petit écran LCD avec la sélection de mode de jeux et l'affichage de la vitesse.` 


---




