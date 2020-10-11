void ritardo_4_img_Ajovalasit(char* img_name)
{
   Immagine_bitmap foto[4];
   char names[100];
   int i;
   float *angolo_ritardo;
   unsigned int *angolo_int_ritardo;
   
   float tempor_I=0,temp_argv;
   float I[4];
   FILE *fw;
   fw=fopen("risultato ritardo 4img.txt","wb");
   

     //caricamento immaginie allocazione memoria vettori isoclina e ritardo
for(i=0;i<4;i++)
	{
		sprintf(names,"%s (%d).bmp",img_name,i+1);
	    printf("caricamento immagine: %s...\n",names);
	    foto[i]=carica_immagine(names);	
	    
	}


    angolo_ritardo  = (float*)malloc(foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(float));
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
 	

	tempor_I=(float)(I[3]-I[1])/(I[0]-I[2]);
	angolo_ritardo[i]=(1/(2*PI))*atan(tempor_I);// calcolo isoclina


	angolo_int_ritardo[i]=(1000*(angolo_ritardo[i]+0.25))/2;    // amplificazione luminosita

 }
 int mezzo;
 mezzo=(foto[0].larghezza_immagine*foto[0].altezza_immagine)/2;

 for(int j=mezzo;j<mezzo+foto[0].larghezza_immagine;j++)
 {
 	
 	fprintf(fw,"%f %d \n",angolo_ritardo[j],angolo_int_ritardo[j]);
 }
     FILE *fwr;
   fwr=fopen("risultato ritardo 4img.raw","wb");
   fwrite(angolo_ritardo,foto[0].altezza_immagine*foto[0].larghezza_immagine*sizeof(float),1,fwr);
   
   
	salva_bmp("risultato_solo_ritardo_4img.bmp",foto[0].header,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[0].larghezza_immagine,foto[0].altezza_immagine,0,foto[0].size);
//	salva_ppm(nome_sav,angolo_int_ritardo,angolo_int_ritardo,angolo_int_ritardo,foto[2].larghezza_immagine,foto[2].altezza_immagine,10);
    free(angolo_ritardo);
    free(angolo_int_ritardo);
    
    
    return ;
}
