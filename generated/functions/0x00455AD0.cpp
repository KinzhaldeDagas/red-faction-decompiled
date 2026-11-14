// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455AD0 rf_save_list_a_enumerate_records
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): All186 native instructions/835 bytes paired with verified456160 after explicit array/literal mappings and call relocations. Build pattern *.svl;57C880(local
// circular sentinel, rootDWORD88E41C, pattern, flags6, NULL callback) retains extension and orders descending SIGNED32 timestamp. Walk next links until sentinel. Unbounded
// concatenate C string AT88E7D0 and node filename+8, call4F35B0(path,NULL level,&record.elapsed_seconds+268,NULL title); only nonzero AL admits. Sign-extend node timestampDWORD+52 to
// record signed64+260, copy filename including NUL at0 leaving padding stale, copy272 bytes BY VALUE to458030 with ECX array6F21AC (callee RET272). Does not clear destination,
// independently sort, prevent duplicates or check append results. Normal cleanup saves next, zeroes node+8, relinks neighbors, clears links, deletes6060E9; SEH cleanup and stack
// cookie present. XOR/JNZ backedge impossible. Final EAX local/scratch residue, not durable sentinel/list pointer. Pattern literals63533C/635340/635344 correspond to
// B635488/63548C/635490.
const char **rf_save_list_a_enumerate_records()
{
  _DWORD *v0; // edi
  const char **result; // eax
  struct RFFrontendRecord272 v2; // [esp-110h] [ebp-3C4h] BYREF
  char v3; // [esp+Bh] [ebp-2A9h]
  unsigned int *v4; // [esp+Ch] [ebp-2A8h]
  unsigned int *v5; // [esp+10h] [ebp-2A4h]
  char *v6; // [esp+14h] [ebp-2A0h]
  char *v8; // [esp+1Ch] [ebp-298h]
  unsigned int v9; // [esp+20h] [ebp-294h]
  const void *v10; // [esp+24h] [ebp-290h]
  char *v11; // [esp+2Ch] [ebp-288h]
  const char *v12; // [esp+30h] [ebp-284h]
  CHAR v13; // [esp+37h] [ebp-27Dh]
  char *v14; // [esp+38h] [ebp-27Ch]
  char *v15; // [esp+3Ch] [ebp-278h]
  CHAR *v16; // [esp+40h] [ebp-274h]
  char v17; // [esp+47h] [ebp-26Dh]
  _DWORD *v18; // [esp+48h] [ebp-26Ch]
  void *v19; // [esp+4Ch] [ebp-268h]
  const char *v20[14]; // [esp+50h] [ebp-264h] BYREF
  const char **i; // [esp+88h] [ebp-22Ch]
  unsigned int v22[69]; // [esp+8Ch] [ebp-228h] BYREF
  const char **v23; // [esp+1A0h] [ebp-114h] BYREF
  char FileName[268]; // [esp+1A4h] [ebp-110h] BYREF

  strcpy(FileName, "*");
  v18 = (const char ***)((char *)&v23 + 3);
  do
  {
    v17 = *((_BYTE *)v18 + 1);
    v18 = (_DWORD *)((char *)v18 + 1);
  }
  while ( v17 );
  v0 = v18;
  *v18 = 1819702062;
  *((_BYTE *)v0 + 4) = 0;
  rf_enumerate_files_sorted(v20, unk_88E41C, FileName, 6, nullptr);
  for ( i = (const char **)v20[0]; i != v20; i = (const char **)*i )
  {
    v16 = MEMORY[0x88E7D0];
    v15 = FileName;
    v14 = FileName;
    do
    {
      v13 = *v16;
      *v15 = v13;
      ++v16;
      ++v15;
    }
    while ( v13 );
    v12 = (const char *)(i + 2);
    v11 = (char *)(i + 2);
    v12 += strlen(v12);
    ++v12;
    v10 = i + 2;
    v9 = v12 - (const char *)(i + 2);
    v8 = (char *)&v23 + 3;
    while ( *++v8 )
      ;
    qmemcpy(v8, v10, v9);
    if ( rf_savegame_validate_headers_and_read_info(FileName, nullptr, (float *)&v22[67], nullptr) )
    {
      *(_QWORD *)&v22[65] = (int)i[13];
      v6 = (char *)(i + 2);
      v5 = v22;
      v4 = v22;
      do
      {
        v3 = *v6;
        *(_BYTE *)v5 = v3;
        ++v6;
        v5 = (unsigned int *)((char *)v5 + 1);
      }
      while ( v3 );
      qmemcpy(&v2, v22, sizeof(v2));
      rf_record272_array_append_by_value(dword_6F21AC, v2);
    }
  }
  for ( i = (const char **)v20[0]; ; i = v23 )
  {
    result = v20;
    if ( i == v20 )
      break;
    v23 = (const char **)*i;
    *((_BYTE *)i + 8) = 0;
    *(_DWORD *)i[1] = *i;
    *((_DWORD *)*i + 1) = i[1];
    *i = nullptr;
    i[1] = nullptr;
    v19 = i;
    operator delete(i);
  }
  return result;
}

