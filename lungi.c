#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// functia compara 2 numere mari stocate in vectori de cifre
int comparareNumereMari(int* a, int* b, int n) {
    int i = 1;
    while (i < n && a[i] == b[i]) {
        i++;
    }
    if (a[i] >= b[i]) {
        return 1;
    }
    return 2;
}
// functia returneaza 1 daca numarul mare stocat in vectorul de cifre a este
// nenul si 0 in caz contrarr
int numarNenul(int* a, int n) {
    int i, ok = 0;
    for (i = 1; i < n; i++) {
        if (a[i] != 0) {
            ok = 1;
        }
    }
    return ok;
}
char* adunare(char* a, char* b, int n) {
    int partea_reala_1[502], partea_imaginara_1[502], partea_reala_2[502],
        partea_imaginara_2[502], suma_reala[502] = {0},
                                 suma_imaginara[502] = {0};
    int i, rest = 0, k1 = 0, k2 = 0;
    // creez 2 vectori de cifre ce reprezinta partile reale ale celor 2 numere
    // mari
    for (i = 0; i <= (n - 1) / 2 - 1; i++) {
        partea_reala_1[k1++] = a[i] - '0';
        partea_reala_2[k2++] = b[i] - '0';
    }
    k1 = 0;
    k2 = 0;
    // creez 2 vectori de cifre ce reprezinta partile imaginare ale celor 2
    // numere mari
    for (i = (n - 1) / 2; i < (n - 1); i++) {
        partea_imaginara_1[k1++] = a[i] - '0';
        partea_imaginara_2[k2++] = b[i] - '0';
    }
    int k = k1;
    if (partea_reala_1[0] == 0) {
        // daca ambele parti reale au semnul +, adun in vectorul suma reala de
        // la drepata la stanga cifra cu cifra, iar daca adunarea cifrelor trece
        // peste ordine, pastrez restul si il adun mai deparete
        if (partea_reala_2[0] == 0) {
            rest = 0;
            for (i = k - 1; i > 0; i--) {
                suma_reala[i] = partea_reala_1[i] + partea_reala_2[i] + rest;
                if (suma_reala[i] > 9) {
                    // in cazul in care rezultatul trece peste limita stocarii
                    // il trunchiez
                    suma_reala[i] = suma_reala[i] % 10;
                    rest = 1;
                } else {
                    rest = 0;
                }
                // daca suma rezultata e nula, fortez bitul de semn sa fie 0
                if (!numarNenul(suma_reala, k)) {
                    suma_reala[0] = 0;
                }
            }
        } else {
            rest = 0;
            // daca al doilea numar are semnul -, vom trata adunarea ca pe
            // scadere si avem 2 cazuri
            // daca partea pozitiva e mai mare decat cea negativa
            if (comparareNumereMari(partea_reala_1, partea_reala_2, k) == 1) {
                // fiecare cifra devine negativa
                for (i = k - 1; i > 0; i--) {
                    partea_reala_2[i] = -partea_reala_2[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_reala[i] =
                        partea_reala_1[i] + partea_reala_2[i] + rest;
                    // daca suma cifrelor e tot negativa, cifra devine 10- cifra
                    // si retin restul -1
                    if (suma_reala[i] < 0) {
                        suma_reala[i] = 10 + suma_reala[i];
                        rest = -1;
                    } else {
                        rest = 0;
                    }
                    // daca suma rezultata e nula, fortez bitul de semn sa fie 0
                    if (!numarNenul(suma_reala, k)) {
                        suma_reala[0] = 0;
                    }
                }
                // daca restul final ramane -1 si suma e nenula, semnul ei va fi
                // -
                if (rest == -1 && numarNenul(suma_reala, k)) {
                    suma_reala[0] = 1;
                }
            } else {
                // daca partea pozitiva e mai mica decat cea negativa
                // fiecare cifra devine negativa
                for (i = k - 1; i > 0; i--) {
                    partea_reala_2[i] = -partea_reala_2[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_reala[i] =
                        partea_reala_1[i] + partea_reala_2[i] - rest;
                    // daca suma cifrelor e negativa, aceasta pastreaza valoarea
                    // absoluta
                    if (suma_reala[i] <= 0) {
                        suma_reala[i] = -suma_reala[i];
                        rest = 0;
                        // daca suma cifrelor trece peste ordine, aceasta devine
                        // 10-suma si retinem restul -1
                    } else {
                        suma_reala[i] = 10 - suma_reala[i];
                        rest = -1;
                    }
                }
                if (rest == 0 && numarNenul(suma_reala, k)) {
                    suma_reala[0] = 1;
                }
                if (!numarNenul(suma_reala, k)) {
                    suma_reala[0] = 0;
                }
            }
        }
        // daca primul numar are partea reala negativa
    } else {
        // daca si al doilea numar are partea reala negativa folosesc
        // proprietatea ca -a-b = -(a+b) si se repetat primul caz cu mentiunea
        // ca suma va avea semnul -
        if (partea_reala_2[0] == 1) {
            rest = 0;
            for (i = k - 1; i > 0; i--) {
                suma_reala[i] = partea_reala_1[i] + partea_reala_2[i] + rest;
                if (suma_reala[i] > 9) {
                    suma_reala[i] %= 10;
                    rest = 1;
                } else {
                    rest = 0;
                }
                if (!numarNenul(suma_reala, k)) {
                    suma_reala[0] = 0;
                }
            }
            suma_reala[0] = 1;
            // daca al doilea numar are partea reala pozitiva se repeta cele 2
            // cazuri pentru adunarea numelor cu semne diferite de mai sus
        } else {
            rest = 0;
            if (comparareNumereMari(partea_reala_1, partea_reala_2, k) == 2) {
                for (i = k - 1; i > 0; i--) {
                    partea_reala_1[i] = -partea_reala_1[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_reala[i] =
                        partea_reala_1[i] + partea_reala_2[i] + rest;
                    if (suma_reala[i] < 0) {
                        suma_reala[i] = 10 + suma_reala[i];
                        rest = -1;
                    } else {
                        rest = 0;
                    }
                }
                if (rest == -1 && numarNenul(suma_reala, k)) {
                    suma_reala[0] = 1;
                }
                if (!numarNenul(suma_reala, k)) {
                    suma_reala[0] = 0;
                }
            } else {
                for (i = k - 1; i > 0; i--) {
                    partea_reala_1[i] = -partea_reala_1[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_reala[i] =
                        partea_reala_1[i] + partea_reala_2[i] - rest;
                    if (suma_reala[i] <= 0) {
                        suma_reala[i] = -suma_reala[i];
                        rest = 0;
                    } else {
                        suma_reala[i] = 10 - suma_reala[i];
                        rest = -1;
                    }
                }
                if (rest == 0 && numarNenul(suma_reala, k)) {
                    suma_reala[0] = 1;
                }
                if (!numarNenul(suma_reala, k)) {
                    suma_reala[0] = 0;
                }
            }
        }
    }
    // pentru suma imaginara se pastreaza exact acelasi cazuri ca la suma reala
    if (partea_imaginara_1[0] == 0) {
        if (partea_imaginara_2[0] == 0) {
            rest = 0;
            for (i = k - 1; i > 0; i--) {
                suma_imaginara[i] =
                    partea_imaginara_1[i] + partea_imaginara_2[i] + rest;
                if (suma_imaginara[i] > 9) {
                    suma_imaginara[i] %= 10;
                    rest = 1;
                } else {
                    rest = 0;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            }
        } else {
            rest = 0;
            if (comparareNumereMari(partea_imaginara_1, partea_imaginara_2,
                                    k) == 1) {
                for (i = k - 1; i > 0; i--) {
                    partea_imaginara_2[i] = -partea_imaginara_2[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_imaginara[i] =
                        partea_imaginara_1[i] + partea_imaginara_2[i] + rest;
                    if (suma_imaginara[i] < 0) {
                        suma_imaginara[i] = 10 + suma_imaginara[i];
                        rest = -1;
                    } else {
                        rest = 0;
                    }
                }
                if (rest == -1 && numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 1;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            } else {
                for (i = k - 1; i > 0; i--) {
                    partea_imaginara_2[i] = -partea_imaginara_2[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_imaginara[i] =
                        partea_imaginara_1[i] + partea_imaginara_2[i] - rest;
                    if (suma_imaginara[i] <= 0) {
                        suma_imaginara[i] = -suma_imaginara[i];
                        rest = 0;
                    } else {
                        suma_imaginara[i] = 10 - suma_imaginara[i];
                        rest = -1;
                    }
                }
                if (rest == 0 && numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 1;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            }
        }
    } else {
        if (partea_imaginara_2[0] == 1) {
            rest = 0;
            for (i = k - 1; i > 0; i--) {
                suma_imaginara[i] =
                    partea_imaginara_1[i] + partea_imaginara_2[i] + rest;
                if (suma_imaginara[i] > 9) {
                    suma_imaginara[i] %= 10;
                    rest = 1;
                } else {
                    rest = 0;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            }
            suma_imaginara[0] = 1;
        } else {
            rest = 0;
            if (comparareNumereMari(partea_imaginara_1, partea_imaginara_2,
                                    k) == 2) {
                for (i = k - 1; i > 0; i--) {
                    partea_imaginara_1[i] = -partea_imaginara_1[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_imaginara[i] =
                        partea_imaginara_1[i] + partea_imaginara_2[i] + rest;
                    if (suma_imaginara[i] < 0) {
                        suma_imaginara[i] = 10 + suma_imaginara[i];
                        rest = -1;
                    } else {
                        rest = 0;
                    }
                }
                if (rest == -1 && numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 1;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            } else {
                for (i = k - 1; i > 0; i--) {
                    partea_imaginara_1[i] = -partea_imaginara_1[i];
                }
                for (i = k - 1; i > 0; i--) {
                    suma_imaginara[i] =
                        partea_imaginara_1[i] + partea_imaginara_2[i] - rest;
                    if (suma_imaginara[i] <= 0) {
                        suma_imaginara[i] = -suma_imaginara[i];
                        rest = 0;
                    } else {
                        suma_imaginara[i] = 10 - suma_imaginara[i];
                        rest = -1;
                    }
                }
                if (rest == 0 && numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 1;
                }
                if (!numarNenul(suma_imaginara, k)) {
                    suma_imaginara[0] = 0;
                }
            }
        }
    }
    // stochez cele 2 sume rezultate intr-un vector suma pe care il convertesc
    // la char
    char suma[1001] = "";
    for (i = 0; i < k; i++) {
        suma[i] = suma_reala[i] + '0';
        suma[i + (n - 1) / 2] = suma_imaginara[i] + '0';
    }
    suma[n - 1] = '\0';
    strcpy(a, suma);
    return a;
}
char* scadere(char* a, char* b, int n) {
    // folosesc proprietatea ca scaderea e un caz partilular de anunare
    // schimb biturile de semn ale partii reale si imaginare ale descazutului si
    // apelez functia adunare
    if (b[0] == '0') {
        b[0] = '1';
    } else {
        b[0] = '0';
    }
    if (b[(n - 1) / 2] == '0') {
        b[(n - 1) / 2] = '1';
    } else {
        b[(n - 1) / 2] = '0';
    }
    strcpy(a, adunare(a, b, n));

    return a;
}

int main() {
    char numarul_a[1001], numarul_b[1001];
    int n;
    char operatie[2];
    scanf("%d", &n);
    getc(stdin);
    fgets(numarul_a, n, stdin);
    getc(stdin);
    fgets(operatie, 2, stdin);
    // daca oeratia citita nu e + sau -, opresc programul
    while (strstr("+-", operatie) != 0) {
        getc(stdin);
        fgets(numarul_b, n, stdin);
        // daca operatia e +, apelez adunare si afisez rezultatul
        if (strcmp(operatie, "+") == 0) {
            strcpy(numarul_a, adunare(numarul_a, numarul_b, n));
            printf("%s\n", numarul_a);
        }
        // daca operatia e -, apelez scadere si afisez rezultatul
        if (strcmp(operatie, "-") == 0) {
            strcpy(numarul_a, scadere(numarul_a, numarul_b, n));
            printf("%s\n", numarul_a);
        }
        getc(stdin);
        fgets(operatie, 2, stdin);
    }
    return 0;
}