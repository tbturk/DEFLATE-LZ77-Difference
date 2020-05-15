#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define OFFSETBITS 10
#define LENGTHBITS 6

#define OFFSETMASK ((1 << (OFFSETBITS)) - 1)
#define LENGTHMASK ((1 << (LENGTHBITS)) - 1)

#define GETOFFSET(x) (x >> LENGTHBITS)
#define GETLENGTH(x) (x & LENGTHMASK)
#define OFFSETLENGTH(x,y) (x << LENGTHBITS | y)

struct token
{
    uint16_t offset_len;
    char takipTekrari;
};
void dosya_okuma();
void lz77_dosya_yazma();
void lz77();
int dosyanin_uzunlugu=0;
char *ileri_tampon;
struct token *veriler;
int sayac=0;

void main()
{
    dosya_okuma();
    LZ77();
    lz77_dosya_yazma();
    printf("Orijinal boyut: %d  Encoded boyut: %d",dosyanin_uzunlugu, sayac * sizeof(struct token));
    return 0;
}
void lz77_dosya_yazma()
{
    FILE * f;
    if (f = fopen("output.txt", "wb"))
    {
        fwrite(veriler, sizeof(struct token), sayac, f);
        fclose(f);
    }

}

void LZ77()
{
    int benzerlik_sayisi=0;
    int uzaklik=0;
    int bitti_mi=0;
    char *temp_i_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    strcpy(temp_i_tampon,ileri_tampon);
    char *arama_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    sprintf(arama_tampon, "");
    while(strlen(temp_i_tampon)>0)
    {
        if(strlen(temp_i_tampon)==1){//sonda eleman tek kalirsa diye
            veriler=(struct token*)realloc(veriler,(sayac+1)*sizeof(struct token));
            veriler[sayac].offset_len= OFFSETLENGTH(0, 0);
            veriler[sayac].takipTekrari=temp_i_tampon[0];
            sayac++;
            for(int k=0; k<strlen(temp_i_tampon); k++)
            {
                temp_i_tampon[k]=temp_i_tampon[k+1];
            }
            break;

        }

        int i=0;//her seferinde temp_i_tamponu ilk karakterden baslatip kontrol etmek icin.
        int varmi=0;//benzerlik buunursa bu deger 1 olur.
        benzerlik_sayisi=0;//kac adae karakterin benedigini tutar.
        uzaklik=0;//karakterin uzakligini tutar.
        int index=strlen(arama_tampon);//i=0 icin arama tamponundaki benzerlik yerini tutar.
        int max_uzaklik=strlen(arama_tampon);
        if(max_uzaklik>1024)
        {
            max_uzaklik=1024;//max uzaklık 2 uzeri 10dan buyuk olamaz
        }
        int max_benzerlik=0;
        for(int j=strlen(arama_tampon); j>=index-max_uzaklik; j--)
        {

            if(arama_tampon[j]==temp_i_tampon[i])
            {
                benzerlik_sayisi=0;
                uzaklik=strlen(arama_tampon)-j;
                varmi=1;
                int index1=j;
                benzerlik_sayisi++;//1
                int x=index1+1,y=1;
                while(arama_tampon[x]==temp_i_tampon[y])
                {
                    if(temp_i_tampon+y==temp_i_tampon+strlen(temp_i_tampon)-1){//benzerlik son eleman ile aynıysa bunu benzerlige katmamak icin
                        break;
                    }
                    benzerlik_sayisi++;
                    x++;
                    y++;
                }

                if(benzerlik_sayisi>=max_benzerlik){

                    uzaklik=strlen(arama_tampon)-j;
                    index=j;
                }
            }
        }
        if(varmi==1)
        {
            //benzerlik varsa yapilan islemler
            char str[2];
            str[0] = 0;
            str[1] = '\0';
            if(benzerlik_sayisi+strlen(arama_tampon)==strlen(ileri_tampon)) //son karakterin null olmaması icin
            {
                bitti_mi=benzerlik_sayisi;
                bitti_mi--;
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
        veriler=(struct token*)realloc(veriler,(sayac+1)*sizeof(struct token));
        if(bitti_mi!=0)
        {
            veriler[sayac].offset_len= OFFSETLENGTH(uzaklik, bitti_mi);
            veriler[sayac].takipTekrari=temp_i_tampon[i+bitti_mi];
        }
        else
        {
            veriler[sayac].offset_len= OFFSETLENGTH(uzaklik, benzerlik_sayisi);
            veriler[sayac].takipTekrari=temp_i_tampon[i+benzerlik_sayisi];
        }
        printf("<%d,%d,%c>\n",uzaklik,benzerlik_sayisi,temp_i_tampon[i+benzerlik_sayisi]);

        sayac++;
        for(int k=0; k<=benzerlik_sayisi; k++)//arama_tampona eklenilen karakterleri temp_i_tampondan siler.
        {
            for(int k=0; k<strlen(temp_i_tampon); k++)
            {
                temp_i_tampon[k]=temp_i_tampon[k+1];
            }

        }
        //printf("%s %d %s%d\n",arama_tampon,strlen(arama_tampon),temp_i_tampon,uzaklik);

        //printf("\n(%d,%c)\n",veriler[sayac-1].offset_len,veriler[sayac-1].takipTekrari);
    }

}

void dosya_okuma()
{
    FILE *dosya=fopen("input.txt","r");
    fseek(dosya, 0, SEEK_END);
    dosyanin_uzunlugu = ftell(dosya);
    ileri_tampon=calloc( 1, dosyanin_uzunlugu);
    fseek(dosya, 0, SEEK_SET);
    fread(ileri_tampon, 1, dosyanin_uzunlugu, dosya);
    fclose(dosya);
}
