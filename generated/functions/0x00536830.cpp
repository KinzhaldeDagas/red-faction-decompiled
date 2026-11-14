// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536830 rf_plane_normal_alignment_negative_dot
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Cdecl two pointers whose first3 floats are normals;returns NEGATIVE dot product. Does not read plane D,normalize,compute angle/acos or distance. Cluster admission tests result<-threshold,equivalent dot>threshold for ordinary finite values;not oppositely facing test.
double __cdecl rf_plane_normal_alignment_negative_dot(float *a1, float *a2)
{
  return -rf_vector_dot(a1, a2);
}

