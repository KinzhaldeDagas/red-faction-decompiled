// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005117B0 rf_emit_thirty_white_particles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclposition3f*,roomDWORD,caller pops8. Always30 particleallocationATTEMPTS,no capacity/position/roomvalidation. Eachiteration no-op constructsthenzeroes76-bytedescriptor;three RNGcalls(Z,Y,X order) jitterrange(-.05,+.05). Position=input+jitter,velocity=samejitter. Bitmap44=global911C74,DWORD48=1,RGBA52 whiteopaque,RGBA56 whitealpha0,flags60=0xC,field64=0;F32size24=random(.005,.015),field28=random(-.01,-.05),field36=random(-.03,-.1),lifetime40=random(1.5,3),otherclearedfieldsstay0. Reversed RNGboundsareNOTsorted. Particlecall(0,descriptor,providedroom,descriptorPosition,-1,NULL,0),ignore result. ReturnsEAX30 fromloopcounter,NOT countsuccess/pointerdespite former inferredvoid*
// returntype;prototypeotherwiseleftunchanged. Noinputmutation orownerentitylookup.
void *__cdecl rf_emit_thirty_white_particles(float *lhs, int a2)
{
  void *result; // eax
  float *v3; // eax
  float *v4; // eax
  float v5; // [esp+4h] [ebp-ACh]
  float v6; // [esp+8h] [ebp-A8h]
  float v7; // [esp+Ch] [ebp-A4h]
  float v8[3]; // [esp+10h] [ebp-A0h] BYREF
  float v9[3]; // [esp+1Ch] [ebp-94h] BYREF
  float sum_result[3]; // [esp+28h] [ebp-88h] BYREF
  _BYTE v11[4]; // [esp+34h] [ebp-7Ch] BYREF
  float copy_result[3]; // [esp+38h] [ebp-78h] BYREF
  float v13[3]; // [esp+44h] [ebp-6Ch] BYREF
  float v14[20]; // [esp+50h] [ebp-60h] BYREF
  float destination[3]; // [esp+A0h] [ebp-10h] BYREF
  int i; // [esp+ACh] [ebp-4h]

  result = rf_vector3_default_construct_noop(destination);
  for ( i = 0; i < 30; ++i )
  {
    rf_particle_descriptor76_construct_noop((int)v14);
    memset(v14, 0, 0x4Cu);
    v7 = rf_random_float_range(-0.050000001, 0.050000001);
    v6 = rf_random_float_range(-0.050000001, 0.050000001);
    v5 = rf_random_float_range(-0.050000001, 0.050000001);
    v3 = rf_vector3_set_components_return_destination(v13, v5, v6, v7);
    rf_vector_copy(destination, copy_result, v3);
    LODWORD(v14[11]) = dword_911C74;
    v14[13] = *(float *)rf_rgba8_construct_components_return_self(v11, 255, 255, 255, 255);
    rf_color4_set_bytes_return_destination(&v14[14], 255, 255, 255, 0);
    LODWORD(v14[15]) |= 0xCu;
    v14[16] = 0.0;
    v14[7] = rf_random_float_range(-0.0099999998, -0.050000001);
    v14[10] = rf_random_float_range(1.5, 3.0);
    LODWORD(v14[12]) = 1;
    v4 = rf_vector_add(lhs, sum_result, destination);
    rf_vector_copy(v14, v9, v4);
    v14[6] = rf_random_float_range(0.0049999999, 0.015);
    rf_vector_copy(&v14[3], v8, destination);
    v14[9] = rf_random_float_range(-0.029999999, -0.1);
    rf_particle_allocate_and_initialize(0, v14, a2, (int)v14, -1, nullptr, 0);
    result = (void *)(i + 1);
  }
  return result;
}

