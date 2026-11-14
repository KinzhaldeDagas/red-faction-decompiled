// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ED94 ?FindHandlerForForeignException@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@HH1@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(exception*,registration*,context*,dispatcherContext,const FuncInfo*,signed state,signed catchDepth,optional marker/targetFrameRegistration*), void. Code80000003 returns
// immediately. Other codes: if first getptd raw PTD+80h translator nonzero, fetch PTD AGAIN, compare its current slot against encoded_null() (provider-dependent, not fixed0); if
// unequal AND code!=E0434F4D call CallSETranslator(exception,registration,context,dispatcher,FuncInfo,catchDepth,marker). Nonzero translator result ->return;
// zero/missing/encoded-null/excluded-code falls back. Helper reloads raw callback from PTD itself; no local decode, cached callback identity or second-read NULL validation guarantee.
// Fallback require nTryBlocksDWORD+12 nonzero else inconsistency. GetRangeOfTrysToCheck(FuncInfo,catchDepth,state,&begin,&end), scan unsigned begin<end with20-byte entries. Require
// signed tryLow<=state<=tryHigh. Consider ONLY last handler at pHandlerArray+16*nCatches-16, WITHOUT nCatches>0 guard. Accept if its type descriptorNULL OR name firstBYTE+8NUL, AND
// adjectivesBYTE mask40 CLEAR. Typed last handler or mask40 set ->skip entire try; earlier handlers never considered. Eligible: EBX=lastHandler,EDI=currentTry,ESI=registration; call
// CatchIt with seven actual stack slots {exception,context,dispatcher,FuncInfo,NULLcatchable,catchDepth,marker},reclaim28. If it returns normally reload state from original argument
// and continue next try. No own exception signature/parameter validation, map/catch-count/NULL/range/cycle guard, destructor, finally, translation decode or allocation. Preserve
// nonvolatile regs; delegate owns nonlocal transfers. Breakpoint bypasses PTD and map checks.
void __cdecl FindHandlerForForeignException(
        struct EHExceptionRecord *a1,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        int a6,
        int a7,
        struct EHRegistrationNode *a8)
{
  PVOID *v8; // edi
  int v9; // esi
  TryBlockMapEntry *i; // edi
  int v11; // eax
  int v12; // ecx
  unsigned int v13; // [esp+4h] [ebp-8h] BYREF
  unsigned int v14; // [esp+8h] [ebp-4h] BYREF

  if ( a1->ExceptionCode != -2147483645 )
  {
    if ( !_getptd()[32]
      || (v8 = (PVOID *)(_getptd() + 32), *v8 == _encoded_null())
      || a1->ExceptionCode == -532459699
      || !_CallSETranslator(a1, a2, a3, a4, a5, a7, a8) )
    {
      if ( !a5->nTryBlocks )
        _inconsistency();
      v9 = a6;
      for ( i = _GetRangeOfTrysToCheck(a5, a7, a6, &v14, &v13); v14 < v13; ++i )
      {
        if ( v9 >= i->tryLow && v9 <= i->tryHigh )
        {
          v11 = (int)i->pHandlerArray + 16 * i->nCatches;
          v12 = *(_DWORD *)(v11 - 12);
          if ( (!v12 || !*(_BYTE *)(v12 + 8)) && (*(_BYTE *)(v11 - 16) & 0x40) == 0 )
          {
            CatchIt((const HandlerType *)(v11 - 16), i, a2, a1, a3, a4, a5, nullptr, a7, a8);
            v9 = a6;
          }
        }
        ++v14;
      }
    }
  }
}

