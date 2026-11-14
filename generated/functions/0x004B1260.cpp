// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1260 rf_multiplayer_set_team_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(teamIndex,sourceCString). Signed bounds require0<=index<2; invalid returns AL0 without touching source/storage. Valid assign C-string into
// RFString7B25F0+12*index, return AL1. No own NULL-string, name-length/runtime/player guard or packet send; colorDWORD+8 unchanged. Return1 after assignment is not allocator status.
char __cdecl rf_multiplayer_set_team_name(unsigned int a1, char *Source)
{
  if ( a1 >= 2 )
    return 0;
  rf_string_assign_from_cstr(&byte_7B25F0[12 * a1], Source);
  return 1;
}

