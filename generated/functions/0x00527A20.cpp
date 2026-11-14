// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527A20 rf_renderer_light_get_enabled_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle, unchecked resolve then return raw BYTE76 throughAL. No boolean normalization, type/aliveness/range validation, serial change or list read.
char __cdecl rf_renderer_light_get_enabled_byte(int a1)
{
  return *((_BYTE *)rf_renderer_light_resolve_handle(a1) + 76);
}

