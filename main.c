#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct ucluKod
{
    int uzaklik;
    int benzerlik;
    char takipTekrari;

};
void dosya_okuma();
int dosyanin_uzunlugu=0;
char *ileri_tampon;
char *arama_tampon;
int benzerlik_sayisi=0;
struct ucluKod *veriler;
void main()
{
    dosya_okuma();
    LZ77();

    return 0;
}
void LZ77()
{
    char *temp_i_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));

    strcpy(temp_i_tampon,ileri_tampon);
    arama_tampon=(char *)malloc((strlen(temp_i_tampon)+1)*sizeof(char));
   // printf("%d %d",strlen(temp_i_tampon),dosyanin_uzunlugu);
   // printf("%s",temp_i_tampon);
   // printf("%d",strlen(temp_i_tampon));
   // printf("%s",temp_i_tampon);

    while(strlen(temp_i_tampon)>0){

       for(int i=0;i<strlen(temp_i_tampon);i++){



       }


    }





}
void dosya_okuma()
{
    FILE *dosya=fopen("input.txt","r");
    char line[100];

    if (dosya == NULL)
    {
        printf("Dosya acilamadi. Lütfen dosyayi kontrol ediniz!");
        exit(1);
    }
    fgets(line, 100, dosya);
    ileri_tampon=(char *)malloc(strlen(line)+1);
    strcpy(ileri_tampon,line);
    while(fgets(line, 100, dosya)!=NULL)
    {
        strcat(ileri_tampon,line);
    }
    dosyanin_uzunlugu=strlen(ileri_tampon);
    //printf("%d %s",strlen(ileri_tampon),ileri_tampon);
    fclose(dosya);
}
