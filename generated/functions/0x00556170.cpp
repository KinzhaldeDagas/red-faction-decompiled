// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556170 rf_solid_expand_bounds_from_selected_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Expands caller-provided min/max vectors from selected vertices204; does not initialize bounds. If BOTH transform pointers(orientation,translation) nonnull, copies vertex XYZ then rotates/translates it; if either missing, uses original XYZ with neither transform. Uses min-ELSE-max helper per axis, so a point establishing new minimum does not also update maximum. No output reset for empty selection.
void __thiscall rf_solid_expand_bounds_from_selected_vertices(
        const void *this,
        float *a2,
        float *a3,
        const float *a4,
        const float *a5)
{
  int first_dword; // eax
  float v7[3]; // [esp+4h] [ebp-14h] BYREF
  float *v8; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)this + 204);
    if ( i >= first_dword )
      break;
    v8 = *(float **)sub_552200((_DWORD *)this + 51, i);
    if ( a4 && a5 )
    {
      rf_vector3_copy_return_destination(v7, v8);
      rf_vector_rotate_translate_in_place(v7, (int)a4, (int)a5);
      rf_aabb_include_point_min_else_max(a2, a3, v7);
    }
    else
    {
      rf_aabb_include_point_min_else_max(a2, a3, v8);
    }
  }
}

