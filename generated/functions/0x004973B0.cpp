// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004973B0 rf_ctf_blue_carrier_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(nullable player), mode1 only. Stores blue carrier77D6DC and clears definition DWORD[DWORD[blueflag77D6E8+660]+68] bit2. Nonnull carrier clears instance +700 home bit200 and
// disarms blue return timer77D75C. Null carrier arms that timer for25000ms without setting home bit, moving the flag, clearing contribution bytes or changing red carrier. No
// authority/flag/definition null guard; caller-cleaned one-pointer ABI.
_DWORD *__cdecl rf_ctf_blue_carrier_set(int a1)
{
  _DWORD *result; // eax

  result = (_DWORD *)rf_multiplayer_game_mode_get();
  if ( result == (_DWORD *)1 )
  {
    unk_77D6DC = a1;
    *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) &= ~2u;
    if ( a1 )
    {
      *(_DWORD *)(dword_77D6E8 + 700) &= ~0x200u;
      return rf_replicator_reset(&unk_77D75C);
    }
    else
    {
      return (_DWORD *)rf_replicator_arm_milliseconds(&unk_77D75C, 25000);
    }
  }
  return result;
}

