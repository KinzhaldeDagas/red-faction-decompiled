// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616991 _isintTOS
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal x87 integer classifier preserves originalST0. Compare rounded duplicate under CURRENT CW; JNZ on ZF only ->notanint setsEAX0. Equal path duplicate
// original,multiply verified0.5,duplicate/round andFCOMPP halves: unequal ->EAX1 then FALL THROUGH RET6169B6;equal ->evenint setsEAX2. Both half temporaries popped, originalST0
// retained. UnorderedNaN setsZF1 and reaches even2, likewise infinities; no PF guard. Existing separate shared-tail boundaries retained; no stack args or CW override.
void __usercall isintTOS(double a1@<st0>)
{
  _ST6 = a1;
  __asm { frndint }
  if ( _ST6 == a1 )
  {
    _ST5 = a1 * dbl_665CB2;
    __asm { frndint }
    if ( _ST5 == a1 * dbl_665CB2 )
      evenint();
    else
      isintTOSret();
  }
  else
  {
    notanint();
  }
}

