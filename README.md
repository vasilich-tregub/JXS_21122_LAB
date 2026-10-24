# JXS_21122_LAB

The code samples in subfolders can be used to understand the working of the JPEG XS 
reference codec. Some use the static library build with the reference codec software, 
JPEG 21122, part 5, ed3, published by ISO. These are best used as extras with 
the reference software package. The other ones are independent pieces of code 
that attempt to implement JPEG XS algorithms and functions recovered in the course 
of back engineering the reference software.

Temporal Differential Coding is a new feature of JPEG XS added in edition 3 of 
ISO/IEC 21122 standard. Part 4 of the standard has a repo of jxc test files 
(tests.zip in https://standards.iso.org/iso-iec/21122/-4/ed-3/en/). I've decoded 
a sequence '308/frame_%08d.jxc' with a decoder of the reference code published in 
https://standards.iso.org/iso-iec/21122/-5/ed-3/en/, item ISO_IEC_21122-5_ED-3.zip.
The images generated can be found in folder JXS_TDC of this repo.