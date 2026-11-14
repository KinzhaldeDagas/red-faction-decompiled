// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDD20 rf_wave_mmio_read_data_chunk_bytes
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments HMMIO,requested bytes,destination,MMCKINFO data chunk,actual output. Gets MMIOINFO; caps requested to chunk DWORD+4 remaining bytes,DECREMENTS remaining BEFORE copying. Copies byte-by-byte from pchNext,refilling with mmioAdvance when buffer exhausted,then commits mmioSetInfo. Success actual=bytes copied,return0,including short read at chunk boundary. Any get/advance/set error actual=0,return-1 even after partial destination writes. Remaining chunk count not restored on failure; no destination capacity check or rollback.
int __cdecl rf_wave_mmio_read_data_chunk_bytes(HMMIO hmmio, unsigned int a2, int a3, int a4, unsigned int *a5)
{
  struct _MMIOINFO pmmioinfo; // [esp+0h] [ebp-50h] BYREF
  int v7; // [esp+48h] [ebp-8h]
  unsigned int i; // [esp+4Ch] [ebp-4h]

  v7 = 0;
  if ( mmioGetInfo(hmmio, &pmmioinfo, 0) )
    goto LABEL_12;
  if ( a2 > *(_DWORD *)(a4 + 4) )
    a2 = *(_DWORD *)(a4 + 4);
  *(_DWORD *)(a4 + 4) -= a2;
  for ( i = 0; i < a2; ++i )
  {
    if ( pmmioinfo.pchNext == pmmioinfo.pchEndRead
      && (mmioAdvance(hmmio, &pmmioinfo, 0) || pmmioinfo.pchNext == pmmioinfo.pchEndRead) )
    {
      goto LABEL_12;
    }
    *(_BYTE *)(i + a3) = *pmmioinfo.pchNext++;
  }
  if ( mmioSetInfo(hmmio, &pmmioinfo, 0) )
  {
LABEL_12:
    v7 = -1;
    *a5 = 0;
  }
  else
  {
    *a5 = i;
  }
  return v7;
}

