// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502880 rf_event_state_unpack_header
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Unpack existing event header: signed16 out+4 /32.0 into event delay+0x294; signed16 out+6!=0 normalizes direction byte+0x2B4; restore remaining deadline from out+8 to+0x298. Queue stable-id remapping for input+0xC=>event+0x2A8 and input+0x10=>event+0x2AC through0x4F5F60, WITHOUT writing those destination fields yet. Does not copy saved id/header+0 into event; outer routines match existing records. Disabled flags are not restored here.
int __cdecl rf_event_state_unpack_header(int a1, int a2)
{
  *(float *)(a1 + 660) = rf_snapshot_dequantize_s16_div32(*(_WORD *)(a2 + 4));
  *(_BYTE *)(a1 + 692) = *(__int16 *)(a2 + 6) != 0;
  rf_snapshot_unpack_replicator_remaining((int *)(a1 + 664), (int *)(a2 + 8));
  rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 12), a1 + 680);
  return rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 16), a1 + 684);
}

