1	Systemvoraussetzungen
Webserver mit Apache 2.x 
Datenbank MySQL 5.0.15 oder h�her mit PDO (f�r die Installation wird eine leere Datenbank ben�tigt)
PHP 5.2.5 oder h�her (5.3 empfohlen)
Speicherplatz 300 MB oder h�her

Einstellungen php.ini
memory_limit=512M oder h�her
max_execution_time 300 oder h�her
Einstellungen my.cnf 
max_allowed_packet = 32M oder h�her

2	Installationsschritte
2.1	Schritt 1
Dateien und Verzeichnisse komplett in das Root-Verzeichnis des Webservers (z.B. httpdocs etc.) kopieren 
2.2	Schritt 2
Datenbank-Dump �dp-datenbunk.sql� mittels phpMyAdmin oder Terminal in eine leere Datenbank auf dem Server importieren. (Terminal-Befehl: mysql �u [DB Benutzername>]-p [DB Name] < dp-datenbunk.sql , anschlie�end wird nach DP Passwort gefragt)
2.3	Schritt 3
Datei /sites/default/settings.php konfigurieren:
Ab Zeile 218:
      'database' => '...',   - Datenbank Name                                                                                                                               
      'username' => '...',   - Datenbank Benutzername                                                                                                                             
      'password' => '...',    - Datenbank Passwort
2.4	Schritt 4
Crontab in Terminal einstellen
# crontab �e

Folgende Zeile hinzuf�gen und crontab-Konfiguration speichern:

* * * * wget -O - -q -t 1  http://www.IHRE-WEBSITE.de /sites/all/modules/contrib/elysia_cron/cron.php?cron_key=XHCCQBIV-aPWhji8dX0Ka-u_PcH3dmphIIr_hQOCD4M

Wenn n�tig, Crontab neustarten
2.5	Schritt 5
Als Administrator anmelden:
E-Mail: bst-bf-admin@nexum.de
Passwort: bst-bf-admin
