// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539A10 rf_face_translate_primary_uv_and_rebase
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Cdecl face,deltaU,deltaV. Traverses circular corner ring from face+64 via corner+20,adds deltas to corner+4/+8 only,stops when next==head. Then calls5357B0 face-average-domain rebase and forwards its incidental pointer EAX. Secondary UV pair untouched;no malformed-ring/cycle guard beyond head test,normalization or packet cache invalidation. Empty ring still invokes rebase,which divides by zero count.
float *__cdecl rf_face_translate_primary_uv_and_rebase(float *a1, float a2, float a3)
{
  int v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = *((_DWORD *)a1 + 16); i; i = v4 )
  {
    *(float *)(i + 4) = *(float *)(i + 4) + a2;
    *(float *)(i + 8) = *(float *)(i + 8) + a3;
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)a1 + 16) )
      v4 = 0;
    else
      v4 = *(_DWORD *)(i + 20);
  }
  return rf_geomod_face_primary_uv_rebase(a1);
}

