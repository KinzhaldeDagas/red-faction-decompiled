// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483DB0 rf_geomod_debris_spawn
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl(backingSolid,sourcePosition3f*), returns object-create result EAX. Builds100-byte mixed spawn descriptor using initializer419580, copies source position0,sets identity
// orientation12,zero linear48/angular60 velocities. Writes SIGNED lifetime-ms DWORD72=-1 (not floating NaN semantics),raw setup-scalar DWORD76=1 (not binary32
// 1.0),flagsDWORD84=0x40000018,creation parameter88=0. Initializer leaves expiry-effect80=-1,event pointer96=0,unused92=0.
// Only ORDERED backingSolid.radius96>double3.0 looks up exact case-insensitive custom sound-set 'big debris bounce'. If found, descriptor event pointer96=that set and OR flags with8;
// bit8 was ALREADY present in0x40000018, so this OR adds no new bit. Equality/NaN skips this lookup. No random velocity/spin or positive lifetime sampling. Calls
// debris_object_create(context-1,backingSolid,descriptor). That verified delegate consumes backing solid for type3 physical debris and destroys it on object creation failure; wrapper
// performs no independent post-call free. Flags0x10 registers additional light-receiver coverage, not a new geometry-query admission flag. Temporary lookup string destroyed on
// normal/unwind paths.
int __cdecl rf_geomod_debris_spawn(int backing_solid, float *source)
{
  char *v2; // eax
  float copy_result[3]; // [esp+4h] [ebp-8Ch] BYREF
  _DWORD v5[2]; // [esp+10h] [ebp-80h] BYREF
  int v6; // [esp+18h] [ebp-78h]
  float destination[3]; // [esp+1Ch] [ebp-74h] BYREF
  float v8[9]; // [esp+28h] [ebp-68h] BYREF
  float v9[3]; // [esp+4Ch] [ebp-44h] BYREF
  float v10[6]; // [esp+58h] [ebp-38h] BYREF
  int v11; // [esp+70h] [ebp-20h]
  int v12; // [esp+74h] [ebp-1Ch]
  int v13; // [esp+7Ch] [ebp-14h]
  int v14; // [esp+8Ch] [ebp-4h]

  rf_geomod_debris_spawn_config_init((int)destination);
  rf_vector_copy(destination, copy_result, source);
  rf_identity_orientation_matrix(v8);
  rf_vector3_zero_return_destination(v9);
  rf_vector3_zero_return_destination(v10);
  v10[3] = NAN;
  LODWORD(v10[4]) = 1;
  v11 = 1073741848;
  v12 = 0;
  if ( *(float *)(backing_solid + 96) > 3.0 )
  {
    rf_string_construct_empty(v5);
    v14 = 0;
    rf_string_assign_from_cstr(v5, "big debris bounce");
    v2 = (char *)rf_string_object_c_str_or_empty(v5);
    v6 = rf_material_custom_sound_set_find(v2);
    if ( v6 )
    {
      v13 = v6;
      v11 |= 8u;
    }
    v14 = -1;
    rf_string_destroy_buffer(v5);
  }
  return rf_geomod_debris_object_create(-1, backing_solid, destination);
}

