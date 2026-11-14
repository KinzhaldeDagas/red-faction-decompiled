// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6EE0 rf_positional_sound_create_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Requires initialized flag and resource_index>=0, finds a free one of 128 slots, gets the resource record and probes its filename. Does not independently check resource_index<2600 or record pointer non-NULL before probing. On success resets slot, sets allocated flag 1, resource +8, update interval +72, deadline +76 with offset zero, and loop bit 8 only when loop byte==1. Queries base frequency into +32 without checking success. Appends the node to the circular list tail and returns its index. Missing file logs an error and returns -1; full pool also returns -1. Allocation does not immediately start playback.
int __cdecl rf_positional_sound_create_point(int a1, int a2, char a3)
{
  int free_slot; // [esp+0h] [ebp-Ch]
  int *v5; // [esp+4h] [ebp-8h]
  char *String2; // [esp+8h] [ebp-4h]

  if ( !byte_1DAEE54 )
    return -1;
  if ( a1 < 0 )
    return -1;
  free_slot = rf_positional_sound_find_free_slot();
  if ( free_slot == -1 )
    return -1;
  String2 = rf_sound_resource_get_record_if_ready(a1);
  if ( rf_sound_file_probe(String2) )
  {
    rf_positional_sound_instance_reset(free_slot);
    v5 = &unk_1DAEE58[27 * free_slot];
    v5[20] = 1;
    v5[2] = a1;
    v5[18] = a2;
    rf_clock_deadline_set_wrapped_offset(v5 + 19, 0);
    if ( a3 == 1 )
      v5[20] |= 8u;
    rf_sound_resource_query_output_format(a1, v5 + 8, nullptr, nullptr);
    v5[1] = unk_1DB245C;
    *v5 = (int)&dword_1DB2458;
    *unk_1DB245C = v5;
    unk_1DB245C = &unk_1DAEE58[27 * free_slot];
    return free_slot;
  }
  else
  {
    sprintf(&unk_18CD828, "Failed to create sound emitter since sound file missing: %s\n", String2);
    return -1;
  }
}

