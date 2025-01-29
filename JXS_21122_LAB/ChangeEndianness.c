// ChangeEndiannes.c : Defines the entry point for the application.
//
/*Change endiannes in Chips' C language flavour*/


const int N = 128;

unsigned big_endian = input("big_endian");          // point to stream; similar to Handel C's lang flavour
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
