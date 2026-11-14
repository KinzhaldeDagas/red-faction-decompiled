// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527A40 rf_renderer_light_set_range
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,UNUSED middleDWORD,newRangeF32. Resolve unchecked, categoryBYTE77 nonzero triggers coverage(mode0) before mutation. Store range60=newRange, squaredRange128=F32(range*range), increment serial once, category coverage again afterward. Middle stack argument unread. No clamping/finite check, active-list invalidation or reordering. Does NOT recompute spot endpoint extent140, so cone extent can remain based on prior range until cone setter runs. Return record pointer when category0, last coverage result cast as pointer otherwise; not reliable API success.
int *__cdecl rf_renderer_light_set_range(int a1, int a2, float a3)
{
  int *result; // eax
  int *v4; // [esp+0h] [ebp-4h]

  v4 = rf_renderer_light_resolve_handle(a1);
  if ( *((_BYTE *)v4 + 77) )
    rf_light_refresh_receiver_coverage((int)v4, 0);
  *((float *)v4 + 15) = a3;
  *((float *)v4 + 32) = *((float *)v4 + 15) * *((float *)v4 + 15);
  ++rf_renderer_light_change_serial;
  result = v4;
  if ( *((_BYTE *)v4 + 77) )
    return (int *)rf_light_refresh_receiver_coverage((int)v4, 0);
  return result;
}

