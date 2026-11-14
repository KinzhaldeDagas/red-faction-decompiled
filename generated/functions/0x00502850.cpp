// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502850 rf_event_state_pack_deleted_identifiers
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Copy4*global count0x90B0DC bytes from saved-identifier list0x90B058 into supplied output, then export count through byte pointer. No identifier conversion, local bounds/count clamp or clearing of source list. This routine packs raw32-bit saved ids, not20-byte event headers.
char __cdecl rf_event_state_pack_deleted_identifiers(void *a1, _BYTE *a2)
{
  char result; // al

  memcpy(a1, unk_90B058, 4 * dword_90B0DC);
  result = dword_90B0DC;
  *a2 = dword_90B0DC;
  return result;
}

