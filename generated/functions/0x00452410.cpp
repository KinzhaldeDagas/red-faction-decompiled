// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452410 rf_input_binding_assign_unique_keyboard_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,targetRow,newFull32Key,slotIndex). First compares targetRow signed WORD+20 then+22
// against FULL32 requested key. Any equality returns that sign-extended key in full EAX immediately, without removing duplicates elsewhere or honoring requested slot. Otherwise
// signed loops rowIndex0..<LIVE countcontext+3596 and keyboardSlot0..1; every sign-extended current WORD equal to full requested key becomes0xFFFF. Then writes LOW16 requested key to
// targetRow+20+2*slotIndex and returns FULL slotIndex in EAX. No target-membership, slot-range, key-range, negative-count or lower-address guard, no mutation of authored
// defaults/other mouse fields except possible unchecked slot alias, and no counter/input reset. Out-of-int16 requested keys cannot match sign-extended existing keys but are still
// truncated into destination, so this is not unconditional post-truncation uniqueness. Scans source rows before final target store; aliases remain observable.
int __cdecl rf_input_binding_assign_unique_keyboard_slot(int a1, int a2, int a3, int a4)
{
  int result; // eax
  int k; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    result = *(__int16 *)(a2 + 2 * i + 20);
    if ( result == a3 )
      return result;
  }
  for ( j = 0; j < *(_DWORD *)(a1 + 3596); ++j )
  {
    for ( k = 0; k < 2; ++k )
    {
      if ( *(__int16 *)(a1 + 28 * j + 12 + 2 * k + 20) == a3 )
        *(_WORD *)(a1 + 28 * j + 12 + 2 * k + 20) = -1;
    }
  }
  *(_WORD *)(a2 + 2 * a4 + 20) = a3;
  return a4;
}

