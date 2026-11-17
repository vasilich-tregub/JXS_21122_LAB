# JXS_21122_LAB

The code samples in subfolders can be used to help the reader understand the working 
of the JPEG XS reference codec. Some use the static library build with the reference 
codec software, JPEG 21122, part 5, ed3, published by ISO. These are best used as 
extras with the reference software package. The other ones are independent pieces 
of code that attempt to implement JPEG XS algorithms and functions recovered in the 
course of back engineering the reference software.

In 2026, JXS sequence processing added to help the reader study 
new Temporal Differential Coding feature of ISO/IEC 21122 ed. 3,
see [JPEG XS 3rd Edition: The New Temporal Differential Coding 
(TDC) Profile](https://journal.smpte.org/periodicals/SMPTE%20Motion%20Imaging%20Journal/134/5/16/)

> Tim Bruylants, Ben Runyan, Jean-Baptiste Lorent

> The 3rd edition of JPEG XS introduces the Temporal Differential Coding 
(TDC) profile, further improving the compression efficiency over the XS 
High profile. TDC adds a wavelet-domain temporal prediction block using 
a single compressed frame buffer to reduce correlation between successive 
frames, especially in static regions, without requiring motion 
compensation or complex algorithms.

Utilities JXS_SequenceDecoder and JXS_SequenceEncoder are basically
jxs_decoder and jxs_encoder, respectively, of the ISO/IEC 21122 ed3 
part 5 reference codec package; I only added performance measurement 
lines and suppressed writing of output sequence files. You can restore 
the writing of files by undefining DO_NOT_WRITE_JXS_SEQUENCE_OUTPUT_FILES 
macro, but if you want use sample encoder/decoder you better use 
originals.

In the March 13, 2024 article [The TDC Profile](https://8kassociation.com/intopix-updates-us-on-jpeg-xs/)
by **8kassotiation** we read 
>The new TDC profiles use a concept called Temporal Differential Coding. 
That is to say, the codec takes account of changes over time as well as 
the spatial features of the image. Previously JPEG standards have focussed 
on spatial features as MPEG standards do. The codec exploits the concept of 
wavelet encoding but TDC introduces the idea of wavelet prediction. The codec 
does not use motion compensation to reduce the complexity of the processing. 
Lorent told us that the codec uses compression to create a frame buffer and 
keep it small to avoid external memory access which adds latency and takes 
a lot of power.<br/>
One of the features of the profile is that a basic frame can be sent with 
a (relatively) high level of compression, but if there is a static image, 
the subsequent frames can continue to add detail to get to a lossless image. 
Lorent gave the example of medical applications where you might need the low 
latency and high quality for applications such as endoscopy, but where static 
images are shown with a very high level of accuracy.

Intrigued by this intra/inter promise to encode the sequence without the 
resource-greedy MPEG4 motion compensation, I set out a few tests of 
encoding to/decoding from an JXS sequence extracted from SINTEL video frames 
(sintelppm.zip with this repo).

To conform to the jxs_encoder/jxs_decoder options format, an output sequence 
should be specified in my tests, even when the 
DO_NOT_WRITE_JXS_SEQUENCE_OUTPUT_FILES macro is defined.

Encoding to JXS sequence without TDC markers:

> \> JXS_SequenceEncoder.exe -c rate=4 -f 1 -n 90 sintelppm/sintel%04d.ppm sintel-no-tdc/sintel%04d.jxc

> [image_open] Using ppm lib to parse input file <br/>
[image_open] Image: 720x306 with bitdepth=8<br/>
72 70 72 70 70 70 71 71 70 72 70 69 70 72 70 70 71 71 71 71 71 70 70 70 70 70 70 70 70 69 70 70 71 
70 70 70 70 71 70 69 70 70 69 73 70 70 72 70 70 70 70 69 70 70 72 70 70 70 71 70 70 70 69 70 69 70 
69 71 69 69 69 67 69 67 68 67 68 69 67 67 67 68 67 68 68 68 67 68 69 69 (milliseconds)

Encoding to JXS sequence with TDC markers:

> \> JXS_SequenceEncoder.exe -c p=tdc -c rate=4 -f 1 -n 90 sintelppm/sintel%04d.ppm sintel/sintel%04d.jxc

> [image_open] Using ppm lib to parse input file <br/>
[image_open] Image: 720x306 with bitdepth=8<br/>
159 195 215 223 216 216 219 214 215 219 219 221 218 221 222 220 232 220 219 221 222 217 220 218 217 
220 177 180 174 169 174 173 174 169 171 172 180 172 167 177 175 164 175 181 178 183 180 180 173 178 
170 178 169 177 176 180 183 175 189 179 177 187 178 192 182 183 184 179 174 154 172 178 214 220 225 
231 233 238 239 250 245 246 249 247 245 246 244 246 240 242 (milliseconds)

sintel%04d.ppm file size is 646K, sintel%04d.jxc file size is 108K: equal file sizes throughout the 
corresponding sequences, both with and without TDC markers.

Decoding from JXS sequence without TDC markers:

> \> JXS_SequenceDecoder -f 1 -n 90 sintel-no-tdc/sintel%04d.jxc sintelppm/sintel%04d.ppm

> Image: 720x306 3-comp@8bpp <br/>
Sampling: 1x1/1x1/1x1 <br/>
17 16 16 16 16 17 16 16 16 17 16 16 16 16 16 16 16 17 16 16 16 16 18 16 16 16 17 16 16 16 16 16 16 
16 17 16 16 17 16 16 16 16 16 16 16 16 16 16 17 16 16 16 16 16 16 16 16 15 16 16 16 16 16 16 16 16 
15 15 16 16 17 17 16 16 16 16 16 16 16 16 17 16 16 16 16 16 16 16 16 17 (milliseconds)

Decoding from JXS sequence with TDC markers:

> \> JXS_SequenceDecoder -f 1 -n 90 sintel/sintel%04d.jxc sintelppm/sintel%04d.ppm

> Image: 720x306 3-comp@8bpp <br/>
Sampling: 1x1/1x1/1x1 <br/>
22 23 23 24 23 23 23 23 23 22 23 22 23 23 23 23 23 23 23 23 23 23 24 23 23 23 20 21 20 21 21 20 20 
21 21 20 21 21 21 20 21 21 20 21 20 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 21 
21 22 21 21 23 23 22 22 23 23 23 23 23 23 23 23 23 23 23 23 23 23 23 23 (milliseconds)

I failed to test encoding with the TDCMLS444.12 profile:

> \> JXS_SequenceEncoder.exe -c p=tdcmls444.12 -f 1 -n 90 sintelppm/sintel%04d.ppm sintel/sintel%04d.jxc

> [image_open] Using ppm lib to parse input file <br/>
[image_open] Image: 720x306 with bitdepth=8 <br/>
RATE Error: unable to reach precinct budget=8600 (min_possible=112624) <br/>
Unable to make the rate allocation on the precinct <br/>
Unable to encode image sintelppm/sintel0001.ppm

As MLS encoding is lossless, it is not obvious what parameters (and therefore command line options) 
might be used to satisfy budget appetite (if the configuration is responsible for this failure).

Still, the sequence can be successfully encoded with MLS.12 profile (no tdc, of course):

> \> JXS_SequenceEncoder.exe -c p=MLS.12 -f 1 -n 90 sintelppm/sintel%04d.ppm sintel-mls/sintel%04d.jxc

> [image_open] Using ppm lib to parse input file <br/>
[image_open] Image: 720x306 with bitdepth=8 <br>
92 90 90 90 91 91 90 93 91 90 90 90 90 90 91 90 90 90 90 90 89 90 90 91 91 90 85 83 84 84 84 85 83 
83 83 83 82 83 86 82 82 82 82 81 82 83 84 82 82 82 83 83 82 83 87 84 84 84 83 83 82 83 83 82 84 82 
84 82 82 75 74 75 75 75 76 74 75 74 76 74 75 74 77 76 75 75 75 75 74 75 (milliseconds)

Encoded with MLS.profile, sintel%04d.jxc file size varies through the sequence:

> 512K 511K 511K 511K 511K 511K 511K 511K 511K 511K 511K 511K 511K 511K 512K 512K 512K 511K 512K 512K 
512K 512K 511K 511K 511K 511K 443K 430K 423K 421K 419K 420K 420K 418K 418K 416K 415K 412K 411K 409K 
408K 405K 403K 403K 402K 401K 401K 401K 403K 404K 404K 405K 404K 406K 406K 406K 406K 405K 405K 405K 
406K 408K 408K 408K 407K 406K 405K 405K 403K 315K 313K 313K 313K 314K 314K 314K 315K 315K 316K 316K 
317K 317K 318K 318K 318K 318K 318K 318K 319K 319K

The jxs_decoder code of sample decoder with 21122 reference codec computes bitstream_buf_max_size 
looking into only the first jxc file of the sequence (line 144, programs/xs_dec_main.c). If there 
is a greater file in the sequence, the function fileio_read, in line 306, fails. In 
JXS_SequenceDecoder, I compute bitstream_buf_max_size over the entire sequence (lines 71-83).

Decoding from JXS sequence encoded with MLS.12 profile:

> \> JXS_SequenceDecoder -f 1 -n 90 sintel-mls/sintel%04d.jxc sintelppm/sintel%04d.ppm

> Image: 720x306 3-comp@8bpp <br/>
Sampling: 1x1/1x1/1x1 <br/>
41 36 37 37 43 38 40 40 40 39 38 37 39 36 37 37 36 36 37 36 36 37 39 37 37 38 35 35 35 32 32 40 35 
35 34 35 35 33 32 32 31 31 31 31 32 32 31 32 32 34 34 34 32 31 31 31 31 31 31 32 33 40 37 37 37 37 
34 34 33 27 27 26 27 27 28 28 29 29 27 27 27 26 27 28 27 27 28 28 29 28 (milliseconds)
