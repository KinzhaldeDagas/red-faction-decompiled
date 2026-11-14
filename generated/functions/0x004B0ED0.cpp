// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0ED0 rf_multiplayer_atexit_clear_team_names
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl noarg atexit callback. For indices0,1 assign verified empty NUL63B588 to RFString7B25F0+12*index. Assignment, not object destructor; preserves
// RGBA DWORD+8, other state, gameplay teams and registry fields. No runtime gate.
void __cdecl rf_multiplayer_atexit_clear_team_names()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
    rf_string_assign_from_cstr(&byte_7B25F0[12 * i], (char *)&byte_63B588);
}

