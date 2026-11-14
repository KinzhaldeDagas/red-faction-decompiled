// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556030 rf_solid_copy_first_face_metadata_matching_uv_key
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): ECX solid plus output24-byte metadata pointer and Face56 key, RET8. Copies six DWORDs Face40..63 from FIRST matching face in solid list112. If no match, initializes output through face metadata initializer. Returns output; no pointer checks.
void *__thiscall rf_solid_copy_first_face_metadata_matching_uv_key(const void *this, void *a2, int a3)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)rf_receiver_get_first_dword((char *)this + 112); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
  {
    if ( i[14] == a3 )
    {
      *(_DWORD *)a2 = i[10];
      *((_DWORD *)a2 + 1) = i[11];
      *((_DWORD *)a2 + 2) = i[12];
      *((_DWORD *)a2 + 3) = i[13];
      *((_DWORD *)a2 + 4) = i[14];
      *((_DWORD *)a2 + 5) = i[15];
      return a2;
    }
  }
  rf_geomod_face_metadata_init(a2);
  return a2;
}

