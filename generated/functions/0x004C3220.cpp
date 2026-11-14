// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3220 rf_firing_effect_ring_create_four_emitters
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl(parentArg,positionVec3,directionVec3), returns old ring slot index. Releases current slot814CF0 first via4C35A0. Sequentially resolves exactly
// youfired,youfiredtoo,youfired_multi,youfiredtoo_multi via emitter-name lookup, copies each132B definition to stack via440010, sets copied direction16 to input direction and copied
// position4 to input position (too variants position=inputPosition+inputDirection*F32.2). No direction normalization here. Each calls
// emitter_create(parentArg,&copiedDefinition,NULLroom,0,1); stores result into slot pointers0/4/8/12, including NULL; all four variants allocated in every mode.
// For EACH definition only when multiplayer BYTE==1 EXACT, overrides copied float40/44=F32.03 and clears WORD52 bit4. Other nonzero mode bytes do not receive these overrides,
// although enable/tick select multiplayer pair for ANY nonzero mode. Stores unnormalized input position/direction into shared slot16/28; increments index and wraps to0 when>=16.
// Missing emitter name-1 is used as table index without validation; no allocation rollback/partial success rejection or index bounds guard. Returns slot index even if all emitter
// creates fail. Source definitions not directly modified by this body; copied two-byte padding54..55 follows assignment helper behavior.
int __cdecl rf_firing_effect_ring_create_four_emitters(int a1, float *lhs, float *source)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-138h] BYREF
  float v9[3]; // [esp+10h] [ebp-12Ch] BYREF
  float v10[3]; // [esp+1Ch] [ebp-120h] BYREF
  float v11[3]; // [esp+28h] [ebp-114h] BYREF
  float v12[3]; // [esp+34h] [ebp-108h] BYREF
  float v13[3]; // [esp+40h] [ebp-FCh] BYREF
  float v14[3]; // [esp+4Ch] [ebp-F0h] BYREF
  float v15[3]; // [esp+58h] [ebp-E4h] BYREF
  float v16[3]; // [esp+64h] [ebp-D8h] BYREF
  float sum_result[3]; // [esp+70h] [ebp-CCh] BYREF
  float scaled_result[3]; // [esp+7Ch] [ebp-C0h] BYREF
  float v19[3]; // [esp+88h] [ebp-B4h] BYREF
  float v20[3]; // [esp+94h] [ebp-A8h] BYREF
  float copy_result[3]; // [esp+A0h] [ebp-9Ch] BYREF
  int v22; // [esp+ACh] [ebp-90h]
  int name; // [esp+B0h] [ebp-8Ch]
  float self; // [esp+B4h] [ebp-88h] BYREF
  float v25[3]; // [esp+B8h] [ebp-84h] BYREF
  float destination[6]; // [esp+C4h] [ebp-78h] BYREF
  float v27; // [esp+DCh] [ebp-60h]
  float v28; // [esp+E0h] [ebp-5Ch]
  __int16 v29; // [esp+E8h] [ebp-54h]

  rf_particle_emitter_definition_construct_noop(&self);
  rf_firing_effect_slot_release_paired_emitters(unk_814CF0);
  name = rf_particle_emitter_definition_find_name("youfired");
  rf_particle_emitter_definition_assign132(&self, dword_867800[name]);
  rf_vector_copy(destination, copy_result, source);
  rf_vector_copy(v25, v20, lhs);
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    v27 = 0.029999999;
    v28 = 0.029999999;
    v29 &= ~4u;
  }
  unk_814CF8[10 * unk_814CF0] = rf_particle_emitter_create(a1, &self, 0, 0, 1);
  name = rf_particle_emitter_definition_find_name("youfiredtoo");
  rf_particle_emitter_definition_assign132(&self, dword_867800[name]);
  rf_vector_copy(destination, v19, source);
  v3 = rf_vector_multiply_scalar(source, scaled_result, 0.2);
  v4 = rf_vector_add(lhs, sum_result, v3);
  rf_vector_copy(v25, v16, v4);
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    v27 = 0.029999999;
    v28 = 0.029999999;
    v29 &= ~4u;
  }
  unk_814CFC[10 * unk_814CF0] = rf_particle_emitter_create(a1, &self, 0, 0, 1);
  name = rf_particle_emitter_definition_find_name("youfired_multi");
  rf_particle_emitter_definition_assign132(&self, dword_867800[name]);
  rf_vector_copy(destination, v15, source);
  rf_vector_copy(v25, v14, lhs);
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    v27 = 0.029999999;
    v28 = 0.029999999;
    v29 &= ~4u;
  }
  unk_814D00[10 * unk_814CF0] = rf_particle_emitter_create(a1, &self, 0, 0, 1);
  name = rf_particle_emitter_definition_find_name("youfiredtoo_multi");
  rf_particle_emitter_definition_assign132(&self, dword_867800[name]);
  rf_vector_copy(destination, v13, source);
  v5 = rf_vector_multiply_scalar(source, v12, 0.2);
  v6 = rf_vector_add(lhs, v11, v5);
  rf_vector_copy(v25, v10, v6);
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    v27 = 0.029999999;
    v28 = 0.029999999;
    v29 &= ~4u;
  }
  unk_814D04[10 * unk_814CF0] = rf_particle_emitter_create(a1, &self, 0, 0, 1);
  rf_vector_copy((float *)&unk_814D08 + 10 * unk_814CF0, v9, lhs);
  rf_vector_copy(&unk_814D14[10 * unk_814CF0], v8, source);
  v22 = unk_814CF0++;
  if ( unk_814CF0 >= 16 )
    unk_814CF0 = 0;
  return v22;
}

