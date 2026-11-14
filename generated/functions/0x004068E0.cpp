// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004068E0 rf_ai_mode5_secondary_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode5 handler. Before dispatch, secondary+692==4 AND DWORD route count+744==0 AND
// action index DWORD+1192!=-1: retrieves RFString at700480+524*index without any other index bounds, then434070(owner handle,string cstr/empty,DWORD block+1196), ignoring result.
// Re-reads secondary after this delegate. Original four-entry jump table for4..7 verified:4 calls route-update(route+744,extra0) then4069D0(block),5 calls406B20,6 calls
// route-update(route,extra0),7 calls406F60. Unsigned range test rejects all other secondary values, including negatives. No same-call redispatch if a chosen handler changes state, no
// primary-mode write or independent return result.
void __cdecl rf_ai_mode5_secondary_dispatch(int *a1)
{
  char *v1; // eax
  int v2; // [esp-4h] [ebp-8h]

  if ( a1[173] == 4 && !a1[186] && a1[298] != -1 )
  {
    v2 = a1[299];
    v1 = (char *)rf_string_object_c_str_or_empty(&unk_700480[131 * a1[298]]);
    sub_434070(*(_DWORD *)(*a1 + 44), v1, v2);
  }
  switch ( a1[173] )
  {
    case 4:
      rf_ai_route_update((int)(a1 + 186));
      rf_ai_mode5_select_unmarked_clutter(a1);
      break;
    case 5:
      rf_ai_mode5_approach_and_associate_target(a1);
      break;
    case 6:
      rf_ai_route_update((int)(a1 + 186));
      break;
    case 7:
      rf_ai_mode5_release_target_after_action(a1);
      break;
    default:
      return;
  }
}

