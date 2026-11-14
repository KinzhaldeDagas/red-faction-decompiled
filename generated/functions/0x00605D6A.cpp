// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605D6A ?_GetRangeOfTrysToCheck@@YAPBU_s_TryBlockMapEntry@@PBU_s_FuncInfo@@HHPAI1@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(FuncInfo*,signed catchDepth,signed
// state,unsigned*begin,unsigned*end), return map+20*begin; outputs half-open index range, not allocation. Load count DWORD FuncInfo+12,map pointer+16. index=count,end=count; save
// current index in local argument slot. While signed depth>=0: if index==FFFFFFFF call noreturn inconsistency; decrement index then dereference entry at map+20*index; boundary when
// signed tryHigh(+4)<state<=signed catchHigh(+8) OR index==FFFFFFFF. Boundary decrements depth, sets end=previous saved index, saves new index; otherwise continue backward scan.
// Native sentinel test occurs AFTER entry access, so transition0->FFFFFFFF can read map[-1] BEFORE recognizing sentinel. On exit increment index, publish begin/end BEFORE range
// validation; unsigned end>originalCount OR begin>end ->inconsistency. Negative initial depth still publishes count+1/count then fails range validation. No NULL/map-length/overflow
// guard, sorting or independent bounds enforcement. Pointer multiplication wraps32. Preserve EBX/ESI/EDI; no errno or success Boolean.
TryBlockMapEntry *__cdecl _GetRangeOfTrysToCheck(
        const struct _s_FuncInfo *a1,
        int a2,
        int a3,
        unsigned int *a4,
        unsigned int *a5)
{
  unsigned int nTryBlocks; // esi
  unsigned int v7; // ebx
  TryBlockMapEntry *v8; // eax
  unsigned int v9; // esi
  TryBlockMapEntry *pTryBlockMap; // [esp+Ch] [ebp-4h]
  const struct _s_FuncInfo *v12; // [esp+18h] [ebp+8h]

  nTryBlocks = a1->nTryBlocks;
  pTryBlockMap = a1->pTryBlockMap;
  v7 = nTryBlocks;
LABEL_8:
  v12 = (const struct _s_FuncInfo *)nTryBlocks;
  while ( a2 >= 0 )
  {
    if ( nTryBlocks == -1 )
      _inconsistency();
    v8 = &pTryBlockMap[--nTryBlocks];
    if ( v8->tryHigh < a3 && a3 <= v8->catchHigh || nTryBlocks == -1 )
    {
      --a2;
      v7 = (unsigned int)v12;
      goto LABEL_8;
    }
  }
  v9 = nTryBlocks + 1;
  *a4 = v9;
  *a5 = v7;
  if ( v7 > a1->nTryBlocks || v9 > v7 )
    _inconsistency();
  return &pTryBlockMap[v9];
}

