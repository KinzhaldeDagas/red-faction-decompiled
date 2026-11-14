// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6360 rf_geomod_saved_position_decode_u16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl(bounds-context pointer,const WORD[3],output float[3]); corrected unused integer result to void: all14 native callers pass3DWORDs,pop12 and discard EAX. Compute F32 spans=(maxXYZ at+84 minus minXYZ at+72), F32 steps=span/DOUBLE65536. Zero-extend each inputWORD to integer0..65535, x87 FILD then multiply stored F32 step and add min; store each output F32 in X,Y,Z order. No bounds/finite/zero-span checks or normalization. Packed0 maps min; for finite positive extent, maximum65535 reaches one step below the ideal max before output rounding, not an exact65535 denominator. Native EAX ends as zero-extended Z word, not pointer/status. Sequential accesses do not provide an
// overlap-safe source snapshot.
void __cdecl rf_geomod_saved_position_decode_u16(
        const float *bounds_context,
        const unsigned __int16 *packed_position,
        float *world_position)
{
  float v3; // [esp+Ch] [ebp-18h]
  float v4; // [esp+10h] [ebp-14h]
  float v5; // [esp+14h] [ebp-10h]
  float v6; // [esp+18h] [ebp-Ch]
  float v7; // [esp+1Ch] [ebp-8h]
  float v8; // [esp+20h] [ebp-4h]

  v3 = bounds_context[21] - bounds_context[18];
  v5 = bounds_context[22] - bounds_context[19];
  v6 = bounds_context[23] - bounds_context[20];
  v4 = v3 / 65536.0;
  v7 = v5 / 65536.0;
  v8 = v6 / 65536.0;
  *world_position = (double)*packed_position * v4 + bounds_context[18];
  world_position[1] = (double)packed_position[1] * v7 + bounds_context[19];
  world_position[2] = (double)packed_position[2] * v8 + bounds_context[20];
}

