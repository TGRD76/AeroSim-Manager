# AeroSim Manager 1.0.0

codé par tgrd76

Gestionnaire local d'addons pour le dossier Community de Microsoft Flight Simulator 2024.
Application Windows 10/11 x64 : ouvrir AeroSim-Manager-1.0.0.exe par double-clic, sans installer Python ni un runtime supplémentaire.

## Première ouverture

1. Entrer son propre prénom : aucun prénom n'est prérempli.
2. Choisir le dossier Community de MSFS 2024 ou utiliser la détection automatique.
3. Lire le guide rapide et ouvrir le dashboard.

La première version publique dispose de son propre indicateur de configuration. Même si une version d'essai était déjà utilisée sur ce profil Windows, la configuration 1.0.0 est proposée une fois.
Aux ouvertures suivantes : Bonjour/Bonsoir avec le prénom enregistré, puis Continuer vers le dashboard.
Le prénom, le message d'accueil et le dossier Community restent modifiables dans Personnaliser.
Les réglages sont enregistrés dans le profil Windows de chaque utilisateur et ne sont pas inclus dans l'exécutable partagé.

## Fonctionnalités

- Dashboard : total des dossiers, actifs, en pause et favoris ; connexion à Community, état du processus MSFS, espace libre, taille de la collection à la demande, dernières actions de la session.
- Mods : inventaire de Community et AeroSim-Disabled, recherche par titre/dossier/créateur/type, filtres et tri des colonnes.
- Glisser-déposer de dossiers et ZIP, y compris plusieurs éléments.
- Recherche des packages dans les sous-dossiers grâce à manifest.json.
- Import par copie avec préparation temporaire ; aucun remplacement d'un dossier existant du même nom.
- Activation/désactivation par déplacement dans AeroSim-Disabled à côté de Community.
- Favoris, ouverture des dossiers, métadonnées et calcul de taille en arrière-plan.
- Thèmes clair/sombre, couleur libre et préréglages, liste compacte/aérée, animations réglables.
- Barre verticale personnalisée : molette, clic sur piste et poignée déplaçable ; colonnes ajustées sans barre horizontale.
- Guide rapide, historique, logo multirésolution et crédit « codé par tgrd76 ».

## Utiliser et partager

Le fichier .exe peut être transmis seul à d'autres utilisateurs de Windows 10/11 x64.
Aucun compte, connexion réseau ou télémétrie dans l'application.
Fermer la version d'essai avant d'ouvrir AeroSim Manager 1.0.0 ; une seule instance peut gérer les fichiers à la fois.
Fermer MSFS avant les imports et changements de statut.
Une opération doit se terminer avant de fermer l'application.

## Fichiers et protections

Les sources importées sont conservées. Les doublons sont ignorés par nom de dossier.
Désactiver ne supprime pas l'addon ; réactiver le remet dans Community.
Pour restaurer sans l'application, déplacer les dossiers de AeroSim-Disabled vers Community sans écraser de dossier existant.
Les liens/jonctions sont affichés mais ne peuvent pas être déplacés ou importés ; ils sont exclus des calculs de taille.
Une opération interrompue peut avoir installé des packages précédents : le bilan l'indique.
Les types viennent du champ content_type du manifest, sans garantie de compatibilité avec MSFS 2024.
Les addons Marketplace ou gérés par un installateur propriétaire restent à gérer avec leur outil d'origine.
Les archives RAR/7z et ZIP chiffrés doivent être extraites manuellement.

Seule l'extraction ZIP utilise une commande Windows PowerShell cachée avec les bibliothèques de compression fournies par Windows. L'interface et les opérations sur les dossiers sont natives.
Les chemins sont transmis par environnement du processus et ne sont pas interpolés dans le code.
Les chemins hors destination, liens symboliques dans l'archive et ZIP dépassant 100 Go décompressés sont refusés.

## Données locales

Préférences : %LOCALAPPDATA%\AeroSimNative\settings.ini (Unicode).
Journal : %LOCALAPPDATA%\AeroSimNative\activity.log.
Journal ZIP : %LOCALAPPDATA%\AeroSimNative\zip-error.log.
Les emplacements internes sont conservés pour reprendre les réglages des versions d'essai.
Les dernières actions du dashboard sont celles de la session ; Historique ouvre le journal persistant.

## Code source et compilation

- app.c : interface et gestion des addons en C/Win32.
- app.rc, app.manifest, aerosim.ico : ressources du programme.
- logo.svg : source vectorielle du logo.
- build.py : compilation de l'exécutable Windows x64.
- tests.c : tests d'intégration à exécuter sur Windows ou dans un environnement Wine fonctionnel.

```
python -m pip install ziglang==0.17.0
python build.py
```

Compilation des tests :

```
python -m ziglang cc -target x86_64-windows-gnu -std=c11 -O1 -Wall -Wextra -Werror -municode -Wl,--stack,33554432 tests.c -lcomctl32 -lshell32 -lole32 -lshlwapi -lcomdlg32 -lgdi32 -luxtheme -lmsimg32 -o tests.exe
```

Puis lancer tests.exe sur Windows. Ils utilisent uniquement un dossier temporaire dédié.

## Validation

La base native et la version visuelle précédente ont été confirmées fonctionnelles par l'utilisateur sur son PC.
La compilation Windows x64 est contrôlée avec avertissements traités comme erreurs. Les ressources, l'inventaire des fichiers livrés et la suppression du prénom prédéfini sont contrôlés.
Les fonctions de contraste réelles en C ont été testées sur 20 000 couples de couleurs.
L'environnement de création est sous Linux et bloque les sockets nécessaires à Wine. La configuration initiale de cette version publique et les tests Windows n'ont donc pas été exécutés ici.
