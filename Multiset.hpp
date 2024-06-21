/**
 * @file Multiset.hpp
 * @author Marcaccio Riccardo
 * @date 2024-06-09 
 */

#ifndef HEADER_MULTISET
#define HEADER_MULTISET

#include <iostream> 

/**
 * @brief Classe templata che rappresenta un Multiset.
 * 
 * Classe multiset che rappresenta un insieme di elementi T ordinati.
 * 
 * @tparam T Tipo degli elementi nel Multiset.
 */
template <typename T> 
class Multiset 
{

public:

    /**
     * @brief Struttura che identifica le coppie valori-occorrenze.
     * 
     * Struttura pubblica 'Pair' che contiene i dati relativi all'elemento di tipo T
     * e numero delle sue occorrenze nello stesso oggetto di classe Multiset.
     * 
     */
    struct Pair {
        const T value; ///< Valore di tipo T.
        int occourences; ///< Numero di occorrenze del valore.

        /**
         * @brief Costruttore della struttura Pair.
         * 
         * Costruttore che inizializza il valore di base e le sue occorrenze.
         * 
         * @param val Valore iniziale della coppia.
         * 
         * @post value = val
         * @post occourences = 1
         */
        Pair(T val) : value(val), occourences(1) {}

        /**
         * @brief Operatore di output per la struttura Pair.
         * @param os Stream di output.
         * @param pr Struttura Pair da stampare.
         * @return Riferimento allo stream di output.
         */
        friend std::ostream& operator<<(std::ostream &os, const typename Multiset<T>::Pair &pr) {
            os << "<" << pr.value << ", " << pr.occourences << ">";
            return os;
        }
    };

private:

    /**
     * @brief Nodo che contiene una Pair e un puntatore al nodo successivo.
     * 
     * Un Multiset viene implementato attraverso una lista a puntatori di tipo
     * Pair_node, contentente una Pair e un puntatore nodo successivo.
     */
    struct Pair_node {
        Pair p; ///< Coppia valori-occorrenze.
        Pair_node *next; ///< Puntatore al nodo successivo.

        /**
         * @brief Costruttore del nodo.
         * 
         * Costruttore della struttura Pair_node che inizializza il valore richiamando il
         * costruttore base dello struct Pair e il puntatore del nodo successivo a nx.
         * 
         * @param val Valore iniziale della coppia.
         * @param nx Puntatore al nodo successivo.
         * 
         * @post p = pair(val)
         * @post next = nx
         */
        Pair_node(T val, Pair_node* nx) : p(val), next(nx) {}

        /**
         * @brief Restituisce il valore della coppia.
         * 
         * Metodo getter per il valore contenuto nella Pair appartente al nodo corrente. Implementato per migliorare
         * la leggibilita` complessiva del codice.
         * 
         * @return Valore di tipo T.
         */
        T get_value() const { return p.value; }

        /**
         * @brief Restituisce il numero di occorrenze del valore.
         * 
         * Metodo getter per il numero di occorrenze contenuto nella Pair appartente al nodo corrente. Implementato 
         * per migliorare la leggibilita` complessiva del codice.
         * 
         * @return Numero di occorrenze.
         */
        int get_occourences() const { return p.occourences; }
    };

    Pair_node *head; ///< Puntatore alla testa della lista a puntatori Pair_node.

public:

    /**
     * @brief Costruttore di default.
     * 
     * Costruttore di default che inzializza il puntatore di testa a 'nullptr'.
     * 
     * @post head = nullptr
     */
    Multiset() : head(nullptr) {}  

    /**
     * @brief Costruttore che crea un Multiset da una coppia di iteratori.
     * 
     * Costruttore che, a partire da due iteratori di un tipo generico Q, inizializza
     * un Multiset aggiungendo man mano gli elementi.
     * 
     * @tparam Q Tipo degli iteratori.
     * @param its Iteratore iniziale.
     * @param ite Iteratore finale.
     * @post Gli elementi nell'intervallo [its, ite) sono aggiunti al Multiset.
     * @throws ... Errore durante la costruzione del nuovo Multiset.
     * @note In caso di eccezioni durante la costruzione del Multiset, la struttura viene cancellata e l'eccezione viene lanciata.
     */
    template <typename Q> 
    Multiset(Q its, Q ite) : head(nullptr) {
        try{
            for(; its != ite; its++)
                add(*its);
        }catch(...){
            clear();
            std::cerr << "Errore durante la costruzione del Multiset." << std::endl;
            throw;
        }
    }

    /**
     * @brief Costruttore di copia.
     * 
     * Costruttore che inzializza un Multiset a partire da un altro oggetto della stessa classe.
     * I due oggetti sono uno la copia dell'altro, rimamendo allocati in due zone separate.
     * 
     * @param other Multiset da copiare.
     * @post Il nuovo Multiset è una copia di `other`.
     */
    Multiset(const Multiset<T> &other) : head(nullptr) {
        *this = other;
    }

    /**
     * @brief Distruttore.
     * 
     * Distruttore della classe che si occupa di svuotare la lista e reimpostare la testa a nullptr.
     * Porta a termine i suoi compiti attraverso la chiamata ad una funzione 'clear()' privata.
     * 
     * @post head = nullptr.
     */
    ~Multiset() {
        clear();
    }

    /**
     * @brief Operatore di assegnamento.
     * 
     * Operatore che permette l'assegnamento di un oggetto Multiset ad un altro.
     * Questa operazione viene effettuata liberando prima il Multiset di destinazione
     * e successivamente aggiungendo elemento per elemento.
     * 
     * @param Y Multiset da assegnare.
     * @return Riferimento al Multiset assegnato.
     * @post Il Multiset corrente è una copia di `Y`.
     * @throws ... Errore durante la costruzione del nuovo Multiset.
     * @note In caso di eccezioni durante la costruzione del Multiset, la struttura viene cancellata e l'eccezione viene lanciata.
     */
    Multiset<T> &operator= (const Multiset<T> &Y) 
    {   
        if(&Y != this) 
        {
            try{
                clear();
                Pair_node *other_ptr = Y.head;
                while(other_ptr != nullptr)
                {
                    for(int i = 0;i < other_ptr->get_occourences(); i++)
                        (*this).add(other_ptr->get_value());
                    other_ptr = other_ptr->next;
                }
            }catch(...){
                clear();
                std::cerr << "Errore durante la copia del Multiset." << std::endl;
                throw;
            }

        }
        return *this;             
    }

    /**
     * @brief Operatore di confronto.
     * 
     * Operatore che confronta due oggetti di tipo Multiset.
     * 
     * @param ms Multiset con cui confrontare.
     * @return true se i Multiset sono uguali.
     */
    bool operator== (const Multiset<T> &ms) const 
    {
        Pair_node *curr_ptr = this->head;
        Pair_node *other_ptr = ms.head;

        while(curr_ptr != nullptr && other_ptr != nullptr) 
        {
            if(curr_ptr->get_value()!=other_ptr->get_value() || curr_ptr->get_occourences()!=other_ptr->get_occourences())
                return false;

            curr_ptr = curr_ptr->next;
            other_ptr = other_ptr->next;            
        }
        return (curr_ptr == nullptr && other_ptr == nullptr);
    }

    /**
     * @brief Iteratore costante per il Multiset.
     */
    class const_iterator {
        Pair_node *ptr;
        friend class Multiset;

        explicit const_iterator(Pair_node* dt) : ptr(dt) {}

    public:
        const_iterator() : ptr(0) {}
        const_iterator(const const_iterator &other) : ptr(other.ptr) {}
        const_iterator& operator= (const const_iterator &other) { ptr = other.ptr; return *this; }
        const Pair& operator* () const { return ptr->p; }
        const Pair* operator-> () const { return &(ptr->p); }
        const_iterator& operator++ () { ptr = ptr->next; return *this; }
        const_iterator operator++ (int) { Pair_node *p=ptr; ptr = ptr->next; return const_iterator(p); }
        bool operator== (const const_iterator &ot) const { return (ptr == ot.ptr); }
        bool operator!= (const const_iterator &ot) const { return (ptr != ot.ptr); }


    };

    /**
     * @brief Restituisce un iteratore costante all'inizio del Multiset.
     * @return Iteratore costante all'inizio del Multiset.
     */
    const_iterator begin() const { return const_iterator(head); }

    /**
     * @brief Restituisce un iteratore costante alla fine del Multiset.
     * @return Iteratore costante alla fine del Multiset.
     */
    const_iterator end() const { return const_iterator(nullptr); }

    /**
     * @brief Aggiunge un valore al Multiset.
     * 
     * Metodo per aggiungere valori in un Multiset. Se il valore e` gia` presente, viene incrementato il
     * valore delle occorrenze; altrimenti viene inserito il valore con numero di occorrenze a 1.
     * 
     * @param val Valore da aggiungere.
     * @return true se l'aggiunta è avvenuta con successo.
     * @post Il valore `val` è aggiunto al Multiset. Se il valore esiste già, incrementa il numero delle sue occorrenze.
     * @throws ... Se si verifica un problema durante l'aggiunta di valori nel Multiset.
     * @note Il metodo potrebbe lanciare delle eccezioni, e` consigliabile gestirle nel codice che utilizza questo metodo.
     */
    bool add(T val) {
        Pair_node *pos_node = relative_pos(val);
    
        if(pos_node == nullptr) {
            if(head != nullptr && head->get_value() == val) // aggiunta occorrenza in testa
                head->p.occourences++;
            else // inserimento elemento nuovo in testa
                head = new Pair_node(val, head);
            return true;
        } else {
            if(pos_node->next != nullptr && pos_node->next->get_value() == val) // aggiunta occorrenza in lista
                pos_node->next->p.occourences++;
            else // inserimento elemento in lista
                pos_node->next = new Pair_node(val, pos_node->next);
            return true;
        }
        return false;
    }

    /**
     * @brief Rimuove un valore dal Multiset.
     * 
     * Metodo per rimuovere un'occorrenza con valore a 'val' dal Multiset. Se il valore delle 
     * occorrenze arriva a 0, il valore viene definitivamente rimosso
     * 
     * @param val Valore da rimuovere.
     * @return true se la rimozione è avvenuta con successo.
     * @post Il valore delle occorenze con valore uguale a `val` è deincrementato. Se il numero delle occorrenze diventa zero, il valore è completamente rimosso.
     */
    bool remove(T val) {
        Pair_node *prev = relative_pos(val), *curr = nullptr;
        if(prev != nullptr && prev->next != nullptr && prev->next->get_value() == val) // rimozione di un valore in lista
            curr = prev->next;
        else if(prev == nullptr && head != nullptr && head->get_value() == val) // rimozione di un valore in testa
            curr = head;
        else
            return false;
        
        if(--curr->p.occourences == 0) {
            if(prev == nullptr)
                head = curr->next;
            else
                prev->next = curr->next;
            delete curr;
        }
        return true;
    }

    /**
     * @brief Verifica se un valore è presente nel Multiset.
     * 
     * Se nel Multiset e` presente un nodo con valore uguale a 'val' e occorrenze > 0, ritorna true.
     * 
     * @param val Valore da cercare.
     * @return true se il valore è presente, false altrimenti.
     */
    bool contains(T val) const {
        return occourences_by_value(val);
    }

    /**
     * @brief Restituisce il numero di occorrenze di un valore nel Multiset.
     * 
     * Cerca il valore nel multiset e restituisce il numero delle sue occorrenze.
     * 
     * @param val Valore da cercare.
     * @return Numero di occorrenze del valore.
     */
    int occourences_by_value(T val) const {
        Pair_node *curr = head;
        while(curr != nullptr) {
            if(curr->get_value() == val)
                return curr->get_occourences();
            curr = curr->next;
        }
        return 0;
    }

    /**
     * @brief Restituisce la somma totale delle occorrenze in un Multiset.
     * 
     * Per ogni valore presente nel Multiset, una variabile temporanea viene incrementata del suo numero
     * di occorrenze.
     * 
     * @return Numero totale delle occorrenze.
     */
    int total_occourences() const  
    {
        Pair_node *curr = head;
        int tot_o = 0;
        while(curr != nullptr)
        {
            tot_o += curr->get_occourences();
            curr = curr->next;
        }
        return tot_o;
    }

    /**
     * @brief Restituisce il numero di valori unici nel Multiset.
     * 
     * Per ogni valore presente nel Multiset, una variabile temporanea viene incrementata di 1.
     * 
     * @return Numero totale di valori.
     */
    int total_values() const   
    {  
        Pair_node *curr = head;
        int counter = 0;
        while(curr != nullptr)
        {
            counter++;
            curr = curr->next;
        }
        return counter;
    }

private:

    /**
     * @brief Trova il nodo che precede l'elemento con il valore dato.
     * 
     * Scorre gli elementi presenti nel Multiset, ritornando un puntatore al nodo che precede 
     * l'elemento con il valore dato.
     * 
     * @param val Valore da cercare.
     * @return Puntatore al nodo che precede l'elemento con il valore dato.
     */
    Pair_node* relative_pos(T val) const {
        Pair_node *prev = nullptr, *curr = head;
        while(curr != nullptr && curr->get_value() < val) {
            prev = curr;
            curr = curr->next;
        }
        return prev;
    }

    /**
     * @brief Cancella tutti gli elementi in un Multiset e imposta la testa a nullptr.
     * 
     * @post head = nullptr.
     */
    void clear(){
        Pair_node *curr = this->head, *next;
        while(curr != nullptr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
    }
};

/**
 * @brief Operatore di output per il Multiset.
 * @param os Stream di output.
 * @param ms Multiset da stampare.
 * @return Riferimento allo stream di output.
 * @post Il contenuto del Multiset `ms` è stampato sullo stream `os`.
 */
template <typename T> 
std::ostream& operator<<(std::ostream &os, const Multiset<T> &ms)
{
    
    typename Multiset<T>::const_iterator it = ms.begin();
    os << ms.total_values();
    for(; it != ms.end(); ++it) {
        os <<", "<< *it;
    }
    os << std::endl;
    return os;
}

#endif
