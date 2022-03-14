# InovativnyProjekt

Zdrojový kód pre inovatívny projekt "balikobox". Ide o inteligentnú krabicu pre balíky, do ktorých kurier doručí zásielku a príjemca si ju vyzdvihne z daného balikoboxu z pred domu.

# Zadanie:
  * Balikobox sa otvori po zadaní kódu generovaného na základe aktuálneho času z aplikácie bez pripojenia na iternet a systém otvorenia balikoboxu.

# Spracovanie:
  * Pre generovanie kódov sa použije hodinový modul, ktorý je najskôr potrebné nakonfigurovať na aktuálny čas ( pomocou programu "setTime.ino"). 
  * Pre overenie čítania vstupu použijeme program "keyTest_read.ino".
  * Po zadavaní jednotlivých čísel 6 miestneho kódu sa za sebou zobrazujú na displeji.
  * Ak bol zadaný kód zhodný s vygenerovaným kódom v arduine, potom sa balikobox otvori. Zopne sa relé modul a do solenoid zámku sa privedie napätie, ktoré nám balikobox otvori.

