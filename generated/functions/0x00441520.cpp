// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441520 rf_player_build_controls_from_embedded_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(player pointer,output pointer), full delegate EAX/incidental null-path EAX. NULL output exits without
// any EAX initialization, player read or output write. Nonnull output takes input-state ADDRESS=player+228, sets canonical flagA iff DWORD[input+104]==EXACT1 and flagB iff
// DWORD[input+132]==EXACT1, then calls441580(player,input,output,flagA,flagB) with five cdecl slots and forwards EAX. These are exact DWORD comparisons, not generic nonzero action
// states. No player NULL, output size/mode, alias, pause, authority or entity-association checks in this body; delegated stores and input-consumption effects remain native.
int __cdecl rf_player_build_controls_from_embedded_input(int a1, int a2)
{
  int result; // eax

  if ( a2 )
    return rf_player_build_control_vectors_from_input(
             a1,
             (float *)(a1 + 228),
             a2,
             *(_DWORD *)(a1 + 332) == 1,
             *(_DWORD *)(a1 + 360) == 1);
  return result;
}

