// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600350 rf_jpeg_jcopy_sample_rows
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jutils.c:jcopy_sample_rows matched): Cdecl(inputRowPointers,intsourceRow,outputRowPointers,intdestRow,intnumRows,unsignednumCols). Startsrow-pointerarraysat4*rowindices;while numRows>0,memcpyexactnumColsbytesfromeachinputrow tocorrespondingoutputrow,advancesboth. Doesnotallocate,scale,checkboundsorsupportoverlappingrowmemory. VoidAPI;incidentalEAXlastmemcpyresultorinitialoutputrow-slotpointerifnoiteration.
void **__cdecl rf_jpeg_jcopy_sample_rows(int a1, int a2, int a3, int a4, int a5, size_t a6)
{
  void **result; // eax
  void *v7; // [esp+0h] [ebp-10h]
  void *Src; // [esp+4h] [ebp-Ch]
  void **v10; // [esp+18h] [ebp+8h]
  void **v11; // [esp+20h] [ebp+10h]

  v10 = (void **)(a1 + 4 * a2);
  result = (void **)(a3 + 4 * a4);
  v11 = result;
  while ( a5 > 0 )
  {
    Src = *v10++;
    v7 = *v11++;
    result = (void **)memcpy(v7, Src, a6);
    --a5;
  }
  return result;
}

