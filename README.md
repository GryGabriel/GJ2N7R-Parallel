
Féléves feladat:
- C nyelven POSIX és OpenMP függvénykönyvtárakkal, valamint Javascript nyelven Web worker-ek segítségével valósítom meg a könyvkódolás nevű titkosítást.

 - A kódolás algoritmusa:
    - A könyvkódolás régen úgy működött, hogy az üzenet írójának és címzettjének is megvolt ugyanaz a könyv, ugyanabban a kiadásban. Az üzenet kódolásához kiválasztottak egy oldalt a könyvből. 
    Ez a program esetében egy fájlba írt szöveg lesz.
    -  Betűk helyett számokból állnak az üzenetek. Minden betűt két szám helyettesít. Az első azt jelzi, hogy hanyadik sorban van a betű, a második a betű helyét a sorban.
    A számsorozatot a program paraméterként kapja meg, majd ezt fejti vissza a szöveg alapján. 

 - A három módszeren kívül szekvenciálisan is megoldom a titkosítást, majd ezeket futási idejük alapján hasonlítom össze különböző üzenet- és szál méretek mellett.

