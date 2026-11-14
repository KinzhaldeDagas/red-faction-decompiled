// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004273E0 rf_entities_copy_resolved_motion_vector
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): No-argument list procedure, incidental fullEAX return. Start node=global DWORD68211C; iterate until exact sentinel ADDRESS681E90, advancing via
// current node DWORD+652 AFTER processing each node. No NULL/cycle/list-count guard or snapshot. Only current movement descriptor pointer+2136 DWORD+4==EXACT1 OR3 admits; no
// descriptor NULL guard. Resolve raw full handle node+2220 through COMMON40CE70, not entity-only resolver. Missing source leaves prior node vector2208 and flags unchanged. Resolved
// source sequentially copies its three FLOATs+324 directly into node vector2208, with thiscall destination/source/result-temp ABI; no rotation, normalization, subtraction or
// velocity-source type restriction. Then40D5B0(node) ORs node DWORD+424 mask80000000 and common flags DWORD+124 mask06000000, without invoking a physics backend activation. No
// inactive/dead/authority or target-distance gate. Empty list returns initial sentinel inEAX; otherwise EAX depends on last descriptor/resolver/reactivation path, not count or
// uniform success.
int rf_entities_copy_resolved_motion_vector()
{
  int result; // eax
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v2; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  result = unk_68211C;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(*(_DWORD *)(i + 2136) + 4) != 1 )
    {
      result = *(_DWORD *)(i + 2136);
      if ( *(_DWORD *)(result + 4) != 3 )
        continue;
    }
    result = rf_object_resolve_handle(*(_DWORD *)(i + 2220));
    v2 = result;
    if ( result )
    {
      rf_vector_copy((float *)(i + 2208), copy_result, (const float *)(v2 + 324));
      result = rf_object_request_physics_reactivation_flags(i);
    }
  }
  return result;
}

