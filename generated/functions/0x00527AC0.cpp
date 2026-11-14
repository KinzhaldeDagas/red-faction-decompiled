// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527AC0 rf_renderer_light_get_range_outer_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,UNUSED middleDWORD,outRangePointer. Resolve unchecked, write only record.range60 to third argument, return resolved record pointer EAX. Does not touch second argument or supply inner radius, category, bounds or serial.
int *__cdecl rf_renderer_light_get_range_outer_only(int a1, int a2, float *a3)
{
  int *result; // eax

  result = rf_renderer_light_resolve_handle(a1);
  *a3 = *((float *)result + 15);
  return result;
}

