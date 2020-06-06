# Projet C++ - Roblit

*Par Hugo Duarte et Florian Cormée*

Roblit s'inspire grandement du jeu mobile Hoplite. Cependant, l'univers est différent. Des micro-robots s'affronte pour la souveraineté sur une carte électronique ! Seulement un duo pourra y rester.

## Instructions de compilation

### Prérequis

Avant de compiler, assurez d'avoir installé la **librairie SFML** ainsi qu'un compilateur `g++` qui supporte le standard **C++17**.

### Compilation et utilisation du Makefile

La compilation est géré par un `makefile`. Ce dernier utilise des `wildcard`s pour trouver les sources et les compiler grâce aux règles implicites.

Pour compiler le jeu et les tests, ouvrez un terminal et naviguez jusqu'à l'adresse du fichier `makefile` puis entrer la commande suivante:

```
make
```

Cette commande est équivalente à `make all`.

On peut compiler uniquement le jeu avec la commande:

```
make build
```

Cette commande génère un exécutable nommé `Jeu`.

On peut compiler uniquement les tests unitaires avec la commande:

```
make test
```

Cette commande génère un exécutable nommé `Test`.

Le fichier permet aussi de supprimer les fichiers objets avec la commande `make clear`. Pour en plus supprimer les exécutables, entrez la commande `make vclear`. On peut intégralement recompiler le jeu ou les tests avec les commandes respectives `make rebuild` et `make retest`.

## Manuel d'utilisation

Roblit oppose deux équipes de robots. La première équipe est de couleur rouge et la seconde est de couleur cyan. Les personnages apparaissent à une position aléatoire. Il en va de même pour les objets ramassables.

Dans le coin supérieur gauche de l'écran, il y a un indicateur de l'équipe qui
joue avec un carré aux couleurs de l'équipe active. Dans ce cas, vous pouvez
sélectionner un personnage de cette couleur. Vous pouvez annulez la sélection en recliquant sur le personnage ou bien en cliquant sur un autre personnage de l'équipe. Vous avez alors sélectionner l'autre membre de votre équipe. Vous pouvez alors cliquer sur une case adjacente au personnage ce que l'y fait s'y déplacer. Au lieu de se déplacer, on peut utiliser un objet. Si le personnage en possède au moins 1, ils seront listé sur le bord gauche de l'écran. Un objet sélectionné passera en surbrillance. Pour l'utiliser, cliquez sur une case adjacent au personnage. Autrement, l'objet ne sera pas utilisé.

Le déplacement ou l'utilisation d'un objet met fin au tour de l'équipe et laisse l'équipe adverse réaliser 1 action. La partie se termine quand une équipe a été annihilée.

Roblit comporte deux types de personnages:

- Les héros:
  - 3 PV
  - Peut ramasser les objets au sol
  - Si un personnage (allié ou ennemi) est voisin avant et après le déplacement du personnage sélectionné, il perd 1 point de vie.
- Les fantassins:
  - 1 PV
  - Ne peut pas ramasser d'objet aussi
  - Est équipé d'un "taser"
  - Ne fait pas de dégat en se déplaçant

Deux types d'objets sont à votre disposition:

- Le taser:
  - Dégat 1 PV
  - Pas de temps de rechargement
- Le gravity gun
  - Pousse un personnage (allié ou ennemi)
  - Pas de dégat (sauf si le personnage sort de la carte dans ce cas 1 PV ou marche sur une case qui lui fait subir des dégats)
  - 3 tours pour le recharger après une utilisation

Le terrain est composé de deux type de case:

- Les cases normales (vertes) surlesquels on peut marcher et si le personnage le permet, ramasser des objets.
- Les cases de pistes électroniques (jaune-orangé) surlesquels un personnage refusera de marchera car il mourrait s'il y allait.

## Commentaires sur le programme

Le programme est pensé pour être facilement étendu. Pour cela, il existe de nombreuses interfaces ce qui réduit le couplage entre les classes concrètes. Dans cette même idée, nous avons implémenté un *design pattern* **MVC**. La vue s'appuie sur un pattern **visiteur**. Le contrôleur est notifié des évènements graphiques par un pattern **observer** modifié pour transmettre les informations sur l'évènement. Cela permet, par exemple d'ajouter des controles au clavier ou à la manette sans rien modifier. Enfin le jeu utilise une machine à état implémenté avec le **state pattern**. Nous avons créé un structure de donnée permettant de manipuler "naturellement" les grilles hexagonales. Nous avons alors développé un itérateur selon le [pattern iterator](https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/Iterator_UML_class_diagram.svg/500px-Iterator_UML_class_diagram.svg.png). Nons avons aussi écrit un gestionnaire de textures basique qui utilise le design pattern **singleton** pour s'assurer de centraliser le chargement des textures et leur stockage.

La bibliothèque implémentée pour l'utilisation des hexagones (namespace `hex`) et plus particulièrement l'objet `Coordonnees` et la machine à état (namespace `partie::etat`) sont essentielles au fonctionnement du jeu. Il peut aussi être intéressant de regarder un objet (par exemple `obj::GravityGun`, `vue::ObjetDessinable` et `Roblit`) pour constater la simplicité dans l'ajout de nouveaux objet. On peut faire le même constat en regardant `per::Heros`, `vue::PersonnageDessinalbe` et `Roblit` pour l'ajout de personnage. Ou encore, `donjon::cases::Sol`, `vue::CaseDessinable` et `partie::Partie` pour l'ajout de case.

## Organisation

Nous avons initialement réparti les principaux namespace. Florian Cormée a écrit le code dans les namespace `hex`, `donjon`, `vue`, `controlleur`. Hugo Duarte a écrit le code des namespace `partie`, `per`, `obj`. Régulièrement, le code rédigé par l'un a été testé, corrigé et nettoyé par l'autre. Au final, tous les codes rédigés ont été écrit par les deux étudiants.

Nous avons donc utilisé un dépot [Github](https://github.com/Bacmel/ProjetCpp) pour l'échange et le versionnage du code. Au début du projet, il y avait des branches dédiées aux principaux namespaces. Une fois un certain nombres de fonctionnalités implémentée, nous avons procédé à l'intégration. Dès lors, nous utilisons une branche pour une opération (ajout d'une fonctionnalité, correction de bugs, etc).
