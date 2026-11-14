// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005710A0 rf_image_write_tga_or_jpeg
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; RF caller/dataflow verified): Voidcdecl(sourceMutablePixels,RFformat,width,height,basePath,jpegFlag,optionalVfileContext). bytesPerPixel=formathelper;assumestightlypackedwidth*Bpprows,noexplicitpitch. UnboundedbasePathcopy/extensionappendtolocalstackname;append.jpg ifflag nonzero,else.tga(doesnotreplaceexistingextension). JPEG Bpp2allocatesnew3*w*hRGB:formatID3extractsRGB565,ID5RGB555(highbitignored),other2-byteformatsleaveuninitializedtemporary(loopsdoNOTadvanceoutput). Bpp3SWAPSsourceR/BINPLACEforeverypixel,encodes,NEVERrestorescallerbuffer. Bpp4mallocRGB3*w*h fromsource[2],[1],[0],ignores4thbyte. Calls5DFA40withoutverticalflip;temporarybuffersfreed,new/mallocfailuresunhandledinJPEGpaths.
// TGAallocates8*widthRLEpacketbuffer,opensvfilemode2withoptionalcontext,resultunchecked;writes18-byteheader:type10RLEtruecolor,noID/colormap,zeroorigins,width/heightlow16,24bpp,descriptor0(bottomorigin). Bpp4convertstoBGR24temporary;otherdepthsdelegatedexistingTGAencoder withdestbytes3/srcBpp. WritesrowsinREVERSEsourceorder(height-1..0),RLEencodes/writesperrow,closesandfreespacketbuffer. IfTGApacketallocationreturnsNULL,DELETESsourcePixels viaoperator delete (unexpectedownershipsideeffect). JPEGignoresoptionalvfilecontextandwritesviafopen. No dimension/overflow/sourcecapacityvalidation.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): Additional verified caller-ownership finding: TGA packet allocation failure at5711DA deletes source argument and returns. Caller570FF0 allocates private source,passes it here,then unconditionally deletes the same address after return (571091). Thus failed TGA packet allocation can reach two operator-delete calls for one source allocation. Original PE/disassembly verified at both functions;no executable fix applied.
void __cdecl rf_image_write_tga_or_jpeg(_BYTE *a1, int a2, int a3, int a4, char *a5, int a6, void *a7)
{
  char *v8; // [esp+10h] [ebp-3D0h]
  char *v10; // [esp+18h] [ebp-3C8h]
  char v11; // [esp+1Fh] [ebp-3C1h]
  char *v12; // [esp+24h] [ebp-3BCh]
  int ii; // [esp+40h] [ebp-3A0h]
  int n; // [esp+44h] [ebp-39Ch]
  _BYTE *v16; // [esp+48h] [ebp-398h]
  _BYTE *v17; // [esp+4Ch] [ebp-394h]
  _BYTE *v18; // [esp+50h] [ebp-390h]
  char v19; // [esp+57h] [ebp-389h]
  int m; // [esp+58h] [ebp-388h]
  int k; // [esp+5Ch] [ebp-384h]
  char *v22; // [esp+60h] [ebp-380h]
  unsigned __int16 v23; // [esp+64h] [ebp-37Ch]
  unsigned __int16 v24; // [esp+68h] [ebp-378h]
  int j; // [esp+6Ch] [ebp-374h]
  int i; // [esp+70h] [ebp-370h]
  _BYTE *v27; // [esp+74h] [ebp-36Ch]
  _BYTE *v28; // [esp+78h] [ebp-368h]
  _BYTE *v29; // [esp+7Ch] [ebp-364h]
  _BYTE *v30; // [esp+7Ch] [ebp-364h]
  _BYTE *v31; // [esp+7Ch] [ebp-364h]
  int v32; // [esp+80h] [ebp-360h]
  _BYTE *v33; // [esp+84h] [ebp-35Ch]
  _BYTE *ElementSize; // [esp+88h] [ebp-358h]
  int kk; // [esp+8Ch] [ebp-354h]
  int jj; // [esp+90h] [ebp-350h]
  _BYTE *v37; // [esp+94h] [ebp-34Ch]
  _BYTE *Block; // [esp+98h] [ebp-348h]
  _BYTE *v39; // [esp+9Ch] [ebp-344h]
  _BYTE *Buffer; // [esp+A0h] [ebp-340h]
  int stream[71]; // [esp+A4h] [ebp-33Ch] BYREF
  int v42; // [esp+1C0h] [ebp-220h] BYREF
  char Str[516]; // [esp+1C4h] [ebp-21Ch] BYREF
  int mm; // [esp+3CCh] [ebp-14h]
  int v45; // [esp+3D0h] [ebp-10h]
  int v46; // [esp+3DCh] [ebp-4h]

  v45 = rf_bitmap_format_bytes_per_pixel(a2);
  v42 = v45 * a3;
  v12 = Str;
  do
  {
    v11 = *a5;
    *v12++ = *a5++;
  }
  while ( v11 );
  if ( a6 )
  {
    v8 = (char *)&v42 + 3;
    while ( *++v8 )
      ;
    strcpy(v8, ".jpg");
    switch ( v45 )
    {
      case 2:
        v28 = operator new(3 * a4 * a3);
        v29 = v28;
        v27 = a1;
        v32 = v42 / 2;
        for ( i = 0; i < a4; ++i )
        {
          for ( j = 0; j < a3; ++j )
          {
            if ( a2 == 3 )
            {
              v24 = *(_WORD *)&v27[2 * j];
              *v29 = 8 * ((int)v24 >> 11);
              v30 = v29 + 1;
              *v30++ = 4 * ((int)v24 >> 5);
              *v30 = 8 * v24;
              v29 = v30 + 1;
            }
            else if ( a2 == 5 )
            {
              v23 = *(_WORD *)&v27[2 * j];
              *v29 = 8 * ((int)v23 >> 10);
              v31 = v29 + 1;
              *v31++ = 8 * ((int)v23 >> 5);
              *v31 = 8 * v23;
              v29 = v31 + 1;
            }
          }
          v27 += 2 * v32;
        }
        rf_image_write_rgb24_jpeg(Str, (int)v28, a3, a4);
        operator delete(v28);
        break;
      case 3:
        v22 = a1;
        for ( k = 0; k < a4; ++k )
        {
          for ( m = 0; m < a3; ++m )
          {
            v19 = *v22;
            *v22 = v22[2];
            v22[2] = v19;
            v22 += 3;
          }
        }
        rf_image_write_rgb24_jpeg(Str, (int)a1, a3, a4);
        break;
      case 4:
        v16 = a1;
        v17 = malloc(3 * a4 * a3);
        v18 = v17;
        for ( n = 0; n < a4; ++n )
        {
          for ( ii = 0; ii < a3; ++ii )
          {
            *v18 = v16[2];
            v18[1] = v16[1];
            v18[2] = *v16;
            v16 += 4;
            v18 += 3;
          }
        }
        rf_image_write_rgb24_jpeg(Str, (int)v17, a3, a4);
        free(v17);
        break;
    }
  }
  else
  {
    v10 = (char *)&v42 + 3;
    while ( *++v10 )
      ;
    strcpy(v10, ".tga");
    Buffer = operator new(8 * a3);
    if ( Buffer )
    {
      rf_vfile_construct_unopened(stream);
      v46 = 0;
      rf_vfile_open_with_extension_cache_control_paths(stream, Str, 2, a7);
      rf_binary_stream_write_byte_host_order(0);
      rf_binary_stream_write_byte_host_order(0);
      rf_binary_stream_write_byte_host_order(10);
      rf_binary_stream_write_word_host_order(stream, 0);
      rf_binary_stream_write_word_host_order(stream, 0);
      rf_binary_stream_write_byte_host_order(0);
      rf_binary_stream_write_word_host_order(stream, 0);
      rf_binary_stream_write_word_host_order(stream, 0);
      rf_binary_stream_write_word_host_order(stream, a3);
      rf_binary_stream_write_word_host_order(stream, a4);
      rf_binary_stream_write_byte_host_order(24);
      rf_binary_stream_write_byte_host_order(0);
      if ( v45 == 4 )
      {
        v37 = a1;
        Block = malloc(3 * a4 * a3);
        v39 = Block;
        for ( jj = 0; jj < a4; ++jj )
        {
          for ( kk = 0; kk < a3; ++kk )
          {
            *v39 = *v37;
            v39[1] = v37[1];
            v39[2] = v37[2];
            v37 += 4;
            v39 += 3;
          }
        }
        v45 = 3;
        v42 = 3 * a3;
        for ( mm = 0; mm < a4; ++mm )
        {
          ElementSize = rf_tga_encode_rle_packets(Buffer, (unsigned int)&Block[v42 * (a4 - mm - 1)], 3, v45, v42);
          rf_vfile_write_bytes_with_optional_feedback(stream, Buffer, (size_t)ElementSize);
        }
        free(Block);
      }
      else
      {
        for ( mm = 0; mm < a4; ++mm )
        {
          v33 = rf_tga_encode_rle_packets(Buffer, (unsigned int)&a1[v42 * (a4 - mm - 1)], 3, v45, v42);
          rf_vfile_write_bytes_with_optional_feedback(stream, Buffer, (size_t)v33);
        }
      }
      rf_vfile_close_stdio_or_vpp(stream);
      operator delete(Buffer);
      v46 = -1;
      rf_vfile_destruct_close_if_open(stream);
    }
    else
    {
      operator delete(a1);
    }
  }
}

