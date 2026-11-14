// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B12E0 rf_multiplayer_copy_team_name_to_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(destinationRFString,teamIndex). Signed0<=index<2 else AL0 and destination untouched. Valid
// assign_from_object(destination,RFString7B25F0+12*index), return AL1. Copies via RFString assignment, not borrowed C-string pointer; no own destination NULL guard, runtime
// admission, color copy or network action.
char __cdecl rf_multiplayer_copy_team_name_to_string(_DWORD *a1, unsigned int a2)
{
  if ( a2 >= 2 )
    return 0;
  rf_string_assign_from_object(a1, (int)&byte_7B25F0[12 * a2]);
  return 1;
}

