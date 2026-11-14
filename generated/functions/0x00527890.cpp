// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527890 rf_renderer_light_set_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,XYZpointer. Resolve unchecked; if categoryBYTE77 nonzero refresh coverage(mode0) BEFORE copy. Copy XYZ to original vector12..20, increment serial once, refresh category coverage again AFTER copy. No change to type, list order, alternate92 fields directly, active-list validity/count or spot/tube secondary direction/endpoint. Return serial when category0, last coverage helper EAX otherwise, not a success result. Coverage helper may do nothing when its global gates disabled.
int __cdecl rf_renderer_light_set_position(int a1, float *source)
{
  int result; // eax
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int *v4; // [esp+Ch] [ebp-4h]

  v4 = rf_renderer_light_resolve_handle(a1);
  if ( *((_BYTE *)v4 + 77) )
    rf_light_refresh_receiver_coverage((int)v4, 0);
  rf_vector_copy((float *)v4 + 3, copy_result, source);
  result = ++rf_renderer_light_change_serial;
  if ( *((_BYTE *)v4 + 77) )
    return rf_light_refresh_receiver_coverage((int)v4, 0);
  return result;
}

