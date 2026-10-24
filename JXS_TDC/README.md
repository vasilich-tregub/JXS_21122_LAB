# JXS TEMPORAL DIFFERENTIAL CODING

Only 8 items (command line argument -n) of the sequence 308 found in  
https://standards.iso.org/iso-iec/21122/-4/ed-3/en/tests.zip are decoded:

> jxs_decoder.exe -f 0 -n 8 308/frame_%08d.jxc 308/frame_%08d.ppm

Files frame_%08d.ppm are converted to frame_%08d.png pictures and, with 
the origin files frame_%08d.jxc, added to the folder JXS_TDC/308 of this 
repo.

Alternatively, views of jxc files viewed by the ref codec ed 2 JXS viewer 
(where TDC markers are ignored) are saved as frame_%08d.jxs.png pictures 
and added to the folder TDC/308_jxc_ed2viewer.