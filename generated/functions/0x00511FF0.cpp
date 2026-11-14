// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511FF0 rf_projectile_try_ricochet_preserve_speed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclprojectile*,caller pops4,normalizedALbool. F32speed=length(projectilevelocity324),unit=velocity/speed,absDot=F32(abs(dot(unit,collisionNormal448))). Readinfo660.F32+640 (parsercos(radians$Ricochet Angle),defaultangle180). RejectAL0 ONLYifORDEREDthreshold<absDot;equalandUNORDEREDNaNadmitted(TESTAH5/JP). Otherwiseunit += normal*F32(2*absDot),normalizewithoutzeroguard. UsesABSdot evenifnormalpointswithmotion;not a generic signedreflectwithincoming check. Coneparameter=F32(1-absDot/double50),clamp[-1,1] throughNaN-preserving40D620;passunitBYVALUE as3stackfloats plusconeparameter to5597C0,outputreceiverunit. Scale sampledunit byORIGINALstoredspeed
// andwriteprojectilevelocity324;returnAL1. Doesnotmoveprojectile,spendremainingdistance,setflags,spawnricochetbitmap,checkbouncecount,normalunitlength orfiniteinput. Zero velocity/NaNcanproduceinvalidoutputwhileAL1.
char __cdecl rf_projectile_try_ricochet_preserve_speed(int a1)
{
  float *v2; // eax
  float *v3; // eax
  float v4[3]; // [esp-8h] [ebp-58h] BYREF
  float scalar; // [esp+4h] [ebp-4Ch]
  float v6; // [esp+8h] [ebp-48h]
  float v7; // [esp+Ch] [ebp-44h]
  float copy_result[3]; // [esp+10h] [ebp-40h] BYREF
  float scaled_result[4]; // [esp+1Ch] [ebp-34h] BYREF
  int v10[3]; // [esp+2Ch] [ebp-24h] BYREF
  float v11; // [esp+38h] [ebp-18h]
  float v12; // [esp+3Ch] [ebp-14h] BYREF
  float vector[3]; // [esp+40h] [ebp-10h] BYREF
  float v14; // [esp+4Ch] [ebp-4h]

  v11 = rf_vector3_length((float *)(a1 + 324));
  rf_vector_divide((float *)(a1 + 324), vector, v11);
  v7 = fabs(rf_vector_dot(vector, (float *)(a1 + 448)));
  v14 = v7;
  if ( *(float *)(*(_DWORD *)(a1 + 660) + 640) < (double)v7 )
    return 0;
  v6 = v14 * 2.0;
  v2 = rf_vector_scale((float *)v10, v6, (float *)(a1 + 448));
  rf_vector_accumulate(vector, v2);
  rf_vector_normalize_reciprocal_sqrt(vector);
  v12 = 1.0 - v14 / 50.0;
  rf_float_clamp_in_place(&v12, -1.0, 1.0);
  scalar = v12;
  rf_vector3_copy_return_destination(v4, vector);
  rf_random_unit_vector_in_cone(vector, v4[0], v4[1], v4[2], scalar);
  v3 = rf_vector_multiply_scalar(vector, scaled_result, v11);
  rf_vector_copy((float *)(a1 + 324), copy_result, v3);
  return 1;
}

