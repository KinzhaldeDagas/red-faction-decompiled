// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004524D0 rf_input_binding_assign_unique_mouse_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,targetRow,newFull32MouseCode), declared signed16 return. Loads targetRow pointer into
// EAX and compares sign-extended current WORD+24 to FULL32 requested code. Equality exits without writes, returning AX=LOW16 targetRow POINTER, not current code or success. Otherwise
// signed rowIndex0..<LIVE countcontext+3596 scans current mouse WORD atcontext+36+28*i; every sign-extended value equal to full requested code is replaced with0xFFFF. Then stores
// LOW16 requested code to targetRow+24 and returns that same low16 in AX, without normalizing upper EAX. No target membership, code range, count repair, authored-default update,
// duplicate cleanup after truncation or input reset. Negative count skips scan but still writes target; requested values outside int16 cannot match existing sign-extended codes yet
// truncate on assignment.
__int16 __cdecl rf_input_binding_assign_unique_mouse_slot(int a1, int a2, int a3)
{
  __int16 result; // ax
  int i; // [esp+0h] [ebp-4h]

  result = a2;
  if ( *(__int16 *)(a2 + 24) != a3 )
  {
    for ( i = 0; i < *(_DWORD *)(a1 + 3596); ++i )
    {
      if ( *(__int16 *)(a1 + 28 * i + 36) == a3 )
        *(_WORD *)(a1 + 28 * i + 36) = -1;
    }
    *(_WORD *)(a2 + 24) = a3;
    return a3;
  }
  return result;
}

