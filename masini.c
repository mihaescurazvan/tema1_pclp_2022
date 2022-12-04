#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// functia cauta un caracter intr-un sir si returneaza 1 daca il gaseste si 0 in
// caz contrar
int cautareCaracter(char *sir, char caracter) {
    int i;
    for (i = 0; i < strlen(sir); i++) {
        if (caracter == sir[i]) {
            return 1;
        }
    }
    return 0;
}
// functia calculeaza numarul de cifre dintr-un sir
int numarCifre(char *sir) {
    int i, contor = 0;
    for (i = 0; i < strlen(sir); i++) {
        if (strchr("0123456789", sir[i]) != NULL) {
            contor++;
        }
    }
    return contor;
}
int *cerinta_a(int *v, char **combustibil, int n) {
    int i;
    // in vetorul de patru elemente v contorizez tipurile de combustibil pe care
    // le au masinile citite
    for (i = 0; i < 4; i++) {
        v[i] = 0;
    }
    for (i = 0; i < n; i++) {
        // daca masina i functioneaza pe benzina incrementez v[0]
        if (strcmp(combustibil[i], "benzina") == 0) {
            v[0]++;
        }
        // daca masina i functioneaza pe motorina incrementez v[1]
        if (strcmp(combustibil[i], "motorina") == 0) {
            v[1]++;
        }
        // daca masina i e hibrida incrementez v[2]
        if (strcmp(combustibil[i], "hibrid") == 0) {
            v[2]++;
        }
        // daca masina i e electrica incrementez v[3]
        if (strcmp(combustibil[i], "electric") == 0) {
            v[3]++;
        }
    }
    return v;
}
// functia returneaza consumul total pentru fiecare marca de masina
double *determinareLitrii(char **brand, char **brand_unic, int k, int n,
                          double *consum, int *km, double *litri) {
    int i, j;
    for (j = 0; j < k; j++) {
        for (i = 0; i < n; i++) {
            if (strcmp(brand_unic[j], brand[i]) == 0) {
                // calculez consumul total de combustibil cu formula din enunt
                // si il castez la double
                litri[j] += (double)((consum[i] * km[i]) / 100);
            }
        }
    }
    return litri;
}
// functia caluleaza suma platita de dealership pentru fiecare marca de masina
double *determinareBani(char **brand, char **brand_unic, int k, int n,
                        char **combustibil, double *consum, int *km,
                        double *bani) {
    int i, j;
    double consum_total;
    for (j = 0; j < k; j++) {
        bani[j] = 0;
        for (i = 0; i < n; i++) {
            if (strcmp(brand_unic[j], brand[i]) == 0) {
                if (strcmp(combustibil[i], "benzina") == 0 ||
                    strcmp(combustibil[i], "hibrid") == 0) {
                    // calculez consumul total al masinii i
                    consum_total = (double)((km[i] * consum[i]) / 100);
                    // adun suma platita pentru masina i care functioneaza pe
                    // benzina sau hibrid la suma platita pentru marca j
                    bani[j] += (double)(consum_total * (double)8.02);
                }
                if (strcmp(combustibil[i], "motorina") == 0) {
                    // calculez consumul total al masinii i
                    consum_total = (double)((km[i] * consum[i]) / 100);
                    // adun suma platita pentru masina i care functioneaza pe
                    // motorina la suma platita pentru marca j
                    bani[j] += (double)(consum_total * (double)9.29);
                }
            }
        }
    }
    return bani;
}
// functia verifica daca un numar de inmatriculare e valid sau nu
int cerinta_c(char *numar) {
    int j;
    char litere[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cifre[15] = "0123456789";
    litere[26] = '\0';
    cifre[10] = '\0';
    // daca numarul de inmatriculare are mai putine de 6 caractere sau mai mult
    // de 8, e invalid
    if (strlen(numar) < 6 || strlen(numar) > 8) {
        return 0;
    } else {
        // daca primul caracter nu e litera, numarul e invalid
        if (cautareCaracter(litere, numar[0]) == 0) {
            return 0;
            // daca numarul are 6 caractere, dar al doilea nu e cifra, numarul e
            // invalid
        } else if (strlen(numar) == 6 &&
                   cautareCaracter(cifre, numar[1]) == 0) {
            return 0;
            // daca al doilea caracter e litera, dar al treilea si al patrulea
            // nu sunt cifre, numarul  e invalid
        } else if (cautareCaracter(cifre, numar[1]) == 0 &&
                   (cautareCaracter(cifre, numar[2]) == 0 ||
                    cautareCaracter(cifre, numar[3]) == 0)) {
            return 0;
            // daca al doilea caracter e cifra dar al treilea e litera, numarul
            // e invalid
        } else if (cautareCaracter(litere, numar[1]) == 0 &&
                   (cautareCaracter(cifre, numar[1]) == 0 ||
                    cautareCaracter(cifre, numar[2]) == 0)) {
            return 0;
        } else {
            // daca ultimele 3 caractere nu sunt litere, numrul e invalid
            for (j = strlen(numar) - 1; j >= strlen(numar) - 3; j--) {
                if (cautareCaracter(litere, numar[j]) == 0) {
                    return 0;
                }
            }
            // daca la 4-lea caracter de la coada e litera, numarul e invalid
            if (cautareCaracter(litere, numar[j]) != 0) {
                return 0;
            }
        }
    }
    // daca numarul contine peste 4 cifre, e invalid
    if (numarCifre(numar) >= 4) {
        return 0;
    }
    return 1;
}

int main() {
    int n, i, j, *km, ok, k;
    char **brand, **numar, **combustibil, operatie, aux[20];
    double *consum;
    int nr_combustibil[4];
    scanf("%d", &n);
    // aloc dinamic vectorii ceruti
    brand = (char **)malloc(n * sizeof(char *));
    numar = (char **)malloc(n * sizeof(char *));
    combustibil = (char **)malloc(n * sizeof(char *));
    km = (int *)malloc(n * sizeof(int));
    consum = (double *)malloc(n * sizeof(double));
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s", aux);
        brand[i] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(brand[i], aux);
        scanf("%s", aux);
        numar[i] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(numar[i], aux);
        scanf("%s", aux);
        combustibil[i] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(combustibil[i], aux);
        scanf("%lf", &consum[i]);
        scanf("%d", &km[i]);
    }
    getc(stdin);
    scanf("%c", &operatie);
    if (operatie == 'a') {
        // apelez functia pentru cerinta a
        cerinta_a(nr_combustibil, combustibil, n);
        // afisez rezulatele dupa formatul cerut
        printf("benzina - %d\n", nr_combustibil[0]);
        printf("motorina - %d\n", nr_combustibil[1]);
        printf("hibrid - %d\n", nr_combustibil[2]);
        printf("electric - %d\n", nr_combustibil[3]);
    }
    if (operatie == 'b') {
        // vectorul in care retin brandurile unice de masini
        char **brand_unic;
        // vectorul in care retin consumul total al brendurilor unice
        double *total_litri;
        // vectorul in care retin suma totala platita de dealership
        double *total_bani;
        brand_unic = (char **)malloc(n * sizeof(char *));
        total_bani = (double *)malloc(n * sizeof(double));
        total_litri = (double *)malloc(n * sizeof(double));
        i = 0;
        j = 0;
        k = 0;
        ok = 1;
        for (i = 0; i < n; i++) {
            ok = 1;
            for (j = 0; j < k; j++) {
                if (strcmp(brand[i], brand_unic[j]) == 0) {
                    ok = 0;
                }
            }
            // daca nu am gasit brandul i in lista brendurilor unice il adaug in
            // lista
            if (ok == 1) {
                strcpy(aux, brand[i]);
                brand_unic[k] =
                    (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(brand_unic[k], aux);
                k++;
            }
        }
        determinareLitrii(brand, brand_unic, k, n, consum, km, total_litri);
        determinareBani(brand, brand_unic, k, n, combustibil, consum, km,
                        total_bani);
        for (i = 0; i < k; i++) {
            printf("%s a consumat %.2lf - %.2lf lei\n", brand_unic[i],
                   total_litri[i], total_bani[i]);
        }
    }
    if (operatie == 'c') {
        ok = 1;
        for (i = 0; i < n; i++) {
            if (cerinta_c(numar[i]) == 0) {
                ok = 0;
                printf("%s cu numarul %s: numar invalid\n", brand[i], numar[i]);
            }
        }
        // daca nu s-a afisat nicun numar invalid, inseamna ca toate sunt valide
        if (ok == 1) {
            printf("Numere corecte!\n");
        }
    }
    return 0;
}