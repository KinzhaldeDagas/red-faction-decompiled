// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553C40 rf_solid_select_vertices_of_selected_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Releases selected-vertex array204 backing storage, then visits every corner of every selected face in array216 and appends its vertex uniquely. Establishes that solid204 is the selected-VERTEX collection, and solid120 holds all vertices. Empty face selection leaves empty released vertex array. Return is face-count bookkeeping.
int __thiscall rf_solid_select_vertices_of_selected_faces(void **this)
{
  int result; // eax
  int *v2; // [esp+0h] [ebp-14h]
  int *j; // [esp+8h] [ebp-Ch]
  int v5; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  rf_pointer_array_release_storage(this + 51);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 54);
    if ( i >= result )
      break;
    v5 = *(_DWORD *)sub_552200(this + 54, i);
    for ( j = *(int **)(v5 + 64); j; j = v2 )
    {
      rf_pointer_array_append_unique(this + 51, *j);
      if ( j[5] == *(_DWORD *)(v5 + 64) )
        v2 = nullptr;
      else
        v2 = (int *)j[5];
    }
  }
  return result;
}

