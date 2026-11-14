// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530E20 rf_geomod_face_corner_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall face,vertexPointer,attributeFloats0..3; RET20 returns new28-byte corner. Allocate without NULL check; set vertex0 and F32 attributes4,8,12,16. If face head64 nonNULL, append before head using head.prev24, keeping head; else self-link next20/prev24 and install head. Append face uniquely to vertex incidence array32. No solid vertex registration, corner-count field, face plane/bounds/UV finalization, duplicate-vertex guard or existing-corner reuse.
float *__thiscall rf_geomod_face_corner_append(float *this, int a2, float a3, float a4, float a5, float a6)
{
  float *v8; // [esp+4h] [ebp-4h]

  v8 = (float *)rf_geomod_corner_allocate();
  *(_DWORD *)v8 = a2;
  v8[1] = a3;
  v8[2] = a4;
  v8[3] = a5;
  v8[4] = a6;
  if ( *((_DWORD *)this + 16) )
  {
    v8[6] = *(float *)(*((_DWORD *)this + 16) + 24);
    v8[5] = *(this + 16);
    *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 16) + 24) + 20) = v8;
    *(_DWORD *)(*((_DWORD *)this + 16) + 24) = v8;
  }
  else
  {
    *((_DWORD *)v8 + 5) = v8;
    *((_DWORD *)v8 + 6) = v8;
    *((_DWORD *)this + 16) = v8;
  }
  rf_pointer_array_append_unique((_DWORD *)(a2 + 32), (int)this);
  return v8;
}

