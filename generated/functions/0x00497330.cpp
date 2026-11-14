// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497330 rf_ctf_red_carrier_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(nullable player), mode1 only. Stores red carrier77D6D8 and clears definition DWORD[DWORD[redflag77D6E4+660]+68] bit2. Nonnull carrier clears instance +700 home bit200 and
// disarms red return timer77D710. Null carrier arms that timer for25000ms without setting home bit, moving the flag, clearing contribution bytes or changing blue carrier. No
// authority/flag/definition null guard; native RET is caller-cleaned one-pointer ABI.
_DWORD *__cdecl rf_ctf_red_carrier_set(int a1)
{
  _DWORD *result; // eax

  result = (_DWORD *)rf_multiplayer_game_mode_get();
  if ( result == (_DWORD *)1 )
  {
    unk_77D6D8 = a1;
    *(_DWORD *)(*(_DWORD *)(dword_77D6E4 + 660) + 68) &= ~2u;
    if ( a1 )
    {
      *(_DWORD *)(dword_77D6E4 + 700) &= ~0x200u;
      return rf_replicator_reset(&unk_77D710);
    }
    else
    {
      return (_DWORD *)rf_replicator_arm_milliseconds(&unk_77D710, 25000);
    }
  }
  return result;
}

