#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h> // unsigned integer kullanip, veriyi kücültebilmek icin.

#define max_uzaklik_bit 10 //arama tamponda maksimum kac bit arama yapilabilecegi (2^10).
#define max_benzerlik_bit 6 //arama tamponda maksimum kac bit benzerlik bulunabilecegi (2^6).

#define OFFSETMASK ((1 << (max_uzaklik_bit)) - 1)   //uzunlugu maskelemek icin(decode ederken OFFSETLENGTH()'e geri sifreleme uygulanir.
#define LENGTHMASK ((1 << (max_benzerlik_bit)) - 1) //benzerligi maskelemek icin(decode ederken OFFSETLENGTH()'e geri sifreleme uygulanir.
#define OFFSETLENGTH(x,y) (x << max_benzerlik_bit | y)  //uzaklik ve benzerligi tek degiskende(struct->offset_len) de sifrelemek icin kullanilir.


struct token    //lz77 tokenlerini tutttugumuz yapi.
{
    uint16_t offset_len;    //uzaklik ve benzerligin sifrelenmis hali.
    char takipTekrari;      //lz77 icin benzerlik tekrarindan sonra tutulan karakter.
};

typedef struct dugum    //huffman agacındaki dugumlerin yapisi.
{
    char ch;            //dugumdeki karakter, eger dugum iki karakterin birlesimiyse null atanir.
    int frekans;        //karakterden, lz77 sikistirilmis metninde kac adet oldugunun sayisini tutar
    struct dugum *sol;  //huffman agacinin 0 bitlik kismi
    struct dugum *sag;  //huffman agacinin 1 bitlik kismi
} dugum;

void dosya_okuma();     //Orijinal metni input.txt'den okuyan fonksiyon.
void lz77_dosya_yazma();    //sifrelenmis metni output.txt ye binary olarak yazan fonksiyon.
void lz77();                //Orijinal metni lzz7 ile sifreleyen fonksiyon
void frekans_analizi(char encoded_text[],char farkli_karakterler[],int frekanslar[]);   //sifrelenmis metnin frekans analizini yapan fonksiyon.
<<<<<<< HEAD
void huffman(char farkli_karakterler[],int frekanslar[],char farkli_karakterler_siralanmis[]);   //huffman kodlama yapan fonksiyon
void huffman_bit_yazdirma(dugum *temp,char *code,char farkli_karakterler_siralanmis[]);//huffman agacindaki karakterleri ve huffman degerlerini yazdiran recursive fonksiyon.
void huffman_dosya_yazdir(char encoded_text[],char farkli_karakterler_siralanmis[]);//huffman kodunu dosyaya yazan fonksiyon.
=======
void huffman(char farkli_karakterler[],int frekanslar[]);   //huffman kodlama yapan fonksiyon
void huffman_bit_yazdirma(dugum *temp,char *code);//huffman agacindaki karakterleri ve huffman degerlerini yazdiran fonksiyon.

>>>>>>> master

int dosyanin_uzunlugu=0;    //orijinal metnin uzunlugu(byte tabanli).
char *ileri_tampon;         //orijinal metnin tutuldugu char dizisi.
struct token *veriler;      //lz77 ile sifrelenmis metnin tokenlerinin tutuldugu dizi.
int sayac=0;                //token sayisini tutan degisken.
int enc_boyut;              //sifrelenmis metnin uzunlugu;
int farkli_boyut=0;         //sifrelenmis metinde kac farkli karakter gectigi.(ayni karakterler teke düsürülüp frekansı oyle bulunmali).
dugum *yigin[200];          //olusturulan huffman dugulerinin tutuldugu yigin.
int yigin_boyut=0;          //yiginin anlik boyutu.
<<<<<<< HEAD
char binary_tokenler[127][10];
int binary_token_boyut=0;
int huffman_kod_uzunlugu=0;
int huffman_sonrasi_boyut=0;
=======


>>>>>>> master

void main()
{
    dosya_okuma();
    lz77();
    lz77_dosya_yazma();
    enc_boyut= sayac * sizeof(struct token);
<<<<<<< HEAD

    char encoded_text[enc_boyut+1];//+1 '\0' sonlandirma karakteri icin.
    char farkli_karakterler[enc_boyut+1];
    char farkli_karakterler_siralanmis[enc_boyut+1];
    int frekanslar[enc_boyut];
    frekans_analizi(encoded_text,farkli_karakterler,frekanslar);
    huffman(farkli_karakterler,frekanslar,farkli_karakterler_siralanmis);
    int toplam_bit_sayisi=0;
    for(int i=0; i<binary_token_boyut; i++)
    {
        toplam_bit_sayisi += strlen(binary_tokenler[i]);
    }
    printf("\nHuffman Kodu: ");
    huffman_dosya_yazdir(encoded_text,farkli_karakterler_siralanmis);
    huffman_sonrasi_boyut+=huffman_kod_uzunlugu+(farkli_boyut*8);
    printf("\n\n\nOrijinal boyut: %d bit  LZ77 Encoded boyut: %d bit   Hufmann Encoded boyut:%d bit\n",dosyanin_uzunlugu*8, enc_boyut*8,huffman_sonrasi_boyut);
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

=======
    printf("\nOrijinal boyut: %d  LZ77 Encoded boyut: %d\n",dosyanin_uzunlugu, enc_boyut);
    char encoded_text[enc_boyut+1];//+1 '\0' sonlandirma karakteri icin.
    char farkli_karakterler[enc_boyut+1];
    int frekanslar[enc_boyut];
    frekans_analizi(encoded_text,farkli_karakterler,frekanslar);
    huffman(farkli_karakterler,frekanslar);

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

>>>>>>> master
void lz77_dosya_yazma()
{
    FILE * f;
    if (f = fopen("output.txt", "w"))
    {
        fwrite(veriler, sizeof(struct token), sayac, f);
        fclose(f);
    }

}

void lz77()
{
    int benzerlik_sayisi=0;
    int uzaklik=0;
    int bitti_mi=0;
    char *temp_i_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    strcpy(temp_i_tampon,ileri_tampon);
    char *arama_tampon=(char *)malloc((strlen(ileri_tampon)+1)*sizeof(char));
    sprintf(arama_tampon, "");

    //arama_tampon ve temp_i_tampon her dongude guncellnir ve ikisi uzerinde benzerlik kontrolu devami saglanir.
    while(strlen(temp_i_tampon)>0)
    {
        if(strlen(temp_i_tampon)==1) //sonda eleman tek kalirsa diye.
        {
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

        int i=0;    //her seferinde temp_i_tamponu ilk karakterden baslatip kontrol etmek icin.
        int varmi=0;    //benzerlik buunursa bu deger 1 olur.
        benzerlik_sayisi=0; //kac adae karakterin benedigini tutar.
        uzaklik=0;  //karakterin uzakligini tutar.
        int index=strlen(arama_tampon); //i=0 icin arama tamponundaki benzerlik yerini tutar.
        int max_uzaklik=strlen(arama_tampon);   //arama tamponda dolasabilecegi maksimum uzaklik.
        if(max_uzaklik>1024)
        {
            max_uzaklik=1024;//max uzaklık 2 uzeri 10dan buyuk olamaz. bkz.line:7
        }
        int max_benzerlik=0;

        //arama tamondaki maksimum benzerligi ve benzerlik oranini bulur.
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

                //benzelik buldugu karakterden itibaren saga dogru dolasmaya  baslar ve benzerlik devam ettigi surece benzerlik_sayisi ni artirir.
                while(arama_tampon[x]==temp_i_tampon[y])
                {
                    if(temp_i_tampon+y==temp_i_tampon+strlen(temp_i_tampon)-1) //benzerlik son eleman ile aynıysa bunu benzerlige katmamak icin
                    {
                        break;
                    }
                    benzerlik_sayisi++;
                    x++;
                    y++;
                }

                if(benzerlik_sayisi>=max_benzerlik)
                {

                    uzaklik=strlen(arama_tampon)-j;
                    index=j;
                }
            }
        }
        //benzerlik varsa yapilan islemler
        if(varmi==1)
        {
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
        //benzerlik yoksa yapilan islemler;
        else
        {
            char str[2];
            str[0] = temp_i_tampon[i];
            str[1] = '\0';
            strcat(arama_tampon,str);

        }
        //Bellekten dizinin boyutunu artirip, token dizisine veri eklenen kisim.
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

        sayac++;    //token sayisinin durumunu guncelleriz.

        //arama_tampona eklenilen karakterleri temp_i_tampondan siler.
        for(int k=0; k<=benzerlik_sayisi; k++)
        {
            for(int k=0; k<strlen(temp_i_tampon); k++)
            {
                temp_i_tampon[k]=temp_i_tampon[k+1];
            }

        }
        //tokenleri ve degerlerini ekrana yazdirir
        printf("\n<%d,%d,%c>\n",uzaklik,benzerlik_sayisi,veriler[sayac-1].takipTekrari);

        //printf("\n(%d,%c)\n",veriler[sayac-1].offset_len,veriler[sayac-1].takipTekrari);
    }
}

void frekans_analizi(char encoded_text[],char farkli_karakterler[],int frekanslar[])
{
    FILE *fp;
    fp = fopen("output.txt", "rb");
<<<<<<< HEAD

    //şifrelenmiş dosyadan karakter okuyup encoded_text isimli char dizisine tum sifrelenmis metni atiyoruz.
    if (fp)
    {
        int sayac=0;
        int c;
        do
        {
            int var=0;
            c = fgetc(fp);
            if (EOF != c)
            {
                encoded_text[sayac]=c;
                sayac++;
            }
        }
        while (EOF != c);
        fclose(fp);

=======

    //şifrelenmiş dosyadan karakter okuyup encoded_text isimli char dizisine tum sifrelenmis metni atiyoruz.
    if (fp)
    {
        int sayac=0;
        int c;
        do
        {
            int var=0;
            c = fgetc(fp);
            if (EOF != c)
            {
                encoded_text[sayac]=c;
                sayac++;
            }
        }
        while (EOF != c);
        fclose(fp);

>>>>>>> master
    }

    //aynı karakterlerden tek bir karakter olacak diziye dönüştüren döngü.
    for(int i=0; i<enc_boyut; i++)
    {
        int var=0;
        for(int j=0; j<farkli_boyut; j++) //farkli karakterlerin boyutu kadar donmeli
        {
            if(encoded_text[i]==farkli_karakterler[j])//farkli karakterler dizisinde varsa 1 doner.
            {
                var=1;
            }
        }
        if(var==0)//farkli_karakterler dizisinde yoksa, diziye eklenir.
        {
            farkli_karakterler[farkli_boyut]=encoded_text[i];
            farkli_boyut++;
        }
    }

    //frekanslar dizisindeki her bir degere baslangic degeri atiyoruz.
    for(int k=0; k<farkli_boyut; k++)
    {
        frekanslar[k]=0;
    }

    //her bir karkterin sifrelenmiş textte kac adet gectigini(frekansini) frekanslar dizisinde guncelliyoruz.
    for(int i=0; i<enc_boyut; i++)
    {
        for(int j=0; j<256; j++)
        {
            char c=j;
            if(encoded_text[i]==c)
            {
                for(int k=0; k<farkli_boyut; k++) //farkli karakterlerin boyutu kadar donmeli
                {
                    if(c==farkli_karakterler[k])//farklı karakterler dizisindeki ile kontrol ediyor
                    {
                        frekanslar[k]++;
                        break;
                    }
                }
                break;
            }
        }
    }

    //frekanslari kucukten buyuge siralama
    for(int i=0; i<farkli_boyut; i++)
    {
        for(int j=i+1; j<farkli_boyut; j++)
        {
            if(frekanslar[i]>frekanslar[j])
            {
                int temp=frekanslar[i];
                frekanslar[i]=frekanslar[j];
                frekanslar[j]=temp;

                char tmp=farkli_karakterler[i];
                farkli_karakterler[i]=farkli_karakterler[j];
                farkli_karakterler[j]=tmp;


            }
        }
    }
}

<<<<<<< HEAD
void huffman(char farkli_karakterler[],int frekanslar[],char farkli_karakterler_siralanmis[])
=======
void huffman(char farkli_karakterler[],int frekanslar[])
>>>>>>> master
{
    yigin[0] = (dugum *)malloc(sizeof(dugum));
    yigin[0]->frekans = 0;

    //farkli_karakterler'deki her bir karakter icin dugum olusturma. ve yigina ekleme.
    for(int i=0; i<farkli_boyut; i++)
    {
        dugum * temp = (dugum *) malloc(sizeof(dugum));
        temp -> ch = farkli_karakterler[i];
        temp -> frekans = frekanslar[i];
        temp -> sol = temp -> sag = NULL;

        //olusturulan dugumu yigina ekleme kismi.
        yigin_boyut++;
        yigin[yigin_boyut] = temp;
        int suanki_boyut = yigin_boyut;
        while(yigin[suanki_boyut/2] -> frekans > temp -> frekans)
        {
            yigin[suanki_boyut] = yigin[suanki_boyut/2];
            suanki_boyut /= 2;
        }
        yigin[suanki_boyut] = temp;
    }
    //agaci olusturma kismi.
    for(int i=0; i<farkli_boyut-1 ; i++)
    {

        dugum * enk_eleman,*aktif_eleman;
        int alt_index,suanki_boyut;
        enk_eleman = yigin[1];
        aktif_eleman = yigin[yigin_boyut--];
        for(suanki_boyut = 1; suanki_boyut*2 <= yigin_boyut ; suanki_boyut = alt_index)
        {
            alt_index = suanki_boyut*2;
            if(alt_index != yigin_boyut && yigin[alt_index+1]->frekans < yigin[alt_index] -> frekans )
            {
                alt_index++;
            }
            if(aktif_eleman -> frekans > yigin[alt_index] -> frekans)
            {
                yigin[suanki_boyut] = yigin[alt_index];
            }
            else
            {
                break;
            }
        }
        yigin[suanki_boyut] = aktif_eleman;
        dugum * sol = enk_eleman;

        enk_eleman = yigin[1];
        aktif_eleman = yigin[yigin_boyut--];
        for(suanki_boyut = 1; suanki_boyut*2 <= yigin_boyut ; suanki_boyut = alt_index)
        {
            alt_index = suanki_boyut*2;
            if(alt_index != yigin_boyut && yigin[alt_index+1]->frekans < yigin[alt_index] -> frekans )
            {
                alt_index++;
            }
            if(aktif_eleman -> frekans > yigin[alt_index] -> frekans)
            {
                yigin[suanki_boyut] = yigin[alt_index];
            }
            else
            {
                break;
            }
        }
        yigin[suanki_boyut] = aktif_eleman;
        dugum * sag = enk_eleman;

        dugum * temp = (dugum *) malloc(sizeof(dugum));
        temp -> ch = 0;
        temp -> sol = sol;
        temp -> sag = sag;
        temp -> frekans = sol->frekans + sag -> frekans;
        yigin_boyut++;
        yigin[yigin_boyut] = temp;
        int suanki_boyut1 = yigin_boyut;
        while(yigin[suanki_boyut1/2] -> frekans > temp -> frekans)
        {
            yigin[suanki_boyut1] = yigin[suanki_boyut1/2];
            suanki_boyut1 /= 2;
        }
        yigin[suanki_boyut1] = temp;
    }



    //OLUSTURULAN AGACI YAZMA KISMI.///////////////////////
    dugum * enk_eleman,*aktif_eleman;
    int alt_index,suanki_boyut;
    enk_eleman = yigin[1];
    aktif_eleman = yigin[yigin_boyut--];
    for(suanki_boyut = 1; suanki_boyut*2 <= yigin_boyut ; suanki_boyut = alt_index)
    {
        alt_index = suanki_boyut*2;
        if(alt_index != yigin_boyut && yigin[alt_index+1]->frekans < yigin[alt_index] -> frekans )
        {
            alt_index++;
        }
        if(aktif_eleman -> frekans > yigin[alt_index] -> frekans)
        {
            yigin[suanki_boyut] = yigin[alt_index];
        }
        else
        {
            break;
        }
    }
    yigin[suanki_boyut] = aktif_eleman;
    dugum *tree = enk_eleman;
    char ikili_kod[10];
    ikili_kod[0] = '\0';
    printf("\n");
<<<<<<< HEAD
    huffman_bit_yazdirma(tree,ikili_kod,farkli_karakterler_siralanmis);
    /////////////////////////////////////////////////////////

}


void huffman_bit_yazdirma(dugum *temp,char *code,char farkli_karakterler_siralanmis[])
{
    if(temp->sol==NULL && temp->sag==NULL)
    {
        printf("%c: %s\n",temp->ch,code);
        strcpy(binary_tokenler[binary_token_boyut],code);
        farkli_karakterler_siralanmis[binary_token_boyut]=temp->ch;
        binary_token_boyut++;
        return;
    }
    int length = strlen(code);
    char solcode[10],sagcode[10];
    strcpy(solcode,code);
    strcpy(sagcode,code);
    solcode[length] = '0';
    solcode[length+1] = '\0';
    sagcode[length] = '1';
    sagcode[length+1] = '\0';
    huffman_bit_yazdirma(temp->sol,solcode,farkli_karakterler_siralanmis);
    huffman_bit_yazdirma(temp->sag,sagcode,farkli_karakterler_siralanmis);
}

void huffman_dosya_yazdir(char encoded_text[], char farkli_karakterler_siralanmis[])
{
    FILE * f;
    if (f = fopen("huffman.txt", "w"))
    {
        for(int i=0; i<enc_boyut; i++)
        {
            for(int j=0; j<farkli_boyut; j++)
            {
                if(encoded_text[i]==farkli_karakterler_siralanmis[j])
                {
                    printf("%s",binary_tokenler[j]);
                    huffman_kod_uzunlugu+=strlen(binary_tokenler[j]);
                    fwrite(binary_tokenler[j], strlen(binary_tokenler[j]), 1, f);
                    break;
                }
            }
        }

        fclose(f);
    }
}

=======
    huffman_bit_yazdirma(tree,ikili_kod);
    /////////////////////////////////////////////////////////

}

//hufmann kodlarini yazdiran recursive fonksiyon.
void huffman_bit_yazdirma(dugum *temp,char *code)
{
    if(temp->sol==NULL && temp->sag==NULL)
    {
        printf("%c: %s\n",temp->ch,code);
        return;
    }
    int length = strlen(code);
    char solcode[10],sagcode[10];
    strcpy(solcode,code);
    strcpy(sagcode,code);
    solcode[length] = '0';
    solcode[length+1] = '\0';
    sagcode[length] = '1';
    sagcode[length+1] = '\0';
    huffman_bit_yazdirma(temp->sol,solcode);
    huffman_bit_yazdirma(temp->sag,sagcode);
}

>>>>>>> master
