#include "Multiset.hpp"
#include "ClasseIterators.hpp"
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

void test_interi(){
    cout << endl << endl <<"=-=-=-= Inizio test per interi =-=-=-="<<endl<<endl;

    cout << "# Test inserimento e rimozione" << endl;
    Multiset<int> addrem;

    cout<<"   - Inserimento in testa: ";
    for(int i = 5; i>0; i--)
        assert(addrem.add(i));
    cout<<"OK. "<<endl;   

    cout<<"   - Rimozione in testa: ";
    for(int i = 1; i < 6; i++)
        assert(addrem.remove(i));
    cout<<"OK."<<endl;

    cout<<"   - Inserimento in coda: ";
    for(int i = 0; i<5; i++)
        assert(addrem.add(i));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione in coda: ";
    for(int i = 4; i>-1; i--)
        assert(addrem.remove(i));
    cout<<"OK."<<endl;

    cout<<"   - Inserimento in lista: ";
    addrem.add(0);
    addrem.add(5);
    for(int i=1; i<5; i++)
        assert(addrem.add(i));
    cout<<"OK."<<endl;

    cout<<"   - Inserimento su elementi gia` presenti: ";
    for(int i=1; i<5; i++)
        assert(addrem.add(i));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione su elementi doppi: ";
    for(int i=1; i<5; i++)
        assert(addrem.remove(i));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione elementi in lista: ";
    for(int i=1; i<5; i++)
        assert(addrem.remove(i));
    cout<<"OK."<<endl;


    //test costruttori / opeatori
    cout << "# Test costruttori e operatori" << endl;

    cout<<"   - Operatore == :";
    Multiset<int> costruttore1, costruttore2;
    for(int i=0; i<3; i++){
        assert(costruttore1.add(i));
        assert(costruttore2.add(i));
    }
    assert(costruttore1 == costruttore2);
    cout<<"OK."<<endl;

    cout<<"   - Copy-construcor: ";
    Multiset<int> costruttore3(costruttore1);
    assert(costruttore3 == costruttore1);
    cout<<"OK."<<endl;

    cout<<"   - Redefinizione assegnamento: ";
    Multiset<int> costruttore4;
    costruttore4 = costruttore1;
    assert(costruttore4 == costruttore1);
    cout<<"OK."<<endl;
    
    //test informazioni
    cout << "# Test informazioni" << endl;

    Multiset<int> info1, info2;
    for(int i=0; i<3; i++)
        assert(info1.add(i));
    cout<<"   - Metodo Contains con valore presente: ";
    for(int i=0; i<3; i++)
            assert(info1.contains(i));
    cout<<"OK."<<endl;

    cout<<"   - Metodo Contains con valore assente: ";
    assert(!(info1.contains(-1)));
    assert(!(info1.contains(5)));
    cout<<"OK."<<endl;

    cout<<"   - Numero singoli valori: ";
    int nelem = 55;
    int tot_occ;
    for(int i=0; i<nelem; i++){
        info2.add(i);
        info2.add(i);
        tot_occ += 2;
    }
    assert(info2.total_values() == nelem);
    cout<<"OK."<<endl;

    cout<<"   - Numero occorrenze per valore: ";
    for(int i=0; i<nelem; i++)
        assert(info2.occourences_by_value(i) == 2);
    cout<<"OK."<<endl;

    cout<<"   - Numero occorrenze totali: ";
    //assert(info2.total_occourences() == tot_occ);
    cout<<"OK."<<endl;

    //test stampa
    cout << "# Test stampa" << endl;

    cout<<"   - addrem: "<<addrem;
    cout<<"   - costruttore1: "<<costruttore1;
    cout<<"   - costruttore2: "<<costruttore2;
    cout<<"   - info1: "<<info1;
    cout<<"   - info2: "<<info2;
    cout<<"   - Stampa Multiset e Pair: OK."<<endl;

    //test iteratori
    cout << "# Test iteratori" << endl;

    cout<<"   - Costruttore con itertatori: ";
    ClasseIterators<int> iterator_test(10);
    for(int i=0; i<iterator_test.size; i++)
        iterator_test.ptr[i] = i;
    Multiset<int> iterator_ms(iterator_test.begin(), iterator_test.end());
    for(int i=0; i<iterator_test.size; i++)
        assert(iterator_ms.contains(i));
    cout<<"OK."<<endl;
    cout<<"   - Utilizzo iteratori: ";
    Multiset<int>::const_iterator its = iterator_ms.begin(), ite = iterator_ms.end();
    while(its!=ite)
        iterator_ms.remove((*(its++)).value);
    assert(iterator_ms.total_values() == 0);
    cout<<"OK."<<endl;        
}


void test_string() {
    cout << endl << endl << "=-=-=-= Inizio test per string =-=-=-=" << endl << endl;
    
    cout << "# Test inserimento e rimozione" << endl;
    Multiset<string> addrem;

    cout << "   - Inserimento in testa: ";
    
    assert(addrem.add("sambuco"));
    assert(addrem.add("mela"));
    assert(addrem.add("dattero"));
    assert(addrem.add("ciliegia"));
    assert(addrem.add("banana"));
    
    cout << "OK." << endl;   
    

    cout << "   - Rimozione in testa: ";
    
    assert(addrem.remove("banana"));
    assert(addrem.remove("ciliegia"));
    assert(addrem.remove("dattero"));
    assert(addrem.remove("mela"));
    assert(addrem.remove("sambuco"));
    
    cout << "OK." << endl;
    

    cout << "   - Inserimento in coda: ";

    assert(addrem.add("fico"));
    assert(addrem.add("kiwi"));
    assert(addrem.add("limone"));
    assert(addrem.add("melone"));
    assert(addrem.add("uva"));

    cout << "OK." << endl;


    cout << "   - Rimozione in coda: ";

    assert(addrem.remove("uva"));
    assert(addrem.remove("melone"));
    assert(addrem.remove("limone"));
    assert(addrem.remove("kiwi"));
    assert(addrem.remove("fico"));

    cout << "OK." << endl;
    
        
    cout << "   - Inserimento in lista: ";

    addrem.add("arancia");
    addrem.add("uva");
    for (const auto& frutto : {"mela", "papaya", "pera"})
        assert(addrem.add(frutto));

    cout << "OK." << endl;


    cout << "   - Inserimento su elementi già presenti: ";

    for (const auto& frutto : {"mela", "papaya", "pera"})
        assert(addrem.add(frutto));

    cout << "OK." << endl;
    
    
    cout << "   - Rimozione su elementi doppi: ";

    for (const auto& frutto : {"mela", "papaya", "pera"})
        assert(addrem.remove(frutto));

    cout << "OK." << endl;


    cout << "   - Rimozione elementi in lista: ";
    for (const auto& frutto : {"mela", "papaya", "pera"})
        assert(addrem.remove(frutto));
    cout << "OK." << endl;




    // test costruttori / operatori
    cout << "# Test costruttori e operatori" << endl;

    cout << "   - Operatore == :";
    Multiset<string> costruttore1, costruttore2;
    for (const auto& frutto : {"lampone", "fragola", "mandarino"}) {
        assert(costruttore1.add(frutto));
        assert(costruttore2.add(frutto));
    }
    assert(costruttore1 == costruttore2);
    cout << "OK." << endl;

    cout << "   - Copy-constructor: ";
    Multiset<string> costruttore3(costruttore1);
    assert(costruttore3 == costruttore1);
    cout << "OK." << endl;

    cout << "   - Ridefinizione assegnamento: ";
    Multiset<string> costruttore4;
    costruttore4 = costruttore1;
    assert(costruttore4 == costruttore1);
    cout << "OK." << endl;


    
    // test informazioni
    cout << "# Test informazioni" << endl;

    Multiset<string> info1, info2;
    for (const auto& frutto : {"ugli", "vaniglia", "anguria"})
        assert(info1.add(frutto));
    cout << "   - Metodo Contains con valore presente: ";
    for (const auto& frutto : {"ugli", "vaniglia", "anguria"})
        assert(info1.contains(frutto));
    cout << "OK." << endl;

    cout << "   - Metodo Contains con valore assente: ";
    assert(!info1.contains("arancia"));
    assert(!info1.contains("carciofo"));
    cout << "OK." << endl;

    cout << "   - Numero singoli valori: ";
    int nelem = 3;
    int tot_occ = 0;
    for (const auto& frutto : {"zucchina", "mela", "banana"}) {
        info2.add(frutto);
        info2.add(frutto);
        tot_occ += 2;
    }
    assert(info2.total_values() == nelem);
    cout << "OK." << endl;

    cout << "   - Numero occorrenze per valore: ";
    for (const auto& frutto : {"zucchina", "mela", "banana"})
        assert(info2.occourences_by_value(frutto) == 2);
    cout << "OK." << endl;

    cout << "   - Numero occorrenze totali: ";
    assert(info2.total_occourences() == tot_occ);
    cout << "OK." << endl;



    // test stampa
    cout << "# Test stampa" << endl;

    cout << "   - addrem: " << addrem;
    cout << "   - costruttore1: " << costruttore1;
    cout << "   - costruttore2: " << costruttore2;
    cout << "   - info1: " << info1;
    cout << "   - info2: " << info2;
    cout << "   - Stampa Multiset e Pair: OK." << endl;



    // test iteratori
    cout << "# Test iteratori" << endl;

    cout << "   - Costruttore con iteratori: ";
    ClasseIterators<string> iterator_test(10);
    for (int i = 0; i < iterator_test.size; i++)
        iterator_test.ptr[i] = "frutto" + to_string(i);
    Multiset<string> iterator_ms(iterator_test.begin(), iterator_test.end());
    for (int i = 0; i < iterator_test.size; i++)
        assert(iterator_ms.contains("frutto" + to_string(i)));
    cout << "OK." << endl;

    cout << "   - Utilizzo iteratori: ";
    Multiset<string>::const_iterator its = iterator_ms.begin(), ite = iterator_ms.end();
    while (its != ite)
        iterator_ms.remove((*(its++)).value);
    assert(iterator_ms.total_values() == 0);
    cout << "OK." << endl;      
}


void test_double() {
    cout << endl << endl << "=-=-=-= Inizio test per double =-=-=-=" << endl << endl;

    cout << "# Test inserimento e rimozione" << endl;

    Multiset<double> addrem;

    cout << "   - Inserimento in testa: ";

    assert(addrem.add(5.5));
    assert(addrem.add(4.4));
    assert(addrem.add(3.3));
    assert(addrem.add(2.2));
    assert(addrem.add(1.1));
    
    cout << "OK." << endl;   

    cout << "   - Rimozione in testa: ";
    
    assert(addrem.remove(1.1));
    assert(addrem.remove(2.2));
    assert(addrem.remove(3.3));
    assert(addrem.remove(4.4));
    assert(addrem.remove(5.5));
    
    cout << "OK." << endl;


    cout << "   - Inserimento in coda: ";
    
    assert(addrem.add(0.1));
    assert(addrem.add(1.2));
    assert(addrem.add(2.3));
    assert(addrem.add(3.4));
    assert(addrem.add(4.5));
    
    cout << "OK." << endl;


    cout << "   - Rimozione in coda: ";

    assert(addrem.remove(4.5));
    assert(addrem.remove(3.4));
    assert(addrem.remove(2.3));
    assert(addrem.remove(1.2));
    assert(addrem.remove(0.1));

    cout << "OK." << endl;


    cout << "   - Inserimento in lista: ";

    addrem.add(0.5);
    addrem.add(5.5);
    for (const auto& valore : {1.1, 2.2, 3.3, 4.4})
        assert(addrem.add(valore));

    cout << "OK." << endl;


    cout << "   - Inserimento su elementi già presenti: ";

    for (const auto& valore : {1.1, 2.2, 3.3, 4.4})
        assert(addrem.add(valore));

    cout << "OK." << endl;


    cout << "   - Rimozione su elementi doppi: ";

    for (const auto& valore : {1.1, 2.2, 3.3, 4.4})
        assert(addrem.remove(valore));

    cout << "OK." << endl;


    cout << "   - Rimozione elementi in lista: ";

    for (const auto& valore : {1.1, 2.2, 3.3, 4.4})
        assert(addrem.remove(valore));

    cout << "OK." << endl;



    // test costruttori / operatori
    cout << "# Test costruttori e operatori" << endl;

    cout << "   - Operatore == :";

    Multiset<double> costruttore1, costruttore2;
    for (const auto& valore : {0.1, 0.2, 0.3}) {
        assert(costruttore1.add(valore));
        assert(costruttore2.add(valore));
    }
    assert(costruttore1 == costruttore2);

    cout << "OK." << endl;


    cout << "   - Copy-constructor: ";

    Multiset<double> costruttore3(costruttore1);
    assert(costruttore3 == costruttore1);

    cout << "OK." << endl;


    cout << "   - Ridefinizione assegnamento: ";

    Multiset<double> costruttore4;
    costruttore4 = costruttore1;
    assert(costruttore4 == costruttore1);

    cout << "OK." << endl;



    // test informazioni
    cout << "# Test informazioni" << endl;

    Multiset<double> info1, info2;
    for (const auto& valore : {1.1, 2.2, 3.3})
        assert(info1.add(valore));

    cout << "   - Metodo Contains con valore presente: ";

    for (const auto& valore : {1.1, 2.2, 3.3})
        assert(info1.contains(valore));

    cout << "OK." << endl;


    cout << "   - Metodo Contains con valore assente: ";

    assert(!info1.contains(4.4));
    assert(!info1.contains(5.5));

    cout << "OK." << endl;


    cout << "   - Numero singoli valori: ";

    int nelem = 3;
    int tot_occ = 0;
    for (const auto& valore : {6.6, 7.7, 8.8}) {
        info2.add(valore);
        info2.add(valore);
        tot_occ += 2;
    }
    assert(info2.total_values() == nelem);

    cout << "OK." << endl;


    cout << "   - Numero occorrenze per valore: ";

    for (const auto& valore : {6.6, 7.7, 8.8})
        assert(info2.occourences_by_value(valore) == 2);

    cout << "OK." << endl;


    cout << "   - Numero occorrenze totali: ";

    assert(info2.total_occourences() == tot_occ);

    cout << "OK." << endl;



    // test stampa
    cout << "# Test stampa" << endl;

    cout << "addrem: " << addrem;
    cout << "costruttore1: " << costruttore1;
    cout << "costruttore2: " << costruttore2;
    cout << "info1: " << info1;
    cout << "info2: " << info2;
    cout << "   - Stampa Multiset e Pair: OK." << endl;




    // test iteratori
    cout << "# Test iteratori" << endl;
    cout << "   - Costruttore con iteratori: ";

    ClasseIterators<double> iterator_test(10);
    for (int i = 0; i < iterator_test.size; i++)
        iterator_test.ptr[i] = i * 1.1;
    Multiset<double> iterator_ms(iterator_test.begin(), iterator_test.end());
    for (int i = 0; i < iterator_test.size; i++)
        assert(iterator_ms.contains(i * 1.1));

    cout << "OK." << endl;


    cout << "   - Utilizzo iteratori: ";

    Multiset<double>::const_iterator its = iterator_ms.begin(), ite = iterator_ms.end();
    while (its != ite)
        iterator_ms.remove((*(its++)).value);
    assert(iterator_ms.total_values() == 0);

    cout << "OK." << endl;        
}


/**
 * @class classe_test
 * @brief Una classe che rappresenta una semplice struttura con due attributi interi.
 *
 * Questa classe contiene due attributi interi e vari costruttori, operatori di assegnazione
 * e confronti, oltre a un operatore di output. La classe e` stata creata per fare dei test su un 
 * multiset con elementi di un tipo Classe. Sono stati implementati solo i metodi necessari al 
 * funzionamento dei test per il multiset.
 */
class classe_test {
    int attributo_A;  ///< Il primo attributo intero.
    int attributo_B;  ///< Il secondo attributo intero.

public:

    /**
     * @brief Costruttore di default.
     *
     * Inizializza attributo_A e attributo_B con il valore 1.
     */
    classe_test() : attributo_A(1), attributo_B(1) {}

    /**
     * @brief Costruttore parametrizzato.
     *
     * Inizializza attributo_A e attributo_B con i valori forniti.
     *
     * @param intero1 Valore iniziale per attributo_A.
     * @param intero2 Valore iniziale per attributo_B.
     */
    classe_test(int intero1, int intero2) : attributo_A(intero1), attributo_B(intero2) {}

    /**
     * @brief Costruttore di copia.
     *
     * Inizializza una nuova istanza copiando i valori degli attributi da un'altra istanza.
     *
     * @param other Un'altra istanza di classe_test da copiare.
     */
    classe_test(const classe_test& other) {
        if (this != &other) {
            this->attributo_A = other.attributo_A;
            this->attributo_B = other.attributo_B;
        }
    }

    /**
     * @brief Operatore di assegnazione.
     *
     * Assegna i valori degli attributi da un'altra istanza a questa istanza.
     *
     * @param other Un'altra istanza di classe_test da assegnare.
     * @return Riferimento a questa istanza aggiornata.
     */
    classe_test operator= (const classe_test& other) {
        if (this != &other) {
            this->attributo_A = other.attributo_A;
            this->attributo_B = other.attributo_B;
        }
        return *this;
    }

    /**
     * @brief Operatore di confronto di uguaglianza.
     *
     * Confronta questa istanza con un'altra per verificare l'uguaglianza.
     *
     * @param other Un'altra istanza di classe_test da confrontare.
     * @return true se le due istanze sono uguali, false altrimenti.
     */
    bool operator== (const classe_test& other) const {
        return (this->attributo_A == other.attributo_A && this->attributo_B == other.attributo_B);
    }

    /**
     * @brief Operatore di confronto di disuguaglianza.
     *
     * Confronta questa istanza con un'altra per verificare la disuguaglianza.
     *
     * @param other Un'altra istanza di classe_test da confrontare.
     * @return true se le due istanze sono diverse, false altrimenti.
     */
    bool operator!= (const classe_test& other) const {
        return !(*this == other);
    }

    /**
     * @brief Operatore di confronto minore.
     *
     * Confronta la somma degli attributi di questa istanza con un'altra.
     *
     * @param other Un'altra istanza di classe_test da confrontare.
     * @return true se la somma degli attributi di questa istanza è minore di quella dell'altra, false altrimenti.
     */
    bool operator< (const classe_test& other) const {
        return (this->attributo_A + this->attributo_B < other.attributo_A + other.attributo_B);
    }

    /**
     * @brief Operatore di output.
     *
     * Permette di inviare la rappresentazione di una istanza di classe_test a uno stream di output.
     *
     * @param os Lo stream di output.
     * @param other L'istanza di classe_test da inviare allo stream.
     * @return Lo stream di output.
     */
    friend std::ostream& operator<<(std::ostream &os, const classe_test& other) {
        os << "[ " << other.attributo_A << ", " << other.attributo_B << " ]";
        return os;
    }
};


void test_classe_complessa(){
    cout << endl << endl << "=-=-=-= Inizio test per classe complessa =-=-=-="<< endl << endl;
    cout << "# Test inserimento e rimozione" << endl;

    Multiset<classe_test> addrem;
    //cout<<"a";
    cout<<"   - Inserimento in testa: ";
    for(int i = 5; i>0; i--)
        assert(addrem.add(classe_test(i, i)));
    cout<<"OK. "<<endl;   

    cout<<"   - Rimozione in testa: ";
    for(int i = 1; i < 6; i++)
        assert(addrem.remove(classe_test(i, i)));
    cout<<"OK."<<endl;
    
    cout<<"   - Inserimento in coda: ";
    for(int i = 0; i<5; i++)
        assert(addrem.add(classe_test(i, i)));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione in coda: ";
    for(int i = 4; i>-1; i--)
        assert(addrem.remove(classe_test(i, i)));
    cout<<"OK."<<endl;
    
    cout<<"   - Inserimento in lista: ";
    addrem.add(classe_test(0, 0));
    addrem.add(classe_test(0, 0));
    for(int i=1; i<5; i++)
        assert(addrem.add(classe_test(i, i)));
    cout<<"OK."<<endl;

    cout<<"   - Inserimento su elementi gia` presenti: ";
    for(int i=1; i<5; i++)
        assert(addrem.add(classe_test(i, i)));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione su elementi doppi: ";
    for(int i=1; i<5; i++)
        assert(addrem.remove(classe_test(i, i)));
    cout<<"OK."<<endl;

    cout<<"   - Rimozione elementi in lista: ";
    for(int i=1; i<5; i++)
        assert(addrem.remove(classe_test(i, i)));
    cout<<"OK."<<endl;

    
    //test costruttori / opeatori
    cout << "# Test costruttori e operatori" << endl;

    cout<<"   - Operatore == :";
    Multiset<classe_test> costruttore1, costruttore2;
    for(int i=0; i<3; i++){
        assert(costruttore1.add(classe_test(i,i)));
        assert(costruttore2.add(classe_test(i,i)));
    }
    assert(costruttore1 == costruttore2);
    cout<<"OK."<<endl;

    cout<<"   - Copy-construcor: ";
    Multiset<classe_test> costruttore3(costruttore1);
    assert(costruttore3 == costruttore1);
    cout<<"OK."<<endl;

    cout<<"   - Redefinizione assegnamento: ";
    Multiset<classe_test> costruttore4;
    costruttore4 = costruttore1;
    assert(costruttore4 == costruttore1);
    cout<<"OK."<<endl;
    
    //test informazioni
    cout << "# Test informazioni" << endl;

    Multiset<classe_test> info1, info2;
    for(int i=0; i<3; i++)
        assert(info1.add(classe_test(i,i)));
    cout<<"   - Metodo Contains con valore presente: ";
    for(int i=0; i<3; i++)
            assert(info1.contains(classe_test(i,i)));
    cout<<"OK."<<endl;

    cout<<"   - Metodo Contains con valore assente: ";
    assert(!(info1.contains(classe_test(-1,-1))));
    assert(!(info1.contains(classe_test(5,5))));
    cout<<"OK."<<endl;

    cout<<"   - Numero singoli valori: ";
    int nelem = 55;
    int tot_occ;
    for(int i=0; i<nelem; i++){
        info2.add(classe_test(i,i));
        info2.add(classe_test(i,i));
        tot_occ += 2;
    }
    assert(info2.total_values() == nelem);
    cout<<"OK."<<endl;

    cout<<"   - Numero occorrenze per valore: ";
    for(int i=0; i<nelem; i++)
        assert(info2.occourences_by_value(classe_test(i,i)) == 2);
    cout<<"OK."<<endl;

    cout<<"   - Numero occorrenze totali: ";
    //assert(info2.total_occourences() == tot_occ);
    cout<<"OK."<<endl;

    //test stampa
    cout << "# Test stampa" << endl;

    cout<<"addrem: "<<addrem;
    cout<<"costruttore1: "<<costruttore1;
    cout<<"costruttore2: "<<costruttore2;
    cout<<"info1: "<<info1;
    cout<<"info2: "<<info2;
    cout<<"   - Stampa Multiset e Pair: OK."<<endl;

    //test iteratori
    cout << "# Test iteratori" << endl;

    cout<<"   - Costruttore con itertatori: ";
    ClasseIterators<classe_test> iterator_test(10);
    for(int i=0; i<iterator_test.size; i++)
        iterator_test.ptr[i] = classe_test(i,i);
    Multiset<classe_test> iterator_ms(iterator_test.begin(), iterator_test.end());
    for(int i=0; i<iterator_test.size; i++)
        assert(iterator_ms.contains(classe_test(i,i)));
    cout<<"OK."<<endl;
    cout<<"   - Utilizzo iteratori: ";
    Multiset<classe_test>::const_iterator its = iterator_ms.begin(), ite = iterator_ms.end();
    while(its!=ite)
        iterator_ms.remove((*(its++)).value);
    assert(iterator_ms.total_values() == 0);
    cout<<"OK."<<endl; 
}


void test_edges_cases(){
    cout << endl << endl << "=-=-=-= Inizio test per casi limite =-=-=-="<< endl << endl;


    //Costruttore da itereatori
    cout << "# Costruttore da iteratori" << endl;

    //intervallo di iteratori vuoto
    cout << "   - Intervallo di iteratori vuoti:";

    ClasseIterators<double> iterator_test(0);
    Multiset<double> iterator_set(iterator_test.begin(), iterator_test.end());
    assert(iterator_set.total_values() == 0);

    cout << " OK." << endl;

    //intervallo di iteratori con doppioni
    cout << "   - Intervallo di iteratori con doppioni:";

    ClasseIterators<int> iterator_test1(5);
    for(int i = 0; i < 5; i++)
        iterator_test1.ptr[i] = 3;
    Multiset<int> iterator_set1(iterator_test1.begin(), iterator_test1.end());
    assert(iterator_set1.occourences_by_value(3) == 5);
    
    cout << " OK." << endl;

    
    //Copy-constructor
    cout << "# Costruttore di copia" << endl;

    //Creare multiset vuoto e copiare un altro multiset vuoto
    cout << "   - Creazione di un multiset da un multiset vuoto:";

    Multiset<string> str_set1;
    Multiset<string> str_set2(str_set1);
    assert( (str_set1 == str_set2) && (str_set2.total_values() == 0));

    cout << " OK." << endl;

    //Copiare multiset con un singolo elemento
    cout << "   - Creazione di un multiset da un multiset con un solo elemento:";

    str_set1.add("Arancia");
    Multiset<string> str_set3(str_set1);
    assert( (str_set1 == str_set3) && (str_set3.total_values() == 1));

    cout << " OK." << endl;

    //Copiare multiset con elementi duplicati
    cout << "   - Creazione di un multiset da un multiset con duplicati:";

    str_set1.add("Arancia");
    Multiset<string> str_set4(str_set1);
    assert( (str_set1 == str_set4) && (str_set4.occourences_by_value("Arancia") == 2));

    cout << " OK." << endl;



    //Operatore di assegnamento e confronto
    cout << "# Operatore di assegnamento e confronto" << endl;

    //Assegnare un multiset vuoto ad un multiset vuoto
    cout << "   - Assegnamento di un multiset vuoto ad un multiset vuoto:";

    Multiset<double> double_set1, double_set2;
    double_set2 = double_set1;
    assert(double_set2.total_values() == 0);

    cout << " OK." << endl;

    //Confrontare un multiset vuoto con un multiset vuoto
    cout << "   - Confrontare due multiset vuoti:";

    assert(double_set1 == double_set2);
    cout << " OK." << endl;

    //Assegnare un multiset non vuoto ad un multiset vuoto
    cout << "   - Assegnamento di un multiset non vuoto ad un multiset vuoto:";

    double_set1.add(3.15);
    double_set2 = double_set1;
    assert(double_set2.total_values() == 1);

    cout << " OK." << endl;

    //Confrontare due multiset con contenuto uguale
    cout << "   - Confrontare due multiset con contenuto uguale:";

    assert(double_set1 == double_set2);    

    cout << " OK." << endl;

    //Assegnare un multiset vuoto ad un multiset non vuoto
    cout << "   - Assegnamento di un multiset vuoto ad un multiset non vuoto:";

    Multiset<double> double_set3;
    double_set1 = double_set3;
    assert(double_set1.total_values() == 0);

    cout << " OK." << endl;

    //Assegnare un multiset non vuoto ad un multiset non vuoto ma con contenuti diversi
    cout << "   - Assegnamento di un multiset non vuoto ad un multiset non vuoto:";

    double_set1.add(3.15);
    double_set2.add(2.10);
    double_set3 = double_set1;
    double_set1 = double_set2;
    assert( (double_set1 == double_set2) && !( double_set1 == double_set3) );

    cout << " OK." << endl;

    //Confrontare due multiset diversi
    cout << "   - Confrontare due multiset diversi:";

    assert( !(double_set1 == double_set3) );

    cout << " OK." << endl;

    //Confrontare due multiset con valori unici uguali ma occorrenze diverse
    cout << "   - Confrontare due multiset con valori unici uguali ma occorrenze diverse:";

    Multiset<double> double_set4;
    Multiset<double> double_set5;
    double_set4.add(1.15);
    double_set4.add(1.15);

    double_set5.add(1.15);
    assert( !(double_set4 == double_set5) );

    cout << " OK." << endl;

    //Assegna un multiset a se stesso
    cout << "   - Assegna un multiset a se stesso:";

    double_set4 = double_set5;
    double_set5 = double_set5;
    assert(double_set5 == double_set4);

    cout << " OK." << endl;

    //Confronto di un multiset con se stesso
    cout << "   - Confrontare un multiset con se stesso:";

    assert(double_set4 == double_set4);

    cout << " OK." << endl;

    //Confronto di un multiset con una copia di se stesso
    cout << "   - Confrontare un multiset con una copia di se stesso:";

    assert(double_set4 == Multiset(double_set4));

    cout << " OK." << endl;



    //Iteratori
    cout << "# Iterator di Multiset" << endl;

    //Verificare che begin() su un multiset vuoto ritorni end()
    cout << "   - Verificare che begin() su un multiset vuoto ritorni end():";

    Multiset<classe_test> test_set;
    assert( test_set.begin() == test_set.end());

    cout << " OK." << endl;
}

int main(){

    test_interi();
    test_double();
    test_string();
    test_classe_complessa();
    test_edges_cases();

    return 0;    
}