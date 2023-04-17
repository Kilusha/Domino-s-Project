# Domino-s-Project

Le but de se projet est de simuler la chute d'une chaine de domino afin d'en observer la propagation de son onde de chute.

Pour cela nous modélisons N dominos avec chacun une tige de
masse m, de hauteur h et d’epaisseur négligeable. Chaque domino sont séparés d’une
distance Delta selon l’axe x. Chacun pivote autour de sa base (rotation d’axe y) en faisant un angle alpha avec l'axe vertcial
(axe z). De plus, nous placons au sommet de chaque domino on ressort de masse negligeable, de constante de raideur k et de longueur à vide l0. Nous tiendrons compte de la viscosité gamma du
milieu de propagation. 
Dans notre programme l'utilisateur peut changer plusieurs parametres : N, Delta, hauteur des dominos (h), vitesse de rotation du 1er domino, gamma, m, la pesanteur g et k.

Toutes ses informations sont à entrer dans la ligne de commande lorsque cela sera demandé. Le programme affichera : 
- l'évolution des angles de tous les dominos de la chaine en fonction du temps.
- l'évolution des longueurs des ressorts de tous les dominos de la chaine en fonction du temps.
- l'évolution de la vitesse linéaire de propagation de l’onde de chute pour les dominos en fonction du temps.
