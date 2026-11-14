// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E02C0 rf_vani_decode_pixel_packets_rle
// UNREALRED VERIFIED [texture-conversion-20261028]: Arguments outputpixels,compressedinput,requestedpixelcount,bytesperpixel. Whileproducedcount<requested,readscontrolbyte. Highbitset=>repeatcount=(control&127)+1,copiesonepixelthrough0x5E03A0into4-bytestacktempthenmemcpyrepeatsit. Highbitclear=>literalcount=control+1,copiescountpixelsandadvancespointers. Returnscompressedbytesconsumed asintegerinEAXdespitepointertype. No inputlength,pixelsremainingoroutputsizecheck; finalpacketcanovershootrequestedcount. bytesperpixel>4overflowsrepeatstacktemp; literalpathalsoallowsuncheckedproductoverflow. No paletteinterpretationorbyteorderconversion.
unsigned __int8 *__cdecl rf_vani_decode_pixel_packets_rle(void *a1, unsigned __int8 *a2, int a3, size_t Size)
{
  _BYTE *v6; // [esp+0h] [ebp-18h] BYREF
  _BYTE Src[4]; // [esp+4h] [ebp-14h] BYREF
  int v8; // [esp+8h] [ebp-10h]
  unsigned __int8 *v9; // [esp+Ch] [ebp-Ch] BYREF
  int v10; // [esp+10h] [ebp-8h]
  void *v11; // [esp+14h] [ebp-4h] BYREF

  v11 = a1;
  v9 = a2;
  v10 = 0;
  while ( v10 < a3 )
  {
    v8 = *v9++;
    if ( (v8 & 0x80) != 0 )
    {
      v8 &= ~0x80u;
      v10 += v8 + 1;
      v6 = Src;
      rf_pixel_copy_run_advance_source_destination(1, (void **)&v6, (const void **)&v9, Size);
      do
      {
        memcpy(v11, Src, Size);
        v11 = (char *)v11 + Size;
      }
      while ( v8-- );
    }
    else
    {
      v10 += v8 + 1;
      rf_pixel_copy_run_advance_source_destination(v8 + 1, &v11, (const void **)&v9, Size);
    }
  }
  return (unsigned __int8 *)(v9 - a2);
}

