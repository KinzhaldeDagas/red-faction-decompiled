// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502230 rf_event_state_pack_header
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Pack20-byte memory snapshot header from enclosing event pointer E: out+0=dword[E+0x24] saved object identifier; out+4=LOW16(trunc(delay_float[E+0x294]*32)); out+6=zero-extended direction byte[E+0x2B4]; out+8=packed remaining deadline E+0x298; out+0xC/+0x10=stable identifiers converted from runtime context E+0x2A8/+0x2AC by0x4BC720. Event common-object subobject starts at E+4, so E+0x24 corresponds common+0x20, not runtime type. Does not pack disabled flags E+0x2B0, class/vtable or arbitrary event fields.
int __cdecl rf_event_state_pack_header(int a1, int a2)
{
  int result; // eax

  *(_DWORD *)a2 = *(_DWORD *)(a1 + 36);
  *(_WORD *)(a2 + 4) = rf_snapshot_quantize_float_times32(*(float *)(a1 + 660));
  *(_WORD *)(a2 + 6) = *(unsigned __int8 *)(a1 + 692);
  rf_snapshot_pack_replicator_remaining((int *)(a1 + 664), (int *)(a2 + 8));
  *(_DWORD *)(a2 + 12) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(a1 + 680));
  result = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(a1 + 684));
  *(_DWORD *)(a2 + 16) = result;
  return result;
}

