#include <stdio.h>
// functia care verifica daca prizonierii castiga sau nu jocul
int check(int *v, int p) {
    // presupunem ca prizonierii castiga jocul
    int ok = 1;
    int i, cnt, crt;
    for (i = 1; i <= p; i++) {
        // fiecare prizonier deschide cel putin o cutie
        cnt = 1;
        crt = v[i];
        // atata timp cat prizonierul nu deschide mai mult de p/2 cutii si cutia
        // deschisa nu contine numarul sau de ordine, jocul continua
        while (cnt <= p / 2 && crt != i) {
            cnt++;
            crt = v[crt];
        }
        // daca prizonierul depaseste numarul maxim de cutii care pot fi
        // deschise, prizonierii pierd
        if (cnt > p / 2) {
            ok = 0;
            break;
        }
    }
    return ok;
}
// functia afiseaza ciclurile formate de cutii
void cicles(int *v, int p) {
    int vizitat[502], i, crt;
    for (i = 0; i <= p; i++) {
        vizitat[i] = 0;
    }
    for (i = 1; i <= p; i++) {
        // daca cutia i nu a mai fost vizitata, incepem un nou ciclu
        if (vizitat[i] == 0) {
            // daca cutia i contine numarul i, eliminam spatiul de la final de
            // ciclu
            if (v[i] == i) {
                printf("%d", i);
            } else {
                printf("%d ", i);
            }
            crt = v[i];
            vizitat[i] = 1;
            // atat timp cat nu gasim numarul de ordine al cutiei i sau cutia la
            // care ajungem nu face parte din alt ciclu,continuam procedeul
            while (i != crt && vizitat[crt] == 0) {
                // daca cutia curenta contine numarul de ordine i, eliminam
                // spatiul de la final de ciclu
                if (v[crt] == i) {
                    printf("%d", crt);
                } else {
                    printf("%d ", crt);
                }
                // marcam cutia curenta ca facand parte dintr-un ciclu
                vizitat[crt] = 1;
                crt = v[crt];
            }
            printf("\n");
        }
    }
}
int main() {
    int p, v[502], i;
    scanf("%d", &p);
    for (i = 1; i <= p; i++) {
        scanf("%d", &v[i]);
    }
    // daca check returneaza 1 prizonierii castiga
    // in caz contrar prizonierii pierd
    if (check(v, p)) {
        printf("Da\n");
    } else {
        printf("Nu\n");
    }
    // apelez functia check pentru afisarea ciclurilor
    cicles(v, p);
    return 0;
}