// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED990 rf_wave_mmio_open_read_source_and_pcm_formats
// UNREALRED VERIFIED [wave-codec-20261028]: Six arguments OS filename,absolute file offset,HMMIO output,source-format allocation pointer,PCM-output-format allocation pointer,parent RIFF chunk output. Initializes ONLY *PCM-format=null,then mmioOpen flags0x10000. Nonzero offset mmioSeek result ignored. Descends root,requires RIFF ID0x46464952 and WAVE type0x45564157. Finds fmt-space chunk0x20746D66,requires size>=16,reads16-byte base format. PCM tag1 sets extra size0; non-PCM reads extra-size WORD. Allocates BOTH formats malloc(18+extraSize),copies source base/cbSize,reads extra bytes. Supports source tags1/2 only: destination PCM tag1,same channels/rate,source bits forPCM or16bits for tag2,cbSize0,computed blockAlign/avgBytesPerSec. Ascends fmt chunk and returns0 with open HMMIO,parent metadata; does not find data chunk yet. Any failure frees/nulls both format pointers,closes/nulls
// HMMIO,returns-1. Since source-format pointer was NOT initialized on entry,caller must supply null or valid owned allocation or early failure can free stale/uninitialized pointer. Does not check extraSize fits fmt chunk,format fields/overflow,source/output aliasing or offset seek success.
int __cdecl rf_wave_mmio_open_read_source_and_pcm_formats(
        LPSTR pszFileName,
        LONG lOffset,
        HMMIO *a3,
        void **a4,
        void **a5,
        LPMMCKINFO pmmcki)
{
  _DWORD *v6; // ecx
  int v8; // [esp+0h] [ebp-38h]
  HMMIO hmmio; // [esp+4h] [ebp-34h]
  char pch[4]; // [esp+8h] [ebp-30h] BYREF
  int v11; // [esp+Ch] [ebp-2Ch]
  int v12; // [esp+10h] [ebp-28h]
  int v13; // [esp+14h] [ebp-24h]
  LONG v14; // [esp+18h] [ebp-20h]
  char v15[2]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v16; // [esp+20h] [ebp-18h]
  struct _MMCKINFO v17; // [esp+24h] [ebp-14h] BYREF

  v16 = 0;
  *a5 = nullptr;
  hmmio = mmioOpenA(pszFileName, nullptr, 0x10000u);
  if ( !hmmio )
    goto LABEL_24;
  if ( lOffset )
    mmioSeek(hmmio, lOffset, 0);
  if ( mmioDescend(hmmio, pmmcki, nullptr, 0) )
    goto LABEL_24;
  if ( pmmcki->ckid != 1179011410 )
    goto LABEL_24;
  if ( pmmcki->fccType != 1163280727 )
    goto LABEL_24;
  v17.ckid = 544501094;
  if ( mmioDescend(hmmio, &v17, pmmcki, 0x10u) )
    goto LABEL_24;
  if ( v17.cksize < 0x10 )
    goto LABEL_24;
  v14 = mmioRead(hmmio, pch, 16);
  if ( v14 != 16 )
    goto LABEL_24;
  if ( *(unsigned __int16 *)pch == 1 )
  {
    *(_WORD *)v15 = 0;
LABEL_14:
    *a5 = malloc(*(unsigned __int16 *)v15 + 18);
    if ( !*a5 )
      goto LABEL_24;
    *a4 = malloc(*(unsigned __int16 *)v15 + 18);
    if ( !*a4 )
      goto LABEL_24;
    v6 = *a4;
    *v6 = *(_DWORD *)pch;
    v6[1] = v11;
    v6[2] = v12;
    v6[3] = v13;
    *((_WORD *)*a4 + 8) = *(_WORD *)v15;
    if ( *(_WORD *)v15 )
    {
      v14 = mmioRead(hmmio, (HPSTR)*a4 + 18, *(unsigned __int16 *)v15);
      if ( v14 != *(unsigned __int16 *)v15 )
        goto LABEL_24;
    }
    v8 = *(unsigned __int16 *)*a4;
    if ( v8 == 1 )
    {
      *((_WORD *)*a5 + 7) = *((_WORD *)*a4 + 7);
    }
    else
    {
      if ( v8 != 2 )
        goto LABEL_24;
      *((_WORD *)*a5 + 7) = 16;
    }
    *(_WORD *)*a5 = 1;
    *((_WORD *)*a5 + 1) = *((_WORD *)*a4 + 1);
    *((_DWORD *)*a5 + 1) = *((_DWORD *)*a4 + 1);
    *((_WORD *)*a5 + 8) = 0;
    *((_WORD *)*a5 + 6) = *((unsigned __int16 *)*a5 + 7) * *((unsigned __int16 *)*a5 + 1) / 8;
    *((_DWORD *)*a5 + 2) = *((_DWORD *)*a5 + 1) * *((unsigned __int16 *)*a5 + 6);
    if ( !mmioAscend(hmmio, &v17, 0) )
      goto LABEL_30;
    goto LABEL_24;
  }
  v14 = mmioRead(hmmio, v15, 2);
  if ( v14 == 2 )
    goto LABEL_14;
LABEL_24:
  v16 = -1;
  if ( *a5 )
  {
    free(*a5);
    *a5 = nullptr;
  }
  if ( *a4 )
  {
    free(*a4);
    *a4 = nullptr;
  }
  if ( hmmio )
  {
    mmioClose(hmmio, 0);
    hmmio = nullptr;
  }
LABEL_30:
  *a3 = hmmio;
  return v16;
}

