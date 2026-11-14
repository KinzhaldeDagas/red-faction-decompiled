// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3DC0 rf_cockpit_get_secondary_reserve_gauge
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Same four-DWORD cdecl gauge ABI as primary3D10; corrected framecount and output integers plus unused incidental pointer return to void. Uses class(entity+660) SECONDARY weapon ID+140; raw AmmoID+36 indexes entity reserve+684 without negative/upper bound checks. Output raw reserve then F32 round of x87 reserve/weapon signed608*(framecount-1), ceil->FTOL+1; low clamp to1 ELSE high clamp toframecount. Not selected-secondary query, loaded-ammo count, total or multiplayer-aware capacity. Sole native caller2F40 supplies4 DWORDs,pops16,discards EAX.
void __cdecl rf_cockpit_get_secondary_reserve_gauge(int entity, int frame_count, int *frame_offset, int *raw_reserve)
{
  float v4; // [esp+4h] [ebp-10h]
  char *v5; // [esp+10h] [ebp-4h]

  v5 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 140);
  *raw_reserve = *(_DWORD *)(entity + 4 * *((_DWORD *)v5 + 9) + 684);
  v4 = (double)*raw_reserve / (double)*((int *)v5 + 152) * (double)(frame_count - 1);
  *frame_offset = (int)rf_math_ceil_float(v4) + 1;
  if ( *frame_offset >= 1 )
  {
    if ( *frame_offset > frame_count )
      *frame_offset = frame_count;
  }
  else
  {
    *frame_offset = 1;
  }
}

