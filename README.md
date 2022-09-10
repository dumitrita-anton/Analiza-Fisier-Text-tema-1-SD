# Analiza-Fisier-Text-tema-1-SD
Anton Dumitrita 324CB

Punctaj local: 85/85

/*fisierele contin si explicatii in comentariile din cod*/
tema1.c
main :  preia numele fisierului de intrare din parametrul dat in linia de comanda
        initializeaza o tabela hash h
        citeste linie cu linie fisierul de intrare pana la finalul acestuia
        foloseste functia strtok pentru a delimita o linie intre comanda si inputul comenzii
        apeleaza functiile HInsert, HPrint, HPrintLen si HPrintMax cu parametrii corespunzatori, functii
        implementate in Hash.c 
        elibereaza memoria

List.c 
LAlloc: aloca un element de tip List cu campul info dat ca parametr
LRemData:   elimina un elemnt care are info == data, din lista 
            parcurge lista data ca parametru si cauta elementul din lista cu informatia
            aceeasi cu cea data ca parametru(data), folosind functia de comparatie data ca parametru
LAddFirst: adauga un element la inceputul unei liste
LAddSorted: functie de inserare sortata cu functia de comparare element data ca parametru
            returneaza elementul inserat


Hash.c
DInit: initializeaza un element de tip Data (pointer la o structura cu campurile <word> - cuvantul si <count> - numarul de aparitii in text)
DAct: actualizeaza campul count al elementului data
LenCompare: functie de comparatie pentru celulele din lista care tin lungimile cuvintelor
DataCompare: functie de comparatie a doua cuvinte (returneaza 0 daca sunt aceleasi cuvinte, compara numarul de aparitii in text pentru a insera descrescator in subliste, daca egale ordoneaza lexicografic)
codHash: calculeaza cod-ul hash pentru un cuvant
HInit: initializeaza tabela hash cu M si functia codHash
HInsert: realizeaza inserarea din cerinta
        foloseste functia InsSublist pentru a insera in lista de liste
        creeaza elementele de tip data ce se insereaza in subliste si link ce se insereaza in bucket
InsSublist: insereaza in sublista corespunzatoare elementul de tip Data

Pentru primul print am folosit functiile: DataPrint, LenPrint, HPrint_Sublist, HPrint_Bucket si HPrint;
DataPrint: afiseaza cuvantul si fecventa lui din text
HPrint_Sublist: afiseaza continutul unei subliste 
LenPrint: afiseaza lungimea apoi sublista de cuvinte cu aceasta lungime
HPrint_Bucket : afiseaza continutul unui bucket
HPrint: parcurge fiecare index al tabelei hash si printeaza bucketurile nevide cu ajutorul functiei anterioare

HPrintLen: afiseaza cuvintele care încep cu o anumita litera si au o anumita lungime
            calculeaza codul hash pe baza caracterului input
            parcurge bucket ul corespunxator si afiseaza doar sublistele cu lungimea din input

/*print n*/
searchList: cauta un element intr o lista si returneaza 1 daca il gaseste
Aceleasi functii ca la primul print doar ca se verifica de fiecare data daca frecventa de aparitie a cuvantului este mai <= decat maxLen
De asemenea se verifica daca exista in subliste elemente care sa verifice aceasta conditie. In caz contrar, nu se mai afiseaza celula cu lungimea sau pozitia in vectorul de liste din tabela hash;

