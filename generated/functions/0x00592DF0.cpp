// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592DF0 rf_vfile_open_stdio_or_vpp
// UNREALRED VERIFIED [vfile-loose-precedence] Opens the resolved source. A VPP member opens its containing archive at the member's block offset; otherwise the resolved loose path is opened directly.
int __thiscall rf_vfile_open_stdio_or_vpp(int this, int a2)
{
  int v3; // eax
  char *Mode; // [esp+8h] [ebp-Ch]
  int *v6; // [esp+Ch] [ebp-8h]
  int *v7; // [esp+Ch] [ebp-8h]
  int first_unused_stream_slot; // [esp+10h] [ebp-4h]
  int v9; // [esp+10h] [ebp-4h]

  if ( (a2 & 2) != 0 )
  {
    first_unused_stream_slot = rf_vfile_find_first_unused_stream_slot();
    if ( first_unused_stream_slot >= 0 )
    {
      v6 = &unk_189CEB0[8208 * first_unused_stream_slot];
      if ( a2 >= 0 )
        Mode = (char *)&unk_6421A8;
      else
        Mode = (char *)&unk_6421A4;
      if ( *(int *)this > 0 )
        rf_vfile_create_registered_directory_chain(*(_DWORD *)this);
      v6[8203] = (int)fopen((const char *)(this + 5), Mode);
      if ( v6[8203] )
      {
        *(_DWORD *)(this + 272) = first_unused_stream_slot;
        *v6 = a2;
        v6[1] = 0;
        v6[3] = 0;
        v6[2] = 0;
        v6[4] = 0;
        v6[8204] = this;
        v6[6] = 0;
        v6[5] = 0;
        v6[7] = 0;
        *(_BYTE *)(this + 4) = 1;
        return 0;
      }
      else
      {
        return -99999;
      }
    }
    else
    {
      return -6;
    }
  }
  else
  {
    if ( !*(_BYTE *)(this + 4) )
      return -4;
    v9 = rf_vfile_find_first_unused_stream_slot();
    if ( v9 < 0 )
      return -6;
    v7 = &unk_189CEB0[8208 * v9];
    v7[8203] = 0;
    if ( *(_DWORD *)(this + 264) )
    {
      if ( !rf_vpackfile_entry_open(*(_DWORD *)(this + 264)) )
        return -99999;
      v7[7] = *(_DWORD *)(*(_DWORD *)(this + 264) + 12);
    }
    else
    {
      v7[8203] = (int)fopen((const char *)(this + 5), "rb");
      if ( !v7[8203] )
        return -99999;
      v3 = _fileno((FILE *)v7[8203]);
      v7[7] = _filelength(v3);
    }
    if ( v7[8203] )
      setvbuf((FILE *)v7[8203], nullptr, 4, 0);
    *(_DWORD *)(this + 272) = v9;
    *v7 = a2;
    v7[1] = 0;
    v7[3] = 0;
    v7[2] = 0;
    v7[4] = 0;
    v7[8204] = this;
    v7[6] = 0;
    v7[5] = 0;
    v7[10] = 0;
    v7[9] = 0;
    v7[8] = -1;
    return 0;
  }
}

