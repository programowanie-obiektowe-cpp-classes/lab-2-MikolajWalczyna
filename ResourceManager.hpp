#pragma once

#include "Resource.hpp"

class ResourceManager {
private:
    Resource* managedResource;
    
public:
    ResourceManager()
    {
        managedResource = new Resource();
        // Konstruktor domyślny
    }

    ~ResourceManager() {
        delete managedResource;
        // Destruktor
    }

    /*
    Podsumowując, jako argumenty funkcji (w tym metod klas) możemy przyjąć:

    Stałe referencje (const T&), jeżeli nie potrzebujemy modyfikować danego argumentu, a jedynie dokonać jego inspekcji. Nie wykonujemy wtedy kopii obiektu.
    Ta opcja potrafi obsłużyć także sytuację, w której użytkownik poda do funkcji obiekt tymczasowy.
    Referencję lvalue (T&), jeżeli chcemy zmodyfikować w funkcji obiekt spoza niej.
    Tej opcji raczej nie stosujemy, gdyż może ona prowadzić do bugów (niechcący podajemy argument, którego wcale nie chcieliśmy modyfikować).
    Zamiast tego korzystamy z argumentów wyjściowych. a = fun(a); bardziej jawnie wyraża nasze intencje niż fun(a);
    Referencję rvalue (T&&), gdy chcemy obsłużyć sytuację, w której nasza funkcja przejmuje własność nad jakimś obiektem.
    Często stosujemy tę opcję obok innych przeciążeń (np. obok stałej referencji) jako optymalizacja dla szczególnego przypadku.
*/
    ResourceManager(const ResourceManager& other) {
        managedResource = new Resource();
        *managedResource = *other.managedResource;
        // Konstruktor kopiujący - kopiujemy zarządzany zasób
    }

    ResourceManager& operator=(const ResourceManager& other) {
        // Operator przypisania - przypisujemy zarządzany zasób
        if (this != &other) {
            *managedResource = *other.managedResource;
        }
        return *this;
    }

    /*Słowo kluczowe noexcept w deklaracji konstruktora przenoszącego oznacza, że ten konstruktor nie generuje wyjątków.
    W praktyce oznacza to, że jeśli konstruktor przenoszący wywoła wyjątek, program zostanie zakończony natychmiast, a komunikat o błędzie zostanie wyświetlony.
    Użycie noexcept ma na celu zwiększenie efektywności, ponieważ kompilator może zoptymalizować kod w przypadku, gdy wiadomo, że funkcja nie generuje wyjątków.

    W kontekście konstruktora przenoszącego w klasie ResourceManager, noexcept jest używane, aby oznaczyć, że operacja przenoszenia zarządzanego zasobu nie powinna generować wyjątków.
    Działa to jako informacja dla kompilatora i optymalizatora, co może poprawić wydajność programu w przypadku operacji przenoszenia.*/

    ResourceManager(ResourceManager&& other) {
        // Konstruktor przenoszący - przenosimy zarządzany zasób
        managedResource = (other.managedResource);
        other.managedResource = nullptr;
    }

    ResourceManager& operator=(ResourceManager&& other) noexcept {
        // Operator przypisania przenoszący - przenosimy zarządzany zasób
        delete managedResource;
        managedResource = other.managedResource;
        other.managedResource = nullptr;
    }

    double get() {
        // Delegujemy wywołanie do metody get zarządzanego zasobu
        return resource.get();
    }
};
