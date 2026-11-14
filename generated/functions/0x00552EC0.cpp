// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552EC0 rf_lightmap_atlas_destroy_all_registered_pages
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): If signed global page-array15A7148 count>0,iterates current count,deletes each nonNULL page through scalar adapter(flags1),then releases array storage. If count<=0,does nothing,including retaining any zero-count backing allocation. No scan of world lightmap descriptors or repair of their atlas pointers;does not reset bitmap/page fields before free. Return mixed initial count/final array-release EAX,not success status.
void **rf_lightmap_atlas_destroy_all_registered_pages()
{
  void **result; // eax
  void *v1; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = (void **)rf_receiver_get_first_dword(unk_15A7148);
  if ( (int)result > 0 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword(unk_15A7148); ++i )
    {
      v1 = *(void **)sub_552200(unk_15A7148, i);
      if ( v1 )
        rf_lightmap_atlas_page_scalar_deleting_destructor(v1, 1);
    }
    return rf_pointer_array_release_storage((void **)unk_15A7148);
  }
  return result;
}

