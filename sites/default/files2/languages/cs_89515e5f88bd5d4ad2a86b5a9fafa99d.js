Drupal.locale = { 'pluralFormula': function($n) { return Number((((($n%10)==1)&&(($n%100)!=11))?(0):((((($n%10)>=2)&&(($n%10)<=4))&&((($n%100)<10)||(($n%100)>=20)))?(1):2))); }, 'strings': { "Unspecified error": "Neznámá chyba", "The changes to these blocks will not be saved until the \x3cem\x3eSave blocks\x3c/em\x3e button is clicked.": "Změny v těchto blocích se neprojeví, dokud je neuložíte pomocí tlačítka \x3cem\x3eUložit bloky\x3c/em\x3e.", "Your server has been successfully tested to support this feature.": "Váš server byl pro tuto funkci úspěšně otestován.", "Your system configuration does not currently support this feature. The \x3ca href=\"http://drupal.org/node/15365\"\x3ehandbook page on Clean URLs\x3c/a\x3e has additional troubleshooting information.": "Váš webový server nepodporuje tuto funkci. \x3ca href=\"http://drupal.org/node/15365\"\x3eVíce informací o Čistých URL\x3c/a\x3e", "Testing clean URLs...": "Testování serveru pro čistá URL...", "An HTTP error @status occurred. \n@uri": "Chyba HTTP: @status \r\n@uri", "Drag to re-order": "Pro přeskupení přetáhněte myší", "Changes made in this table will not be saved until the form is submitted.": "Změny provedené v této tabulce budou uloženy až po odeslání  formuláře.", "Select all rows in this table": "Označit všechny řádky v této tabulce", "Deselect all rows in this table": "Zrušit označení všech řádek v této tabulce", "Split summary at cursor": "Oddělit upoutávku pod kursorem", "Join summary": "Sloučit s upoutávkou", "An error occurred. \n@uri\n@text": "Nastala chyba.\r\n@uri\r\n@text", "An error occurred. \n@uri\n(no information available).": "Nastala chyba. \r\n@uri\r\n(nejsou k dispozici žádné informace)." } };