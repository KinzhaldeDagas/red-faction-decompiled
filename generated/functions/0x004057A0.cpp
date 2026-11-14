// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004057A0 rf_ai_mode13_inherit_attached_entity_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, central mode13 callback. Cancels tracked body action BEFORE attachment resolution. Resolves owner full attachment
// handle+512 as ENTITY. Found ->40BA80(block,attached entity DWORD+1376), copying its retained AI target handle through guarded setter, not attachment handle itself. Missing
// ->40B2D0(block). No own mode write, route reset, sound or retry; return incidental helper result.
char __cdecl rf_ai_mode13_inherit_attached_entity_target(int *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  rf_ai_cancel_tracked_body_action(a1);
  v2 = rf_entity_resolve_handle(*(_DWORD *)(*a1 + 512));
  if ( v2 )
    return sub_40BA80(a1, *(_DWORD *)(v2 + 1376));
  else
    return sub_40B2D0(a1);
}

