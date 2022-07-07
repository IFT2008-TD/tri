//
// Created by Pascal Charpentier on 2022-07-02.
//

#ifndef TRI_TRI_H
#define TRI_TRI_H

#include <algorithm>

/**
 * InsertSort: version indicée
 * En-place: oui
 * Stable: oui
 * Pire cas: O(n^2)
 * Meilleur cas: O(n) (vecteur déjà trié!)
 *
 * Utilisé en pratique pour terminer d'autres algo plus performants.  Exemple: pour des vecteurs d'environ 10-100 éléments
 * il est plus rapide que QuickSort.  QuickSort est donc implanté pour qu'un appel récursif à de petits sous-arrays utilise
 * InsertSort pour terminer l'algo.  Donc si j'ai un million de clés à trier, j'aurai 100000 appels à InsertSort au lieu
 * de 100000 appels à QuickSort en fin d'algo, ce qui pourrait faire une différence importante au niveau performance.
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template<typename T>
void tri_insertion(std::vector<T>& v) {
    size_t len = v.size() ;
    if (len < 2) return ;

    for (size_t i = 1; i < len; ++i) {
        T courant = v[i] ;
        size_t j = i ;
        while ((j > 0) && (courant < v[j-1])) {
            v[j] = v[j-1] ;
            --j ;
        }
        v[j] = courant ;
    }
}

/**
 * InsertSort: version itérateurs
 * En-place: oui
 * Stable: oui
 * Pire cas: O(n^2)
 * Meilleur cas: O(n) (vecteur déjà trié!)
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template <typename T>
void tri_insertion_2(std::vector<T>& v) {
    if (v.size() < 2) return ;
    for (auto it = v.begin() + 1; it < v.end(); ++it) {
        T courant = *it ;
        auto it_prec = it - 1 ;
        while ((it != v.begin()) && (courant < *it_prec) ) {
            *it = *it_prec ;
            -- it ;
            -- it_prec ;
        }
        *it = courant ;
    }
}

/**
 * Prend un sous-array de v, allant de d à f, partitionné à mid.  On suppose que les sous-array  d-mid et mid-f sont triés.
 * Fusionne les deux sous-arrays dans le vecteur auxiliaire aux, et recopie le résultat dans v aux indices correspondants.
 *
 * @tparam T
 * @param v Vecteur à trier
 * @param aux Vecteur auxiliaire servant d'espace de travail
 * @param d Début du sous-array de gauche
 * @param mid début du sous-array de droite
 * @param f Fin du sous-array de droite
 */
template<typename T>
void aux_fusion(std::vector<T>& v, std::vector<T>& aux, size_t d, size_t mid, size_t f) {
    size_t len_gauche = mid - d ;
    size_t len_droite = f - mid ;
    if (len_gauche == 0 ||len_droite == 0) return ;

    size_t len = f - d ;

    size_t idx_gauche = d ;
    size_t idx_droite = mid ;
    size_t idx = 0 ;
    while (idx_gauche != mid && idx_droite != f) {
        if (v[idx_gauche] < v[idx_droite]) {
            aux[idx] = v[idx_gauche] ;
            ++idx_gauche ;
        }
        else {
            aux[idx] = v[idx_droite] ;
            ++idx_droite ;
        }
        ++idx ;
    }

    if (idx_gauche == mid) for (; idx_droite != f; ++idx_droite, ++idx) aux[idx] = v[idx_droite] ;
    else for (; idx_gauche != mid; ++idx_gauche, ++idx) aux[idx] = v[idx_gauche] ;

    std::move(aux.begin(), aux.begin() + len, v.begin() + d) ;
}

/**
 * Fonction auxiliaire récursive de mergesort: Trie le sous-array de v allant de d à f.
 * @tparam T
 * @param v Vecteur à trier
 * @param aux Vecteur auxiliaire servant d'espace de travail
 * @param d Début du sous-array à trier
 * @param f Fin du sous-array à trier
 */
template<typename T>
void aux_tri_fusion(std::vector<T>& v, std::vector<T>& aux, size_t d, size_t f) {
    assert(d <= f) ;
    if ((f - d) < 2) return ;

    auto mid = d + (f - d) / 2 ;

    aux_tri_fusion(v, aux, d, mid) ;
    aux_tri_fusion(v, aux, mid, f) ;

    aux_fusion(v, aux, d, mid, f) ;
}


/**
 * MergeSort
 * En-place: non.  Requiert O(n) mémoire
 * Stable: Oui
 * Pire cas: O(n log(n))
 * Meilleur cas: O(n log(n))
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template<typename T>
void tri_fusion(std::vector<T>& v) {
    size_t len = v.size() ;
    if (len < 2) return ;
    std::vector<T> aux(len) ;

    aux_tri_fusion(v, aux, 0, len) ;
}


/**
 * HeapSort
 * En-place: oui
 * Stable: Non
 * Pire cas: O(n log(n))
 * Meilleur cas: O(n) (seulement si toutes les valeurs sont identiques!!!)
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template <typename T>
void tri_par_tas(std::vector<T>& v) {
    size_t len = v.size() ;
    if (len < 2) return ;

    // "Insérer" chaque élément du vecteur dans le tas-max et percoler vers le haut
    for (size_t i = 1; i < len; ++i) {
        size_t idx_courant = i ;
        T elem = v[idx_courant] ;
        size_t idx_parent = (idx_courant - 1) / 2 ;
        while ((idx_courant > 0) && (elem > v[idx_parent])) {
            v[idx_courant] = v[idx_parent] ;
            idx_courant = idx_parent ;
            idx_parent = (idx_courant - 1) / 2 ;
        }
        v[idx_courant] = elem ;
    }

    // Échanger l'élément max du tas avec la dernière feuille et percoler vers le bas
    for (size_t i = len - 1; i > 0; --i) {
        std::swap(v[0], v[i]) ;

        // Commencer au sommet
        size_t idx_courant = 0 ;
        T elem = v[idx_courant] ;
        size_t idx_enfant = 1 ;

        // On arrête de percoler si l'enfant est hors-limite
        while (idx_enfant < i)  {
            T enfant = v[idx_enfant] ;

            // On percole vers le plus grand des deux enfants, s'il y en a deux
            if ((idx_enfant != i-1) && (enfant < v[idx_enfant + 1])) {
                enfant = v[idx_enfant + 1] ;
                ++ idx_enfant ;
            }

            // On arrête de percoler si le parent est plus grand que les enfants
            if (elem >= enfant) break ;

            // Percolation: on remonte le noeud enfant et on descend d'un niveau
            v[idx_courant] = enfant ;
            idx_courant = idx_enfant ;
            idx_enfant = 2 * idx_courant + 1 ;
        }
        v[idx_courant] = elem ;
    }
}

template<typename T>
typename std::vector<T>::iterator
partition(std::vector<T>& v, typename std::vector<T>::iterator debut, typename std::vector<T>::iterator fin) {
    auto len = static_cast<size_t> (fin - debut) ;
    if (len < 2) return debut ;
    size_t offset = len / 2 ;


    auto gauche = debut ;
    auto droite = fin - 1;
    auto pivot = debut + offset ;  // ATTENTION: TRÈS MAUVAIS CHOIX!!!

    std::swap(*pivot, *droite) ;
    pivot = droite ;
    droite = pivot - 1 ;

     while (gauche <= droite) {
         if (*gauche > *pivot) {
             if (*droite < *pivot) {
                 std::swap(*droite, *gauche);
                 ++ gauche;
             }
             -- droite;
         }
         else {
             if (*droite > *pivot) -- droite ;
             ++ gauche ;
         }
     }
     std::swap(*gauche, *pivot) ;
     return gauche ;
}

/**
 * Fonction auxiliaire récursive de QuickSort.  Trie le sous-array allant de debut à fin.
 * @tparam T
 * @param v Vecteur à trier
 * @param debut Itérateur sur le début du sous-array à trier
 * @param fin Itérateur sur la fin du sous-array à trier
 */
template<typename T>
void aux_tri_rapide(std::vector<T>& v, typename std::vector<T>::iterator debut, typename std::vector<T>::iterator fin) {
    auto len = static_cast<size_t> (fin - debut) ;
    if (len < 2) return ;

    auto mid = partition(v, debut, fin) ;
    aux_tri_rapide(v, debut, mid) ;
    aux_tri_rapide(v, mid, fin) ;
}

/**
 * QuickSort: dans la pratique, l'algorithme le plus performant!
 * En-place: oui
 * Stable: Non
 * Pire cas: O(n^2) ATTENTION: Très sensible au choix du pivot!!!
 * Meilleur cas: O(n log(n))
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template<typename T>
void tri_rapide(std::vector<T>& v) {
    size_t len = v.size() ;
    if (len < 2) return ;
    aux_tri_rapide(v, v.begin(), v.end()) ;


}

/**
 * BubbleSort: un algorithme inefficace, inutilisé en pratique sauf pour enseignement.  Son seul avantage est de prendre
 * trois lignes.  Anyway, insertsort prend aussi quelques lignes.
 * En-place: oui
 * Stable: oui
 * Pire cas: O(n^2)
 * Meilleur cas: O(n^2)
 *
 * @tparam T
 * @param v Vecteur d'éléments à trier
 */
template <typename T>
void tri_bulle(std::vector<T>& v) {
    size_t len = v.size() ;
    if (len < 2) return ;

    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = len - 1; j > i; j--) {
            if (v[j] < v[j-1]) std::swap(v[j], v[j-1]) ;
        }
    }
}



#endif //TRI_TRI_H
