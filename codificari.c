#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// utilizez functia schimbareLitere pentru a nu iesii din randul literelor
char schimbareLitera(char litera, int cheie) {
    char alfabet[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alfabet[52] = '\0';
    int i;
    for (i = 0; i < strlen(alfabet); i++) {
        if (litera == alfabet[i]) {
            // daca noul indice al literei depaseste lungimea sirului,
            // rezultatul va fi modulo 52 (lungimea sirului) pentru a crea un
            // ciclu
            return alfabet[(i + cheie) % 52];
        }
    }
    return 0;
}
// utilizez functia reschimbareLitere pentru a nu iesii din randul literelor
// la decodificari
char reschimbareLitera(char litera, int cheie) {
    char alfabet[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alfabet[52] = '\0';
    int i;
    for (i = 0; i < strlen(alfabet); i++) {
        if (litera == alfabet[i]) {
            // daca noul indice al literei e negativ, rezultatul va fi modulo 52
            // (lungimea sirului) pentru a crea un ciclu
            return alfabet[(i - cheie) % 52];
        }
    }
    return 0;
}
char *codificareA(char *mesaj, char *cheie) {
    int randuri, coloane, i, j, k, l;
    // creez matricea cu numarul de coloane egal cu numarul de litere al cheii
    // matricea are numarul de randuri egal cu catul impartirii dintre lungimea
    // mesajului si lungimea cheii, daca impartirea da restul 0, trebuie
    // incrementat numarul de randuri
    if (strlen(mesaj) % strlen(cheie) == 0) {
        randuri = strlen(mesaj) / strlen(cheie);
    } else {
        randuri = strlen(mesaj) / strlen(cheie) + 1;
    }
    randuri += 1;
    coloane = strlen(cheie);
    char a[randuri][coloane];
    k = 0;
    // primul rand va conctine cheia
    for (j = 0; j < coloane; j++) {
        a[0][j] = cheie[k++];
    }
    k = 0;
    // asezam caracterele din mesaj in matrice
    for (i = 1; i < randuri; i++) {
        for (j = 0; j < coloane; j++) {
            if (k < strlen(mesaj)) {
                a[i][j] = mesaj[k++];
            } else {
                a[i][j] = ' ';
            }
        }
    }
    // ordonam coloanele matricii in ordinea lexicografica a cheii
    for (i = 0; i < coloane - 1; i++) {
        for (j = i + 1; j < coloane; j++) {
            if (a[0][i] > a[0][j]) {
                for (l = 0; l < randuri; l++) {
                    char aux = a[l][i];
                    a[l][i] = a[l][j];
                    a[l][j] = aux;
                }
            }
        }
    }
    k = 0;
    // parcurgem matricea pe coloane in ordinea cheii ordonate si fiecare
    // caracter il adaugam mesajul criptat cat timp k e cel mult lungimea cheii

    for (j = 0; j < coloane; j++) {
        for (l = 1; l < randuri; l++) {
            if (k <= strlen(mesaj)) {
                mesaj[k++] = a[l][j];
            }
        }
    }

    mesaj[k] = '\0';
    return mesaj;
}
char *codificareB(char *mesaj, int cheie) {
    char aux;
    int i, j;
    // permutam mesajul la dreapta de "cheie" ori
    for (j = 0; j < cheie; j++) {
        aux = mesaj[strlen(mesaj) - 1];
        for (i = strlen(mesaj) - 1; i > 0; i--) {
            mesaj[i] = mesaj[i - 1];
        }
        mesaj[0] = aux;
    }
    // pentru primele "cheie" caractere aduna la codul lor ascii "cheie"
    for (j = 0; j < cheie; j++) {
        // daca cheia e mai mare decat lungimea mesajului, caracterul de criptat
        // trebuie sa fie restul a impartirea cu lungimea mesajului
        i = j % strlen(mesaj);
        // daca caracterul e spatiu, nu il criptez
        if (mesaj[i] != ' ') {
            // avem 2 cazuri: daca litera care trebuie criptata e majuscula sau
            // litera mica
            if (mesaj[i] >= 'A' && mesaj[i] <= 'Z') {
                // daca e majuscula si adunam valoarea cheii la codul ascii al
                // literei e posibil ca rezultatul sa fie unul dintre cele 6
                // caractere dintre majuscule si litere mici; in acest caz
                // trebuie sa mai adaugam 6 pentru a sari caracterele care nu
                // sunt litere
                if (mesaj[i] + cheie >= 'A' && mesaj[i] + cheie <= 'Z') {
                    mesaj[i] += cheie;
                } else {
                    mesaj[i] += cheie + 6;
                }
                // daca litera care trebuie criptata e mica, apelam functia
                // schimbareLitera care foloseste un vector cu litere mici
                // continuate de majuscule iar litera care trebuie criptata se
                // afla la pozitia i va fi criptata la pozitia i+cheie din
                // vector
            } else {
                mesaj[i] = schimbareLitera(mesaj[i], cheie);
            }
        }
    }
    return mesaj;
}
char *decodificareA(char *mesaj, char *cheie) {
    int randuri, coloane, i, j, k, l;
    // creez matricea cu aceleasi dimensiuni ca la codificareA
    if (strlen(mesaj) % strlen(cheie) == 0) {
        randuri = strlen(mesaj) / strlen(cheie);
    } else {
        randuri = strlen(mesaj) / strlen(cheie) + 1;
    }
    randuri += 1;
    coloane = strlen(cheie);
    char a[randuri][coloane];
    char *cheie_inversa;
    cheie_inversa = (char *)malloc((strlen(cheie) + 1) * sizeof(char));
    // vectorul indici retine pozitiile la care se aflau caracterele din cheie
    // dupa ce aceasta va fi sortata
    int indici[51];
    for (i = 0; i < strlen(cheie); i++) {
        indici[i] = i;
    }
    strcpy(cheie_inversa, cheie);
    // in cheie_inversa se va afla cheia ordonata lexicografica si aceasta va
    // constitui primul rand din matrice
    for (i = 0; i < strlen(cheie_inversa) - 1; i++) {
        for (j = i + 1; j < strlen(cheie_inversa); j++) {
            if (cheie_inversa[i] > cheie_inversa[j]) {
                char aux = cheie_inversa[i];
                cheie_inversa[i] = cheie_inversa[j];
                cheie_inversa[j] = aux;
                int auxi = indici[i];
                indici[i] = indici[j];
                indici[j] = auxi;
            }
        }
    }
    for (j = 0; j < coloane; j++) {
        a[0][j] = cheie_inversa[k++];
    }
    k = 0;
    // asez mesajul criptat pe coloane
    for (j = 0; j < coloane; j++) {
        for (i = 1; i < randuri; i++) {
            if (k < strlen(mesaj)) {
                a[i][j] = mesaj[k++];
            } else {
                a[i][j] = ' ';
            }
        }
    }
    k = 0;
    // matricea decriptata va contine mesajul decriptat pe randuri
    char decriptat[500][500];
    for (i = 0; i < randuri; i++) {
        for (j = 0; j < coloane; j++) {
            decriptat[i][j] = ' ';
        }
    }
    // asezam in matricea decriptata coloanele corespunzatoare indicilor cheii
    // necriptate
    for (j = 0; j < coloane; j++) {
        for (l = 0; l < randuri; l++) {
            decriptat[l][indici[j]] = a[l][j];
        }
    }
    k = 0;
    // mesajul decriptat va fi citit pe randuri din matricea decriptata
    for (l = 1; l < randuri; l++) {
        for (j = 0; j < coloane; j++) {
            if (k <= strlen(mesaj)) {
                mesaj[k++] = decriptat[l][j];
            }
        }
    }
    mesaj[k] = '\0';
    return mesaj;
}

char *decodificareB(char *mesaj, int cheie) {
    char aux;
    int i, j;
    // pentru primele "cheie" caractere scad la codul lor ascii "cheie"
    for (j = 0; j < cheie; j++) {
        // daca cheia e mai mare decat lungimea mesajului, caracterul de
        // decriptat trebuie sa fie restul a impartirea cu lungimea mesajului
        i = j % strlen(mesaj);
        // caractrerul e spatiu sau \0 nu il decriptez
        if (mesaj[i] != ' ' && mesaj[i] != '\0') {
            // avem 2 cazuri: daca litera care trebuie criptata e majuscula sau
            // litera mica
            if (mesaj[i] >= 'a' && mesaj[i] < 'z') {
                // daca litera criptata e mica si dupa scaderea valorii cheii nu
                // obtinem o litera trebuie sa scadem inca 6, pentru a sari
                // caracterele aflat intre majuscule si litere mici
                if (mesaj[i] - cheie >= 'a' && mesaj[i] - cheie < 'z') {
                    mesaj[i] -= cheie;
                } else {
                    mesaj[i] = mesaj[i] - (cheie + 6);
                }
                // daca litera e majuscula apelez functia reschimbareLitera care
                // foloseste un vector cu litere mici continuate de majuscule
                // iar litera care trebuie decriptata se afla la pozitia i va fi
                // criptata la pozitia i-cheie din vector
            } else {
                mesaj[i] = reschimbareLitera(mesaj[i], cheie);
            }

            // daca caracterul decriptat nu mai este litera, apelez
            // reschimbareLitera pentru a ramane in randul literelor
        }
    }
    // permutam mesajul la stanga de "cheie" ori
    for (j = 0; j < cheie; j++) {
        aux = mesaj[0];
        for (i = 0; i < strlen(mesaj) - 1; i++) {
            mesaj[i] = mesaj[i + 1];
        }
        mesaj[strlen(mesaj) - 1] = aux;
    }
    return mesaj;
}

int main() {
    char mesaj[500], operatie[20];
    fgets(mesaj, 500, stdin);
    // elimin \n de la finalul mesajului
    mesaj[strlen(mesaj) - 1] = '\0';
    scanf("%s", operatie);
    // citesc operatiile de criptare/decriptare pana intalnesc STOP
    while (strcmp(operatie, "STOP") != 0) {
        if (strcmp("CodificareA", operatie) == 0) {
            char cheie[50];
            getchar();
            fgets(cheie, 50, stdin);
            // elimin \n de la finalul cheii
            cheie[strlen(cheie) - 1] = '\0';
            codificareA(mesaj, cheie);
        }
        if (strcmp("CodificareB", operatie) == 0) {
            int cheie;
            scanf("%d", &cheie);
            codificareB(mesaj, cheie);
        }
        if (strcmp("DecodificareA", operatie) == 0) {
            char cheie[50];
            getchar();
            fgets(cheie, 50, stdin);
            // elimin \n de la finalul cheii
            cheie[strlen(cheie) - 1] = '\0';
            decodificareA(mesaj, cheie);
        }
        if (strcmp("DecodificareB", operatie) == 0) {
            int cheie;
            scanf("%d", &cheie);
            decodificareB(mesaj, cheie);
        }
        puts(mesaj);
        scanf("%s", operatie);
    }

    return 0;
}