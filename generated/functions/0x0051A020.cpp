// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A020 rf_solid_face_adopt_link
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,existing face,RET4. Walks circular ordered corner list at face64 via next20,uniquely appends EACH corner vertex pointer to solid vertex array120,then appends existing face to solid face list112. Does not allocate/copy face or vertices,create incidence links,assign room/spatial ownership,finalize geometry/project UVs or test duplicate face membership. EAX follows list-append helper;no count/pointer/cycle checks. Used to transfer standalone generated polygon faces into new solid.
int __thiscall rf_solid_face_adopt_link(int *this, int a2)
{
  int *v3; // [esp+0h] [ebp-Ch]
  int *i; // [esp+8h] [ebp-4h]

  for ( i = *(int **)(a2 + 64); i; i = v3 )
  {
    rf_pointer_array_append_unique(this + 30, *i);
    if ( i[5] == *(_DWORD *)(a2 + 64) )
      v3 = nullptr;
    else
      v3 = (int *)i[5];
  }
  return rf_solid_face_list_append(this + 28, a2);
}

