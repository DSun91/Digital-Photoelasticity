#include<stdio.h>
#include<stdlib.h>

typedef struct
{
  char magic_num[3]; 
  unsigned char header[54];
  unsigned int altezza_immagine;
  unsigned int larghezza_immagine;
  unsigned int data_setoff;
  unsigned short int colorplanes;
  unsigned short int bit;
  unsigned int compress;
  unsigned int size;
  unsigned int   *red;
  unsigned int   *green;
  unsigned int   *blue;
  
}Immagine_bitmap;


Immagine_bitmap carica_immagine(char* nome_file){
    
	Immagine_bitmap img;                   	                   
    FILE *fp;
    
	int allocazione_mem;
	int i;   
	unsigned char *foto_temp;

	fp = fopen(nome_file, "rb"); 
    
    
if(!fp)
  {
  	printf("file inesistente...\ncontrollare la presenza delle immagini nella cartella di lavoro, oppure la correttezza del nome..");
  	exit(34);
  }
  
  fread(&img.magic_num[0],sizeof(img.magic_num),1,fp);
  fseek(fp,10,0);
  fread(&img.data_setoff,sizeof(unsigned int),1,fp);
  fseek(fp,18,0);
  fread(&img.larghezza_immagine,sizeof(unsigned int),1,fp);
  fread(&img.altezza_immagine,sizeof(unsigned int),1,fp);
  fread(&img.colorplanes,sizeof(unsigned short int),1,fp);       
  fread(&img.bit,sizeof(unsigned short int),1,fp);
  fread(&img.compress,sizeof(unsigned  int),1,fp);
  fread(&img.size,sizeof(unsigned int),1,fp);
 
  
  fseek(fp,0,0);
  fread(img.header,54,1,fp);// header
  
if(img.bit!=24)
{
	printf("formato bitmap non supportato...\n");
	system("pause");
	exit(255);
}
 
 printf("informazioni immagine:\nnome file: %s\nlarghezza_immagine:  %d pixel\n",nome_file,img.larghezza_immagine);                         	
 printf("altezza immagine: %d pixel\nbit per canale: %d bit\n",img.altezza_immagine,img.bit/3);
 printf("dimensione file: %d bytes \ndata setoff: %d\n\n",img.size ,img.data_setoff);  
 printf("----------------------------------------------------------------------------\n\n");              	               
   
    allocazione_mem=(img.altezza_immagine*img.larghezza_immagine);
    
    img.red=(unsigned int*)malloc(allocazione_mem*sizeof(unsigned int));
   
    img.blue=(unsigned int*)malloc(allocazione_mem*sizeof(unsigned int));
    
    img.green=(unsigned int*)malloc(allocazione_mem*sizeof(unsigned int));
    
    
    fseek(fp,img.data_setoff,0);
    foto_temp=(unsigned char*)malloc(img.size*sizeof(unsigned char));                       	
    fread(foto_temp,img.size*sizeof(unsigned char),1,fp); 
	
	/* FILE *fw,*fw1; 

	fw1 = fopen("immagine.ppm","wb");
	fprintf(fw1,"P6\n%d %d\n255\n",img.larghezza_immagine,img.altezza_immagine);      
	fwrite(foto_temp,img.size,1,fw1);
    
    fw = fopen("immagine.bmp","wb");
	fwrite(img.header,54,1,fw);
    fwrite(foto_temp,img.size*sizeof(unsigned char),1,fw);
	
	fclose(fw);
	fclose(fw1);
	              */     
		int ind_generic=0;			   
					   
for(i=0;i<img.larghezza_immagine*img.altezza_immagine;i++)
    {
    	 img.blue[i]= foto_temp[ind_generic];
    	 img.green[i]=foto_temp[ind_generic+1];
    	 img.red[i] =foto_temp[ind_generic+2];
    	
         ind_generic+=3;
         //
	
			                           
	}			   
				      	
   /* 
   
   se nel caso si vuole salvare in .ppm
   
   int salto_riga=1;
    int ind_generic=3*img.larghezza_immagine*(img.altezza_immagine-salto_riga);       
	
	
for(i=0;i<img.larghezza_immagine*img.altezza_immagine;i++)
    {
    	 img.blue[i]= foto_temp[ind_generic];
    	 img.green[i]=foto_temp[ind_generic+1];
    	 img.red[i] =foto_temp[ind_generic+2];
    	
         ind_generic+=3;
         //printf("r= %d g= %d b= %d\n",img.red[i],img.green[i],img.blue[i]);
		if(i>=(img.larghezza_immagine*salto_riga)){ ind_generic=3*img.larghezza_immagine*(img.altezza_immagine-salto_riga);
			                               salto_riga++;}
			                           
	}


*/
	fclose(fp);  
    return img;
}



void salva_bmp(char* filename,unsigned char* header,unsigned int red[],unsigned int green[],
                unsigned int blue[],int larghezza,int altezza,int coeff,int size)
{
     FILE *fw; 
	fw = fopen(filename,"wb");
	// queto per immagine row
    
    unsigned char *foto_temp;
    int ind_generic=0;

foto_temp=(unsigned char*)malloc(size*sizeof(unsigned char));
 
 
   for(int i=0;i<larghezza*altezza;i++)
    {    
       
	     	foto_temp[ind_generic]=blue[i];
    	    foto_temp[ind_generic+1]=green[i];
    	    foto_temp[ind_generic+2]=red[i];
    	    ind_generic+=3;
		
     }

    
	fwrite(header,54,1,fw);
    fseek(fw,54,0);
	fwrite(foto_temp,size,1,fw);
	
	fclose(fw);
	return;
}


/*void salva_ppm(char* filename,unsigned int red[],unsigned int green[],unsigned int blue[],int larghezza,int altezza,int coeff)
{
	FILE *fw; 
	fw = fopen(filename,"wb");
    unsigned char *foto_temp;
    int ind_generic=0;

foto_temp=(unsigned char*)malloc(larghezza*altezza*3);
 
 
   for(int i=0;i<larghezza*altezza;i++)
    {    
        if(coeff!=0)
    	{
    		foto_temp[ind_generic]=red[i]*coeff;
    	    foto_temp[ind_generic+1]=green[i]*coeff;
    	    foto_temp[ind_generic+2]=blue[i]*coeff;
    	    ind_generic+=3;
		}
		else
		{
			foto_temp[ind_generic]=red[i];
    	    foto_temp[ind_generic+1]=green[i];
    	    foto_temp[ind_generic+2]=blue[i];
    	    ind_generic+=3;
		}
     }
    fprintf(fw,"P6\n%d %d\n255\n ",larghezza,altezza);      
	fwrite(foto_temp,(larghezza*altezza*3),1,fw);
    fclose(fw);
return;
  
}



int main()
{
	Immagine_bitmap a;
	
	a=carica_immagine("cotter (1).bmp");
	salva_bmp("immagine.bmp",a.header,a.red,a.green,a.blue,a.larghezza_immagine,a.altezza_immagine,0,a.size);
	//salva_ppm("immagine.ppm",a.red,a.green,a.blue,a.larghezza_immagine,a.altezza_immagine,0);
		
	return 0;
	}


	                                             */                                                                  
