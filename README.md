## Kompilacja i uruchomienie
Projekt można skompilować przy użyciu standardowego kompilatora C++ obsługującego standard C++17. 

Będąc w głównym katalogu projektu, wykonaj polecenie łączące wszystkie pliki źródłowe:
```bash
g++ src/*.cpp -o symulator -std=c++17
```

Następnie uruchom wygenerowany plik:
```bash
./symulator
```
## Jak grać (Sterowanie)
Po uruchomieniu programu zostaniesz poproszony o podanie wymiarów planszy (minimalnie 5x5). Świat wygeneruje się automatycznie, zaludniając siatkę zwierzętami i roślinami. 

Gracz wciela się w **Człowieka** (reprezentowanego przez literę `C`). Rozgrywka jest turowa.

**Klawiszologia:**
*   **Strzałki kierunkowe:** Ruch postacią na sąsiednie pole (wymusza walkę, jeśli pole jest zajęte).
*   **M:** Aktywacja specjalnej umiejętności "Całopalenie" (obszarowe zniszczenie wszystkich sąsiadów). Umiejętność trwa 5 tur, po czym wymaga 5 tur odnowienia.
*   **ENTER:** Zignorowanie ruchu (czekanie w miejscu).
*   **Z:** Zapisanie aktualnego stanu gry (tworzy plik `zapis.txt`).
*   **W:** Wczytanie ostatniego zapisu gry.
*   **ESC:** Natychmiastowe wyjście z symulacji.

*Uwaga: Interfejs i sterowanie strzałkami zostały zoptymalizowane pod terminale systemów UNIX (macOS/Linux).*