// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E850 rf_solid_clear_authored_room_visibility_byte352
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall solid no stack args, iterate pointer array144 (authored rooms), clear ONLY BYTE352 of each room. Does not clear BYTE353, depth356 or clip rectangle364..376, nor traverse array156. Returns final count EAX; signed count<=0 skips loop. Called before local-player view pass442950. No global visible-list reset or portal-cache invalidation.
// [UnrealRed physical spheres 2026-11-12; executable-store scan] Clears authored room byte352(+160h) to0. Together with520A70 setting it to1 this is the render portal-visibility state consumed by410170 ally admission; do not substitute UE component visibility or all loaded rooms.
int __thiscall rf_solid_clear_authored_room_visibility_byte352(int this)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 144));
    if ( i >= result )
      break;
    *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)(this + 144), i) + 352) = 0;
  }
  return result;
}

