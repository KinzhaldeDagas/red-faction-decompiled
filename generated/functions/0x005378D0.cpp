// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005378D0 rf_lightmap_point_to_clamped_uv
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall lightmap mapping record,pointXYZ,outputU,outputV. Reads point components using unchecked indices stored at record+96/+100,scales by float+76/+80,adds offsets+84/+88,stores outputs then clamps each inclusive[0,1]. No axis-index validation,bilinear filtering,pixel coordinate conversion or half-texel adjustment. Returns void;normal/third component irrelevant except selected axes.
void __thiscall rf_lightmap_point_to_clamped_uv(int this, char *a2, float *a3, float *a4)
{
  float *v4; // eax
  float v5; // [esp+4h] [ebp-10h]
  float v7; // [esp+Ch] [ebp-8h] BYREF
  float v8; // [esp+10h] [ebp-4h]

  v5 = *(float *)rf_vector_component_address_unchecked(a2, *(_DWORD *)(this + 100));
  v4 = (float *)rf_vector_component_address_unchecked(a2, *(_DWORD *)(this + 96));
  rf_vector2_assign_components(&v7, *v4, v5);
  v7 = v7 * *(float *)(this + 76);
  v8 = v8 * *(float *)(this + 80);
  rf_vector2_accumulate(&v7, (float *)(this + 84));
  *a3 = v7;
  *a4 = v8;
  rf_float_clamp_in_place(a3, 0.0, 1.0);
  rf_float_clamp_in_place(a4, 0.0, 1.0);
}

