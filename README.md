# 312CC_Mihaescu_Razvan_Tema1 PCLP 2022

## Cutii | Timp de lucru: 2 ore

Pentru problema **cutii.c** am folosit 2 functii specifice celor 2 cerinte ale problemei:
* pentru prima cerinta am folosit functia **check** care verifica daca prizonierii castiga jocul. Am presupus ca prizonierii castiga initializand o variabila ok cu 1.  am folosit 2 variabile: cnt (care este un contor pentru numarul de cutii deschise de un prizonier) si crt (care retine valoarea care se afla in cutia curenta). Daca prizonierul deschide cutia cu numarul sau de ordine inainte de a deschide jumatate dintre cutii, functia returneaza 1, adica prizonierii castiga, iar in caz contrar 0, adica prizonierii pierd.
* pentru a doua cerinta am folosit functia **cicles** care afiseaza ciclurile formate de cutii. Am folosit un vector vizitat care este initial 0, iar pentru fiecare valoare gasita marchez indicele de oridine al sau din vizitat cu 1. Pentru fiecare numar incepand de la 1, daca nu a fost vizitat, incep un nou cilcu. Adaug la ciclu cate un nou element pana cand intalnescu unul deja vizitat sau pana cand cutia deschisa contine numarul cu care incepe ciclul.

## Lungi | Timp de lucru: 2 zile

Pentru problema **lungi.c** am folosit 2 siruri de caractere care reprezinta numerele care trebuie adunate/scazute si un sir care va contine '+', '-' sau '0'. Daca sirul operatie e '+' sau '-' trebuie apelata una dintre cele 2 functii **adunare** sau **scadere**, iar daca este '0' se opreste programul. 
* pentru operatia '+' am creat functia adunare. Fiecare sir de caractere il sparg in cate 2 vectori de cifre care reprezinta partile reale si cele imaginare ale lor. Calculez suma partilor imaginare si a partilor reale. Daca ambii termeni ai adunarii au semnul + adun cifra cu cifra de la drepata la stanga, iar daca rezultatul trece peste ordine retin restul si il transmit mai departe. Daca ambii termeni ai adunarii au semnul - , repetam procedeul anterior, cu mentiunea ca suma va avea semnul '-'. Daca cei 2 termeni au semne alternante avem 2 cazuri: 
  *
  *
