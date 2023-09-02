#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct medicine{
    char name[30];
    int price;
    int sales;
    char ex_date[10];
    int unit;
    struct medicine *l;
    struct medicine *r;
};

struct user{
    char name[30];
    int buys[10];
    int age;
    int n;
    char m_buys[10][30];
    char buyDate[10];
    struct user *l;
    struct user *r;
};

struct sales{
    char m_name[10][30];
    char u_name[30];
    int price[10];
    int sales;
    int m;
    struct sales *l;
    struct sales *r;
};

struct medicine* in_pre(struct medicine *r){
      while( r!=NULL && r->r!=NULL){
          r=r->r;
      }
      return r;
}

struct medicine* delete(struct medicine **m,char *c){
      struct medicine *t=(*m),*r;
      if((*m)==NULL){
        return NULL;
      }
      if((*m)->l==NULL && (*m)->r==NULL){
        (*m)=NULL;
        free(t);
        return NULL;
      }
      if(strcmp(t->name,c)>0) t=t->l;
      else if(strcmp(t->name,c)<0) t=t->r;
      else{
           r=in_pre(t->l);
           if(r==NULL) return NULL;
           strcpy(r->name,t->name);
           strcpy(r->ex_date,t->ex_date);
           r->sales=t->sales;
           r->price=t->price;
           r->unit=t->unit;
           r->l=delete(&r->l,r->name);
      }
}

void add_stock(struct medicine **m){
        FILE *fp=fopen("Medicine.txt","a+");
         struct medicine *m1=(*m),*m2=NULL,*m3;
         printf("How many medicine data you want to add to the store: ");
         int n;
         scanf("%d",&n);
         for(int i=0;i<n;i++)
         {
            m1=(*m);
            m3=(struct medicine*)malloc(sizeof(struct medicine));
            printf("Enter name of medicine: "); fflush(stdin);
            gets(m3->name);
            printf("Enter price of medicine: ");
            scanf("%d",&m3->price);
            printf("Enter units of medicine: ");
            scanf("%d",&m3->unit);
            printf("Enter expiry date of medicine: "); fflush(stdin);
            gets(m3->ex_date);
            m3->sales=0;
            m3->l=NULL;
            m3->r=NULL;
            if((*m)==NULL){
                (*m)=m3;
            }
            else{
               while(m1!=NULL){
                    m2=m1;
                    if(strcmp(m3->name,m1->name)>0){
                         m1=m1->r;
                    }
                    else if(strcmp(m3->name,m1->name)<0){
                        m1=m1->l;
                    }
                }
                if(strcmp(m3->name,m2->name)<0) m2->l=m3;
                else m2->r=m3;
            }
            fprintf(fp,"%s %d %d %s %d\n",m3->name,m3->price,m3->unit,m3->ex_date,m3->sales);
         }
         fclose(fp);
}

void display(struct medicine *m,int i){
    int j=1;
    if(m!=NULL){
        display(m->l,i);
      if(i==1)  printf("# %10s%15d%10d%15s%10d\n",m->name,m->price,m->unit,m->ex_date,m->sales);
      else if(i==2) printf("#%10s%15d%10d%15s\n",m->name,m->price,m->unit,m->ex_date);
         display(m->r,i);
    }
}

struct medicine* search(struct medicine *s,char *c,int i){
    while(s!=NULL){
     if(strcmp(s->name,c)>0){
        s=s->l;
    }
    else if(strcmp(s->name,c)<0){
        s=s->r;
    }
    else{
        if(i==1){
        printf("%10s%15s%10s%15s%10s\n\n","Name","Price","Units","Expiry date","Sales");
        printf("%10s%15d%10d%10s%10d\n",s->name,s->price,s->unit,s->ex_date,s->sales);
        break;
        }
        else if(i==2){
            return s;
        }
        else if(i==3){
            printf("%10s%15s%10s%15s\n\n","Name","Price","Units","Expiry date");
            printf("%10s%15d%10d%15s\n",s->name,s->price,s->unit,s->ex_date);
            break;
        }
        }
    }
    if(s==NULL){
         printf("Data not found...\n");
    }
}

void display_s(struct sales *s){
    if(s!=NULL){
        display_s(s->l);
        int j=(s->m);
        printf("# %10s%10d%15s%10d\n",s->m_name[0],s->price[0],s->u_name,s->sales);
        for(int i=1;i<j;i++){
         printf("  %10s%10d\n",s->m_name[i],s->price[i]);
        }
        display_s(s->r);
    }
}

void show(struct user *p){
    if(p!=NULL){
        show(p->l);
        int j=(p->n);
        printf("# %10s%15s%10d%15s%15d\n",p->m_buys[0],p->name,p->age,p->buyDate,p->n);
        for(int i=1;i<j;i++){
         printf("  %10s\n",p->m_buys[i]);
        }
        show(p->r);
    }
}

void Admin(struct medicine **m,struct sales **s,struct user **u){
    struct medicine *p=(*m);
    printf("\n\nPlease enter a password to login to the account: ");
    int x,y;
    char a[20];
    fflush(stdin);
    gets(a);
    if(strcmp(a,"DSA")==0){
       printf("\nWelcome to the admin section...\n");
       do{
    printf("1. Add a new stock\n2. Display all medicines\n3. Remove the medicine\n4. Search any medicine\n5. Display all the sales\n6. Show user data\n7. Exit");
       printf("\n\nPress: ");
       scanf("%d",&x);
       switch (x)
       {
       case 1:
       add_stock(&(*m));
        break;
       case 2:
      printf("%13s%15s%10s%15s%10s\n\n","Name","Price","Units","Expiry date","Sales");
       display(*m,1);
       break;
       case 3:
      printf("\nEnter the name of medicine: ");
      char d[20]; fflush(stdin);
      gets(d);
      delete(*m,d);
       break;
       case 4:
       printf("\nEnter the name of medicine: ");
       char c[20];
       fflush(stdin); gets(c);
       search(*m,c,1);
       break;
       case 5:
       printf("%12s%10s%15s%10s\n\n","Medicine","price","client","sales");
       display_s(*s);
       break;
       case 6:
       printf("%12s%15s%10s%15s%15s\n\n","Medicines","Name","Age","Buy date","Buys");
       show(*u);
       break;
       case 7:
       break;
       default:
        break;
       }
    }while(x!=6);
    }
    else printf("Enter a appropriate password.\n\n");
}

struct sales* search3(struct sales *s,char *k){
    while(s!=NULL)
    {
        if(strcmp(s->u_name,k)>0) s=s->l;
        else if(strcmp(s->u_name,k)<0) s=s->r;
        else return s;
    }
    return NULL;
}

void create_s(struct medicine *k,struct sales **s,char *sn){
    struct sales *s1=(*s),*s2=NULL,*s3,*s4;
    s3=(struct sales*)malloc(sizeof(struct sales));
    s4=search3(*s,sn);
    if(s4==NULL){
        int j=0;
    strcpy(s3->m_name[j],k->name);
    strcpy(s3->u_name,sn);
    s3->price[j]=k->price;
    (s3->m)=1;
    s3->sales=k->sales;
    s3->l=s3->r=NULL;
    if((*s)==NULL){
                (*s)=s3;
            }
            else{
               while(s1!=NULL){
                    s2=s1;
                    if(strcmp(s1->u_name,s3->u_name)<0){
                         s1=s1->r;
                    }
                    else if(strcmp(s1->u_name,s3->u_name)>0){
                        s1=s1->l;
                    }
                }
                if(strcmp(s2->u_name,s3->u_name)>0) s2->l=s3;
                else s2->r=s3;
            }
    }
    else{
        int j=(s4->m);
        (s4->m)=(s4->m)+1;
        s4->price[j]=k->price;
        strcpy(s4->m_name[j],k->name);
        s4->sales+=k->sales;
    }
}

struct user* search2(struct user *u,char *n){
             while(u!=NULL){
                if(strcmp(u->name,n)>0) u=u->l;
                else if(strcmp(u->name,n)<0) u=u->r;
                else return u;
             }
             if(u==NULL) return NULL;
}

void create_u(struct user **u,struct medicine *k,struct sales **s){
        struct user *u1=(*u),*u2=NULL,*u3,*u4;
        u3=(struct user*)malloc(sizeof(struct user));
        printf("Enter your name: "); fflush(stdin);
        gets(u3->name);
        u4=search2(*u,u3->name);
        if(u4==NULL){
        printf("Enter your age: ");
        scanf("%d",&u3->age);
        printf("Enter date: "); fflush(stdin);
        gets(u3->buyDate);
        int j=0;
        strcpy(u3->m_buys[j],k->name);
        u3->buys[j]=k->sales;
        (u3->n)=1;
            u3->l=NULL;
            u3->r=NULL;
            if((*u)==NULL){
                (*u)=u3;
            }
            else{
               while(u1!=NULL){
                    u2=u1;
                    if(strcmp(u3->name,u1->name)>0){
                         u1=u1->r;
                    }
                    else if(strcmp(u3->name,u1->name)<0){
                        u1=u1->l;
                    }
                }
                if(strcmp(u3->name,u2->name)<0) u2->l=u3;
                else u2->r=u3;
            }
        }
        else{
            int j=(u4->n);
            (u4->n)=(u4->n)+1;
            u4->buys[j]=k->sales;
            strcpy(u4->m_buys[j],k->name);
        }
        create_s(k,&(*s),u3->name);
}

void buy_m(struct medicine **m,struct sales **s,struct user **u){
        printf("Our services are: \n");
        printf("%12s%15s%10s%15s\n","Name","Price","Qauntity","Expiry date");
        display(*m,2);
        struct medicine *m1=NULL;
        int c,d;
        char b[20];
        printf("\nIf you want to buy any medicine please press 1 otherwise 2: ");
        scanf("%d",&c);
        if(c==1){
           printf("Please enter the name of the medicine to buy:"); fflush(stdin);
           gets(b);
           m1=search(*m,b,2);
           do{
           printf("Please enter the units to buy medicine: ");
           scanf("%d",&d);
           }while(m1->unit<d);
           m1->unit-=d;
           m1->sales+=d*(m1->price);
           if(m1==NULL) printf("\n1");
           create_u(u,m1,&(*s));
           }
        else return;
}

struct user *search1(struct user *s,char *b){
         while(s!=NULL){
            if(strcmp(s->name,b)>0) s=s->l;
            else if(strcmp(s->name,b)<0) s=s->r;
            else{
                 return s;
            }
         }
}

void getbill(struct medicine **m,struct user **u,struct sales **s){
    char c[30];
    int sales=0;
     printf("Enter your name: "); fflush(stdin);
     gets(c);
     struct user *s1=search1(*u,c);
     if(s1!=NULL){
      printf("\t\t=========================================\n");
       printf("\t\t            Medical Bill                 \n");
       printf("\t\t=========================================\n");
     printf(" Date : %s\n Name : %s\n Age  : %d\n",s1->buyDate,s1->name,s1->age);
     printf(" Your order details: \n Total Purchased items: %d\n",s1->n);
     printf(" Your orders: \n\n");
     printf("%15s%15s\n**************************************\n","Medicines","Fairs");
     for(int i=0;i<(s1->n);i++){
        printf("%15s%15d \n",s1->m_buys[i],s1->buys[i]);
        sales+=s1->buys[i];
     }
     
     printf("\n**************************************\n\tTotal payments = %d\n",sales);
     }
     else{
        printf("\nNo record found.....\n");
     }
}

void user(struct medicine **m,struct sales **s,struct user **u)
{
    char b[20];
    int x,y;
        printf("\nWelcome to medical store: ");
        do{
        printf("\n1. Buy a medicine\n2. See a price of a medicine\n3. Display all the medicines\n4. Display final bill\n5. Exit");
        printf("\nPress: ");
        scanf("%d",&x);
        switch (x)
        {
        case 1:
        printf("How many items you want to buy: ");
        scanf("%d",&y);
        for(int i=0;i<y;i++)
        buy_m(&(*m),&(*s),&(*u));
        break;
        case 2:
        printf("Enter the name of medicine: "); fflush(stdin);
        gets(b);
        search(*m,b,3);
        break;
        case 3:
        display(*m,2);
        break;
        case 4:
        getbill(&(*m),&(*u),&(*s));
        break;
        case 5:
        break;
        default:
            break;
        }
        }while(x!=5);
}

void make_medi(struct medicine **m){
    struct medicine *m1,*m2,m3,*m4;
    FILE *fp=fopen("Medicine.txt","r");
       while(fscanf(fp,"%s %d %d %s %d\n",m3.name,&m3.price,&m3.unit,m3.ex_date,&m3.sales)!=EOF){
            m1=(struct medicine*)malloc(sizeof(struct medicine));
            m2=(*m);
            m1->l=m1->r=NULL;
            strcpy(m1->name,m3.name);
            m1->price=m3.price;
            m1->unit=m3.unit;
            strcpy(m1->ex_date,m3.ex_date);
            m1->sales=m3.sales;
                  if((*m)==NULL){
                     (*m)=m1;
                  }
                  else{
                    while(m2!=NULL){
                    m4=m2;
                    if(strcmp(m2->name,m3.name)>0) m2=m2->l;
                    else m2=m2->r;
                    }
                   if(strcmp(m4->name,m3.name)>0) m4->l=m1;
                  else m4->r=m1;
                  }
        }
        fclose(fp);
}

int main()
{
        struct medicine *m=NULL;
        struct sales *s=NULL;
        struct user *u=NULL;
        make_medi(&m);
        int n;
        do{
            printf("\n 1. Admin section\n 2. User section\n 3. Exit");
            printf("\n Press: ");
        scanf("%d",&n);
            if(n==1){
                Admin(&m,&s,&u);
            }
            else if(n==2){
                user(&m,&s,&u);
            }
        }while(n!=3);
        printf("\n\n===================== Thanks for visiting !!!=====================\n\n");
}