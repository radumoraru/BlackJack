# BlackJack
>Acesta este jocul **Blackjack** implementat în limbajul **C** folosind structuri de date precum: **Arbori Binari** ( folosit pentru sortarea *string-urilor*  ) și **Liste Simplu Înlănțuite** ( Pentru prinstarea într-un fișier text *.txt* ).                                                                             

 [![MIT license](https://img.shields.io/badge/license-MIT-blue.svg)](https://badges.mit-license.org/)
 [![NrOfPageVisits](http://hits.dwyl.io/RalucaMagdoiu/Minesweeper-ASD.svg)](http://hits.dwyl.io/radumoraru/BlackJack)

---

# Cuprins 
* ### Instalare
* ### Exemple din Consolă
* ### Exemple din Cod
* ### License

---
# Instalare

Nu există cerințe preliminare pentru acest proiect cât timp există un  **IDE compatibil în C**.


#### Clonează acest Repository în calculatorul tău folosind  https://github.com/radumoraru/Blackjack

---

# Exemple din Consolă

![Alt Text](http://g.recordit.co/8FTAP7QfmK.gif)

---
```C

void afisare()  //Functia de afisare a jucatorului curent
{
    jucator *q;
    q=prim;

    if(q!=NULL) //daca nodul nu este gol
    {
        printf("\n%s ",q->nume); // printarea jucatorului
    }
}

```
