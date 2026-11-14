// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552DF0 rf_solid_destroy_lightmap_descriptors
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Recovered thiscall solid. ONLY if descriptor-array+192 count>0,deletes each nonNULL124-byte descriptor through51E950(flags1),releases array backing,then walks solid face list+112 and stores WORD lightmap index54=FFFF. If count<=0,does not release allocated backing or reset any face indices. Does not free global atlas pages or invalidate room render packets. Existing int EAX normally0 at loop exit,not descriptor count/status. Bounds552DF0..552EB5 original already-code region.
int __thiscall rf_solid_destroy_lightmap_descriptors(void *this)
{
  int result; // eax
  void **v3; // [esp+Ch] [ebp-Ch]
  int j; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  result = rf_receiver_get_first_dword((char *)this + 192);
  if ( result > 0 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 192); ++i )
    {
      v3 = *(void ***)sub_552200((_DWORD *)this + 48, i);
      if ( v3 )
        rf_lightmap_descriptor_scalar_deleting_destructor(v3, 1);
    }
    rf_pointer_array_release_storage((void **)this + 48);
    result = rf_receiver_get_first_dword((char *)this + 112);
    for ( j = result; j; j = result )
    {
      *(_WORD *)(j + 54) = -1;
      result = rf_solid_face_next_link(j);
    }
  }
  return result;
}

