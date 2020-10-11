
#define PI 3.14159265

void calcolo_4_img_generalizzato(char* img_name)
{
   Immagine_bitmap foto[4];
   char names[100];
   int i;
   float *angolo_isoclina;
   float *angolo_ritardo;
   unsigned int *angolo_int_isoclina;
   unsigned int *angolo_int_ritardo;
   float tempor_I=0,temp_argv;
   float I[4];
   int risposta;
   int min_iso,max_iso;
   FILE *fw;
   fw=fopen("risultato ritardo 4img generalizzato.txt","wb");

   printf("\nSi desidera rilevare nel risultato un intervallo generico di isocline? 1=s 2=n");
   scanf("%d",&risposta);
   if(risposta==1)
   {
   	printf("\nInserire i valori in gradi:\n\t\tlimite inferiore intervallo:\t");
   	scanf("%d",&min_iso);
   	printf("\nlimite superiore intervallo:\t");
	scanf("%d",&max_iso);    
   }


     //caricamento immaginie allocazione memoria vettori isoclina e ritardo
for(i=0;i<4;i++)
	{
		sprintf(names,"%s (%d).bmp",img_name,i+1);
	    printf("caricamento immagine: %s...\n",names);
	    foto[i]=carica_immagine(names);	
	    
	}

    angolo_isoclina = (float*)malloc(foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(float));
    angolo_ritardo  = (float*)malloc(foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(float));
    angolo_int_isoclina     = (unsigned int*)malloc(foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(unsigned int));
    angolo_int_ritardo    = (unsigned int*)malloc(foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(unsigned int));
   	//caricamento immaginie allocazione memoria vettori isoclina e ritardo
   
   //printf("\ncalcolo in corso, attendere prego...\t");
 for(i=0;i<foto[0].altezza_immagine*foto[0].larghezza_immagine;i++)
 {
 	//media dei tre canali RGB
 	for(int k=0;k<4;k++)
 	{
 		I[k]=(float)(foto[k].red[i]+foto[k].green[i]+foto[k].blue[i])/3.0;
	}
 	

	tempor_I=(float)(I[0]+I[1]-(2*I[3]))/((2*I[2])-(I[0]+I[1]));
	angolo_isoclina[i]=(0.5)*atan(tempor_I);// calcolo isoclina
	temp_argv=(float)(2*I[2]-(I[0]+I[1]))/((I[1]-I[0])*cos(2*angolo_isoclina[i]));
	angolo_ritardo[i]=(float)(1.0/(2.0*PI))*atan(temp_argv);// calcolo ritardo
	
	angolo_isoclina[i]*=57.2958; // angoli in gradi
	//angolo_ritardo[i]*=57.2958;  // angoli in gradi
	angolo_ritardo[i]+=0.25;
	if(angolo_isoclina[i]<0) angolo_isoclina[i]+=90;
	
	if(risposta==1)
	{
		if(angolo_isoclina[i]<max_iso && angolo_isoclina[i]>min_iso){ angolo_isoclina[i]=0;}// mappatura intervallo angoli	
	}	
	angolo_int_isoclina[i]=angolo_isoclina[i];// amplificazione luminosita	
	angolo_int_ritardo[i]=angolo_ritardo[i]*1000/2;    

 }
 int mezzo;
 mezzo=(foto[0].larghezza_immagine*foto[0].altezza_immagine)/2;
 
 for(int j=mezzo;j<mezzo+foto[0].larghezza_immagine;j++)
 {
 	
 	fprintf(fw,"%f %d \n",angolo_ritardo[j],angolo_int_ritardo[j]);
 }
 
 	salva_bmp("risultato_isoclina_4img_generalizzato.bmp",foto[0].header,angolo_int_isoclina,angolo_int_isoclina,angolo_int_isoclina,foto[0].larghezza_immagine,foto[0].altezza_immagine,0,foto[0].size);
    
	salva_bmp("risultato_ritardo_4img_generalizzato.bmp",foto[0].header,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[0].larghezza_immagine,foto[0].altezza_immagine,10,foto[0].size);
	//salva_ppm(nome_sav,angolo_int_isoclina,angolo_int_isoclina,angolo_int_isoclina,foto[2].larghezza_immagine,foto[2].altezza_immagine,10);
	//salva_ppm(nome_sav,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[2].larghezza_immagine,foto[2].altezza_immagine,10);
	free(angolo_isoclina);
    free(angolo_ritardo);
    free(angolo_int_isoclina);
    free(angolo_int_ritardo);
    
    
    return ;
}
