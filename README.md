# Domino-s-Project
# Bienvenue au Projet : Domino 👋 🎲
[![Documentation](https://img.shields.io/badge/documentation-yes-brightgreen.svg)](https://github.com/Kilusha/Domino-s-Project/blob/KILUSHA/Projet___Domino_Final_V3.pdf)

> Le but de ce projet est de simuler la chute d'une chaine de Nmax dominos afin d'observer la propagation de l'onde de chute qui la traverse et d'en tirer quelques caratéristiques.

Pour cela nous modélisons Nmax dominos avec chacun une tige de masse m, de hauteur h et d’épaisseur négligeable. Chaque domino est séparé du suivant d’une distance Delta selon l’axe x. Chacun d'entre eux pivote autour de sa base (rotation d’axe y) en faisant un angle alpha avec l'axe vertical (axe z). De plus, nous plaçons au sommet de chacun, un ressort de masse négligeable, de constante de raideur k et de longueur à vide l0 afin de modéliser les forces appliquées entre chaque domino lors de la chute de ces derniers. Nous tenons compte de la viscosité gamma du milieu de propagation dans lequel a lieu l'expérience, ainsi que de la pesanteur qui entre indéniablement en jeu. L'amorce de la chute est donnée par une vitesse de rotation initiale fournie au 1er domino de la chaîne. À chaque instant t séparé d'un intervalle de temps dt fixé dans le programme et non-modifiable, ce dernier enregistre les valeurs de tous les angles que forment les dominos par rapport à l'axe vertical afin de les stocker dans un fichier texte. Il en est de même pour la longueur des ressorts de tous les dominos qui est donc stockée par le programme dans un fichier texte également. La vitesse de propagation linéaire de l'onde de chute à travers la chaîne de domino est aussi calculée et stockée dans un fichier texte à chaque instant par le programme. Tous ces fichiers ayant été générés dans le but de pouvoir tracer 3 graphiques : celui de l'évolution de l'angle de chaque domino en fonction du temps, celui de l'évolution de la longueur du ressort de chaque domino en fonction du temps, et enfin celui de l'évolution de la vitesse linéaire de l'onde de chute en fonction du temps. Les graphiques sont tracés automatiquement sans qu'il n'y ait besoin d'utiliser gnuplot dans un terminal à part.


### 🏠 [Homepage](https://github.com/Kilusha/Domino-s-Project/tree/KILUSHA)

## 📝 Utilisation

La première commande à éxecutée pour faire fonctionner ce code est de le compiler à l'aide de la ligne de commande suivante :
```sh
make
```
La seconde étape à suivre consiste à exécuter l'exécutable depuis votre terminal grâce à la ligne de commande suivante :
```sh
./main
```
À partir de là, il vous suffit de vous laisser guider par les instructions du programme.

Vous allez être amené à saisir : 

    * le nombre de dominos Nmax qui compose votre chaîne,
    * la distance delta qui sépare vos dominos,
    * la hauteur de vos dominos,
    * la vitesse de rotation initiale de vos dominos,
    * la viscosité moléculaire du milieu de propagation,
    * la masse de vos dominos,
    * la pesanteur de la planète sur laquelle vous souhaitez réaliser l'expérience,
    * la constante de raideur du ressort.

### ⚠️ Attention : Toutes les données à saisir doivent être renseignées dans les unitées du système international (qui sont toujours précisées dans les questions).

Une fois toutes ces instructions réalisées, vous pourrez constater l'apparition des 3 graphiques dans 3 fenêtres différentes qui s'ouvriront devant vous.

Dans votre terminal, vous trouverez quelques phrases pour vous faire patienter et méditer pendant l'exécution du programme, ainsi que certaines délarations ou affirmations afin de vous présenter des informations utiles comme la valeur de l'angle choc entre les 2 premiers dominos, le temps correspondant au choc du premier domino avec son voisin de droite, le temps de chute total de la chaîne de dominos, la bonne sauvegarde des différents fichiers texte, et d'autres informations qui diffèrent selon la configuration de votre expérience.

À noter que ce programme est dotée de toutes les sécurités nécéssaire pour ne pas planter en cas de faute de saisie ou de choix absurde ou quoique ce soit d'autre.


## 👥 Auteurs

👤 **Kiliann Palay**

* Github: [@Kilusha](https://github.com/Kilusha)
* LinkedIn: [@kiliannpalay](https://linkedin.com/in/kiliannpalay)

👤 **Marina Serre**

* Github: [@marinightx](https://github.com/marinightx)
* LinkedIn: [@marinaserre](https://linkedin.com/in/marinaserre)

## 💌 Show your support

Laissez une ⭐️ dans votre commentaire sur notre page git si vous avez aimé ce projet !

***
_Ce README a été généré avec ❤️_