// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530FF0 rf_geomod_face_copy_to_output
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall sourceFace,outputSolid,UNUSED sourceSolidDWORD,finalizeLowBYTE RET12. Allocate/link face in outputSolid112 with source metadata, then redundantly copy metadata40..63 again. Walk original corner order. For each source vertex, if mappingDWORD28==0 allocate44-byte position copy into outputSolid120 and save pointer28; otherwise reuse mapping WITHOUT validating output ownership. Append corner with all four attribute floats only if mapped VERTEX POINTER not already anywhere in new face ring: repeated mapped vertices are globally collapsed even when UV attributes differ. Count only appended distinct pointers. Source textureDWORD48 negative ->copy-1, else preserve; output
// lightmapWORD54 always-1. If <3 appended or finalize(newFace,sourceNULL,lowBYTEflag) returnsfalse, unlink new face from output and destroy it, returnNULL. Allocated output vertices and source mapping pointers remain on failure; no rollback/selection-array cleanup/bounds finalize. Success returns face with no copied room/spatial owner; plane recomputed by finalize, not directly copied. Caller must clear mappings when changing output context.
unsigned int *__thiscall rf_geomod_face_copy_to_output(
        const unsigned int *this,
        int *solid,
        int a3,
        unsigned __int8 a4)
{
  int v5; // [esp+10h] [ebp-18h]
  int v7; // [esp+18h] [ebp-10h]
  int i; // [esp+1Ch] [ebp-Ch]
  unsigned int *link; // [esp+20h] [ebp-8h]
  int v10; // [esp+24h] [ebp-4h]

  link = rf_solid_face_allocate_link(solid, this + 10);
  link[10] = *(this + 10);
  link[11] = *(this + 11);
  link[12] = *(this + 12);
  link[13] = *(this + 13);
  link[14] = *(this + 14);
  link[15] = *(this + 15);
  v10 = 0;
  for ( i = *(this + 16); i; i = v5 )
  {
    if ( !*(_DWORD *)(*(_DWORD *)i + 28) )
      *(_DWORD *)(*(_DWORD *)i + 28) = rf_solid_vertex_copy_append(solid, *(float **)i);
    v7 = *(_DWORD *)(*(_DWORD *)i + 28);
    if ( !rf_geomod_face_contains_shared_vertex(link, v7) )
    {
      rf_geomod_face_corner_append(
        (float *)link,
        v7,
        *(float *)(i + 4),
        *(float *)(i + 8),
        *(float *)(i + 12),
        *(float *)(i + 16));
      ++v10;
    }
    if ( *(_DWORD *)(i + 20) == *(this + 16) )
      v5 = 0;
    else
      v5 = *(_DWORD *)(i + 20);
  }
  if ( *((int *)this + 12) <= -1 )
    link[12] = -1;
  else
    link[12] = *(this + 12);
  *((_WORD *)link + 27) = -1;
  if ( v10 < 3 || !rf_geomod_face_finalize_geometry((int)link, nullptr, a4) )
  {
    rf_solid_face_list_remove(solid + 28, (int)link);
    rf_geomod_face_destroy(link);
    return nullptr;
  }
  return link;
}

