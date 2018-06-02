#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <math.h>
#include <time.h>
#include <string.h>



void startjoc();
void reguli();
void test_bani();
void dealer();
void intrebare();
int pariere(); /// intreaba jucatorul cat sa parieze
void rezultate();
void intrebarefinal();
void mainscreen();
void cartealeatorie(); /// genereaza carte aleatorie


/// Variabile globale
char nume_jucator[20];
int l;  /// puncte carte trasa player
int d;  /// puncte carte trasa dealer
int carte_random=0; /// draw a card
int bani=500;
int jucator_total=0;    /// puncte carti player
int dealer_total=0; /// puncte carti dealer
int pariu=0;
int won=0;  /// win-uri / player
int loss=0; /// Lose-uri / player


typedef struct jucator
{
    char *nume;
    struct jucator *urm;

}jucator;

jucator *prim;


jucator *adauga(char *nume)
{
    jucator *q,*p;

    p=(jucator*)malloc(sizeof(jucator));
    p->nume=(char*)malloc(strlen(nume)+1);

    strcpy(p->nume,nume);
    p->urm=NULL;

    if(p==NULL || p->nume==NULL)
    {
         printf("Eroare la alocare!");
         exit(0);
    }

    if(prim==NULL)
        return p;
    else
    {
        if(strcmp(prim->nume,p->nume)>0)
        {
            p->urm=prim;
            return p;
        }
        else
        {
            q=prim;
            while(q->urm!=NULL && strcmp(q->urm->nume,p->nume)<0)
            {
                q=q->urm;
                p->urm=q->urm;
                q->urm=p;
            }
            return prim;
        }
    }
}

void afisare()
{
    jucator *q;
    q=prim;

    if(q!=NULL)
    {
        printf("\n%s ",q->nume);
    }
}

void iesire_program()
{
    system("cls");
    printf("La revedere, o zi placuta\n");
    system("pause");
    create();
    afisare_arb();

    exit(0);
}

void incepejocul()
{
    char var1;
    int var2;
    printf("\n Sunteti pregatit? ");
    printf("\n ----------------- ");
    printf("\n       (D/N)\n");
    scanf("%c",&var1);

    while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n'))
    {
        scanf("%c",&var1);
    }

    system("cls");

    if((var1=='D') || (var1=='d'))
    {
        printf("Incepe jocul...........1\n");
        printf("Reguli.................2\n");
        printf("Iesire.................3\n");
        printf("Varianta...............");
        scanf("%d",&var2);
    }
    else
    {
        if((var1=='N') || (var1=='n'))
            iesire_program();
    }

    switch(var2)
    {
        case 1:
            {
                system("cls");
                startjoc();
                break;
            }
        case 2:
            {
                system("cls");
                reguli();
                break;
            }
        case 3:
            {
                system("cls");
                printf("Sunteti sigur ca doriti sa iesiti ?");
                scanf("%c",&var1);

                while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n'))
                {
                    printf("\nVa rugam introduceti o valoare: ");
                    scanf("%c",&var1);
                }

                if((var1=='D') || (var1=='d')) //Daca da
                {
                    iesire_program();
                }
                else
                {
                    if((var1=='N') || (var1=='n'))
                    {
                        system("cls");
                        incepejocul();

                    }
                }
                break;

            }
        default:
            {
                printf("\n\nO zi placulta \n\n");
                break;
            }
    }

}



void reguli()
{
    char var1;
    printf("---REGULI---\n");
    printf("Blackjack, cunoscut si sub numele de 21, este un joc des intalnit in cazinouri.\n");
    printf("Jocul a castigat popularitate deoarece este usor de jucat, jucatorul ce are suma\n");
    printf("cartilor 21 sau cel mai aproape de 21 castiga.\n");
    printf("Valoarea carților: cartile intre 2 si 10 au valoarea scrise pe ele, figurile au valoarea 10,\n");
    printf("asul poate fi 1 sau 11 dupa preferinta jucatorului.\n");
    printf("\nDoriti intoarcerea la ecranul anterior ? D/N: ");
    scanf("%c",&var1);

    while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n'))
    {
        scanf("%c",&var1);
    }

    if((var1=='D') || (var1=='d')) /// Daca da
    {
        system("cls");
        incepejocul();
    }
    else
    {
        if((var1=='N') || (var1=='n'))
        {
            iesire_program();
        }
    }

}


void cartealeatorie() /// genereaza carte aleatorie
{
    srand((unsigned) time(NULL));
    l=rand()%13+1;

    if(l > 10)
    {
        l=10;
    }

    if(l == 1) /// daca cartea este As, schimba valoarea in functie de nevoile jucatorului
    {
        if(jucator_total<=10) ///daca scorul total este mai mic decat 10, ramane 11
        {
                l=11;
        }

        else                /// daca scorul total este mai mare decat 11, schimba in 1
        {
                l=1;
        }
    }

}

void startjoc()
{
    int p=0; /// valoarea totala a jucatorului
    char var3;

    test_bani();
    system("pause");

    printf("\nBani: LEI %d",bani);

    cartealeatorie();

    jucator_total = p + l;
     p = jucator_total;

     printf("\nTotalul este: %d\n", p); /// Printeaza totalul jucatorului
     dealer();
     pariere();

     while(1) ///daca nr este mai mic decat 21
     {
         if(bani <= 0)
         {
             intrebarefinal();
         }

         if(p==21) ///Daca totalul este 21, castiga
         {
             system("cls");
             printf("\nAveti punctajul de %d puncte\n",jucator_total);
             printf("\nAti castigat\n");

             won=won+1;
             bani=bani+pariu;
             dealer_total=0;

             printf("\nAveti %d wins si %d losses\n", won,loss);
            break;

         }

         if(p>21) ///Daca totalul este mai mare decat 21, atunci pierde
         {
             system("cls");
             printf("\nAveti punctajul de %d puncte\n",jucator_total);
             printf("\nAti depasit 21.\n");

             loss=loss+1;
             bani=bani-pariu;

             printf("\nAveti %d wins si %d losses\n", won,loss);
             dealer_total=0;

             break;

         }

         if(p<21) ///daca totalul este mai mic decat 21
         {

             scanf("%c",&var3);

             while((var3!='C') && (var3!='c')) /// introduce valoare gresita
             {
                 printf("\n");
                 printf("\nVa rugam introduceti 'C' : ");
                 scanf("%c",&var3);
             }

             system("cls");

             cartealeatorie();

             jucator_total=p+l;
             p=jucator_total;

             printf("Totalul este: %d\n", p);

             dealer();

             if(dealer_total==21) ///daca dealerul are 21, pierde
             {
                 printf("\nDealerul castiga cu 21 de puncte.\n");

                 loss=loss+1;
                 bani=bani-pariu;

                 printf("\nAveti %d wins si %d losses\n", won,loss);

                 dealer_total=0;

                 break;
             }

             if(dealer_total>21) ///daca dealerul are peste 21, castiga
             {
                 printf("\nAti castigat. Dealerul a depasit 21.\n");

                 won=won+1;
                 bani=bani+pariu;

                 printf("\nAveti %d wins si %d losses\n", won,loss);

                 dealer_total=0;
                 break;
             }
         }
     }

         if(bani <= 0)
            intrebarefinal();
         else
            intrebare();
}

void dealer()
{
    int z;
    if(dealer_total<17)
    {
      srand((unsigned) time(NULL) + 1);

      z=rand()%13+1;

      if(z<=11)
      {
          d=z;
      }
      if(z>11) /// daca nr generat este mai mare decat 10, schimba valoarea in 10
      {
          d=10;
      }
      dealer_total=dealer_total+d;
    }
    printf("Dealerul are un total de %d", dealer_total); /// printeaza totalul dealerului
}


void test_bani()
{
    if(bani<=0) ///daca nu mai are bani, jocul se termina
    {
        printf("Sfarsitul jocului...");
        bani=500;
        intrebare();
    }
}

int pariere() /// intreaba jucatorul cat sa parieze
{
    printf("\n\nSuma pariata: LEI ");
    do
        {
            scanf("%d",&pariu);
        }while(pariu<=0);

    if(pariu>bani) /// daca jucatorul pariaza mai multi bani decat are la dispozitie
    {
        printf("Va rugam pariati in conformitate cu banii pe care ii detineti.\n");
        printf("Introduceti suma pariata: ");
        scanf("%d",&pariu);
        return pariu;
    }
    else return pariu;
}

void intrebare() ///functie care intreaba jucatorul daca mai doreste sa mai joace
{
    char var1;
    printf("\nDoriti sa mai incercati o data.?");
    printf("\nIntroduceti D sau N: ");

    scanf("%c",&var1);

    while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n')) ///tasta gresita introdusa
    {
        scanf("%c",&var1);
    }

    if((var1 == 'D') || (var1 == 'd')) ///daca alege DA
    {
        system("cls");
        startjoc();
    }
    else
    {
        if((var1=='N') || (var1=='n')) ///daca alege NU
        {
            system("cls");
            rezultate();
            printf("\n Doriti sa incepeti un jou joc? [D/N]: ");
            scanf("%c",&var1);

            while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n')) ///tasta gresita introdusa
            {
                scanf("%c",&var1);
            }
            if((var1 == 'D') || (var1 == 'd')) ///daca alege DA
                mainscreen();
                else
                {
                    iesire_program();
                }
        }
    }

}

void rezultate()
{
        FILE *f;
        FILE *b;
        f=fopen("BlackJack.txt","a+");
        b=fopen("BlackJack_b.txt","a+");

        fprintf(f,"\n----------------------------\n");
        fprintf(f,"Numele Jucatorului: %s\n",prim->nume);
        fprintf(f,"\nAti castigat de %d ori\n", won);
        fprintf(f,"\nAti pierdut de %d ori\n", loss);

        fprintf(b,"%d %d %s\n",won,loss,prim->nume);
        fclose(b);
        fclose(f);
}

void intrebarefinal()
{
    char var1;
    printf("\nAti pierdut. Doriti sa mai incercati o data? \n");
    printf("\nIntroduceti D sau N: ");

    scanf("%c",&var1);

    while((var1!='D') && (var1!='d') && (var1!='N') && (var1!='n')) ///tasta gresita introdusa
    {
        scanf("%c",&var1);
    }

    if((var1 == 'D') || (var1 == 'd')) /// daca alege DA
    {
        system("cls");
        rezultate();
        won=0;
        loss=0;
        bani=500;
        mainscreen();
    }
    else
    {
        if((var1=='N') || (var1=='n')) ///daca alege NU
        {
            printf("\n\n La revedere!!!!!\n\n");
            rezultate();
            create();
            afisare_arb();

            exit(0);
        }
    }

}

void mainscreen()
{
    int opt;
    char nume[10];

    if(prim == NULL)
    {
      printf("Numele...");
      gets(nume);
      prim=adauga(nume);
      printf("Jucatorul autentificat :%s\n", prim->nume);

    }
    else
    {
      printf("Numele...");
      gets(nume);
      gets(nume);

      prim->urm= (jucator *)malloc(sizeof(jucator));
      prim=prim->urm;
      prim=adauga(nume);

      printf("Jucatorul nou autentificat :%s\n", prim->nume);
    }



    while(1)
    {
        system("cls");
        printf("1......Afisarea Jucatorilor\n");
        printf("2......Incepere Joc\n");
        printf("3......Iesire\n");
        printf("Varianta..... ");
        scanf("%d",&opt);
        fflush(stdin);

        switch(opt)
        {
            case 1:
                {
                    afisare();
                    printf("\n");
                    system("pause");
                    break;
                }
            case 2:
                {
                    incepejocul();
                }
            case 3:
                {
                    rezultate();
                    iesire_program();
                }
            default:
                printf("\n1....4\n");
        }
        getch();
    }
}



typedef struct nod_arbore{
    char *nume;
    int won,loss;

    struct nod_arbore *stanga,*dreapta;

}nod;

nod *radacina;


nod * New_node(char *name, int win,int lose)
{
    nod *temp;
    temp=(nod *) malloc(sizeof(nod));
    temp->loss=lose;
    temp->won=win;
    temp->nume=(char*)malloc(strlen(name)+1);
    strcpy(temp->nume,name);
    temp->dreapta=NULL;
    temp->stanga=NULL;
    return temp;
}


void create()
{
    FILE *a;
    a=fopen("BlackJack_b.txt","r");

    int w=0,l=0;
    char n[10];
    nod *tr;

    if(fscanf(a,"%d",&w) != -1)
    {
        fscanf(a,"%d",&l);
        fgets(n,10,a);

        nod *temp;
        temp =New_node(n,w,l);
        radacina=temp;
    }

    tr=radacina;

    while(fscanf(a,"%d",&w) != -1)
    {
        fscanf(a,"%d",&l);
        fgets(n,10,a);

        nod *temp;
        temp =New_node(n,w,l);

        if(temp->won > tr->won)
            {
                tr->dreapta = temp;
                tr=tr->dreapta;

            }
        else if(temp->won <= tr->won)
            {
                tr->stanga = temp;
                tr=tr->stanga;
            }

    }


    fclose(a);

}

void afisare_arb()
{
    FILE *f;
    f=fopen("Rezultate.txt","w");
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

int main()
{
    system("COLOR 1F");
    FILE *f;
    f=fopen("BlackJack.txt","w");
    fclose(f);
    f=fopen("BlackJack_b.txt","w");
    fclose(f);

    prim=NULL;

    mainscreen();
    incepejocul();

    create();
    afisare_arb();
    return 0;
}
