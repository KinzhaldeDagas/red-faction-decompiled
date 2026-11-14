// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617A0B __setenvp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, startup environ initialization0/-1.
// Initialize mb table if needed. Source NUL-separated block20213A0 NULL ->-1. Count entries excluding ones whose FIRST byte is equals; calloc_crt(count+1,4), publish narrowenv2021360
// immediately, failure-1. For each included entry calloc_crt(strlen+1,1), store pointer, strcpy_s; copy error Watson(5zeros). Full success free source block, clear20213A0, terminate
// pointer array, set2022F88=1,return0. Per-string allocation failure frees ONLY pointer array, sets narrowenvNULL,returns-1: earlier allocated strings leak and source block remains
// owned globally; initflag not changed. No own lock, overflow guard, whole-block bound validation or cleanup of prior global environ.
int _setenvp()
{
  char *v0; // esi
  int v1; // edi
  _DWORD *v3; // edi
  char *i; // esi
  size_t v5; // eax
  rsize_t v6; // ebx
  char *v7; // eax

  if ( !unk_2022F94 )
    __initmbctable();
  v0 = unk_20213A0;
  v1 = 0;
  if ( !unk_20213A0 )
    return -1;
  while ( *v0 )
  {
    if ( *v0 != 61 )
      ++v1;
    v0 += strlen(v0) + 1;
  }
  v3 = _calloc_crt(v1 + 1, 4u);
  unk_2021360 = v3;
  if ( !v3 )
    return -1;
  for ( i = unk_20213A0; ; i += v6 )
  {
    if ( !*i )
    {
      free(unk_20213A0);
      unk_20213A0 = nullptr;
      *v3 = 0;
      unk_2022F88 = 1;
      return 0;
    }
    v5 = strlen(i);
    v6 = v5 + 1;
    if ( *i != 61 )
      break;
LABEL_16:
    ;
  }
  v7 = (char *)_calloc_crt(v5 + 1, 1u);
  *v3 = v7;
  if ( v7 )
  {
    if ( strcpy_s(v7, v6, i) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    ++v3;
    goto LABEL_16;
  }
  free(unk_2021360);
  unk_2021360 = nullptr;
  return -1;
}

