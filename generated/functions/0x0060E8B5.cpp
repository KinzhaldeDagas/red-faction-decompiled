// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E8B5 ?IsInExceptionSpec@@YAEPAUEHExceptionRecord@@PBU_s_ESTypeList@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI EDI=const two-DWORD exception-spec record
// {signedCount,HandlerTypeArray*}, one caller-popped stack const exceptionRecord*, AL Boolean0/1; upper EAX unspecified. NULL spec invokes noreturn inconsistency (native terminate
// fallback follows if it returns). Signed count<=0 ->AL0 WITHOUT touching exception pointer. For EACH spec entry index0..count-1, re-read exception.ThrowInfo+1Ch
// ->CatchableTypeArray+0Ch, signed count and pointer list at+4. For each positive catchable count, call TypeMatch(specArray+16*specIndex,currentCatchable,ThrowInfo), reclaim12; first
// successful match for this spec sets local resultBYTE1 and stops only INNER catchable loop. Continue ALL remaining spec entries even after match; result sticky1. Thus existential
// match but no outer early return; later entries can still fault or invoke delegates. Reload spec count each outer test, no snapshots of mutable tables. No own exception
// code/magic/parameter/NULL/array bounds guard, allocation, errno or qualifiers beyond TypeMatch. Preserve EDI; save EBX/ESI only nonempty path. Original call sites supply EDI
// separately, not ordinary two-stack-argument ABI.
unsigned __int8 __usercall IsInExceptionSpec@<al>(const _DWORD *a1@<edi>, const struct EHExceptionRecord *a2)
{
  CatchableTypeArray *pCatchableTypeArray; // eax
  int nCatchableTypes; // ebx
  const CatchableType **arrayOfCatchableTypes; // esi
  int v6; // [esp+4h] [ebp-8h]
  unsigned __int8 i; // [esp+Bh] [ebp-1h]

  if ( !a1 )
    _inconsistency();
  v6 = 0;
  for ( i = 0; v6 < *a1; ++v6 )
  {
    pCatchableTypeArray = a2->params.pThrowInfo->pCatchableTypeArray;
    nCatchableTypes = pCatchableTypeArray->nCatchableTypes;
    arrayOfCatchableTypes = (const CatchableType **)pCatchableTypeArray->arrayOfCatchableTypes;
    if ( pCatchableTypeArray->nCatchableTypes > 0 )
    {
      while ( !__TypeMatch((const HandlerType *)(16 * v6 + a1[1]), *arrayOfCatchableTypes, a2->params.pThrowInfo) )
      {
        --nCatchableTypes;
        ++arrayOfCatchableTypes;
        if ( nCatchableTypes <= 0 )
          goto LABEL_9;
      }
      i = 1;
    }
LABEL_9:
    ;
  }
  return i;
}

