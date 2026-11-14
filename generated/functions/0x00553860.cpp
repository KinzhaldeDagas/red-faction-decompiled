// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553860 rf_solid_label_selected_vertex_components
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Resets vertex+28 to -1 for all solid vertices in array120, then scans selected vertices204. Every negative-labeled seed starts recursive connected-component labeling with *nextLabel, incrementing that caller counter. Caller must supply a suitable nonnegative starting counter; counters/recursion are unchecked. Return is scan bookkeeping.
int __thiscall rf_solid_label_selected_vertex_components(_DWORD *this, int *a2)
{
  int result; // eax
  int *v3; // eax
  int v4; // [esp-4h] [ebp-10h]
  int v6; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 30); ++i )
    *(_DWORD *)(*(_DWORD *)sub_552200(this + 30, i) + 28) = -1;
  result = rf_receiver_get_first_dword(this + 51);
  v6 = result;
  for ( j = 0; j < v6; ++j )
  {
    if ( *(int *)(*(_DWORD *)sub_552200(this + 51, j) + 28) < 0 )
    {
      v4 = *a2;
      v3 = (int *)sub_552200(this + 51, j);
      rf_solid_label_selected_vertex_component_recursive(this, *v3, v4);
      ++*a2;
    }
    result = j + 1;
  }
  return result;
}

