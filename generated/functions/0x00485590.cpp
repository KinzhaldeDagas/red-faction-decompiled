// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485590 rf_level_text_sound_handles_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs. Loops64 slots at0x6FF888,stride12; writes only sound DWORD+8=-1 (base0x6FF890). Leaves first RFString8 bytes unchanged, performs no sound unload, text clearing or
// parser work. Normal final loop increment leaves EAX64; not a sound-load status.
int rf_level_text_sound_handles_initialize()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    unk_6FF890[3 * i] = -1;
    result = i + 1;
  }
  return result;
}

