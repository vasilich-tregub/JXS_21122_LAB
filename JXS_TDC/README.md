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

citing 
https://journal.smpte.org/periodicals/SMPTE%20Motion%20Imaging%20Journal/134/5/16/ :

> JPEG XS 3rd Edition: The New Temporal Differential Coding (TDC) Profile
Tim Bruylants, Ben Runyan, Jean-Baptiste Lorent
The 3rd edition of JPEG XS introduces the Temporal Differential Coding 
(TDC) profile, further improving the compression efficiency over the XS 
High profile. TDC adds a wavelet-domain temporal prediction block using 
a single compressed frame buffer to reduce correlation between successive 
frames, especially in static regions, without requiring motion 
compensation or complex algorithms. It preserves JPEG XS's key features: 
lightweight, fast compression with low latency, near-lossless quality, 
and low complexity. Experiments indicate that TDC significantly improves 
detail preservation and edge sharpness, with Peak Signal-to-Noise Ratio 
(PSNR) gains exceeding 10 dB in graphics, e-sports, gaming, and desktop 
videos. And, for high-motion content, TDC maintains at least the same 
performance as XS High. Compatible across Central Processing Units (CPUs), 
Graphical Processing Units (GPUs), Field Programmable Gate Arrays (FP-GAs), 
and Application-Specific Integrated Circuits (ASICs), TDC offers a seamless 
upgrade for existing JPEG XS ecosystems. This paper details TDC's technical 
aspects and demonstrates its performance benefits, emphasizing that latency 
and complexity remain unaffected.