// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004855D0 rf_level_text_clear_slots
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs. Assigns empty C string0x638FEF to first RFString of32 separate slots at0x6FFB88,stride12, leaving their third DWORD untouched. Then assigns empty C string0x63903F to
// RFString of64 level-text slots at0x6FF888,stride12 and sets each sound handle+8=-1. Uses string assignment, not raw memset/destructor; does not unload old sound resources. Called
// only after a level text file opens successfully, or directly by level teardown. Return EAX is incidental string-assignment result.
_DWORD *rf_level_text_clear_slots()
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 32; ++i )
  {
    rf_string_assign_from_cstr(&unk_6FFB88[3 * i], (char *)&byte_638FEF);
    result = (_DWORD *)(i + 1);
  }
  for ( j = 0; j < 64; ++j )
  {
    result = rf_string_assign_from_cstr(&byte_6FF888[12 * j], (char *)&byte_63903F);
    unk_6FF890[3 * j] = -1;
  }
  return result;
}

