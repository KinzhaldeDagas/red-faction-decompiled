// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1920 rf_sound_resource_estimate_size
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Unsigned index>=2600 returns 0. If the sample is not loaded, constructs a virtual file and queries its stored filename size. If loaded, computes int(outputField2 * outputField1 * backendDuration)/8 after querying format fields. This is the literal estimate, without an additional channels factor. Format-query failure leaves stack outputs unset; no independent ready guard. No callers found in current IDA xrefs.
int __cdecl rf_sound_resource_estimate_size(unsigned int a1)
{
  int size; // [esp+8h] [ebp-144h]
  int v3; // [esp+Ch] [ebp-140h]
  float duration_backend; // [esp+10h] [ebp-13Ch]
  int self[70]; // [esp+18h] [ebp-134h] BYREF
  int v6; // [esp+134h] [ebp-18h] BYREF
  int v7; // [esp+138h] [ebp-14h] BYREF
  int v8; // [esp+13Ch] [ebp-10h] BYREF
  int v9; // [esp+148h] [ebp-4h]

  if ( a1 >= 0xA28 )
    return 0;
  rf_vfile_construct_unopened(self);
  v9 = 0;
  if ( unk_1D85DE8[16 * a1] < 0 )
  {
    size = rf_vfile_get_size((int)self, &rf_sound_resource_registry[64 * a1], (int)byte_98967F);
    v9 = -1;
    rf_vfile_destruct_close_if_open(self);
    return size;
  }
  else
  {
    duration_backend = rf_sound_query_duration_backend(a1);
    rf_sound_resource_query_output_format(a1, &v6, &v8, &v7);
    v3 = (int)((double)(v8 * v6) * duration_backend) / 8;
    v9 = -1;
    rf_vfile_destruct_close_if_open(self);
    return v3;
  }
}

