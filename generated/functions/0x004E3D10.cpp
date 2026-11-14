// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3D10 rf_cockpit_get_primary_reserve_gauge
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(entity,int framecount,int*frame,int*rawreserve), corrected pointer-like framecount/output types and unused incidental pointer return to void. Weapon ID is class(entity+660)+136, NOT selected weapon. Read weapon record1360*ID, AmmoID DWORD+36; directly index entity+684+4*AmmoID, store signed raw reserve output. No negative AmmoID or ownership check. x87 integer reserve /signed weapon DWORD+608 *signed wrapping(framecount-1); F32 round, ceil_float, FTOL,+1. Set frame<1 to1; ELSE cap frame>framecount toframecount, with no positive-count/zero-denominator/finite guard or multiplayer-max selection. Both native callers pass4 DWORDs,pop16 and discard EAX. No normalization or pending-reload subtraction.
void __cdecl rf_cockpit_get_primary_reserve_gauge(int entity, int frame_count, int *frame_offset, int *raw_reserve)
{
  float v4; // [esp+4h] [ebp-10h]
  char *v5; // [esp+10h] [ebp-4h]

  v5 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)(*(_DWORD *)(entity + 660) + 136);
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

