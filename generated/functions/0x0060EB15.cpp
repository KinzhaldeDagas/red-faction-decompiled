// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060EB15 ___BuildCatchObjectHelper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const exceptionRecord*,destinationBase,const
// HandlerType*,const CatchableType*), action code0/1/2, not construction success Boolean. SEH4 original scope65EBC8: filter60EC80 always1, handler60EC84 restoresESP then terminate.
// BEFORE try arming, read HandlerType.pType+4 and first nameBYTE+8; NULL descriptor/empty name ->0. Require dispCatchObj+8 nonzero OR adjectives DWORD signbit80000000 set, else0.
// High adjective signbit selects destinationBase directly; otherwise destination=base+dispCatchObj+12 modulo32. Arm try0 only after these checks/address calculation; direct-call
// faults before arming escape this local filter. Predicate61D509 checks ONLY rawDWORD nonzero, never probes pointer validity; compatibility1 slots ignored. Handler adjectives mask8
// reference: require exception.object+18h and destination nonNULL, store RAW object pointer into destination, then AdjustPointer(object,&Catchable.PMD+8) and overwrite with adjusted
// pointer. Partial raw pointer retained if adjustment faults before termination. Nonreference Catchable properties BYTE mask1 simple: same nonNULL checks, memcpy_0(destination,raw
// object,RAW sizeDWORD+20); if size==4 AND copied DWORD nonNULL, adjust that COPIED pointer value via PMD and overwrite. Other sizes or copiedNULL need no adjustment. No size
// positivity/capacity guard; delegate memcpy has its own overlap behavior. Nonreference/nonsimple copyFunction+24 NULL: require object/destination nonNULL, AdjustPointer original
// object then memcpy raw sizeDWORD to destination, code0. NonNULL copyFunction: check object,destination,copyFunction nonzero, perform NO copy/constructor here; return1 if properties
// mask4 clear,2 if set. This code tells wrapper which member-call argument list to use. Any failed nonzero predicate ->inconsistency inside armed scope; exceptions in armed body
// caught and terminate. Normal disarm-2/SEH epilog, return0 for skip/completed reference/copy,1/2 deferred copy constructor. No allocation, object/type/range validation, pointer
// decode, destination rollback or NULL-adjusted-source check. TypeMatch is caller responsibility. Handler/Catchable layouts use existing local types; native control flow
// authoritative where generic predicate/member prototypes distort pseudocode.
int __cdecl __BuildCatchObjectHelper(
        const struct EHExceptionRecord *a1,
        void *a2,
        const HandlerType *a3,
        const CatchableType *a4)
{
  const struct TypeDescriptor *pType; // ecx
  int dispCatchObj; // ecx
  void **v6; // esi
  void *pExceptionObject; // eax
  void *v8; // eax
  void *v9; // eax
  void *v11; // [esp-8h] [ebp-34h]
  size_t sizeOrOffset; // [esp-4h] [ebp-30h]
  int v13; // [esp+10h] [ebp-1Ch]

  v13 = 0;
  pType = a3->pType;
  if ( pType )
  {
    if ( pType->name[0] )
    {
      dispCatchObj = a3->dispCatchObj;
      if ( dispCatchObj || a3->adjectives < 0 )
      {
        v6 = (void **)a2;
        if ( a3->adjectives >= 0 )
          v6 = (void **)((char *)a2 + dispCatchObj + 12);
        if ( (a3->adjectives & 8) != 0 )
        {
          if ( crt_dword_is_nonzero_bool((int)a1->params.pExceptionObject) && crt_dword_is_nonzero_bool((int)v6) )
          {
            pExceptionObject = a1->params.pExceptionObject;
            *v6 = pExceptionObject;
            v8 = __AdjustPointer(pExceptionObject, &a4->thisDisplacement);
LABEL_11:
            *v6 = v8;
            return v13;
          }
        }
        else
        {
          v11 = a1->params.pExceptionObject;
          if ( (a4->properties & 1) != 0 )
          {
            if ( crt_dword_is_nonzero_bool((int)v11) && crt_dword_is_nonzero_bool((int)v6) )
            {
              memcpy_0(v6, a1->params.pExceptionObject, a4->sizeOrOffset);
              if ( a4->sizeOrOffset != 4 || !*v6 )
                return v13;
              v8 = __AdjustPointer(*v6, &a4->thisDisplacement);
              goto LABEL_11;
            }
          }
          else if ( a4->copyFunction )
          {
            if ( crt_dword_is_nonzero_bool((int)v11)
              && crt_dword_is_nonzero_bool((int)v6)
              && crt_dword_is_nonzero_bool((int)a4->copyFunction) )
            {
              return ((a4->properties & 4) != 0) + 1;
            }
          }
          else if ( crt_dword_is_nonzero_bool((int)v11) && crt_dword_is_nonzero_bool((int)v6) )
          {
            sizeOrOffset = a4->sizeOrOffset;
            v9 = __AdjustPointer(a1->params.pExceptionObject, &a4->thisDisplacement);
            memcpy_0(v6, v9, sizeOrOffset);
            return v13;
          }
        }
        _inconsistency();
      }
    }
  }
  return 0;
}

