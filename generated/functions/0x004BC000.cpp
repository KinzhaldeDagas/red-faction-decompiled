// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC000 rf_object_bind_model_filename_by_kind
// UNREALRED VERIFIED [original-shadow-radius-20261027] Model binding obtains sphere center and radius through 0x564E70 -> 0x562420 -> 0x562440; Object+120 is radius plus length(center). 0x513B10 copies Object+120 into shadow packet +0. This is model-derived, not a collision capsule radius. Animated type 2 dispatch passes definition+0x19C0 to 0x566AC0 (verified instruction operands).
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Panic linked_eye arrival threshold reads common+78 produced here:564E70 sphere then40CFA0(center)+rawRadius,final binary32 store4BC133.40CFA0 rounds squaredsum tofloat;40CFF0->40D010 rounds sqrt tofloat at40D01C. No actor/component scale enters this source radius.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Item common model creation first unbounded-copies authoredfilename into32byte Str even for static type; lengths>=32 reach unsafe native stackwrite and are unsupported host execution domains, not parser row failures. Type1 forwards originalfilename to563EC0/561C50/5B7F80. Type2 strips LASTdot suffix thencharacterinstance. Type3 originalfilename→VFX. Unknownkind0 has no generic static fallback.
int __cdecl rf_object_bind_model_filename_by_kind(int a1, char *a2, int a3)
{
  char v4; // [esp+Bh] [ebp-41h]
  char *v5; // [esp+10h] [ebp-3Ch]
  char *v6; // [esp+14h] [ebp-38h]
  char *last_char_wrapper; // [esp+18h] [ebp-34h]
  float v8[3]; // [esp+1Ch] [ebp-30h] BYREF
  char Str[32]; // [esp+28h] [ebp-24h] BYREF

  v6 = a2;
  v5 = Str;
  do
  {
    v4 = *v6;
    *v5++ = *v6++;
  }
  while ( v4 );
  last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 46);
  if ( last_char_wrapper )
    *last_char_wrapper = 0;
  switch ( a3 )
  {
    case 1:
      *(_DWORD *)(a1 + 128) = rf_model_handle_load_v3m_mode1(a2, 1, (void *)0xFFFFFFFF);
      break;
    case 2:
      *(_DWORD *)(a1 + 128) = rf_model_handle_load_character_instance(Str, 0, 0);
      break;
    case 3:
      *(_DWORD *)(a1 + 128) = rf_vfx_load_instance(a2, (int)byte_98967F);
      break;
  }
  *(_DWORD *)(a1 + 132) = -1;
  if ( !*(_DWORD *)(a1 + 128) )
    return 0;
  rf_object_model_bound_hook_noop();
  rf_vector3_default_construct_noop(v8);
  rf_model_handle_bounds_sphere_adapter(*(_DWORD **)(a1 + 128), (int)v8, (float *)(a1 + 120));
  *(float *)(a1 + 120) = rf_vector3_length(v8) + *(float *)(a1 + 120);
  if ( a3 == 3 )
    rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 128), 0, 1.0);
  *(_DWORD *)(a1 + 620) = rf_model_handle_find_root_bone_adapter(*(_DWORD **)(a1 + 128));
  return *(_DWORD *)(a1 + 128);
}

