// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA510 rf_event_create_load_level_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event type22 through common creator. Copy supplied filename string object; if ANY dot is found, call substring helper with length(original)-4 and replace local copy, then append .rfl and assign event string+0x2B8. No suffix identity or minimum-length validation in this routine. Store raw byte argument+0x2C0 without bool normalization. Does not check level existence or request transition during creation.
int __cdecl rf_event_create_load_level_record(float *a1, char **a2, char a3)
{
  unsigned int v3; // eax
  void *v5; // [esp+4h] [ebp-38h]
  void *v6; // [esp+Ch] [ebp-30h]
  _BYTE v7[8]; // [esp+14h] [ebp-28h] BYREF
  _BYTE v8[8]; // [esp+1Ch] [ebp-20h] BYREF
  _DWORD v9[2]; // [esp+24h] [ebp-18h] BYREF
  int v10; // [esp+2Ch] [ebp-10h]
  int v11; // [esp+38h] [ebp-4h]

  v10 = rf_mission_event_create_at_position(a1, 0x16u);
  if ( v10 )
  {
    rf_string_copy_construct_from_object(v9, a2);
    v11 = 0;
    if ( rf_string_find_case_insensitive((int *)a2, ".", 0) >= 0 )
    {
      v3 = rf_string_length_from_cstr((const char **)a2);
      v6 = rf_string_left_count(a2, v8, v3 - 4);
      LOBYTE(v11) = 1;
      rf_string_assign_from_object(v9, (int)v6);
      LOBYTE(v11) = 0;
      rf_string_destroy_buffer(v8);
    }
    v5 = rf_string_concat_object_cstr(v7, v9, ".rfl");
    LOBYTE(v11) = 2;
    rf_string_assign_from_object((_DWORD *)(v10 + 696), (int)v5);
    LOBYTE(v11) = 0;
    rf_string_destroy_buffer(v7);
    *(_BYTE *)(v10 + 704) = a3;
    v11 = -1;
    rf_string_destroy_buffer(v9);
  }
  return v10;
}

