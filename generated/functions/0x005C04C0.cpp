// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C04C0 rf_sound_load_entry
// Streams a registered sound entry's referenced file on first use.
// UNREALRED VERIFIED [sound-backend]: Lazy-loads a registered sound through the virtual filesystem and forwards filename, resolved source, size, resource options, and load mode to the lower backend. This RF wrapper is format-agnostic and contains no waveform codec loop.
int __cdecl rf_sound_load_entry(int a1, char a2, char a3)
{
  int v4; // eax
  char v5; // [esp+Bh] [ebp-345h]
  char *v6; // [esp+10h] [ebp-340h]
  char *filename_buffer_pointer; // [esp+14h] [ebp-33Ch]
  char v8[516]; // [esp+1Ch] [ebp-334h] BYREF
  int v9; // [esp+220h] [ebp-130h] BYREF
  int self[70]; // [esp+224h] [ebp-12Ch] BYREF
  char *String2; // [esp+340h] [ebp-10h]
  int v12; // [esp+34Ch] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return -1;
  if ( a1 == -1 )
    return -1;
  String2 = &rf_sound_resource_registry[64 * a1];
  if ( *((int *)String2 + 12) < 0 )
  {
    rf_renderer_reserved_noop_5709C0();
    rf_vfile_construct_unopened(self);
    v12 = 0;
    if ( rf_vfile_resolve_open_source((int)self, String2, (int)byte_98967F) != 1 )
    {
      sprintf(&unk_18CD828, "Sound file not found: %s\n", &rf_sound_resource_registry[64 * a1]);
      v12 = -1;
      rf_vfile_destruct_close_if_open(self);
      return -1;
    }
    if ( !rf_vfile_copy_vpp_archive_path_and_block_offset(self, v8, &v9, 128) )
    {
      filename_buffer_pointer = rf_vfile_get_filename_buffer_pointer((char *)self);
      v6 = v8;
      do
      {
        v5 = *filename_buffer_pointer;
        *v6++ = *filename_buffer_pointer++;
      }
      while ( v5 );
      v9 = 0;
    }
    if ( rf_sound_backend_mode == 1 )
    {
      v4 = rf_sound_register_sample_name_path(String2, v8, v9, *((_DWORD *)String2 + 13), a2);
      *((_DWORD *)String2 + 12) = v4;
    }
    String2[63] = a3;
    rf_renderer_reserved_noop_5709D0();
    v12 = -1;
    rf_vfile_destruct_close_if_open(self);
  }
  if ( *((int *)String2 + 12) < 0 )
    sprintf(&unk_18CD828, "Error loading sound: %s\n", &rf_sound_resource_registry[64 * a1]);
  return *((_DWORD *)String2 + 12);
}

