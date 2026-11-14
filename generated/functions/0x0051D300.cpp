// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D300 rf_solid_finalize_derived_face_attach_and_select
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall solid,newFace,sourceFace,selectDerived. If both nonNULL,calls5308E0 finalize(new,source,0). Success copies source spatial-node pointer72,optionally append-unique new face to selected array solid+216,appends face to node+24 list if source72 nonNULL,and attaches to source room68 if present. Failure removes/destroys new face. Does not remove source face;callers decide afterward. No rollback if later attach/select side effect fails;source plane/geometry behavior inherited from verified nonNULL-source finalizer.
void __thiscall rf_solid_finalize_derived_face_attach_and_select(int *this, _DWORD *a2, int a3, char a4)
{
  if ( a2 && a3 )
  {
    if ( rf_geomod_face_finalize_geometry((int)a2, a3, 0) )
    {
      a2[18] = *(_DWORD *)(a3 + 72);
      if ( a4 )
        rf_pointer_array_append_unique(this + 54, (int)a2);
      if ( *(_DWORD *)(a3 + 72) )
        rf_geomod_spatial_node_face_list_append((int *)(*(_DWORD *)(a3 + 72) + 24), (int)a2);
      if ( *(_DWORD *)(a3 + 68) )
        rf_geomod_room_face_attach(*(float **)(a3 + 68), (int)a2);
    }
    else
    {
      rf_solid_face_remove_destroy(this, a2, 0);
    }
  }
}

