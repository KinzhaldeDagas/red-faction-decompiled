// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DFA40 rf_image_write_rgb24_jpeg
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; RF caller/dataflow verified): Cdecl(filename,tightlyPackedRGBbytes,width,height). fopen(filename,wb);failurequietlyreturnsNULLinEAXwithoutJPEGinitialization. BuildsSTACKarray1024rowpointers,eachpixels+i*3*width,withNOheight<=1024check;largerheightoverwriteslocalcompress/errorobjects. StandardJPEGerrmanager(defaultfatalexit),CreateCompress(version62,size372),stdio_dest;imageW/H,inputcomponents3,in_color_spaceRGB2. set_defaults=>quality75baseline/YCbCrdefaultsampling;thenEXPLICITdct_method192=2JDCT_FLOAT. start_compress(write_all_tablesTRUE),singlewrite_scanlines(allheight)ignorescount,finish,fclose,destroy. No rowflip,R/Bconversion,pitchparameter orsourcecopy. NativeEAXonsuccessisincidentalJPEGdestroyresult(stackcinfoaddress),NOTvalidFILE*:existingFILE*inferredreturntypeshouldnotbeusedasstream.
// AllthreeknownRFcallsin0x5710A0ignoreEAX;no guaranteedpublicstatuscontract.
FILE *__cdecl rf_image_write_rgb24_jpeg(char *FileName, int a2, int a3, int a4)
{
  FILE *result; // eax
  int i; // [esp+0h] [ebp-1210h]
  FILE *Stream; // [esp+4h] [ebp-120Ch]
  _DWORD v7[1024]; // [esp+8h] [ebp-1208h] BYREF
  _DWORD v8[94]; // [esp+1008h] [ebp-208h] BYREF
  _DWORD v9[35]; // [esp+1180h] [ebp-90h] BYREF

  result = fopen(FileName, "wb");
  Stream = result;
  if ( result )
  {
    for ( i = 0; i < a4; ++i )
      v7[i] = a2 + i * 3 * a3;
    v8[0] = rf_jpeg_std_error(v9);
    rf_jpeg_CreateCompress((char *)v8, 62, 372);
    rf_jpeg_stdio_dest((int)v8, (int)Stream);
    v8[7] = a3;
    v8[8] = a4;
    v8[9] = 3;
    v8[10] = 2;
    rf_jpeg_set_defaults((int)v8);
    v8[48] = 2;
    rf_jpeg_start_compress(v8, 1);
    rf_jpeg_write_scanlines(v8, (int)v7, a4);
    rf_jpeg_finish_compress(v8);
    fclose(Stream);
    return (FILE *)rf_jpeg_destroy_compress((int)v8);
  }
  return result;
}

