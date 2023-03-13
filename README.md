# Domino-s-Project
Projet des Dominos modélisation semestre 2 M1


Instructions du git :



QUELQUES COMMANDES CLEFS DE BASE :



git help blabla \\If you forgot how to use blabla

git status \\For checking if it's up to date

git branch -a \\Give the list of all branches

git pull \\Met tout le dépot local à jour

git pull origin MA_BRANCHE \\Met à jour le dépot local d'une branche spécifique

git diff HEAD \\Liste les différences entre le contenu du dernier commit et celui du répertoir de travail

git fetch \\Permet de récupérer toutes les données des commits effectués sur la branche courante qui n'existent pas encore dans ta version en local. Ces données seront stockées dans le répertoire de travail local mais ne seront pas fusionnées avec ta branche locale. Si tu souhaites fusionner ces données pour que ta branche soit à jour, tu dois utiliser ensuite la commande git merge.

git merge main \\Fusionne 2 branches ensembles. Permet de copier coller la branche spécifiée (ici main) sur l'autre (celle où tu te trouves) si tu préfères en remplaçant les données existantes sur la branche cible. Pour se faire il faut se placer sur la branche cible en vérifiant d'y être avec le HEAD de git status. Vérifier qu'elle soit à jour avec un git fetch. Vérifier que le dépot est à jour avec un git pull. et Ensuite effectuer le git merge.

git push -u origin KILUSHA \\POUR MOI TKT PAS T'EN PREOCUPES PAS. Permet de créer une branche distante nommée KILUSHA. Ainsi la branche sur laquelle je me trouve en tapant cette commande va suivre cette branche distante.



LES COMMITS :



Le but de git est de récupérer ce qui est sur le dépôt distant (sur github qui est l'équivalent du cloud Apple ou Samsung ou du Drive Google), pour pouvoir travailler sur tous les fichiers du projet souhaitée sans avoir de risques de pertes de données. L'avantage c'est que tu récupères tous les fchiers, tu bosses de ton côté, moi du mien, sans que ça pose le moindre problème, et ensuite on met à jour le dépot distant lorsque nous sommes prêts. Ainsi je récipère ta version, tu récupère la mienne également, et nous pouvons les fusionnées en toute simplicité à l'aide de certaines ligne de commandes que tu découvriras dans ce résumé de Github.

Ainsi quand tu as ton dossier sur les dominos qui est à jour, tu peux travailler sur ton code. Tout ce que tu modifieras sera changé sur ton ordinateur SEULEMENT. Une fois que tu as fait tous les changements que tu voulais, tu es donc prête à le déposer sur le dépôt distant ce qui aura pour but de mettre à jour les versions distantes qui se trouvent sur Github. Pour ce faire, il va falloir utiliser les commandes suivantes :

git add . \\N'oublie pas le point à la fin il est très important. Cette commande ici revient à dire : Prend un carton et ajoute TOUS les fichiers qui sont dans le répertoire où je me trouve. Si tu veux pas sélectionner TOUS les fichiers car par exemple il y en a que tu n'as pas modifier ou autre, alors tu peux explicitement écrire lesquels tu choisis d'ajouter dans ton carton en remplaçant le . par le nom du ou des fichiers concernés. Perso je te conseil de toujours utilisé le . car même si tu ne modifies pas tout, au moins tu ne risques pas d'oublier quoique ce soit et si les fichiers sont identiques bah ça les remplacera mais ça restera les même alors c'est tout bénef. De plus, les commandes qui suivent sont assez exigentes donc il est préférable que tu privilégies cette commande pour le bon déroulement de la suite. 

git commit -m "Tape ton message" \\Cette commande signifie : Vazy ferme le carton qui contient tous les fichiers que j'ai ajouté avec la commande précédente et met le scotch pour qu'il soit prêt à être expédié et ajoute le message "Tape ton message" dessus (genre "Correction du problème avec l'angle choc + correction de la durée de chute des dominos" histoire de savoir ce que tu as fait comme travail pour identifier ce qu'il y a de nouveau, ça permet d'avoir un super historique bien propre). N'OUBLIE PAS LES GUILLEMETS ICI !


git push <dépôt> <Branche> \\Ici tu envoies le colis avec toutes tes modifications dans le dépôt distant (nommé origin pour nous car Git donne ce nom par défaut) tout simplement. Il va donc écraser ce qu'il y a dans le dépot distant de la branche où tu veux envoyer tes données (que tu auras spécifié dans la commande) pour y remplacer par ce que tu as mis dans le carton (qui correspond à ce que tu as sur ton dépôt local à savoir ce que tu as sur ton pc). LES < > NE SONT PAS A METTRE BIEN SÛR, ICI ILS SONT UTILES UNIQUEMENT POUR TE MONTRER CE QUE TU DOIS PERSONALISER DANS LA COMMANDE.




LES BRANCHES :



Créer une branche, c’est en quelque sorte comme créer une “copie” de notre projet pour développer et tester de nouvelles fonctionnalités sans impacter le projet de base. La branche par défaut dans Git s’appelle master ou main. Cette branche va se déplacer automatiquement à chaque nouveau commit pour pointer sur le dernier commit effectué tant qu’on reste sur cette branche. Ca fonctionne comme une pile en fait. La branche main va toujours pointer l'assiette la plus haute de la pile. Et dès que tu fais un commit et un push, alors la branche pointe le tout dernier commit que tu as fait afin d'être le plus à jour possible. Bien sûr si tu es sur une autre branche, par exemple la branche MARINA, alors celle ci pointra le dernier commit que tu auras envoyé (push) sur la branche MARINA. La mention HEAD permet tout simplement de savoir sur quelle branche tu te trouves actuellement. C'est la raison pour laquelle lorsque tu écris git status la mention HEAD apparaît devant le branche sur laquelle tu travailles actuellement.

git branch NOM_DE_LA_BRANCHE \\Permet de créer une branche nommée NOM_DE_LA_BRANCHE mais en local seulement ATTENTION !


git checkout NOM_DE_LA_BRANCHE \\Permet de switcher sur la branche souhaitée (NOM_DE_LA_BRANCHE)




LES TAGS :



Les tags sont uilisés pour écrire des versions de programmes. Je pense qu'ils peuvent nous êtres utils comme des paliers sur lesquels se baser. Par exemple imagine on a 3 problème à régler sur notre code. Alors on fera plusieurs commits jusqu'à tant que ces trois problèmes soient résolus et ça pourra faire une sorte de palier avant de réattaquer un problème différent du code qui se situe à un autre niveau ou un truc du genre tu vois. On peux s'en servir pour séquencer les recherches qu'on fait pour solutionner nos problèmes sur notre code. On l'utilisera de la manière suivante :

git tag V1.0.1 \\Ici le V1.0.1 est un exemple mais tu mets ce que tu veux. Je pense que c'est une bonne idée d'utiliser ce genre de "code" pour éditer des versions tout simplement.




LES STASHS :



git stash \\Stash en anglais correspond à une étagère. Cette commande est utile pour stocker de manière temporaire ton taff comme si tu posais un livre de cuisine sur une étagère alors que tu étais en train de suivre la rectte, dans le but de faire quelque chose d'autre de plus important qui ne peut pas attendre. Ca permet donc de mettre en pause ton travail sans risquer de faire de la merde. Jez te dirai dans quels cas c'est utile si besoin.

git stash pop \\Permet de reprendre ton livre de cuisine pour revenir à où tu t'étais arrêté car quand tu l'as posé sur l'étagère, c'est comme si tu revenais en arrière sur le code d'origne avant que tu aies fait tes modifications.














Par rapport à notre façon de fonctionner : Ce que je te propose c'est que tu travailles sur la branche MARINA TOUT LE TEMPS. Moi je travail sur la branche KILUSHA TOUT LE TEMPS. Et lorsqu'on a besoin de réunir nos codes alors je te montrerai la procédure une fois et ensuite tu sauras la faire dès que nous aurons besoin de fusionner nos codes. La branche main restera intacte et nous la changerons dès qu'il faudra à savoir, quand on aura solutionner de gros problèmes. A chaque grosse étapes en quelques sortes, on fera une copie du code sur la branche main. Comme ça elle correspond à une copie propre à laquelle on peut revenir à tout moment en cas de problème.
La branche PROF ne sert qu'à poser les documents du prof et le prog qu'il nous file de base sur Moodle comme ça si tu as besoin tu as un accès rapide à celui ci.
Le gros avantage de tout ça c'est que toi tu pourras récupérer mes modifications de code sans que ça intervienne avec les tiennes. Dès que tu feras un git pull ou un git fetch selon la situation (je te le dirai), tu récupèreras mon code sans que ça ne change quoique ce soit au tien.
1. L'idée principale et l'esprit qu'il faut avoir c'est le suivant : A chauqe fois qu'on travaillera cette matière (chez nous ou en cours peu importe), la TOUTE PREMIERE CHOSE A FAIRE sera d'exécute un git pull. Comme ça tu récupère tout et tu es à jour avec le dépôt distant avant de commencer quoique ce soit. 
2. Ensuite tu verifies que tu es bien sur ta branche nommée MARINA. Pour ce faire tu exécutes la commande git status. Si tu n'ets pas sur la branche Marina, alors il faudra que tu changes avec la commande git checkout MARINA.
3. Et là tu travailles ce que tu veux comme tu veux librement sans risquer le moindre problème. Et une fois que tu as terminé ce que tu voulais faire (pense à découper le plus possible ton travail ce sera le plus simple), alors tu devvras faire un commit en tapant la commande git add . , puis git commit -m "TAPE TON MESSAGE", et enfin git push.
4. C'est tout ! Concernant tout le reste, si tu as besoin de plus d'informations ou autre surtout n'hésite jmmais à me demander ce sera toujours la meilleure chose que tu puisses faire car si tu tentes un truc sans être sûr de toi vu que je t'ai mis admin, tu as le droit de tout faire y compris de tout supprimer par inadvertance haha. Donc n'hésite jamais voili voilou j'espère que ça t'aura aidé cette petite aide.



OK j ai lu
