// LZCC.c : Defines the entry point for the application.
//
/*LZSS Compression Component*/
/*Jonathan P Dawson 2014-07.10*/

const int N = 128;

unsigned big_endian = input("big_endian");
unsigned little_endian = output("little_endian");

void main() {

    unsigned msbyte, lsbyte;
    unsigned ix;

    unsigned new_size;

    while (1) {
        for (ix = 0; ix < N / 2; ix++) {
            msbyte = fgetc(big_endian);
            lsbyte = fgetc(big_endian);
            fputc(lsbyte, little_endian);
            fputc(msbyte, little_endian);
        }
    }
}
