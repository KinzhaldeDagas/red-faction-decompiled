// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004859E0 rf_level_text_get_string_and_sound
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl(signed index,out RFString*,out sound DWORD*), ALsuccess. Signed0..63 copies stored RFString and sound handle+8 to outputs and returns1, even when string empty or handle-1.
// Invalid/negative index assigns empty C string0x639057 to out text and returns0 WITHOUT writing out sound. No NULL output guard, sound playback or load-on-demand. Caller must not
// infer invalid sound was reset to-1.
char __cdecl rf_level_text_get_string_and_sound(unsigned int a1, _DWORD *a2, _DWORD *a3)
{
  if ( a1 < 0x40 )
  {
    rf_string_assign_from_object(a2, (int)&byte_6FF888[12 * a1]);
    *a3 = unk_6FF890[3 * a1];
    return 1;
  }
  else
  {
    rf_string_assign_from_cstr(a2, (char *)&byte_639057);
    return 0;
  }
}

