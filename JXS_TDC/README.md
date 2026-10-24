# JXS TEMPORAL DIFFERENTIAL CODING

First 8 items (command line argument -n) of the sequence 308 taken from   
https://standards.iso.org/iso-iec/21122/-4/ed-3/en/tests.zip are decoded
with the command:

> jxs_decoder.exe -f 0 -n 8 308/frame_%08d.jxc 308/frame_%08d.ppm

Files frame_%08d.ppm are converted to frame_%08d.png pictures and, with 
the origin files frame_%08d.jxc, stored to the folder JXS_TDC/308 of this 
repo.

For camparison, png-views of jxc files viewed by the ref_codec_ed.2-based 
JXS viewer (this viewer omits TDC markers) are saved as frame_%08d.jxs.png 
pictures and stored to the folder TDC/308_jxc_ed2viewer.

Yet another folder, '308+1', stores some of the images decoded with the 
command

> jxs_decoder.exe -f 1 -n 32 308/frame_%08d.jxc 3081/frame1_%08d.ppm

i.e., starting with the next file after the sequence beginning: command 
line argument -f set to 1.

---

citing 
https://journal.smpte.org/periodicals/SMPTE%20Motion%20Imaging%20Journal/134/5/16/ :

> JPEG XS 3rd Edition: The New Temporal Differential Coding (TDC) Profile

> Tim Bruylants, Ben Runyan, Jean-Baptiste Lorent

> The 3rd edition of JPEG XS introduces the Temporal Differential Coding 
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