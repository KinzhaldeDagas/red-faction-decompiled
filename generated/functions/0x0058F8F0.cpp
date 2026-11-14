// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F8F0 rf_sound_register_sample_name_path
// UNREALRED VERIFIED [dsound-creation-20261028]: Five arguments logical name,OS filepath,absolute wave offset,metadata DWORD,header-only byte. Looks up name0x590170; valid matching hash entry increments reference DWORD+588 andreturns existing index,ignoring new path/offset/mode. Otherwise uses index=global count0x1BA1818,unbounded copies name into record+0 andfilepath+256,stores offset+512,metadata+520,then0x58FA70. Failure clears only two leading string bytes,returns-1; partial resources can remain. Success stores hash+516,increments existing reference field+588 WITHOUT initializing it here,then increments count. No4096 capacity/name length checks or hole reuse search.
int __cdecl rf_sound_register_sample_name_path(char *String2, char *a2, int a3, int a4, char a5)
{
  char v6; // cl
  char v7; // cl
  _BYTE *v8; // [esp+8h] [ebp-20h]
  _BYTE *v10; // [esp+18h] [ebp-10h]
  char *v11; // [esp+1Ch] [ebp-Ch]
  char *v12; // [esp+20h] [ebp-8h]
  int sample_index_by_name; // [esp+24h] [ebp-4h]
  int v14; // [esp+24h] [ebp-4h]

  sample_index_by_name = rf_sound_find_sample_index_by_name(String2);
  if ( sample_index_by_name < 0 || unk_1951A0C[148 * sample_index_by_name] == -1 )
  {
    v14 = unk_1BA1818;
    v12 = (char *)&unk_1951808 + 592 * unk_1BA1818;
    v11 = String2;
    v10 = v12;
    do
    {
      v6 = *v11;
      *v10++ = *v11++;
    }
    while ( v6 );
    v8 = v12 + 256;
    do
    {
      v7 = *a2;
      *v8++ = *a2++;
    }
    while ( v7 );
    *((_DWORD *)v12 + 128) = a3;
    *((_DWORD *)v12 + 130) = a4;
    if ( rf_sound_sample_load_header_or_static_buffer(v14, a5) == -1 )
    {
      *v12 = 0;
      v12[256] = 0;
      return -1;
    }
    else
    {
      *((_DWORD *)v12 + 129) = rf_sound_name_hash_rotate6_case_sensitive(String2);
      ++unk_1951A54[148 * v14];
      ++unk_1BA1818;
      return v14;
    }
  }
  else
  {
    ++unk_1951A54[148 * sample_index_by_name];
    return sample_index_by_name;
  }
}

