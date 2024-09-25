#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include<process.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
#define MAX_STRING_SIZE 1000
// ANSI escape codes for text colors
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BLACK   "\x1b[30m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_BROWN   "\x1b[33m"
#define ANSI_LIGHTGRAY  "\x1b[37m"
#define ANSI_DARKGRAY   "\x1b[90m"
#define ANSI_LIGHTBLUE  "\x1b[94m"
#define ANSI_LIGHTGREEN "\x1b[92m"
#define ANSI_LIGHTCYAN  "\x1b[96m"
#define ANSI_LIGHTRED   "\x1b[91m"
#define ANSI_LIGHTMAGENTA "\x1b[95m"
#define ANSI_YELLOW     "\x1b[93m"
#define ANSI_WHITE      "\x1b[97m"
#define M 51
char S[M][M],S1[M][M],RP[M][M],g;
int top=0,top1=0,trp=0;
struct node {
	char sname[M];
	struct node *rc;
	struct node *lc;
} *f,*l;
struct node * H[M]={NULL};
FILE *q;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
void insert(char *ns)
{ 
strcpy(S[++top],ns);
   
}
void sortStack(){ int i,j;
	for( i=1;i<=top;i++){
		strcpy(S1[i],S[i]);
	}
	    int n = top1;
    for (i = 1; i < n - 1; i++) {
        for ( j = 1; j < n - i - 1; j++) {
            if (strcmp(S1[j], S1[j + 1]) > 0) {
                char temp[50];
                strcpy(temp, S1[j]);
                strcpy(S1[j], S1[j + 1]);
                strcpy(S1[j + 1], temp);
            }
        }
    }
    int u;
     SetConsoleTextAttribute(h,15);
    printf("\nENTER\n");
     SetConsoleTextAttribute(h,14);
printf("\n1). A-Z SORTING\n");
 SetConsoleTextAttribute(h,13);
printf("\n2). Z-A SORTING\n");
scanf("%d",&u);
if(u==1){
	for(i=1;i<top1;i++){
		 SetConsoleTextAttribute(h,11);
		printf("%s",S1[i]);
	}
}
else if(u==2){
	for( i=top;i>0;i--){
		 SetConsoleTextAttribute(h,11);
		printf("%s",S1[i]);
	}
}
}
void strdel( char k[])
{ int i,flag=0;
  for(i=top;i>0;i--)
  { if(strcmp(S[i],k)==0)
       { flag=1;
          strcpy(S[i],"\0");
          break;
	   }
  }
  if(flag==0)
  {    SetConsoleTextAttribute(h,15);
	  printf("Not Found \n");
	  return ;}
}
int search( char s[])
{ int i,flag=0;
  for(i=top;i>0;i--)
  { if(strcmp(S[i],s)==0)
       { flag=1;
          return i;
	   }
  }
  if(flag==0)
  {    SetConsoleTextAttribute(h,15);
	  printf("Not Found \n");
	  return -1;}
return 0;
}
struct node * create(int n){
	struct node *nn;
	
	char sn[M];
	while(1){
		f=H[n];
		 SetConsoleTextAttribute(h,9);
		printf("\nEnter Song Name and Press -1 to Stop\n");
		scanf("%s",sn);
	    if(strcmp(sn,"-1")==0)
	       break;
	    nn=(struct node *)malloc(sizeof(struct node));
	    strcpy(nn->sname,sn);
	    nn->rc=NULL;
	    nn->lc=NULL;
	    if(f==NULL){
	    	H[n]=nn;
	    	f=nn;
	    	
		}
		else{
			while(f->rc!=NULL){
				f=f->rc;
			}
			f->rc=nn;
			nn->lc=f;
		}
	}
	return f;
}
//BST................
struct n{
	char sn[M];
	struct n *r;
	struct n *l;
	
};
struct n *newnode(char sna[]){
	struct n *temp=(struct n *)malloc(sizeof(struct n));
	strcpy(temp->sn,sna);
	temp->l=NULL;
	temp->r=NULL;
	return temp;
}
void inorder(struct n * root){
	if(root!=NULL){
		inorder(root->l);
		 SetConsoleTextAttribute(h,1);
		printf("%s\n",root->sn);
		inorder(root->r);
	}
}
struct n *inserts(struct n * nodes, char sna[]){

	if(nodes==NULL)
	   return newnode(sna);
	if(strcmpi(sna,nodes->sn)<0)
	  nodes->l=inserts(nodes->l,sna);
	else
	nodes->r=inserts(nodes->r,sna);
return nodes;
}
 void mains(struct node *t){
 	printf("\nCREATING \n");
 	struct node *temp=t;
 	struct n *root=NULL;
 	while(temp!=NULL){
 		root=
	inserts(root,temp->sname);
 		temp=temp->rc;
	 }
	 inorder(root);
 }

void albumdisplay(char *z){
	struct node *temp;
	 int k= search(z);
	temp=H[k];
	 SetConsoleTextAttribute(h,11);
		printf("%d-->",k);
		 SetConsoleTextAttribute(h,14);
		printf("%s\n",S[k]);
		
		while(temp!=NULL){
			 SetConsoleTextAttribute(h,10);
			printf("%s->",temp->sname);
			temp=temp->rc;
		}
		printf("\n");
	
}

//soundsss

void playsong(char z[]){
	  char c,q,d[3],m[3],y[5],h[3],min[3],sec[3],final[20]={"\0"};

		printf("\nPress 'Q' to Stop the Song\n");
    PlaySound(TEXT(z),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
	strcpy(RP[++trp] , z); 
    fflush(stdin);
	scanf("%c",&q);
	if(q=='Q'||q=='q')
	 PlaySound(0,0,0);
	 
}

	 void playSong(const char* songFile) {
    PlaySound(songFile, NULL, SND_ASYNC);
   
}

void pauseSong() {
    PlaySound(NULL, 0, 0);
}

void playqueue(){
    const char* songs[M] = {
        "Ekadantaya.wav",
        "KrishnaBGM.wav",
        "MidnightTrek.wav",
        "VandeMataram.wav",
        "Komaram-Bheemudu.wav",
        "DarshanaHridayam.wav",
        "HasiBangayi.wav",
        "Chellame.wav",
		"avengers.wav",
        "gasolina.wav",
        "desperado.wav",
        
    };

    int currentSong = 0;
    int isPlaying = 0;

    while (1) {
    	//system("cls");
    	system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
    	 SetConsoleTextAttribute(h,15);
        printf("\nMUSIC PLAYER\n");
         SetConsoleTextAttribute(h,14);
        printf("\n1). PLAY/PAUSE SONG\n");
         SetConsoleTextAttribute(h,11);
        printf("\n2). NEXT SONG\n");
         SetConsoleTextAttribute(h,12);
        printf("\n3). EXIT\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isPlaying) {
                    playSong(songs[currentSong]);
                     strcpy(RP[++trp] , songs[currentSong]); 
					isPlaying = 1;
                } else {
                    pauseSong();
                    isPlaying = 0;
                }
                break;

            case 2:
                pauseSong();
                isPlaying = 0;
                currentSong = (currentSong + 1) % M;
                playSong(songs[currentSong]);
                strcpy(RP[++trp] , songs[currentSong]);
                isPlaying = 1;
                break;

            case 3:
                pauseSong();
                return;
                
                //return 0;

            default:
            	 SetConsoleTextAttribute(h,15);
                printf("Invalid choice.\n");
                break;
        }
    }

    
}
void Albumdisplay(){ 
    //system("cls");

     int i,q,e,y,ao;
   char N[M],k[M],o,z[M];
   struct node *temp;    
	while(1){
		 //system("cls");
		 SetConsoleTextAttribute(h,14);
		 printf("\n");
	    	system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
		 printf("\nExisting Albums are : \n");
		 printf("\n");
    for(i=1;i<=top;i++){
    	 SetConsoleTextAttribute(h,12);
    	printf("%d. %s\n",i,S[i]);
	}
	MQ:
	//	system("cls");
	SetConsoleTextAttribute(h,9);
	printf("\nENTER: \n");
	SetConsoleTextAttribute(h,10);
	printf("\n1). SORT\n");
	SetConsoleTextAttribute(h,11);
	printf("\n2). VIEW ALBUM\n");
	SetConsoleTextAttribute(h,12);
	printf("\n3). CREATE ALBUM\n");
	SetConsoleTextAttribute(h,13);
	printf("\n4). DELETE ALBUM\n");
	SetConsoleTextAttribute(h,14);
	printf("\n5). DELETE SONG\n");
	SetConsoleTextAttribute(h,15);
	printf("\n6). PLAY QUEUE\n");
	SetConsoleTextAttribute(h,6);
	printf("\n7). EXIT\n");
	scanf("%d",&q);
	system("cls");
	if(q==6){
		system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
		playqueue();
	}
	if(q==1){
	//sort	albums
	 int r;
	 system("cls");
	 system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
	 SetConsoleTextAttribute(h,14);
	          printf("HOW SHALL WE SORT!!!\n");
	          SetConsoleTextAttribute(h,12);
			  printf("\n1). RECENTLY ADDED\n");
			  SetConsoleTextAttribute(h,10);
			  printf("\n2). A-Z\n");
			  scanf("%d",&r);
	if(r==1){
		system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
		for( y=top;y>0;y--){
			SetConsoleTextAttribute(h,13);
		    printf("Recently Added Order: \n");
			printf("%s\n",S[y]);
		}
	if(r==2){
		system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
		sortStack();
		SetConsoleTextAttribute(h,11);
		for(int u=0;u<=top1;u++)
		   printf("%s\n",S1[u]);
	}
	}
	}
	else if(q==2){ 
	system("cls");
	system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
	SetConsoleTextAttribute(h,10);
	printf("Existing Albums are : \n");
    for(i=1;i<=top;i++){
    	SetConsoleTextAttribute(h,12);
    	printf("%d. %s\n",i,S[i]);
	                   }
int w,i,o;
	 while(1){
	   system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
                SetConsoleTextAttribute(h,13);
	   printf("Enter album Name to Display: \n");
       scanf("%s",z); 
       albumdisplay(z); 
       //system("cls");
       SetConsoleTextAttribute(h,15);
	   printf("\nENTER\n");
	   SetConsoleTextAttribute(h,6);
	   printf("\n1). GO BACK\n");
	   SetConsoleTextAttribute(h,3);
	   printf("\n2). PLAY SONG\n");
	   SetConsoleTextAttribute(h,11);
	   printf("\n3). SORT\n");
	   SetConsoleTextAttribute(h,2);
       scanf("%d",&w);
       if( w==1){
	      break;
                }
				
		       else if(w==2){
        	
        char x[M];
 //FILE *fp;
	//REMINDER//
  while(1){
   system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
                printf("\n");
                albumdisplay(z); 
            SetConsoleTextAttribute(h,13);
  	printf("Enter song name to play or Enter 'exit' to EXIT\n");
  	fflush(stdin);
  	scanf("%s",&x);
  	if(strcmpi(x,"exit")==0)
  	   break;
	  playsong(x);
  }
}	
        else if(w==3){
              int r;
              system("cls");
              system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
              printf("\nHOW TO SORT!!\n");
			  printf("\n1.Recentlyadded\n2.A-Z\n");
			  scanf("%d",&r);
			  if(r==1){
			     printf("\nAlbum songs recently added\n");
 				 struct node *kk=H[ao];
                 while(kk->rc!=NULL){
               	 kk=kk->rc;
                                }
				 while(kk!=NULL){
 	            printf("%s\n",kk->sname);
 	             kk=kk->lc;
 }  	
			  }
			  else if(r==2){
			     printf("\nDisplay Album Songs in Sorted Fashion: \n");
                 mains(H[ao]);  	
			  }      	
		}
             }
	}
	else if(q==3){
		system("cls");
		system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
	 while(1){
   	i=top;
   	SetConsoleTextAttribute(h,13);
    printf("\nEnter Album Name : \n");
      scanf("%s",N);
      insert(N);
      create(top);
       	SetConsoleTextAttribute(h,12);
      printf("\nDo you want to Create another Album\n");
       	SetConsoleTextAttribute(h,11);
      printf("\nEnter Y for YES and N for NO\n");
      fflush(stdin);
      scanf("%c",&o);
      if(o=='n'||o=='N'){
      	break;
	  }
    }	
	}
	else if(q==4){ char z[M];
	     int k;
	     system("cls");
	     system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
	     struct node*temp;
	      	SetConsoleTextAttribute(h,13);
	     printf("\nEnter Album Name\n");
	      scanf("%s",z);
	      k=search(z);
	      strdel(z);
	      temp=H[k];
	      H[k]==NULL;
	      free(temp);
}
else if(q==5){
	char z[M],so[M];
	int k;
	system("cls");
	system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
	struct node*temp;
	struct node*prev=NULL;
	 	SetConsoleTextAttribute(h,12);
	printf("\nEnter Album You Wanted to Delete\n");
	scanf("%s",z);
	k=search(z);
	temp=H[k];
	 	SetConsoleTextAttribute(h,10);
	printf("\nEnter Song You Wanted to Delete in the Album \n");
	scanf("%s",so);
	while(temp!=NULL)
	{ if(strcmp(temp->sname,so)==0 && prev==NULL)
	{
	struct node*c=temp;
  H[k]=temp->rc;
  temp->rc->lc=H[k];
  
  free(c);
  break;
	
	}
	else if(strcmp(temp->sname,so)==0 && prev!=NULL)
{ struct node*c=temp;
    prev->rc=temp->rc;
    temp->rc->lc=prev;
    

    free(c);
    break;
}
else
{prev=temp;
temp=temp->rc;
}
	}
	
	
}
if(q==7){
	return;
}
}
}
// Structure to represent a Task
struct Task {
    char TaskName[50];
    char Subject[50];
    char Type[50];
    char SubmissionDate[12]; // Format: YYYY-MM-DD
    struct Task* next;
    struct Task* prev;
};

// Structure to represent a Binary Search Tree node
struct BSTNode {
    struct Task* task;
    struct BSTNode* left;
    struct BSTNode* right;
};

// Structure to represent a completed Task
struct CompletedTask {
    struct Task* task;
    struct CompletedTask* next;
};

// Function to create a new Task node
struct Task* createTask(const char* taskName, const char* subject, const char* type, const char* submissionDate) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newTask->TaskName, taskName);
    strcpy(newTask->Subject, subject);
    strcpy(newTask->Type, type);
    strcpy(newTask->SubmissionDate, submissionDate);
    newTask->next = NULL;
    newTask->prev = NULL;
    return newTask;
}

// Function to insert a Task node into the double linked list
void insertTask(struct Task** head, struct Task* newTask) {
    if (*head == NULL) {
        *head = newTask;
    } else {
        struct Task* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
        newTask->prev = current;
    }
}

// Function to display tasks in sorted order based on Submission Date using BST
void inorderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf(ANSI_CYAN "Task: %s\nSubject: %s\nType: %s\nSubmission Date: %s\n\n" ANSI_RESET, root->task->TaskName, root->task->Subject, root->task->Type, root->task->SubmissionDate);
        inorderTraversal(root->right);
    }
}

// Function to insert a Task node into the Binary Search Tree
struct BSTNode* insertBST(struct BSTNode* root, struct Task* newTask) {
    if (root == NULL) {
        struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        newNode->task = newTask;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    // Compare submission dates for sorting
    if (strcmp(newTask->SubmissionDate, root->task->SubmissionDate) < 0) {
        root->left = insertBST(root->left, newTask);
    } else {
        root->right = insertBST(root->right, newTask);
    }
    return root;
}

// Function to search tasks by submission date in BST
void searchBySubmissionDate(struct BSTNode* root, const char* date) {
    //printf("%s",root->task->SubmissionDate);
	if (root != NULL) {
        int cmp = strcmp(date, root->task->SubmissionDate);
        if (cmp == 0) {
            printf(ANSI_GREEN "Task found:\n");
            printf(ANSI_CYAN "\nTask: %s\nSubject: %s\nType: %s\nSubmission Date: %s\n\n" ANSI_RESET, root->task->TaskName, root->task->Subject, root->task->Type, root->task->SubmissionDate);
            printf(ANSI_RESET);
        } else if (cmp < 0) {
            searchBySubmissionDate(root->left, date);
        } else {
            searchBySubmissionDate(root->right, date);
        }
    } else {
        printf(ANSI_RED "Task not found for the specified date.\n" ANSI_RESET);
    }
}

// Function to search tasks by subject in BST
void searchBySubject(struct Task** root, const char* subject) {
	//printf("%s",*root->Subject);
	int flag=0;
	struct Task* l=*root;
    while(l != NULL) {
        int cmp = strcmp(subject, l->Subject);
        if (cmp == 0) {
            flag=1;
            break;}
            l=l->next;
        } if(flag==1){
		     printf(ANSI_MAGENTA "Task found:\n");
            printf(ANSI_CYAN "\nTask: %s\nSubject: %s\nType: %s\nSubmission Date: %s\n\n" ANSI_RESET, l->TaskName, l->Subject, l->Type, l->SubmissionDate);
            printf(ANSI_RESET);}
			/*else if (cmp < 0) {
            searchBySubject(root->left, subject);
        } else {
            searchBySubject(root->right, subject);
        }*/
    else {
        printf(ANSI_RED "\nTask not found for the specified subject.\n" ANSI_RESET);
    }
}

// Function to search tasks by type in BST
void searchByType(struct Task ** root, const char* type) {
    int flag=0;
	struct Task* l=*root;
    while(l != NULL) {
        int cmp = strcmp(type, l->Type);
        if (cmp == 0) {
            flag=1;
            break;}
            l=l->next;
        } if(flag==1){
		     printf(ANSI_MAGENTA "\nTask found:\n");
            printf(ANSI_CYAN "\nTask: %s\nSubject: %s\nType: %s\nSubmission Date: %s\n\n" ANSI_RESET, l->TaskName, l->Subject, l->Type, l->SubmissionDate);
            printf(ANSI_RESET);}
    else {
        printf(ANSI_RED "\nTask not found for the specified type.\n" ANSI_RESET);
    }
}



// Function to create a new CompletedTask node
struct CompletedTask* createCompletedTask(struct Task* task) {
    struct CompletedTask* newCompletedTask = (struct CompletedTask*)malloc(sizeof(struct CompletedTask));
    if (newCompletedTask == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    newCompletedTask->task = task;
    newCompletedTask->next = NULL;
    return newCompletedTask;
}

// Function to insert a CompletedTask node into the list
void insertCompletedTask(struct CompletedTask** head, struct CompletedTask* newCompletedTask) {
    if (*head == NULL) {
        *head = newCompletedTask;
    } else {
        newCompletedTask->next = *head;
        *head = newCompletedTask;
    }
}

// Function to view completed tasks
void viewCompletedTasks(struct CompletedTask* completedTasks) {
    if (completedTasks == NULL) {
        printf(ANSI_YELLOW "No completed tasks found.\n" ANSI_RESET);
        return;
    }

    printf(ANSI_LIGHTGREEN "\nCompleted Tasks:\n\n" ANSI_RESET);
    struct CompletedTask* current = completedTasks;
    while (current != NULL) {
        printf(ANSI_CYAN "\nTask: %s\nSubject: %s\nType: %s\nSubmission Date: %s\n\n" ANSI_RESET, current->task->TaskName, current->task->Subject, current->task->Type, current->task->SubmissionDate);
        current = current->next;
    }
}

// Function to display the main menu
void displayMainMenu() {
    SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,15);
    printf("\nWORKSPACE MENU:\n");
    printf("\n");
    SetConsoleTextAttribute(h,12);
    printf("1). Add a Task\n");
    printf("\n");
    SetConsoleTextAttribute(h,10);
    printf("2). View Tasks Sorted by Submission Date\n");
    printf("\n");
    SetConsoleTextAttribute(h,9);
    printf("3). Search Tasks\n");
    printf("\n");
    SetConsoleTextAttribute(h,14);
    printf("4). Mark Task as Completed\n");
    printf("\n");
    SetConsoleTextAttribute(h,6);
    printf("5). View Completed Tasks\n");
    printf("\n");
    SetConsoleTextAttribute(h,15);
    printf("6). Exit\n");
    printf("\n");
    SetConsoleTextAttribute(h,13);
    printf("Enter your choice: ");
}

// Function to display the search menu
void displaySearchMenu() {	
 SetConsoleTextAttribute(h,12);
    printf("\nSEARCH MENU:\n");
     SetConsoleTextAttribute(h,10);
    printf("\n1). Search by Submission Date\n");
     SetConsoleTextAttribute(h,9);
    printf("\n2). Search by Subject\n");
     SetConsoleTextAttribute(h,14);
    printf("\n3). Search by Type\n");
     SetConsoleTextAttribute(h,13);
    printf("\n4). Back to Main Menu\n");
     SetConsoleTextAttribute(h,6);
    printf( "\nEnter your choice: ");
}
// Function to read tasks from a file and populate the data structures
void readTasksFromFile(const char* filename, struct Task** taskList, struct BSTNode** bstRoot) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        exit(1);
    }

    char line[256]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file)) {
        char taskName[50], subject[50], type[50], submissionDate[12];
        if (sscanf(line, "%49s %49s %49s %11s", taskName, subject, type, submissionDate) == 4) {
            struct Task* newTask = createTask(taskName, subject, type, submissionDate);
            insertTask(taskList, newTask);
            *bstRoot = insertBST(*bstRoot, newTask);
        } else {
            printf("Invalid line format: %s", line);
        }
    }

    fclose(file);
}

void readCompletedTasksFromFile(const char* filename, struct CompletedTask** completedTasks, struct Task* taskList) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        exit(1);
    }

    char line[256]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file)) {
        char taskName[50];
        if (sscanf(line, "%49s", taskName) == 1) {
            // Find the corresponding task in taskList
            struct Task* current = taskList;
            while (current != NULL) {
                if (strcmp(current->TaskName, taskName) == 0) {
                    struct CompletedTask* newCompletedTask = createCompletedTask(current);
                    insertCompletedTask(completedTasks, newCompletedTask);
                    break;
                }
                current = current->next;
            }
        } else {
            printf("Invalid line format: %s", line);
        }
    }

    fclose(file);
}
void saveCompletedTasksToFile(const char* filename, struct CompletedTask* completedTasks) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        exit(1);
    }

    struct CompletedTask* current = completedTasks;
    while (current != NULL) {
        fprintf(file, "%s\n", current->task->TaskName);
        current = current->next;
    }

    fclose(file);
}
void saveTasksToFile(const char* filename, struct Task* taskList) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        exit(1);
    }

    struct Task* current = taskList;
    while (current != NULL) {
        fprintf(file, "%s %s %s %s\n", current->TaskName, current->Subject, current->Type, current->SubmissionDate);
        current = current->next;
    }

    fclose(file);
}

struct node1
{
    char name[100];
    char category[10];
    long long int phone;
    char cf[20];
    struct node1 *prev;
    struct node1 *next;
} *first = NULL, *last = NULL;

void makeNameProperCase(char *name)
{
    int i = 0;

    if (name[i] >= 'a' && name[i] <= 'z')
    {
        name[i] = name[i] - 32;
        i++;
    }

    while (name[i] != '\0')
    {
        if (name[i] >= 'A' && name[i] <= 'Z')
            name[i] = name[i] + 32;
        i++;
    }
}

// Function to insert a new friend into the linked list
void insert()
{
    //... (your existing insert code)
    system("cls");
    SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
    
    int op, c;
    char exitValue[] = "exit";

  
        struct node1 *nn;
        nn = (struct node1 *)malloc(sizeof(struct node1));
        printf("\nWELCOME TO FRIENDS LIST\n");
        SetConsoleTextAttribute(h,14);
        printf("\nEnter Name of the Friend\n ");
        scanf(" %[^\n]", nn->name);
        makeNameProperCase(nn->name);
        SetConsoleTextAttribute(h,10);
        printf("\nSelect friend category\n");
        SetConsoleTextAttribute(h,9);
		printf("\n1). School Friend\n");
		SetConsoleTextAttribute(h,13);
		printf("\n2). Intermediate Friend\n");
		SetConsoleTextAttribute(h,12);
		printf("\n3). College Friend\n");
		SetConsoleTextAttribute(h,14);
		printf("\nYour Option: \n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            strcpy(nn->category, "school");
            break;
        case 2:
            strcpy(nn->category, "inter");
            break;
        case 3:
            strcpy(nn->category, "college");
            break;
        default:
            printf("Invalid option\n");
            free(nn);
            return;
        }
        SetConsoleTextAttribute(h,3);
        printf("\nEnter the phone number: \n");
        scanf("%lld", &nn->phone);
        SetConsoleTextAttribute(h,6);
        printf("\nEnter:");
        SetConsoleTextAttribute(h,9);
		printf("\n1). Close Friend\n");
		SetConsoleTextAttribute(h,12);
		printf("\n2). Not Close Friend\n");
		SetConsoleTextAttribute(h,14);
		printf("\nYour Option: \n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            strcpy(nn->cf, "Close friend");
            break;
        case 2:
            strcpy(nn->cf, "Not close friend");
            break;
        default:
        	SetConsoleTextAttribute(h,11);
            printf("Invalid Option\n");
            free(nn); 
            return;
        }

        if (first == NULL)
        {
            first = nn;
            last = nn;
        }
        else
        {
            nn->prev = last;
            last->next = nn;
            last = nn;
        }
        last->next = NULL;
        first->prev = NULL;
        SetConsoleTextAttribute(h,11);
        printf("\nDesired Details of your Friend are Saved to the Friends list Successfully\n");
        SetConsoleTextAttribute(h,14);
        printf("\nThis Page will be redirected to the Friends list Menu in 5 seconds\n");
        sleep(6);
        

}

// Function to delete a friend from the linked list
void del()
{   system("cls");
    SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
    
    // ... (your existing delete code)
	struct node1 *temp;
    char delname[100];
    int flag = 0;
    if (first == NULL)
    {   SetConsoleTextAttribute(h,14);
        printf("Friends list is empty!!\n");
        return;
    }
    SetConsoleTextAttribute(h,14);
    printf("\nEnter Name of the Friend to Delete from Friends list: \n");
    scanf(" %[^\n]", delname);
    temp = first;
    while (temp != NULL)
    {
        if (strcmpi(temp->name, delname) == 0)
        {
            flag = 1;
            break;
        }
        else
            temp = temp->next;
    }
    if (flag == 1)
    {
        if (temp == first)
            first = temp->next;
        if (temp == last)
            last = temp->prev;
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
SetConsoleTextAttribute(h,12);
        printf("\n%s has been Deleted from Friends list\n", delname);
        free(temp);
    }
	else
	{
	SetConsoleTextAttribute(h,10);
        printf("Name not found in the friends list\n");}
    SetConsoleTextAttribute(h,14);
        printf("\nThis Page will be redirected to the Friends list Menu in 5 seconds\n");
        sleep(6);
        
}

// Function to search for a friend in the linked list
void search()
{    system("cls");
    SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
    
    // ... (your existing search code)
    struct node1 *temp;
    char key[100];
    int flag = 0;
    if (first == NULL)
    {   SetConsoleTextAttribute(h,11);
        printf("\nFriends list is empty!!\n");
        return;
    }
    SetConsoleTextAttribute(h,10);
    printf("\nEnter Name of the Friend to Search in Friends list: \n");
    scanf(" %[^\n]", key);
    temp = first;
    while (temp != NULL)
    {
        if (strcmpi(temp->name, key) == 0)
        {
            flag = 1;
            break;
        }
        else
            temp = temp->next;
    }
    if (flag == 1)
    {
    	SetConsoleTextAttribute(h,13);
        printf("\n%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
    }
    else
        printf("Name not found in the friends list\n");
    SetConsoleTextAttribute(h,14);
        printf("\nThis Page will be redirected to the Friends list Menu in 5 seconds\n");
        sleep(6);
        
}

// Function to perform a bubble sort on the linked list
void bubbleSort()
{
    // ... (your existing bubble sort code)
    if (first == NULL)
    {  SetConsoleTextAttribute(h,11);
        printf("Friends list is empty!!\n");
        return;
    }

    int swapped;
    struct node1 *temp;
    struct node1 *left = NULL;

    do
    {
        swapped = 0;
        temp = first;

        while (temp->next != left)
        {
            if (strcmpi(temp->name, temp->next->name) > 0)
            {
                char tempName[100];
                char tempCategory[10];
                long long int tempPhone;
                char tempCF[20];

                strcpy(tempName, temp->name);
                strcpy(tempCategory, temp->category);
                tempPhone = temp->phone;
                strcpy(tempCF, temp->cf);

                strcpy(temp->name, temp->next->name);
                strcpy(temp->category, temp->next->category);
                temp->phone = temp->next->phone;
                strcpy(temp->cf, temp->next->cf);

                strcpy(temp->next->name, tempName);
                strcpy(temp->next->category, tempCategory);
                temp->next->phone = tempPhone;
                strcpy(temp->next->cf, tempCF);

                swapped = 1;
            }
            temp = temp->next;
        }
        left = temp;
    } while (swapped);
}

// Function to view friends based on different criteria
void view()
{
    // ... (your existing view code)
    system("cls");
	SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
    
    if (first == NULL)
    {  SetConsoleTextAttribute(h,11);
        printf("\nFriends list is empty!!\n");
        return;
    }

    int op, v;
    SetConsoleTextAttribute(h,3);
    printf("\nView Friends List By: \n");
    SetConsoleTextAttribute(h,4);
	printf("\n1). By Category\n");
	SetConsoleTextAttribute(h,5);
	printf("\n2). By Type\n");
	SetConsoleTextAttribute(h,6);
	printf("\n3). In Sorted view\n");
	SetConsoleTextAttribute(h,7);
	printf("\n4). Recently Added\n");
	SetConsoleTextAttribute(h,8);
	printf("\nYour option: \n");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
    	system("cls");
	SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
        SetConsoleTextAttribute(h,10);
		printf("\nEnter:\n");
		SetConsoleTextAttribute(h,5);
		printf("\n1). To View School Friends\n");
		SetConsoleTextAttribute(h,6);
		printf("\n2). To View Intermediate Friends\n");
		SetConsoleTextAttribute(h,4);
		printf("\n3). To View College Friends\n");
		SetConsoleTextAttribute(h,2);
		printf("\nYour option: \n");
        scanf("%d", &v);
        switch (v)
        {
        case 1:
            for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            {
                if (strcmpi(temp->category, "school") == 0)
                    printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
            }
            printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
        case 2:
            for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            {
                if (strcmpi(temp->category, "inter") == 0)
                    printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
            }
            break;
        case 3:
            for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            {
                if (strcmpi(temp->category, "college") == 0)
                    printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
            }
            printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
        default:
            printf("Invalid option\n");
        }
        break;
    case 2:
    		system("cls");
	SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
        SetConsoleTextAttribute(h,3);
		printf("\nEnter :\n");
        SetConsoleTextAttribute(h,4);
		printf("\n1). To View Close Friends\n");
		SetConsoleTextAttribute(h,5);
		printf("\n2). To View Non Close Friends\n");
		SetConsoleTextAttribute(h,6);
		printf("\nYour option: \n");
        scanf("%d", &v);
        switch (v)
        {
        case 1:
            for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            {
                if (strcmpi(temp->cf, "Close friend") == 0)
                    printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
            }
            printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
        case 2:
            for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            {
                if (strcmpi(temp->cf, "Not close friend") == 0)
                    printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
            }
            printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
        default:
        	SetConsoleTextAttribute(h,11);
            printf("Invalid option\n");
        }
        break;
    case 3:
        bubbleSort();
        for (struct node1 *temp = first; temp != NULL; temp = temp->next)
            printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
        printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
    case 4:
        for (struct node1 *temp = last; temp != NULL; temp = temp->prev)
            printf("%s %s %lld %s\n", temp->name, temp->category, temp->phone, temp->cf);
        printf("\nPress any key to return to Friends list Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;
    default:
    	SetConsoleTextAttribute(h,15);
        printf("Invalid option\n");
    }
}

// Function to read friend data from a file into the linked list
void readFriendsFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {   SetConsoleTextAttribute(h,14);
        printf("Error opening the file for reading.\n");
        return;
    }

    struct node1 *nn;

    while (1)
    {
        nn = (struct node1 *)malloc(sizeof(struct node1));
        if (nn == NULL)
        {   SetConsoleTextAttribute(h,1);
            printf("Memory allocation failed.\n");
            exit(1);
        }

        if (fscanf(file, " %[^\n]", nn->name) == EOF)
        {
            free(nn);
            break;
        }

        makeNameProperCase(nn->name);

        fscanf(file, " %9s %lld %19s", nn->category, &nn->phone, nn->cf);

        nn->prev = NULL;
        nn->next = NULL;

        if (first == NULL)
        {
            first = nn;
            last = nn;
        }
        else
        {
            nn->prev = last;
            last->next = nn;
            last = nn;
        }
    }

    fclose(file);
}

// Function to write friend data from the linked list to a file
void writeFriendsToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {    SetConsoleTextAttribute(h,9);
        printf("Error opening the file for writing.\n");
        return;
    }

    struct node1 *temp = first;

    while (temp != NULL)
    {
        fprintf(file, "%s\n%s\n%lld\n%s\n", temp->name, temp->category, temp->phone, temp->cf);
        temp = temp->next;
    }

    fclose(file);
}


void receive_messages(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == SOCKET_ERROR || bytes_received == 0) {
            perror("Error receiving message");
            break;
        }

        // Print the message with red color (received message)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("%s\n", buffer);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
}

int main() {
	int op;
	
	T:do{
		
	system("cls");
	SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,11);
		printf("******************************************************************************\n");
		SetConsoleTextAttribute(h,15);
		printf("\n");
		printf("SELECT OPTION:");
		printf("\n");
	SetConsoleTextAttribute(h,4);
	printf("\n");
	printf("1) OFFICIAL\n");
		SetConsoleTextAttribute(h,9);
		printf("\n");
	printf("2) UNOFFICIAL\n");
	printf("\n");
	SetConsoleTextAttribute(h,6);
	printf("3) FAQ`S\n");
	printf("\n");
	SetConsoleTextAttribute(h,10);
	printf("4) ABOUT US\n");
	printf("\n");
	SetConsoleTextAttribute(h,11);
	printf("5) CONTACT US\n");
	printf("\n");
	SetConsoleTextAttribute(h,13);
	printf("6) FEEDBACK\n");
	printf("\n");
	SetConsoleTextAttribute(h,14);
	printf("7) REPORT COLLECTOR\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("8) EXIT\n");
	printf("\n");
	//SetConsoleTextAttribute(h,10);
	scanf("%d",&op);
	if(op==2){
	
		QQ:
		int opp;
		
			SetConsoleTextAttribute(h,12);
		system("cls");
				SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                              UNOFFICIAL!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,1);
	printf("\n");
	printf("1)CHAT\n");
	printf("\n");
		SetConsoleTextAttribute(h,10);
		printf("2)FRIENDS LIST\n");
		printf("\n");
		SetConsoleTextAttribute(h,11);
			printf("3)MUSIC PLAYER\n");
			printf("\n");
		SetConsoleTextAttribute(h,13);
		printf("4)EXIT To Main Menu\n");
		printf("\n");
		SetConsoleTextAttribute(h,14);
		printf("Enter Your Option\n");
		printf("\n");
	SetConsoleTextAttribute(h,8);
	scanf("%d",&opp);
	if(opp==4){
		goto T;
	}
	system("cls");
	if(opp==1){
    WSADATA wsa_data;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    int result;
    system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             SOCIAL MEDIA!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        perror("Error creating client socket");
        WSACleanup();
        return 1;
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    char x[15];
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        //printf("%s\n", buffer);
    printf("\nEnter IP address of the Server\n");
    scanf("%s",x);
    server_addr.sin_addr.s_addr = inet_addr(x); // Server IP address
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
     SetConsoleTextAttribute(h,11);
    // Connect to the server
    result = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR) {
        perror("Error connecting to the server");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Create a separate thread for receiving messages
    HANDLE receive_thread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)receive_messages, (LPVOID)client_socket, 0, NULL);

    if (receive_thread == NULL) {
        perror("Error creating thread");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Send and receive messages in the main thread
    char buffer[BUFFER_SIZE];

    while (1) {
        //printf("Enter a message (or type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        //if (strcmp(buffer, "exit") == 0) {
        //    break;
        //}

        // Send the message to the server
        if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            perror("Error sending message");
            break;
        }
    }

    // Wait for the receive thread to finish
    WaitForSingleObject(receive_thread, INFINITE);

    // Close the receive thread handle
    CloseHandle(receive_thread);

    // Close the socket
    closesocket(client_socket);

    // Clean up Winsock
    WSACleanup();
}
if(opp==2){
	
    int choice;

    // Load friend data from the file when the program starts
    readFriendsFromFile("friends.txt");
    SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
                SetConsoleTextAttribute(h,14);

    while (1)
    
    { system("cls");
	SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             FRIENDS LIST!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
                SetConsoleTextAttribute(h,14);
        printf("\nFRIENDS MENU:\n");
        SetConsoleTextAttribute(h,9);
		printf("\n1). Insert a Friend\n");
		SetConsoleTextAttribute(h,13);
		printf("\n2). Delete a Friend\n");
		SetConsoleTextAttribute(h,12);
		printf("\n3). Search For a Friend\n");
		SetConsoleTextAttribute(h,11);
		printf("\n4). View Friends List\n");
		SetConsoleTextAttribute(h,10);
		printf("\n5). Exit\n");
		SetConsoleTextAttribute(h,9);
		printf("\nYour choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert();
            writeFriendsToFile("friends.txt");
            break;
        case 2:
            del();
            writeFriendsToFile("friends.txt");
            break;
        case 3:
            search();
            break;
        case 4:
            view();
            break;
        case 5:
            // Save friend data to the file before exiting
            writeFriendsToFile("friends.txt");
            //printf("Exiting...\n");
            goto QQ;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
if(opp==3){
	int i,ao,op;
   char N[M],k[M],o;
   struct node *temp;

do{   system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                //viewCompletedTasks(completedTasks);
   SetConsoleTextAttribute(h,12);
	printf("\nMENU:\n");
	SetConsoleTextAttribute(h,3);
	printf("\n1). RECENTLY PLAYED\n");
	SetConsoleTextAttribute(h,13);
	printf("\n2). ALBUMS\n");

	SetConsoleTextAttribute(h,14);
	printf("\n3). EXIT\n");
	scanf("%d",&op);
	switch(op){
		case 1:  system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
		
		
		SetConsoleTextAttribute(h,11);
		printf("\nRECENTLY PLAYED SONGS: \n");
               	for(int t=trp;t>0;t--)
                    printf("%s\n",RP[t]);
                printf("\nPress any key to return to Workshop Menu");
                fflush(stdin);
                scanf("%c",&g);
				break;
		case 2: 
		system("cls");
      SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             MUSIC PLAYER!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
		
		SetConsoleTextAttribute(h,11);
		Albumdisplay();
		        break;
	    
		case 3: goto QQ;
	}
}
while(op!=4);
	
}
else
goto QQ;
}
if(op==1){
	int xp;
	R:
		system("cls");
		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                              OFFICIAL!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,4);
	printf("\n");
		SetConsoleTextAttribute(h,10);
	printf("1)WORKSPACE\n");
	printf("\n");
		SetConsoleTextAttribute(h,9);
	printf("2)COMING SOON\n");
		printf("\n");
		SetConsoleTextAttribute(h,13);
	printf("3)EXIT To Main Menu\n");
		SetConsoleTextAttribute(h,14);
			printf("\n");
	printf("Enter Your Choice\n");
	scanf("%d",&xp);
	system("cls");
	if(xp==3){
		goto T;
	}
	if(xp==2){
		SetConsoleTextAttribute(h,6);
		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                              OFFICIAL!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,4);
		printf("\nCOMING SOON.....Some New features are On Their Way...\n");
		printf("\n");
		SetConsoleTextAttribute(h,2);
		printf("We will Ping you with the necessary Updates...Stay Tuned With US\n");
		printf("\n");
	SetConsoleTextAttribute(h,15);	
		printf("You will be redirected to the Official menu in 15 seconds....");
	sleep(15);
	}
	if(xp==1){
		system("cls");
	
		struct Task* taskList = NULL;
    struct BSTNode* bstRoot = NULL;
    struct CompletedTask* completedTasks = NULL;
       //schoolfmain();
    int choice, subChoice;
    char temp[50];

    readTasksFromFile("data.txt", &taskList, &bstRoot);
    readCompletedTasksFromFile("completed_tasks.txt", &completedTasks, taskList);
	do {  
    
    void fmain();
        system("cls");
        char g;
         displayMainMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline
  system("cls");
        
        switch (choice) {
            case 1: {
			
            		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                printf(ANSI_LIGHTGREEN "\nEnter Task Name: ");
                scanf("%s", temp);
                char taskName[50];
                strcpy(taskName, temp);
                SetConsoleTextAttribute(h,14);
                printf("\n");
                printf("Enter Subject: ");
                scanf("%s", temp);
                char subject[50];
                strcpy(subject, temp);
                SetConsoleTextAttribute(h,3);
                printf("\n");
                printf("Enter Type: ");
                scanf("%s", temp);
                char type[50];
                strcpy(type, temp);
                SetConsoleTextAttribute(h,13);
                printf("\n");
                printf("Enter Submission Date (YYYY-MM-DD): ");
                scanf("%s", temp);
                char submissionDate[12];
                strcpy(submissionDate, temp);

                struct Task* newTask = createTask(taskName, subject, type, submissionDate);
                insertTask(&taskList, newTask);
                bstRoot = insertBST(bstRoot, newTask);
                SetConsoleTextAttribute(h,12);
                saveTasksToFile("data.txt", taskList);
                saveCompletedTasksToFile("completed_tasks.txt", completedTasks);
                printf("\nTask added successfully!\n");
                 SetConsoleTextAttribute(h,14);
                printf("\nPress any key to return to Workshop Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;}
            

            case 2:{
			
            		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
            	SetConsoleTextAttribute(h,10);
                printf("\nTasks Sorted by Submission Date:\n\n");
                inorderTraversal(bstRoot);
                SetConsoleTextAttribute(h,14);
                printf("\nPress any key to return to Workshop Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;}
            

            case 3:{
		
                do{system("cls");
                		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                    displaySearchMenu();
                    scanf("%d", &subChoice);
                    getchar(); // Consume newline

                    switch (subChoice) {
                        case 1:
                        	{        system("cls");
									SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                            printf( "\nEnter Submission Date to Search (YYYY-MM-DD): ");
                            scanf("%s", temp);
                            searchBySubmissionDate(bstRoot, temp);
                            SetConsoleTextAttribute(h,14);
                            printf("\nPress any key to return to Search Menu");
                            fflush(stdin);
                              scanf("%c",&g);
                            if(g>0)
                             break;}

                        case 2:
                        	
                        		{system("cls");
								SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                        	SetConsoleTextAttribute(h,14);
                            printf("\nEnter Subject to Search: ");
                            //char te[100];
                            scanf("%s", temp);
                            searchBySubject(&taskList, temp);
                            SetConsoleTextAttribute(h,14);
                            SetConsoleTextAttribute(h,14);
                            printf("\nPress any key to return to Search Menu");
                             fflush(stdin);
                             scanf("%c",&g);
                             if(g>0)
                              break;}

                        case 3:
                        	{system("cls");
							SetConsoleTextAttribute(h,10);
                        		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                            printf("\nEnter Type to Search: ");
                            scanf("%s", temp);
                            searchByType(&taskList, temp);
                            SetConsoleTextAttribute(h,14);
                            printf("\nPress any key to return to Search Menu");
                            fflush(stdin);
                            scanf("%c",&g);
                            if(g>0)
                            break;}

                        case 4:
                            {system("cls");
							break;}

                        default:
                           {system("cls");
							 printf(ANSI_RED "\nInvalid choice!\n" ANSI_RESET);
                            break;}
                    }
                } while (subChoice != 4);
                break;}

            case 4: 
            	{
				system("cls");
				SetConsoleTextAttribute(h,14);
            		SetConsoleTextAttribute(h,14);
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             WORKSPACE!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
                printf("\nEnter Task Name to Mark as Completed: ");
                scanf("%s", temp);
                struct Task* current = taskList;
                while (current != NULL) {
                    if (strcmp(current->TaskName, temp) == 0) {
                        struct CompletedTask* newCompletedTask = createCompletedTask(current);
                        insertCompletedTask(&completedTasks, newCompletedTask);
                        printf(ANSI_GREEN "\nTask marked as completed!\n" ANSI_RESET);
                      break;
                    }
                    current = current->next;
                }
                if (current == NULL) {
                    printf(ANSI_RED "\nTask not found!\n" ANSI_RESET);
                }
                SetConsoleTextAttribute(h,14);
                printf("\nPress any key to return to Workshop Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;}
            

            case 5: 
            	{system("cls");
						SetConsoleTextAttribute(h,14);
	               printf("******************************************************************************\n");
	               printf("\n");
                	SetConsoleTextAttribute(h,15);
	                printf("                            C");
	               SetConsoleTextAttribute(h,12);
	               printf("H");
	                SetConsoleTextAttribute(h,10);
	                  printf("A");
	                   SetConsoleTextAttribute(h,11);
	                    printf("M");
	                   SetConsoleTextAttribute(h,6);
	                 printf("P");
	                  SetConsoleTextAttribute(h,15);
	                   printf("S UNITY");
	                      SetConsoleTextAttribute(h,13);
                           printf("!!!\n");
                    	printf("\n");
                        	SetConsoleTextAttribute(h,12);
                          	printf("                             WORKSPACE!!\n");
                        	SetConsoleTextAttribute(h,11);
                        	printf("\n");
	                  	printf("******************************************************************************\n");
                viewCompletedTasks(completedTasks);
                SetConsoleTextAttribute(h,14);
                printf("\nPress any key to return to Workshop Menu");
                fflush(stdin);
                scanf("%c",&g);
                if(g>0)
                break;}
            

            case 6: 
			{system("cls");
			saveTasksToFile("data.txt", taskList);
    saveCompletedTasksToFile("completed_tasks.txt", completedTasks);
    SetConsoleTextAttribute(h,15);
               //printf("Exiting...\n");
			   break;}

            default:system("cls");
            	SetConsoleTextAttribute(h,12);
                printf("\nInvalid choice!\n");
                break;
        }
    } while (choice != 6);

    // Cleanup: Free memory allocated for tasks, BST nodes, and completed tasks
    while (taskList != NULL) {
        struct Task* temp = taskList;
        taskList = taskList->next;
        free(temp);
    }

    // You need to free the BST nodes here.

    while (completedTasks != NULL) {
        struct CompletedTask* temp = completedTasks;
        completedTasks = completedTasks->next;
        free(temp);
    }

		
	}
	goto R;
}
if(op==3)
{   
    SetConsoleTextAttribute(h,14);
    
    char m1,E;
    system("cls");
//	SetConsoleTextAttribute(h,14);
    
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                               FAQ'S!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
		printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,1);
	printf("\n");
SetConsoleTextAttribute(h,10);
printf("HELP : \n");
SetConsoleTextAttribute(h,9);
printf("\n");
printf("FREQUENTLY ASKED QUESTIONS (FAQ'S)\n");
printf("\n");
SetConsoleTextAttribute(h,12);
printf("******************************************************************************\n");
printf("\n");
q=fopen("HELP(FAQ_S).txt","r");
//SetConsoleTextAttribute(h,14);
while(feof(q)==0)
		{   //SetConsoleTextAttribute(h,14);
			m1=getc(q);
			SetConsoleTextAttribute(h,14);
			printf("%c",m1);
		}
fclose(q);
SetConsoleTextAttribute(h,11);
printf("____________________________________________________________________________________________\n");
printf("Press any key to return to MAIN MENU : ");
fflush(stdin);
scanf("%c",&E);
}


if(op==4)
 {  char a;
 system("cls");
 SetConsoleTextAttribute(h,14);
    
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                               ABOUT US!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
	printf("******************************************************************************\n");

SetConsoleTextAttribute(h,14);
	
	printf("The ........ Is a demo model of a social media platform for college level where\nstudents can unite and have fun along with the opportunity to share their \nknowledge among themselves leading to the collective development of the \nstudents in a joyful way. It provides students a base for \ntheir refreshment. It also helps them in gaining information about the technical and \nnon technical aspects and events of the college. This application is currently with\nlimited features"); 
	SetConsoleTextAttribute(h,9);
	printf("\n1.Official Section\n");
	SetConsoleTextAttribute(h,14);
    printf("# This section deals with the official aspects of the college and students.");
    printf("\n# It consists of a workspace where students can plan and save their tasks to be done\nat a single place and makes them easier to check and accomplish their tasks.");
    printf("\n# The remaining aspects of official section like the official information,timetables\nattendance , reports will be available in our future web-application");
   SetConsoleTextAttribute(h,9);
    printf("\n2.Unofficial Section\n");
    SetConsoleTextAttribute(h,14);
    printf("# The interesting and fun part in the application is hidden in this part of the \napplication.");
  printf("\n# This is where students can come together and chat,listen music and more");
    printf("\n# For now this has the following options");
    SetConsoleTextAttribute(h,12);
   	 printf("\n$ Chat");
   	 SetConsoleTextAttribute(h,11);
   	 printf("\n$ Music Player");
   	 SetConsoleTextAttribute(h,10);
   	 printf("\n$ Friends list");
   	 SetConsoleTextAttribute(h,14);
printf("\nIn our modern lives this platform makes the learning more intersting for the students\nalong with providing a platform to collabarate with their peers and help them\nmaking their college life better.....");
printf("\nWe have our own organistaion/team name as SHM. For any queries you can also contact us\nthrough team mail.");
printf("For further interesting features stay tuned to us on linkedin,insta,X..\n");
printf("The actual fun is on the way!!!!!!!...\n");
	SetConsoleTextAttribute(h,11);
	
printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,12);
printf("\n");
printf("\n");
printf("ORGANISATION DETAILS :\n");
printf("\n");
	SetConsoleTextAttribute(h,14);
printf("NAME : SHM\n");
printf("\n");
	SetConsoleTextAttribute(h,11);
printf("______________________________________________________________________________\n");
printf("\n");
	SetConsoleTextAttribute(h,12);
printf("TEAM MEMBERS :\n");
printf("\n");
	SetConsoleTextAttribute(h,14);
printf("1.) T.SAI SUSHANTH\n");
printf("2.) L.HARI CHARAN\n" );
printf("3.) S.MAYAN BRAHMAM\n");
printf("3.) V.PAVAN PRANEETH\n");
printf("\n");
	SetConsoleTextAttribute(h,11);
printf("******************************************************************************\n");
	SetConsoleTextAttribute(h,10);
printf("Press any key to return to Main Menu : ");
fflush(stdin);
scanf("%c",&a);
}

if(op==5)
{FILE *cu;
char m3,C;
system("cls");
SetConsoleTextAttribute(h,14);
    
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                             CONTACT US!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
	printf("******************************************************************************\n");
SetConsoleTextAttribute(h,10);
printf("\n");
cu=fopen("CONTACT US.txt","r");
SetConsoleTextAttribute(h,14);
while(feof(cu)==0)
		{
			m3=getc(cu);
			printf("%c",m3);
		}
fclose(cu);
printf("_______________________________________________________________________________\n");
SetConsoleTextAttribute(h,13);
printf("Press any key to return to MAIN MENU : ");
fflush(stdin);
scanf("%c",&C);
}

if(op==6)
{FILE *fe;
system("cls");
char m4,name[20],F,n1[5]="FBK";
SetConsoleTextAttribute(h,14);
    
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                          FEEDBACK COLLECTOR!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
	printf("******************************************************************************\n");
SetConsoleTextAttribute(h,5);
	printf("\n");
//printf("******************************************************************************\n");
printf("\n");
SetConsoleTextAttribute(h,11);
printf("ENTER USERNAME : ");
scanf("%s",name);
strcat(name,n1);
fe=fopen(name,"w");
SetConsoleTextAttribute(h,10);
printf("\n PLEASE GIVE YOUR FEEDBACK.....IT MEANS A LOT TO US\n");
printf("\n Click Ctrl+z to terminate\n");
while((m4=getchar())!=EOF)
fputc(m4,fe);
fclose(fe);
SetConsoleTextAttribute(h,14);
printf("THANK YOU FOR THE FEEDBACK!!\n");
printf("Kindly Forward the (username)FBK file to the Mail provided!(shm181407@gmail.com)\n");
SetConsoleTextAttribute(h,15);
printf("____________________________________________________________________________________\n");
printf("\n");
SetConsoleTextAttribute(h,3);
printf("Press any key to return to MAIN MENU : ");
fflush(stdin);
scanf("%c",&F);
}

if(op==7)
{FILE *re;
system("cls");
SetConsoleTextAttribute(h,14);
    
	printf("******************************************************************************\n");
	printf("\n");
	SetConsoleTextAttribute(h,15);
	printf("                            C");
	SetConsoleTextAttribute(h,12);
	printf("H");
	SetConsoleTextAttribute(h,10);
	printf("A");
	SetConsoleTextAttribute(h,11);
	printf("M");
	SetConsoleTextAttribute(h,6);
	printf("P");
	SetConsoleTextAttribute(h,15);
	printf("S UNITY");
	SetConsoleTextAttribute(h,13);
    printf("!!!\n");
	printf("\n");
	SetConsoleTextAttribute(h,12);
	printf("                           REPORT COLLECTOR!!\n");
	SetConsoleTextAttribute(h,11);
	printf("\n");
	printf("******************************************************************************\n");
SetConsoleTextAttribute(h,5);
SetConsoleTextAttribute(h,10);
char m5,R,name1[20],n2[5]="REP";
	//printf("REPORT COLLECTOR : \n");
	printf("\n");
//printf("*************************************************************************************************************************************************\n");
printf("\n");
SetConsoleTextAttribute(h,6);
printf("ENTER USERNAME : ");
scanf("%s",name1);
strcat(name1,n2);
re=fopen(name1,"w");
SetConsoleTextAttribute(h,11);
printf("\n PLEASE NOTIFY US WITH THE BUGS THAT YOU COME ACROSS WHILE USING CHAMPS Unity\n");
printf("\n Click Ctrl+Z to stop \n");
while((m5=getchar())!=EOF)
fputc(m5,re);
fclose(re);
SetConsoleTextAttribute(h,14);
printf("THANK YOU FOR THE REPORT.WE WILL PUT OUR COMPLETE EFFORTS IN RESOLVING THE ISSUE!!\n");
printf("Kindly forward the (username)REP file to the mail provided!(shm181407@gmail.com)\n");
SetConsoleTextAttribute(h,4);
printf("________________________________________________________________________________\n");
printf("\n");
SetConsoleTextAttribute(h,9);
printf("Press any key to return to MAIN MENU : ");
fflush(stdin);
scanf("%c",&R);
}
}while(op<=7);
//return 0;

}
