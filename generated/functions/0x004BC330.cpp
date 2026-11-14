// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC330 rf_object_publish_position_and_bounds
// UNREALRED VERIFIED [trigger-airlock-20261022] Copies position to common/current/predicted storage and marks dirty; this setter alone does not immediately assign common room. UnrealRed airlock adapter currently queries authored room faces at current player/mover position rather than implementing this complete cached membership lifecycle.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Initial type9 setter copies SAME point to common+3C, physicscurrent+E4 and predicted+F0. Uses common+180 outer-radius operand: <=0 sets both bounds190/19C tocurrentpoint; otherwise currentpoint±radius with native float stores. Marksdirty4000000. This scalar is not automatically common+78 modelradius; actual4D7580/setup-copy chain must establish its producer.
// UNREALRED VERIFIED QUALIFICATION [combat-original-snapdown-20261112]: At4BC3DF..4BC3F0, x87 radius comparison followed by TEST AH,41h/JNZ selects point-only bounds for radius<=0 OR unordered (NaN); only ORDERED radius>0 computes point+-radius. Existing comments describing only <=0 omit the unordered case. Same input point writesCOMMON3C/current228/predicted240 and ORs COMMON flags124 with0x04000000, without changing any orientation matrix, cached ROOM, or shape/physics query word428.
int __thiscall rf_object_publish_position_and_bounds(int this, float *source)
{
  float *v2; // eax
  float *v3; // eax
  float v6[3]; // [esp+8h] [ebp-74h] BYREF
  float v7[3]; // [esp+14h] [ebp-68h] BYREF
  float v8[3]; // [esp+20h] [ebp-5Ch] BYREF
  int v9[3]; // [esp+2Ch] [ebp-50h] BYREF
  float v10[3]; // [esp+38h] [ebp-44h] BYREF
  int v11[3]; // [esp+44h] [ebp-38h] BYREF
  float v12[3]; // [esp+50h] [ebp-2Ch] BYREF
  float v13[3]; // [esp+5Ch] [ebp-20h] BYREF
  float copy_result[4]; // [esp+68h] [ebp-14h] BYREF
  _DWORD *v15; // [esp+78h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v15 = sub_4DD720(*(_DWORD *)(this + 44));
    if ( v15 )
    {
      if ( rf_string_equals_case_insensitive((int)(v15 + 2), "dave-2") && *source != 0.0 )
        LODWORD(copy_result[3]) = 10;
    }
  }
  rf_vector_copy((float *)(this + 60), copy_result, source);
  rf_vector_copy((float *)(this + 228), v13, source);
  rf_vector_copy((float *)(this + 240), v12, source);
  if ( *(float *)(this + 384) <= 0.0 )
  {
    rf_vector_copy((float *)(this + 400), v7, (const float *)(this + 228));
    rf_vector_copy((float *)(this + 412), v6, (const float *)(this + 228));
  }
  else
  {
    v2 = rf_vector3_subtract_scalar_from_components((float *)(this + 228), (float *)v11, *(float *)(this + 384));
    rf_vector_copy((float *)(this + 400), v10, v2);
    v3 = rf_vector3_add_scalar_to_components((float *)(this + 228), (float *)v9, *(float *)(this + 384));
    rf_vector_copy((float *)(this + 412), v8, v3);
  }
  *(_DWORD *)(this + 124) |= 0x4000000u;
  return this;
}

