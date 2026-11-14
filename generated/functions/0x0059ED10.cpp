// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059ED10 rf_vpackfile_load_internal
// UNREALRED VERIFIED [vpp-streaming] Reads the VPP header and table in 0x800-byte blocks, admits the entry list, then assigns aligned payload offsets.
int __cdecl rf_vpackfile_load_internal(int a1)
{
  int v2; // [esp+0h] [ebp-81Ch]
  int Buffer[512]; // [esp+4h] [ebp-818h] BYREF
  int v4; // [esp+808h] [ebp-14h]
  int v5; // [esp+80Ch] [ebp-10h]
  FILE *Stream; // [esp+810h] [ebp-Ch]
  int v7; // [esp+814h] [ebp-8h]
  int v8; // [esp+818h] [ebp-4h] BYREF

  v4 = 0;
  v8 = 0;
  Stream = fopen((const char *)(a1 + 32), "rb");
  if ( !Stream )
    return 0;
  fread(Buffer, 0x800u, 1u, Stream);
  if ( rf_vpackfile_process_header(a1, Buffer) && rf_vpackfile_init_file_list(a1) )
  {
    v5 = *(_DWORD *)(a1 + 164);
    v4 = 1;
    while ( v5 )
    {
      if ( v5 <= 32 )
        v2 = v5;
      else
        v2 = 32;
      v7 = v2;
      v5 -= v2;
      fread(Buffer, 0x800u, 1u, Stream);
      if ( !rf_vpackfile_add_entries(a1, (int)Buffer, v7, &v8) )
        goto LABEL_12;
      ++v4;
    }
    rf_vpackfile_setup_file_offsets(a1, v4);
    fclose(Stream);
    return 1;
  }
  else
  {
LABEL_12:
    fclose(Stream);
    return 0;
  }
}

