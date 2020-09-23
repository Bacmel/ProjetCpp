# C++ Project - Roblite

*By Hugo Duarte and Florian Cormée*

Roblite is greatly inspired by the mobile game Hoplite. However, the universe is different. Micro-robots compete for sovereignty on an electronic
card! Only a duo will be able to stay there.

Thanks to [Bvok](https://facepunchss13.proboards.com/thread/1456/bvoks-sprite-bin) and [AK](https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/ef2c82eb-ab3b-4bdb-88ad-5bae9c705695/d95cy6j-83c3a500-8ded-4bab-bbdb-0f382fb7290e.png/v1/fill/w_353,h_118,q_80,strp/half_life_2_custom_gravity_gun_sprite_sheet_by_dantewreckmen_999_d95cy6j-fullview.jpg?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOiIsImlzcyI6InVybjphcHA6Iiwib2JqIjpbW3siaGVpZ2h0IjoiPD0xMTgiLCJwYXRoIjoiXC9mXC9lZjJjODJlYi1hYjNiLTRiZGItODhhZC01YmFlOWM3MDU2OTVcL2Q5NWN5NmotODNjM2E1MDAtOGRlZC00YmFiLWJiZGItMGYzODJmYjcyOTBlLnBuZyIsIndpZHRoIjoiPD0zNTMifV1dLCJhdWQiOlsidXJuOnNlcnZpY2U6aW1hZ2Uub3BlcmF0aW9ucyJdfQ.3rRfddHg5iG5DBsjdDR1DXeMTMV_QCNo3FhOpG8-5d0) for their sprites.

*Read this in other language:[Français](README.md)*

## Compilation instructions

### Prerequisites

Before compiling, make sure you have installed the **SFML library** and a `g++` compiler that supports the **C++17** standard.

### Compiling and using the Makefile

The compilation is managed by a `makefile`. The latter uses `wildcard`s to find the sources and compile them using implicit rules.

To compile the game and the tests, open a terminal and navigate to the address of the `makefile' and enter the following command:

```
make
```

This order is equivalent to `make all`.

You can only compile the game with the command :

```
make build
```

This command generates an executable named `Jeu`.

Only unit tests can be compiled with the command :

```
make test
```

This command generates an executable named `Test`.

The file also allows you to delete object files with the `make clear` command. To additionally delete executables, enter the command `make vclear`.
You can completely recompile the game or the tests with the respective commands `make rebuild` and `make retest`.

Important note : The tests include a test of the graphical part. It opens a **black window which must be closed to complete the tests**.

## User manual

Roblite pits two teams of robots against each other. The first team is red and the second is cyan. The characters appear in a random
position. The same applies to the pickable objects.

In the upper left corner of the screen there is an indicator of the team playing with a square in the colours of the active team. In this case you can
select a character of that colour. You can cancel the selection by clicking on the character again or by clicking on another character of
the team. You have now selected the other member of your team. You can then click on a square next to the character and click on the character to move to it.
Instead of moving, you can use an object. If the character has at least 1, they will be listed on the left edge of the screen. A selected object
will be highlighted. To use it, click on a box adjacent to the character. Otherwise, the item will not be used.

Moving or using an object ends the team's turn and lets the opposing team perform 1 action. The game ends when a team has been annihilated.

Roblite has two types of characters:

- Heroes:
  - 3 PV
  - Can pick up objects from the ground
  - If a character (ally or enemy) is a neighbour before and after the selected character's move, he loses 1 hit point.
- Foot soldiers:
  - 1 VP
  - Cannot pick up any objects as well
  - Is equipped with a taser
  - Does no damage when moving around

Two types of objects are at your disposal:

- The taser:
  - Damage 1 PV
  - No recharging time
- The gravity gun
  - Pushes a character (ally or enemy)
  - No damage (except if the character steps off the map in this case 1 VP or steps on a square that causes damage).
  - 3 turns to recharge it after use

The terrain is composed of two types of hut:

- The normal (green) squares on which you can walk, and if the character allows it, pick up objects.
- The squares of electronic tracks (yellow-orange) on which a character will refuse to walk because he would die if he went there.


## Comments on the programme

The programme is designed to be easily extended. For this purpose, there are numerous interfaces, which reduces the coupling between concrete classes. In
the same idea, we have implemented a *design pattern* **MVC**. The view is based on a **visitor** pattern. The controller is notified of graphical events
by a modified **observer** pattern to transmit information about the event. This makes it possible, for example, to add controls to the keyboard or
joystick without modifying anything. Finally the game uses a state machine implemented with the **state pattern**. We have created a data structure allowing to
manipulate "naturally" hexagonal grids. We then developed an iterator according to the [pattern iterator](https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/Iterator_UML_class_diagram.svg/500px-Iterator_UML_class_diagram.svg.png). We also wrote a basic texture manager
that uses the **singleton** design pattern to ensure that textures are loaded and stored centrally.

The library implemented for the use of hexagons (namespace `hex`) and more specifically the `coordonnées` object and the state machine (namespace
`partie::etat`) are essential to the operation of the game. It can also be interesting to look at an object (e.g. `obj::GravityGun`,
`vue::ObjetDessinable` and `Roblite`) to see how easy it is to add new objects. You can make the same observation by looking at `per::Heros`,
`vue::PersonnageDessinable` and `Roblite` to add a character. Or, `donjon::cases::Sol`, `vue::CaseDessinable` and `partie::Partie` for adding
squares.

## Organisation

We initially distributed the main namespace. Florian Cormée wrote the code in the namespace `hex`, `donjon`, `vue`, `controleur`. Hugo Duarte wrote
the code in the namespaces `partie`, `per`, `obj`. Regularly, the code written by one was tested, corrected and cleaned by the other. In the end, all the codes
written were written by both students.

So we used a Git repository for the exchange and versioning of the code. At the beginning of the project, there were branches dedicated to the main namespaces. Once
a certain number of functionalities were implemented, we proceeded with the integration. From then on, we use a branch for an operation (addition of
a feature, bug fixes, etc).
