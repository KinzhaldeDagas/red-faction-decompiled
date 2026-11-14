// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A41D0 rf_render_evaluate_three_lights_rgb8
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl unused first argument,RGB BYTE destination,normal vector. For each of3 global directions at0x1C99898,0x1C998B0,0x1C998C8,uses max(dot(normal,direction),0). For each RGB channel sums3 corresponding light colors weighted by these dots plus globals0x1CF74E0/E4/E8,clamps ONLY UPPER bound255,rounds/converts via0x5A4190 add12582912 bit helper,stores3 bytes. No lower-bound clamp,normal normalization,alpha write,pointer validation or state mutation besides output. Returns last blue conversion result,not RGB pointer. Negative totals therefore follow conversion helper bit behavior.
int __cdecl rf_render_evaluate_three_lights_rgb8(int a1, _BYTE *a2, float *a3)
{
  int result; // eax
  float v4; // [esp+4h] [ebp-48h]
  double v5; // [esp+8h] [ebp-44h]
  float v6; // [esp+10h] [ebp-3Ch]
  double v7; // [esp+14h] [ebp-38h]
  float v8; // [esp+1Ch] [ebp-30h]
  double v9; // [esp+20h] [ebp-2Ch]
  float v10; // [esp+28h] [ebp-24h]
  float v11; // [esp+2Ch] [ebp-20h]
  float v12; // [esp+30h] [ebp-1Ch]

  if ( rf_vector_dot(a3, unk_1C99898) >= 0.0 )
    v12 = rf_vector_dot(a3, unk_1C99898);
  else
    v12 = 0.0;
  if ( rf_vector_dot(a3, unk_1C998B0) >= 0.0 )
    v11 = rf_vector_dot(a3, unk_1C998B0);
  else
    v11 = 0.0;
  if ( rf_vector_dot(a3, unk_1C998C8) >= 0.0 )
    v10 = rf_vector_dot(a3, unk_1C998C8);
  else
    v10 = 0.0;
  if ( unk_1C998A4 * v12 + unk_1C998BC * v11 + unk_1C998D4 * v10 + unk_1CF74E0 <= 255.0 )
    v9 = unk_1C998A4 * v12 + unk_1C998BC * v11 + unk_1C998D4 * v10 + unk_1CF74E0;
  else
    v9 = 255.0;
  v8 = v9;
  *a2 = rf_float_to_byte_add_12582912_bits(v8);
  if ( unk_1C998A8 * v12 + unk_1C998C0 * v11 + unk_1C998D8 * v10 + unk_1CF74E4 <= 255.0 )
    v7 = unk_1C998A8 * v12 + unk_1C998C0 * v11 + unk_1C998D8 * v10 + unk_1CF74E4;
  else
    v7 = 255.0;
  v6 = v7;
  a2[1] = rf_float_to_byte_add_12582912_bits(v6);
  if ( unk_1C998AC * v12 + unk_1C998C4 * v11 + unk_1C998DC * v10 + unk_1CF74E8 <= 255.0 )
    v5 = unk_1C998AC * v12 + unk_1C998C4 * v11 + unk_1C998DC * v10 + unk_1CF74E8;
  else
    v5 = 255.0;
  v4 = v5;
  result = rf_float_to_byte_add_12582912_bits(v4);
  a2[2] = result;
  return result;
}

