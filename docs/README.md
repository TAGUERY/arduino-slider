# Documentation  

## Recherche et conception  

`À l’origine, je voulais créer un slider motorisé pour une caméra. Mais en prenant en compte le temps à disposition, le matériel et le budget, j’ai décidé d’adapter l’idée tout en gardant le concept du slider.`  

`Ce projet est conçu pour être installé sous une corbeille à papier. L’objectif est d’ajouter un défi lors du recyclage des feuilles : au lieu de simplement jeter le papier, les utilisateurs doivent viser une poubelle qui bouge. Le slider se déplace de manière aléatoire de droite à gauche, ce qui ajoute une difficulté supplémentaire.`  

`Le mouvement est contrôlé par un moteur et des capteurs. Il effectue des allers-retours entre deux extrémités, et un capteur détecte lorsque la plateforme atteint un bord pour la faire repartir dans l’autre sens.`  

![Description de l'image](/docs/assets/croquis-de-recherche.png)  

---

## Circuit électronique  

`Le circuit est basé sur un Arduino Uno, un moteur pas à pas et des capteurs de distance.`  

---

### Schéma  

![Description de l'image](/docs/assets/schematics_bb.png)  

---


### BOM  

| Réf | Composant                           | Quantité | Description                                | Fournisseur / Lien                                            |
| --- | ----------------------------------- | -------- | ------------------------------------------ | ------------------------------------------------------------- |
| 1   | Arduino Uno R3                      | 1        | Microcontrôleur ATmega328P                 | [Arduino](https://store.arduino.cc/products/arduino-uno-rev3) |
| 2   | Breadboard                          | 1        | Plaque de prototypage                      | [Lien](#)                                                     |
| 3   | HC-SR04 Sensor                      | 2        | Capteur de distance pour détecter les bords | [Lien](#)                                                     |
| 4   | Alimentation 12 V                   | 1        | Alimentation pour le moteur                | [Lien](#)                                                     |
| 5   | Shield Adafruit V3                  | 1        | Shield pour contrôler le moteur            | [Lien](#)                                                     |
| 6   | Moteur pas à pas Mercury Motor SM 42BYG011-25 | 1 | Moteur pour déplacer le slider | [Lien](#) |
| 7   | Poulie Z40 GT2-6 (5 mm)             | 1        | Poulie pour la courroie GT2                | [Bastelgarage](https://www.bastelgarage.ch/poulie-z40-gt2-6-avec-un-alesage-de-5mm-et-un-siege-de-16mm) |
| 8   | Kit de réparation de courroie GT2 (2000 mm) | 1 | Courroie GT2 pour le déplacement du slider | [Bastelgarage](https://www.bastelgarage.ch/kit-de-reparation-de-courroie-gt2-2000mm) |
| 9   | Poulie Z20 GT2-6 (5 mm)             | 1        | Deuxième poulie GT2                        | [Bastelgarage](https://www.bastelgarage.ch/poulie-z20-gt2-6-avec-alesage-de-5mm-et-siege-de-16mm) |
| 10  | Pince à courroie GT2 (9 mm)         | 1        | Fixation de la courroie                    | [Bastelgarage](https://www.bastelgarage.ch/pince-a-courroie-gt2-9mm) |
| 11  | Vis M3                              | 2        | Fixation du moteur                         | [Lien](#) |
| 12  | Rondelles                           | 5        | Renforts pour la fixation                  | [Lien](#) |
| 13  | Équerres                            | 5        | Support pour la structure                  | [Lien](#) |


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
- **Détection d'obstacles** avec deux capteurs **HC-SR04**, permettant de stopper ou inverser la direction du moteur.  
- **Changement aléatoire de direction** après un intervalle de temps défini.  
- **Contrôle manuel** via deux boutons pour changer la direction ou activer/désactiver le moteur.  
- **Réglage dynamique de la vitesse** avec un potentiomètre.  

### Points d'amélioration  
- Ajouter une gestion plus fine des courbes de vitesse pour éviter les à-coups.  
- Optimiser la gestion des interruptions pour la lecture des capteurs.  
- Implémenter une option pour mémoriser les dernières vitesses et directions en cas de redémarrage.  

---


## Roadmap  

`- Ajouter une option pour régler la vitesse du mouvement.`  
`- Ajouter un signal sonore ou une LED pour indiquer qu’un papier a bien été lancé.`  
`- Explorer l’ajout d’un capteur pour détecter si un papier est bien entré dans la corbeille.`  

