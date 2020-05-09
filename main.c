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
    int benzerlik_sayisi=0;
    int uzaklik=0;
    strcpy(temp_i_tampon,ileri_tampon);
    //printf("%d %d",strlen(temp_i_tampon),dosyanin_uzunlugu);
    char *arama_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    sprintf(arama_tampon, "");
    printf("%s %d",arama_tampon,strlen(arama_tampon));
    while(strlen(temp_i_tampon)>0)
    {

        for(int i=0; i<strlen(temp_i_tampon); i++)
        {
            benzerlik_sayisi=0;
            uzaklik=0;
            for(int j=strlen(arama_tampon); j>=0 ; j--)
            {

                if(arama_tampon[j]==temp_i_tampon[i])
                {

                    benzerlik_sayisi++;
                    uzaklik=j;
                }

            }
            if(benzerlik_sayisi==0)
            {
                arama_tampon[0]=temp_i_tampon[0];
                //char* tmp*="a";
                //sprintf(tmp, temp_i_tampon[i]);
                 //printf("batu");
                //printf(tmp);
                //strcat(arama_tampon, tmp);
                /*veriler->benzerlik=benzerlik_sayisi;
                veriler->uzaklik=uzaklik;
                veriler->takipTekrari=temp_i_tampon[i+benzerlik_sayisi];*/

                for(int k=0; k<strlen(temp_i_tampon); k++)
                {
                    temp_i_tampon[k]=temp_i_tampon[k+1];
                }
                printf("%s %d",arama_tampon,strlen(arama_tampon));

                exit(0);

            }



        }

    }
    //printf("%d %d %s",veriler->uzaklik,veriler->benzerlik,veriler->takipTekrari);

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
