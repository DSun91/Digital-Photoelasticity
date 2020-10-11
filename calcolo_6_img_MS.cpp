void calcolo_6_img(char* img_name)
{
   Immagine_bitmap foto[6];
   char names[100];
   int i;
   float *angolo_isoclina;
   float *angolo_ritardo;
   unsigned int *angolo_int_isoclina;
   unsigned int *angolo_int_ritardo;
   float tempor_I=0,temp_argv,N_1,N_2,D;
   float I[6];
   int risposta;
   int min_iso,max_iso;
   FILE *fw;
   fw=fopen("risultato ritardo 6img.txt","wb");
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
for(i=0;i<6;i++)
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
   
   printf("\ncalcolo in corso, attendere prego...\t");
   
 for(i=0;i<foto[0].altezza_immagine*foto[0].larghezza_immagine;i++)
 {
 	//media dei tre canali RGB
 	for(int k=0;k<6;k++)
 	{
 		I[k]=(float)(foto[k].red[i]+foto[k].green[i]+foto[k].blue[i])/3.0;
	}
 	

	
	
	    
	tempor_I=(float)(I[2]-I[3])/(I[0]-I[1]);
	angolo_isoclina[i]=(float)(0.25)*atan(tempor_I);
	if(angolo_isoclina[i]<0) angolo_isoclina[i]+=(PI/2.0);
	
	N_1=(float)((float)((I[0]+I[1]+I[2]+I[3])/2.0)-2*I[4]);	
	N_2=(float)((2*I[5])-((float)(I[0]+I[1]+I[2]+I[3])/2.0));
	
	float t1,t2,t3,t4,t5;
	    
		t1=pow((I[0]-I[1]),2);
	    
		t2= pow((I[2]-I[3]),2);
	    
		t3=(float)(t1 + t2);
	    
	D=(((float)(I[0]+I[1]-I[2]-I[3])/2.0)-sqrt(t3));
	temp_argv=(float)((N_1*sin(2*angolo_isoclina[i])+N_2*cos(2*angolo_isoclina[i]))/D);
		
	angolo_ritardo[i]=(float)((1.0/(2.0*PI))*atan(temp_argv));
	angolo_isoclina[i]*=57.2958; // angoli in gradi
//	angolo_ritardo[i]*=57.2958;  // angoli in gradi
    angolo_ritardo[i]+=0.25;
	if(angolo_isoclina[i]<0) angolo_isoclina[i]+=90;
		
	if(risposta==1)
	{
		if(angolo_isoclina[i]<max_iso && angolo_isoclina[i]>min_iso){ angolo_isoclina[i]=0;}// mappatura intervallo angoli	
	}

	angolo_int_isoclina[i]=10*angolo_isoclina[i];// amplificazione luminosita
	angolo_int_ritardo[i]=1000*angolo_ritardo[i]/2;// amplificazione luminosita	
	    

 }
 
 int mezzo;
 mezzo=(foto[0].larghezza_immagine*foto[0].altezza_immagine)/2;
 
 for(int j=mezzo;j<mezzo+foto[0].larghezza_immagine;j++)
 {
 	
 	fprintf(fw,"%f %d \n",angolo_ritardo[j],angolo_int_ritardo[j]);
 }
 
	//salva_ppm(nome_sav,angolo_int_isoclina,angolo_int_isoclina,angolo_int_isoclina,foto[2].larghezza_immagine,foto[2].altezza_immagine,10);
	salva_bmp("risultato_isoclina_6img.bmp",foto[0].header,angolo_int_isoclina,angolo_int_isoclina,angolo_int_isoclina,foto[0].larghezza_immagine,foto[0].altezza_immagine,0,foto[0].size);
	salva_bmp("risultato_ritardo_6img.bmp",foto[0].header,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[0].larghezza_immagine,foto[0].altezza_immagine,0,foto[0].size);
	//salva_ppm(nome_sav,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[2].larghezza_immagine,foto[2].altezza_immagine,10);
	free(angolo_isoclina);
    free(angolo_ritardo);
    free(angolo_int_isoclina);
    free(angolo_int_ritardo);
    
    
    return ;
}
