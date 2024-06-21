#ifndef HEADER_CLASSEITERATORS
#define HEADER_CLASSEITERATORS
#include <iostream>

/**
 * @class ClasseIterators
 * @brief Una classe template che implementa un semplice contenitore con iteratori.
 *
 * Questa classe fornisce un semplice contenitore che alloca un array di tipo T
 * e fornisce funzionalità di iteratore per scorrere gli elementi. La classe e` stata implementata
 * per avere una generica sequenza di dati, identificata da una coppia di iteratori al fine di 
 * effettuare test sulla classe multiset. Sono stati implementati solo i metodi necessari allo
 * svolgimento dei test.
 *
 * @tparam T Il tipo di elementi memorizzati nel contenitore.
 */
template <typename T>
class ClasseIterators {
public:
    T *ptr;  ///< Puntatore all'array allocato dinamicamente di tipo T.
    int size;  ///< La dimensione dell'array.

    /**
     * @brief Definizione del tipo per un iteratore.
     */
    typedef T* iterator;

    /**
     * @brief Costruttore che alloca un array della dimensione data.
     *
     * Questo costruttore inizializza il contenitore con un array della dimensione specificata.
     * Se la dimensione è 0, non viene allocata memoria.
     *
     * @param _size La dimensione dell'array da allocare. Il valore predefinito è 10.
     */
    ClasseIterators(unsigned int _size = 10) : ptr(nullptr) {
        if(_size != 0)
            ptr = new T[_size];
        size = _size;
    }

    /**
     * @brief Distruttore che dealloca l'array.
     *
     * Il distruttore libera la memoria allocata per l'array.
     */
    ~ClasseIterators() { delete[] ptr; }

    /**
     * @brief Restituisce un iteratore all'inizio dell'array.
     *
     * Questa funzione restituisce un puntatore al primo elemento dell'array.
     *
     * @return Un iteratore che punta al primo elemento dell'array.
     */
    iterator begin() const { return ptr; }

    /**
     * @brief Restituisce un iteratore alla fine dell'array.
     *
     * Questa funzione restituisce un puntatore all'elemento successivo all'ultimo elemento
     * dell'array.
     *
     * @return Un iteratore che punta all'elemento successivo all'ultimo elemento dell'array.
     */
    iterator end() const { return (ptr == nullptr) ? ptr : ptr + size; }
};

#endif
