/*
   LZ4 - Fast LZ compression algorithm
   Header File
   Copyright (C) 2011, Yann Collet.
   BSD License

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
  
       * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following disclaimer
   in the documentation and/or other materials provided with the
   distribution.
  
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined (__cplusplus)
extern "C" {
#endif


//****************************
// Simple Functions
//****************************

int LZ4_compress   (char* source, char* dest, int isize);
int LZ4_uncompress (char* source, char* dest, int osize);

/*
LZ4_compress :
	return : the number of bytes in compressed buffer dest
	note : destination buffer must be already allocated. 
		To avoid any problem, size it to handle worst cases situations (input data not compressible)
		Worst case size is : "inputsize + 0.4%", with "0.4%" being at least 8 bytes.

LZ4_uncompress :
	return : the number of bytes read in the source buffer
			 If the source stream is malformed, the function will stop decoding and return a negative result, indicating the byte position of the faulty instruction
			 This version never writes beyond dest + osize, and is therefore protected against malicious data packets
	note 1 : osize is the output size, therefore the original size
	note 2 : destination buffer must be already allocated
*/


//****************************
// Advanced Functions
//****************************

int LZ4_uncompress_unknownOutputSize (char* source, char* dest, int isize, int maxOutputSize);

/*
LZ4_uncompress :
	return : the number of bytes decoded in the destination buffer (necessarily <= maxOutputSize)
			 If the source stream is malformed, the function will stop decoding and return a negative result, indicating the byte position of the faulty instruction
			 This version never writes beyond dest + maxOutputSize, and is therefore protected against malicious data packets
	note 1 : isize is the input size, therefore the compressed size
	note 2 : destination buffer must already be allocated, with at least maxOutputSize bytes
	note 3 : this version is slower by up to 10%, and is therefore not recommended for general use
*/


int LZ4_compressCtx(void** ctx, char* source,  char* dest, int isize);

/*
LZ4_compressCtx :
	This function explicitly handles the CTX memory structure.
	It avoids allocating/deallocating memory between each call, improving performance when malloc is time-consuming.

	On first call : provide a *ctx=NULL; It will be automatically allocated.
	On next calls : reuse the same ctx pointer.
	Use different pointers for different threads when doing multi-threading.

	note : performance difference is small, mostly noticeable when repetitively calling the compression algorithm on many small segments.
*/


//*********************************
// Faster Decoding function
//*********************************

#define LZ4_uncompress_fast LZ4_decode
int LZ4_decode (char* source, char* dest, int isize);

/*
LZ4_decode : This version is the fastest one, besting LZ4_uncompress by a few %.
	return : the number of bytes in decoded buffer dest
	note 1 : isize is the input size, therefore the compressed size
	note 2 : destination buffer must be already allocated. 
			The program calling the decoder must know in advance the size of decoded stream to properly allocate the destination buffer
			The destination buffer size must be at least "decompressedSize + 3 Bytes"
			This version is **unprotected** against malicious data packets designed to create buffer overflow errors.
			It is therefore deprecated, but still present in this version for compatibility.
*/


#if defined (__cplusplus)
}
#endif
