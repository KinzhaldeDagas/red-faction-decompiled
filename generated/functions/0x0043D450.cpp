// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D450 rf_entity_spawn_flagged_blood_marks
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl entity pointer. Tests flags DWORD+2064 mask0x08000000 and calls blood surface-mark helper(entity,literal eye,5.0,0.25). Then reloads flags and independently tests mask0x10000000 for helper(entity,literal spine,8.0,0.5). Both paths can run in eye-then-spine order; no local gore-enabled/class/model/node validity check or flag consumption. No own source-field writes, allocation or defined result; mark admission and effects belong to delegate.
void __cdecl rf_entity_spawn_flagged_blood_marks(int a1)
{
  if ( (*(_DWORD *)(a1 + 2064) & 0x8000000) != 0 )
    rf_blood_surface_mark_spawn_at_prop(a1, (char *)off_633218, 5.0, 0.25);
  if ( (*(_DWORD *)(a1 + 2064) & 0x10000000) != 0 )
    rf_blood_surface_mark_spawn_at_prop(a1, "spine", 8.0, 0.5);
}

