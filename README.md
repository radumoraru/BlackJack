# BlackJack
>Acesta este jocul **Blackjack** implementat în limbajul **C** folosind structuri de date precum: **Arbori Binari** ( folosiți pentru sortarea *string-urilor*  ) și **Liste Simplu Înlănțuite** ( Pentru printarea într-un fișier text *.txt* ).                                                                             

 [![MIT license](https://img.shields.io/badge/license-MIT-blue.svg)](https://badges.mit-license.org/)
 [![NrOfPageVisits](http://hits.dwyl.io/RalucaMagdoiu/Minesweeper-ASD.svg)](http://hits.dwyl.io/radumoraru/BlackJack)

---

# Cuprins 
* ### Instalare
* ### Exemple din Consolă
* ### Exemple din Cod
* ### Licență

---
# Instalare

Nu există cerințe preliminare pentru acest proiect cât timp există un  **IDE compatibil în C**.


#### Clonează acest Repository în calculatorul tău folosind  https://github.com/radumoraru/Blackjack

---

# Exemple din Consolă

![Alt Text](http://g.recordit.co/8FTAP7QfmK.gif)

---

# Exemple din Cod


**Functia de afișare a jucătorului curent**
```C

void afisare()  
{
    jucator *q;
    q=prim;

    if(q!=NULL) //daca nodul nu este gol
    {
        printf("\n%s ",q->nume); // printarea jucatorului
    }
}

```
**Functia de începere a jocului**
```C

void startjoc()
{
    int p=0; /// valoarea totală a jucatorului
    char var3;

    test_bani();
    system("pause");

    printf("\nBani: LEI %d",bani); // printează banii deținuți de către jucător

    cartealeatorie(); //se apelează funcția de alegere a unei cărți aleatorii

    jucator_total = p + l;
     p = jucator_total;

     printf("\nTotalul este: %d\n", p); /// Printeaza totalul jucatorului
     dealer();
     pariere();

```
**Functia de afisare a rezultatelor în fișier**
```C

void rezultate()
{
        FILE *f;
        FILE *b;
        f=fopen("BlackJack.txt","a+"); //Deschidem fișierul unde vom printa rezultatele
        b=fopen("BlackJack_b.txt","a+"); //Deschidem fișierul de unde arborele va prelua datele pentru sortare

        fprintf(f,"\n----------------------------\n");
        fprintf(f,"Numele Jucatorului: %s\n",prim->nume); //printăm numele în primul fișier
        fprintf(f,"\nAti castigat de %d ori\n", won); //printăm rundele câștigate în primul fișier
        fprintf(f,"\nAti pierdut de %d ori\n", loss); //printăm rundele pierdute în primul fișier

        fprintf(b,"%d %d %s\n",won,loss,prim->nume); //printăm în al doilea fișier
        fclose(b);
        fclose(f);
}
```
![Alt Text](http://g.recordit.co/JSkIF70y6J.gif)


**Functia de afisare a arborelui**
```C
void afisare_arb()
{
    FILE *f;
    f=fopen("Rezultate.txt","w"); // deschidem fișierul de Rezultate
    nod * tr; 
    tr=radacina;
    while(1)
    {
        if(tr->dreapta != NULL)
            {
                if(tr->won == tr->dreapta->won)
                    fprintf(f,"%s este egal cu%s\n",tr->nume,tr->dreapta->nume);
                    else
                        fprintf(f,"%s este mai slab ca si %s\n",tr->nume,tr->dreapta->nume);
                tr=tr->dreapta;
            }
        else if(tr->stanga != NULL)
            {
                if(tr->won == tr->stanga->won)
                    fprintf(f,"%s este egal cu%s\n",tr->nume,tr->stanga->nume);
                    else
                        fprintf(f,"%s este mai bun ca si %s\n",tr->nume,tr->stanga->nume);
                tr=tr->stanga;
            }
        if(tr->dreapta == tr->stanga)
            break;
    }

}


```
# Licență

* **[MIT license](https://opensource.org/licenses/mit-license.php "MIT license")** 
* Click mai sus pentru mai multe detalii
