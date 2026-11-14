// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527320 rf_renderer_light_resolve_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl signed handle. Return address0x00D03830 + low32(handle*268), rawIMUL10Ch/ADD, without dereference, bounds, active-type, generation, negative-index or overflow check. Handle is direct slot index, not unique lifetime ID; -1 maps268 bytes before pool. No serial/count change.
int *__cdecl rf_renderer_light_resolve_handle(int a1)
{
  return &rf_renderer_light_records[67 * a1];
}

