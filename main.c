#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int uzaklik;
    int benzerlik;
    char takipTekrari;

} ucluKod;
void dosya_okuma();
int dosyanin_uzunlugu=0;
char *ileri_tampon;
ucluKod *veriler;
int sayac=0;

void main()
{
    //veriler=(ucluKod*)malloc(1*sizeof(ucluKod));
    dosya_okuma();
    LZ77();

    return 0;
}

void LZ77()
{
    int benzerlik_sayisi=0;
    int uzaklik=0;
    char *temp_i_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    strcpy(temp_i_tampon,ileri_tampon);
    char *arama_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    sprintf(arama_tampon, "");
    //printf("%s %d",arama_tampon,strlen(arama_tampon));
    while(strlen(temp_i_tampon)>0)
    {
        int i=0;//her seferinde temp_i_tamponu ilk karakterden baslatip kontrol etmek icin.
        int varmi=0;//benzerlik buunursa bu deger 1 olur.
        benzerlik_sayisi=0;//kac adae karakterin benedigini tutar.
        uzaklik=0;//karakterin uzakligini tutar.
        int index=strlen(arama_tampon);//i=0 icin arama tamponundaki benzerlik yerini tutar.

        for(int j=strlen(arama_tampon); j>=0 ; j--)
        {
            if(arama_tampon[j]==temp_i_tampon[i])
            {
                uzaklik=strlen(arama_tampon)-j;
                varmi=1;
                index=j;
            }
        }
        if(varmi==1)
        {
            //benzerlik varsa yapilan islemler
            char str[2];
            str[0] = 0;
            str[1] = '\0';
            benzerlik_sayisi++;//1
            int x=index+1,y=1;
            while(arama_tampon[x]==temp_i_tampon[y])
            {
                benzerlik_sayisi++;
                x++;
                y++;
            }
            for(int k=0; k<=benzerlik_sayisi; k++)//benzerlik kadar karakteri arama tamponuna ekler
            {
                str[0] = temp_i_tampon[k];
                strcat(arama_tampon,str);
            }

        }
        else     //benzerlik yoksa yapilan islemler;
        {
            char str[2];
            str[0] = temp_i_tampon[i];
            str[1] = '\0';
            strcat(arama_tampon,str);

        }
        veriler=(ucluKod*)realloc(veriler,(sayac+1)*sizeof(ucluKod));

        veriler[sayac].benzerlik=benzerlik_sayisi;
        veriler[sayac].uzaklik=uzaklik;
        veriler[sayac].takipTekrari=temp_i_tampon[i+benzerlik_sayisi];
        sayac++;
        for(int k=0; k<=benzerlik_sayisi; k++)//arama_tampona eklenilen karakterleri temp_i_tampondan siler.
        {
            for(int k=0; k<strlen(temp_i_tampon); k++)
            {
                temp_i_tampon[k]=temp_i_tampon[k+1];
            }

        }
        printf("%s %d %s\n",arama_tampon,strlen(arama_tampon),temp_i_tampon);

        printf("\n(%d,%d,%c)\n",veriler[sayac-1].uzaklik,veriler[sayac-1].benzerlik,veriler[sayac-1].takipTekrari);
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
