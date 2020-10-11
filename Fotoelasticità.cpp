#include<stdio.h>
#include<math.h>
#include"bmp_loader.cpp"
#include"calcolo_4_img_generalizzato.cpp"
#include"calcolo_6_img_MS.cpp"
#include"ritardo_4_img.cpp"
#include"isoclina_4_img.cpp"

int main()
{
	
	
	
	char img_name[100];

	int risposta;
	system("color a");
    printf("\nProgramma per il calcolo automatizzato di frange fotoelastiche\n");
    printf("scegliere metodo utilizzato:\n\t\t\t\t1)4 immagini generalizzato\n\t\t\t\t");
    printf("2)6 immagini (prof. Giovanni Petrucci)\n\t\t\t\t3)calcolo solo ritardo 4 immagini\n\t\t\t\t4)calcolo solo isoclina 4 immagini\nrisposta:\t");
    
	
	scanf("%d",&risposta);
	printf("Inserire nome serie immagini:\nrisposta:\t");
	scanf(" %s",img_name);
	

switch(risposta)
{
	case 1: calcolo_4_img_generalizzato(img_name);
	break;
	case 2: calcolo_6_img(img_name);
	break;
	case 3: ritardo_4_img_Ajovalasit(img_name);
	break;
	case 4: isoclina_4_img_Ajovalasit(img_name);
	break;
}
printf("\nfinito!!! ");
system("pause");
return 0;
        
}

