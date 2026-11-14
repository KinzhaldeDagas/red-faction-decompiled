// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00534840 rf_geomod_face_clone_reversed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall sourceFace, one UNUSED stack DWORD; RET4, return new face inEAX. Allocate96-byte face using metadata40..63, then explicitly copy those sixDWORDs again. Append a new corner for EVERY source ring entry in forward order, reusing exact source vertex pointers and copying four F32 attributes4/8/12/16; no vertex cloning or pointer deduplication. Appender adds reciprocal incidence. Call finalize(newFace,sourceFace,0), IGNORE its return, then unconditionally reverse corner winding and plane and return newFace. Thus invalid finalization does not destroy or reject the clone. Room68/spatial72/decal76 remain allocator-cleared; no solid-list insertion, vertex registration, lightmap reset, or NULL allocation
// guard. Existing corner attributes stay associated with their vertex entries after reversal.
float *__thiscall rf_geomod_face_clone_reversed(float *this, int a2)
{
  int v3; // [esp+10h] [ebp-10h]
  int i; // [esp+18h] [ebp-8h]
  float *v6; // [esp+1Ch] [ebp-4h]

  v6 = (float *)rf_geomod_face_allocate((_DWORD *)this + 10);
  v6[10] = *(this + 10);
  v6[11] = *(this + 11);
  v6[12] = *(this + 12);
  v6[13] = *(this + 13);
  v6[14] = *(this + 14);
  v6[15] = *(this + 15);
  for ( i = *((_DWORD *)this + 16); i; i = v3 )
  {
    rf_geomod_face_corner_append(
      v6,
      *(_DWORD *)i,
      *(float *)(i + 4),
      *(float *)(i + 8),
      *(float *)(i + 12),
      *(float *)(i + 16));
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)this + 16) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 20);
  }
  rf_geomod_face_finalize_geometry((int)v6, this, 0);
  rf_geomod_face_reverse_winding((int)v6);
  return v6;
}

